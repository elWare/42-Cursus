#!/usr/bin/env bash
# =============================================================================
# leak_test.sh — Memory leak tester for ft_irc using Valgrind + test_00_interactive.py
#
# Usage:
#   ./leak_test.sh <binary> <port> <password> [num_clients]
#
# Example:
#   ./leak_test.sh ./ircserv 6667 secret 5
#
# Requirements:
#   - valgrind installed
#   - python3 installed
#   - test_00_interactive.py and ./conf/ in the same directory as this script
# =============================================================================

# ── colours ──────────────────────────────────────────────────────────────────
RED='\033[0;31m'
GRN='\033[0;32m'
YEL='\033[1;33m'
CYN='\033[0;36m'
BLD='\033[1m'
RST='\033[0m'

# ── helpers ───────────────────────────────────────────────────────────────────
log()  { echo -e "${CYN}[leak_test]${RST} $*"; }
ok()   { echo -e "${GRN}[  OK  ]${RST} $*"; }
warn() { echo -e "${YEL}[ WARN ]${RST} $*"; }
fail() { echo -e "${RED}[ FAIL ]${RST} $*"; }
sep()  { echo -e "${BLD}────────────────────────────────────────────────────${RST}"; }

# ── argument parsing ──────────────────────────────────────────────────────────
BINARY="${1:-./ircserv}"
PORT="${2:-6668}"
PASSWORD="${3:-secret}"
NUM_CLIENTS="${4:-5}"

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
TESTER="$SCRIPT_DIR/test_00_interactive.py"
LOG_DIR="$SCRIPT_DIR/valgrind_logs"
TIMESTAMP="$(date +%Y%m%d_%H%M%S)"
VALGRIND_LOG="$LOG_DIR/valgrind_${TIMESTAMP}.log"
SUMMARY_LOG="$LOG_DIR/summary_${TIMESTAMP}.log"

mkdir -p "$LOG_DIR"

# ── preflight checks ──────────────────────────────────────────────────────────
sep
log "Preflight checks …"

if ! command -v valgrind &>/dev/null; then
    fail "valgrind not found. Install it with: sudo apt install valgrind"
    exit 1
fi
ok "valgrind: $(valgrind --version)"

if ! command -v python3 &>/dev/null; then
    fail "python3 not found."
    exit 1
fi
ok "python3: $(python3 --version)"

if [[ ! -x "$BINARY" ]]; then
    fail "Binary not found or not executable: $BINARY"
    exit 1
fi
ok "Binary: $BINARY"

if [[ ! -f "$TESTER" ]]; then
    fail "test_00_interactive.py not found at: $TESTER"
    exit 1
fi
ok "Tester: $TESTER"

# check port is free
if ss -ltn 2>/dev/null | grep -q ":${PORT} " || \
   netstat -ltn 2>/dev/null | grep -q ":${PORT} "; then
    fail "Port $PORT is already in use."
    exit 1
fi
ok "Port $PORT is free."
sep

# ── start server under Valgrind ───────────────────────────────────────────────
log "Starting server under Valgrind …"
log "  Binary   : $BINARY"
log "  Port     : $PORT"
log "  Password : (hidden)"
log "  Log      : $VALGRIND_LOG"
sep

valgrind \
    --tool=memcheck \
    --leak-check=full \
    --show-leak-kinds=all \
    --track-origins=yes \
    --track-fds=all \
    --error-exitcode=1 \
    --log-file="$VALGRIND_LOG" \
    "$BINARY" "$PORT" "$PASSWORD" &

VALGRIND_PID=$!
log "Valgrind PID: $VALGRIND_PID"

# give the server time to bind
sleep 2

if ! kill -0 "$VALGRIND_PID" 2>/dev/null; then
    fail "Server failed to start. Check $VALGRIND_LOG for details."
    exit 1
fi
ok "Server is up."
sep

# ── cleanup trap ──────────────────────────────────────────────────────────────
cleanup() {
    sep
    log "Stopping server (PID $VALGRIND_PID) …"
    kill -TERM "$VALGRIND_PID" 2>/dev/null
    wait "$VALGRIND_PID" 2>/dev/null
    VALGRIND_EXIT=$?
    log "Valgrind exited with code: $VALGRIND_EXIT"
    parse_report
}
trap cleanup EXIT INT TERM

# ── test phases ───────────────────────────────────────────────────────────────

run_phase() {
    local phase="$1"
    local duration="$2"
    local extra_args="${3:-}"

    sep
    log "Phase $phase — $duration seconds …"
    python3 "$TESTER" "$NUM_CLIENTS" 127.0.0.1 "$PORT" \
        --password "$PASSWORD" $extra_args &
    TESTER_PID=$!
    sleep "$duration"
    kill -TERM "$TESTER_PID" 2>/dev/null
    wait "$TESTER_PID" 2>/dev/null
    ok "Phase $phase complete."
}

# Phase 1 — persistent connections, loop messages
run_phase 1 15

# Phase 2 — reconnect mode (connect → msg → disconnect, repeat)
run_phase 2 15 "--reconnect"

# Phase 3 — stress: more clients, shorter window
log "Phase 3 — stress test with $((NUM_CLIENTS * 3)) clients …"
python3 "$TESTER" "$((NUM_CLIENTS * 3))" 127.0.0.1 "$PORT" \
    --password "$PASSWORD" --reconnect &
TESTER_PID=$!
sleep 20
kill -TERM "$TESTER_PID" 2>/dev/null
wait "$TESTER_PID" 2>/dev/null
ok "Phase 3 complete."

sep
log "All test phases finished. Stopping server …"
# cleanup() fires via trap

# ── report parser ─────────────────────────────────────────────────────────────

parse_report() {
    sep
    log "Parsing Valgrind report …"
    sep

    if [[ ! -f "$VALGRIND_LOG" ]]; then
        fail "Valgrind log not found: $VALGRIND_LOG"
        return
    fi

    # extract key sections
    local heap_summary
    local leak_summary
    local error_summary
    local fd_summary

    heap_summary=$(grep -A5  "HEAP SUMMARY"   "$VALGRIND_LOG" | head -10)
    leak_summary=$(grep -A10 "LEAK SUMMARY"   "$VALGRIND_LOG" | head -15)
    error_summary=$(grep -A2 "ERROR SUMMARY"  "$VALGRIND_LOG" | head -5)
    fd_summary=$(grep        "FILE DESCRIPTORS" "$VALGRIND_LOG" | head -5)

    # counts
    local definitely_lost possibly_lost still_reachable errors fd_leaks

    definitely_lost=$(grep "definitely lost" "$VALGRIND_LOG" | \
        grep -oP '\d+ bytes' | head -1)
    possibly_lost=$(grep "possibly lost" "$VALGRIND_LOG" | \
        grep -oP '\d+ bytes' | head -1)
    still_reachable=$(grep "still reachable" "$VALGRIND_LOG" | \
        grep -oP '\d+ bytes' | head -1)
    errors=$(grep "ERROR SUMMARY" "$VALGRIND_LOG" | \
        grep -oP '^\S.*errors' | head -1)
    fd_leaks=$(grep -c "Open file descriptor" "$VALGRIND_LOG" || true)

    # ── classify each open FD by type ────────────────────────────────────────
    # Valgrind prints blocks like:
    #   Open file descriptor N: <path or description>
    #     <inherited from parent> / <socket> / <pipe> / etc.
    #     at 0x... (syscall)
    #     by 0x... (function)
    #
    # We scan those blocks and classify them.

    classify_fds() {
        python3 - "$VALGRIND_LOG" <<'PYEOF'
import sys, re

log = open(sys.argv[1], errors='replace').read()
blocks = re.split(r'(?=Open file descriptor \d+)', log)

fd_types = {
    'TCP socket (server listen)': 0,
    'TCP socket (client connection)': 0,
    'Unix domain socket': 0,
    'Pipe': 0,
    'Regular file': 0,
    'stdin / stdout / stderr': 0,
    'epoll / signalfd / eventfd / timerfd': 0,
    'Valgrind internal (log file / inherited)': 0,
}

details = []
real_leaks = 0

for block in blocks:
    m = re.match(r'Open file descriptor (\d+):', block)
    if not m:
        continue
    fd_num = int(m.group(1))
    block_lower = block.lower()

    # Valgrind's own log fd or any inherited-from-parent fd → not our leak
    is_inherited = bool(re.search(r'inherited from parent', block, re.IGNORECASE))
    is_valgrind_log = bool(re.search(r'valgrind[_\-].*\.log|valgrind_logs', block, re.IGNORECASE))

    if fd_num in (0, 1, 2):
        fd_type = 'stdin / stdout / stderr'
    elif is_inherited or is_valgrind_log:
        fd_type = 'Valgrind internal (log file / inherited)'
    elif re.search(r'socket.*type.*sock_stream|tcp|inet', block_lower):
        if re.search(r'bind|listen|server', block_lower):
            fd_type = 'TCP socket (server listen)'
        else:
            fd_type = 'TCP socket (client connection)'
        real_leaks += 1
    elif re.search(r'unix|sock_unix|af_unix', block_lower):
        fd_type = 'Unix domain socket'
        real_leaks += 1
    elif re.search(r'pipe|fifo', block_lower):
        fd_type = 'Pipe'
        real_leaks += 1
    elif re.search(r'epoll|signalfd|eventfd|timerfd', block_lower):
        fd_type = 'epoll / signalfd / eventfd / timerfd'
    elif re.search(r'open.*file|/proc|/dev|/tmp|/home|/usr|/etc|\.so|\.log', block_lower):
        fd_type = 'Regular file'
    else:
        fd_type = 'Valgrind internal (log file / inherited)'

    fd_types[fd_type] += 1

    lines = block.strip().splitlines()
    desc = lines[1].strip() if len(lines) > 1 else '(no description)'
    details.append((fd_num, fd_type, desc))

if not details:
    print("  (no open file descriptors reported)")
else:
    print(f"  {'FD':>4}  {'Type':<42}  Description")
    print(f"  {'----':>4}  {'------':42}  -----------")
    for fd_num, fd_type, desc in sorted(details):
        marker = '·' if 'Valgrind' in fd_type or fd_num < 3 else '⚠'
        print(f"  {marker} {fd_num:>3}  {fd_type:<42}  {desc[:55]}")
    print()
    print("  Summary by type:")
    for t, count in fd_types.items():
        if count:
            marker = '⚠' if count and 'socket' in t.lower() or 'pipe' in t.lower() else '·'
            print(f"    {marker}  {t:<42}  x{count}")
    print()
    if real_leaks == 0:
        print("  ✓ No real FD leaks — Valgrind internal FDs are expected and harmless.")
    else:
        print(f"  ✗ {real_leaks} real FD leak(s) detected — sockets/pipes not closed by your code.")
PYEOF
    }

    # ── console report ────────────────────────────────────────────────────────
    echo ""
    echo -e "${BLD}════════════════════════════════════════════════════${RST}"
    echo -e "${BLD}           VALGRIND MEMORY LEAK REPORT              ${RST}"
    echo -e "${BLD}════════════════════════════════════════════════════${RST}"
    echo ""

    echo -e "${BLD}── Heap Summary ──────────────────────────────────${RST}"
    echo "$heap_summary"
    echo ""

    echo -e "${BLD}── Leak Summary ──────────────────────────────────${RST}"
    echo "$leak_summary"
    echo ""

    echo -e "${BLD}── File Descriptors ──────────────────────────────${RST}"
    echo "  Total open FDs at exit: $fd_leaks"
    echo ""
    classify_fds
    echo ""

    echo -e "${BLD}── Error Summary ─────────────────────────────────${RST}"
    echo "$error_summary"
    echo ""

    # ── verdict ───────────────────────────────────────────────────────────────
    echo -e "${BLD}── Verdict ───────────────────────────────────────${RST}"

    local clean=true

    if [[ "$definitely_lost" == "0 bytes" || -z "$definitely_lost" ]]; then
        ok "Definitely lost : ${definitely_lost:-0 bytes}"
    else
        fail "Definitely lost : $definitely_lost  ← LEAK DETECTED"
        clean=false
    fi

    if [[ "$possibly_lost" == "0 bytes" || -z "$possibly_lost" ]]; then
        ok "Possibly lost   : ${possibly_lost:-0 bytes}"
    else
        warn "Possibly lost   : $possibly_lost"
    fi

    if [[ -n "$still_reachable" && "$still_reachable" != "0 bytes" ]]; then
        warn "Still reachable : $still_reachable  (may be intentional)"
    else
        ok "Still reachable : ${still_reachable:-0 bytes}"
    fi

    # Count only real FD leaks (exclude inherited/valgrind own log FD)
    real_fd_leaks=0
    if [[ $fd_leaks -gt 0 ]]; then
        real_fd_leaks=$(python3 - "$VALGRIND_LOG" <<'PYEOF'
import sys, re
log = open(sys.argv[1], errors='replace').read()
blocks = re.split(r'(?=Open file descriptor \d+)', log)
count = 0
for block in blocks:
    m = re.match(r'Open file descriptor (\d+):', block)
    if not m:
        continue
    fd_num = int(m.group(1))
    if fd_num in (0, 1, 2):
        continue
    if re.search(r'inherited from parent|valgrind[_\-].*\.log|valgrind_logs', block, re.IGNORECASE):
        continue
    if re.search(r'socket|pipe|fifo', block, re.IGNORECASE):
        count += 1
print(count)
PYEOF
)
    fi

    if [[ $fd_leaks -gt 0 && $real_fd_leaks -eq 0 ]]; then
        ok "FD leaks        : none (FD reported is Valgrind's own log file — harmless)"
    elif [[ $real_fd_leaks -gt 0 ]]; then
        fail "FD leaks        : $real_fd_leaks real FD(s) not closed by your code ← LEAK"
        clean=false
    else
        ok "FD leaks        : none"
    fi

    if grep -q "Invalid read\|Invalid write\|Use of uninitialised\|Conditional jump" \
        "$VALGRIND_LOG"; then
        fail "Memory errors   : invalid reads/writes or uninitialised values found"
        clean=false
    else
        ok "Memory errors   : none"
    fi

    echo ""
    if $clean; then
        echo -e "${GRN}${BLD}  ✓ No memory leaks or errors detected.${RST}"
    else
        echo -e "${RED}${BLD}  ✗ Issues found. Review $VALGRIND_LOG for details.${RST}"
    fi

    echo -e "${BLD}════════════════════════════════════════════════════${RST}"
    echo ""

    # ── save summary ──────────────────────────────────────────────────────────
    {
        echo "=== ft_irc Valgrind Summary — $(date) ==="
        echo "Binary    : $BINARY"
        echo "Port      : $PORT"
        echo "Clients   : $NUM_CLIENTS"
        echo ""
        echo "--- Heap Summary ---"
        echo "$heap_summary"
        echo ""
        echo "--- Leak Summary ---"
        echo "$leak_summary"
        echo ""
        echo "--- Error Summary ---"
        echo "$error_summary"
        echo ""
        echo "--- FD leaks ---"
        echo "Open FD leak entries: $fd_leaks"
        classify_fds
        echo ""
        if $clean; then
            echo "VERDICT: CLEAN — no leaks or errors detected."
        else
            echo "VERDICT: ISSUES FOUND — see $VALGRIND_LOG for full details."
        fi
    } > "$SUMMARY_LOG"

    ok "Summary saved to : $SUMMARY_LOG"
    ok "Full Valgrind log: $VALGRIND_LOG"
    sep
}
