#!/usr/bin/env bash
# =============================================================================
# nc_test.sh — ft_irc server tester using netcat (nc)
#
# Usage:
#   ./nc_test.sh
#
# Tests: registration, join, privmsg, topic, mode, invite, kick, part, quit
# =============================================================================

SERVER="127.0.0.1"
PORT=7777
PASS="test123"
DELAY=0.4       # seconds between commands (adjust if server is slow)
# timeout 3s: the server doesn't close the socket after QUIT (client closes
# first), so nc would hang forever with -w. We use system timeout instead,
# which kills nc after 3s ensuring we capture all responses sent by the server.
NC_TIMEOUT=3

# ── colours ──────────────────────────────────────────────────────────────────
RED='\033[0;31m'; GRN='\033[0;32m'; YEL='\033[1;33m'
CYN='\033[0;36m'; BLD='\033[1m';    RST='\033[0m'

ok()  { echo -e "${GRN}[  OK  ]${RST} $*"; }
fail(){ echo -e "${RED}[ FAIL ]${RST} $*"; }
sep() { echo -e "${BLD}────────────────────────────────────────────────${RST}"; }
log() { echo -e "${CYN}[  >>  ]${RST} $*"; }

# ── helper: send a sequence of commands via nc ────────────────────────────────
# $1 = label, $2 = expected string in response, rest = commands
# Note: netcat-openbsd uses \n only, not \r\n. Removed all \r from commands.
run_test() {
    local label="$1"
    local expect="$2"
    shift 2
    local cmds=("$@")

    # netcat-openbsd doesn't handle \r\n properly, so we use simple \n line endings
    local response
    response=$(printf "%s\n" "${cmds[@]}" | timeout ${NC_TIMEOUT}s nc "$SERVER" "$PORT" 2>&1)

    if echo "$response" | grep -q "$expect"; then
        ok "$label"
    else
        fail "$label  (expected: '$expect')"
        echo "    Server response:"
        echo "$response" | sed 's/^/      /'
    fi
}

# ── preflight ─────────────────────────────────────────────────────────────────
sep
echo -e "${BLD}  ft_irc nc tester — ${SERVER}:${PORT}${RST}"
sep

if ! command -v nc &>/dev/null; then
    fail "netcat (nc) not found. Install with: sudo apt install netcat-openbsd"
    exit 1
fi

if ! nc -z "$SERVER" "$PORT" 2>/dev/null; then
    fail "Server not reachable at ${SERVER}:${PORT}. Is ircserv running?"
    exit 1
fi
ok "Server is up at ${SERVER}:${PORT}"
sep

# ─────────────────────────────────────────────────────────────────────────────
# TEST 1 — Basic registration (PASS + NICK + USER → welcome 001)
# ─────────────────────────────────────────────────────────────────────────────
run_test "Registration: PASS + NICK + USER → 001 welcome" "001" \
    "PASS $PASS" \
    "NICK TestUser" \
    "USER testuser 0 * :Test User" \
    "JOIN #bienvenidos"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 2 — Wrong password → 464 ERR_PASSWDMISMATCH
# ─────────────────────────────────────────────────────────────────────────────
run_test "Wrong password → 464 ERR_PASSWDMISMATCH" "464" \
    "PASS wrongpassword" \
    "NICK BadUser" \
    "USER bad 0 * :Bad User"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 3 — Command before registration → 451 ERR_NOTREGISTERED
# ─────────────────────────────────────────────────────────────────────────────
run_test "JOIN before registration → 451 ERR_NOTREGISTERED" "451" \
    "JOIN #test"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 4 — JOIN a channel → server echoes JOIN
# ─────────────────────────────────────────────────────────────────────────────
run_test "JOIN #bienvenidos → channel echo" "JOIN" \
    "PASS $PASS" \
    "NICK JoinUser" \
    "USER joinuser 0 * :Join Tester" \
    "JOIN #bienvenidos"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 5 — PRIVMSG to channel
# ─────────────────────────────────────────────────────────────────────────────
run_test "PRIVMSG to channel (no error expected)" "JOIN" \
    "PASS $PASS" \
    "NICK MsgUser" \
    "USER msguser 0 * :Msg Tester" \
    "JOIN #bienvenidos" \
    "PRIVMSG #bienvenidos :Hola desde nc!"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 6 — TOPIC set and query
# ─────────────────────────────────────────────────────────────────────────────
run_test "TOPIC set → 332 or TOPIC echo" "332\|TOPIC" \
    "PASS $PASS" \
    "NICK TopicUser" \
    "USER topicuser 0 * :Topic Tester" \
    "JOIN #topictest" \
    "TOPIC #topictest :Mi tema de prueba" \
    "TOPIC #topictest"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 7 — MODE +i (invite only)
# ─────────────────────────────────────────────────────────────────────────────
run_test "MODE +i set → MODE echo" "MODE" \
    "PASS $PASS" \
    "NICK ModeUser" \
    "USER modeuser 0 * :Mode Tester" \
    "JOIN #modetest" \
    "MODE #modetest +i"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 8 — MODE +k (channel key)
# ─────────────────────────────────────────────────────────────────────────────
run_test "MODE +k (password) → MODE echo" "MODE" \
    "PASS $PASS" \
    "NICK KeyUser" \
    "USER keyuser 0 * :Key Tester" \
    "JOIN #keytest" \
    "MODE #keytest +k clave123"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 9 — MODE +l (user limit)
# ─────────────────────────────────────────────────────────────────────────────
run_test "MODE +l (user limit) → MODE echo" "MODE" \
    "PASS $PASS" \
    "NICK LimitUser" \
    "USER limituser 0 * :Limit Tester" \
    "JOIN #limittest" \
    "MODE #limittest +l 10"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 10 — PART a channel → PART echo
# ─────────────────────────────────────────────────────────────────────────────
run_test "PART channel → PART echo" "PART" \
    "PASS $PASS" \
    "NICK PartUser" \
    "USER partuser 0 * :Part Tester" \
    "JOIN #parttest" \
    "PART #parttest :Adios"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 11 — KICK sin permisos de operador → 482 ERR_CHANOPRIVSNEEDED
# ─────────────────────────────────────────────────────────────────────────────
log "Test 11: KICK — verificando que sin permisos de operador el kick falla..."

# Create a fresh channel for KICK test to avoid state pollution from previous tests
# Spawns victim in background, then attacker tries to KICK without ops rights
( printf "PASS %s\nNICK Victima\nUSER victima 0 * :Victim\nJOIN #kicktest\n" "$PASS" \
    | timeout 10s nc "$SERVER" "$PORT" &>/dev/null ) &
VICTIM_PID=$!
sleep 0.8   # give victim time to join

# Attacker joins but does NOT take operator privileges
run_test "KICK sin ser operador → 482 ERR_CHANOPRIVSNEEDED" "482" \
    "PASS $PASS" \
    "NICK Attacker" \
    "USER attacker 0 * :Attacker" \
    "JOIN #kicktest" \
    "KICK #kicktest Victima :prueba de kick sin permisos"

wait $VICTIM_PID 2>/dev/null

# ─────────────────────────────────────────────────────────────────────────────
# TEST 12 — INVITE (requires target user online)
# ─────────────────────────────────────────────────────────────────────────────
log "Test 12: INVITE — spawning guest client in background..."

( printf "PASS %s\nNICK Invitado\nUSER invitado 0 * :Guest\n" "$PASS" \
    | timeout 10s nc "$SERVER" "$PORT" &>/dev/null ) &
GUEST_PID=$!
sleep 0.8

run_test "INVITE user → 341 RPL_INVITING" "341" \
    "PASS $PASS" \
    "NICK Anfitrion" \
    "USER anfitrion 0 * :Host" \
    "JOIN #invitetest" \
    "MODE #invitetest +i" \
    "INVITE Invitado #invitetest"

wait $GUEST_PID 2>/dev/null

# ─────────────────────────────────────────────────────────────────────────────
# TEST 13 — PING → PONG
# ─────────────────────────────────────────────────────────────────────────────
run_test "PING → PONG response" "PONG" \
    "PASS $PASS" \
    "NICK PingUser" \
    "USER pinguser 0 * :Ping Tester" \
    "PING :testtoken"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 14 — Unknown command → 421 ERR_UNKNOWNCOMMAND
# ─────────────────────────────────────────────────────────────────────────────
run_test "Unknown command → 421 ERR_UNKNOWNCOMMAND" "421" \
    "PASS $PASS" \
    "NICK UnkUser" \
    "USER unkuser 0 * :Unknown Tester" \
    "COMANDOFALSO param1 param2"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 15 — NICK change after registration
# ─────────────────────────────────────────────────────────────────────────────
run_test "NICK change after registration → NICK echo" "NICK" \
    "PASS $PASS" \
    "NICK OldNick" \
    "USER oldnick 0 * :Nick Changer" \
    "NICK NewNick"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 16 — Buffer overflow: NICK > 512 bytes → server survives
# ─────────────────────────────────────────────────────────────────────────────
BIG_NICK=$(python3 -c "print('A'*600)")
run_test "Oversized NICK (600 chars) → server handles it" "001\|432\|ERROR\|NICK" \
    "PASS $PASS" \
    "NICK ${BIG_NICK}" \
    "NICK SafeNick" \
    "USER safeuser 0 * :Safe User"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 17 — PRIVMSG to non-existent user → 401 ERR_NOSUCHNICK
# ─────────────────────────────────────────────────────────────────────────────
run_test "PRIVMSG to non-existent nick → 401 ERR_NOSUCHNICK" "401" \
    "PASS $PASS" \
    "NICK RealUser" \
    "USER realuser 0 * :Real User" \
    "PRIVMSG UsuarioFantasma :hola"

# ─────────────────────────────────────────────────────────────────────────────
# TEST 18 — KICK with missing params → 461 ERR_NEEDMOREPARAMS
# ─────────────────────────────────────────────────────────────────────────────
run_test "KICK without target → 461 ERR_NEEDMOREPARAMS" "461" \
    "PASS $PASS" \
    "NICK KickFuzz" \
    "USER kickfuzz 0 * :Kick Fuzzer" \
    "JOIN #fuzztest" \
    "KICK #fuzztest"

# ─────────────────────────────────────────────────────────────────────────────
# SUMMARY
# ─────────────────────────────────────────────────────────────────────────────
sep
echo -e "${BLD}  All tests completed.${RST}"
sep
