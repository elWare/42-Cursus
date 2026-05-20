#!/usr/bin/env python3
"""
irc_tester.py — Replicates ft_irc-tester (opsec-infosec/ft_irc-tester)

Usage:
    python3 irc_tester.py <num_clients> <server_ip> <port> [--password <pass>] [--reconnect]

Options:
    --password <pass>  Server password; overrides <password> in replace.conf
    --reconnect        Enable Option 2: connect → send → disconnect → loop
                       (equivalent to compiling with -D RECONNECT_ON_MSG)

Configuration files (same as the original tool, place them in ./conf/):
    replace.conf       — tag replacements, e.g.  <nick> client
    connect.conf       — commands sent once, right at connection
    after-connect.conf — commands sent once after connection (supports delays)
    loop.conf          — commands sent repeatedly at random intervals
    disconnect.conf    — commands sent on disconnect / SIGINT

Special variables replaced in all .conf files:
    {0}  → server IP address
    {1}  → port number
    {2}  → client ID  (0 … n-1)
    {3}  → random timer interval for this client (3-60 s)
    {4}  → socket file descriptor number

Delay syntax inside .conf files:
    [1000]   → sleep 1000 ms
    [{3}000] → sleep {3}*1000 ms  (resolved AFTER other substitutions)
"""

import socket
import threading
import random
import time
import sys
import os
import re
import signal
from pathlib import Path

# ── globals ──────────────────────────────────────────────────────────────────
CONF_DIR = Path("./conf")
_clients: list["IRCClient"] = []
_shutdown = threading.Event() 

# Pool de mensajes aleatorios para {MSG}
# Los clientes los usan en loop.conf con  PRIVMSG <channel> :{MSG}
_MESSAGES = [
    "¡Hola a todos! Soy el cliente {2} 👋",
    "¿Cómo va todo por aquí?",
    "Este servidor IRC funciona genial 🚀",
    "Cliente {2} reportando desde {0}:{1}",
    "¿Alguien ha probado el modo --reconnect?",
    "Llevo {3}s de intervalo, el tiempo pasa rápido",
    "¡Buenas! Cliente {2} al habla",
    "Ping... ¿hay alguien ahí?",
    "Todo tranquilo desde el cliente {2} 🟢",
    "Mandando saludos desde el fd {4}",
    "¡Qué buen servidor! Sin caídas 💪",
    "Cliente {2} enviando mensaje de prueba #{3}",
    "¿Qué tal el ft_irc? A mí me parece brutal 😄",
    "Silencio en el canal... rompiendo el hielo 🧊",
    "¡42 mola! Saludos desde {0}",
    "Que pasa, Wey",
]


# ── helpers ──────────────────────────────────────────────────────────────────

def load_conf(filename: str) -> list[str]:
    """Return non-empty lines from a conf file; empty list if file missing."""
    path = CONF_DIR / filename
    if not path.exists():
        return []
    with open(path, "r") as f:
        return [line.rstrip("\n") for line in f if line.strip()]


def load_replacements() -> dict[str, str]:
    """Parse replace.conf → { '<tag>': 'value', … }"""
    replacements: dict[str, str] = {}
    for line in load_conf("replace.conf"):
        parts = line.split(None, 1)
        if len(parts) == 2:
            replacements[parts[0]] = parts[1]
    return replacements


def apply_replacements(text: str, replacements: dict[str, str],
                       client_id: int, server_ip: str, port: int,
                       interval: int, fd: int) -> str:
    """Apply replace.conf tags and special {N} / {MSG} variables."""
    # {MSG} → random message (resolved first so {2},{3}… inside it also expand)
    text = text.replace("{MSG}", random.choice(_MESSAGES))
    for tag, value in replacements.items():
        text = text.replace(tag, value)
    text = text.replace("{0}", server_ip)
    text = text.replace("{1}", str(port))
    text = text.replace("{2}", str(client_id))
    text = text.replace("{3}", str(interval))
    text = text.replace("{4}", str(fd))
    return text


def parse_and_send(lines: list[str], sock: socket.socket,
                   replacements: dict[str, str], client_id: int,
                   server_ip: str, port: int, interval: int) -> None:
    """Send lines to the server, honouring [NNN] delay syntax."""
    fd = sock.fileno()
    i = 0
    while i < len(lines):
        line = apply_replacements(lines[i], replacements,
                                  client_id, server_ip, port, interval, fd)
        # delay line: [1000]  or  [{3}000] (already resolved above)
        delay_match = re.fullmatch(r'\[(\d+)\]', line.strip())
        if delay_match:
            ms = int(delay_match.group(1))
            _shutdown.wait(ms / 1000)
        else:
            try:
                sock.sendall((line + "\r\n").encode("utf-8", errors="replace"))
            except OSError:
                pass
        i += 1


# ── IRC client thread ─────────────────────────────────────────────────────────

class IRCClient(threading.Thread):
    def __init__(self, client_id: int, server_ip: str, port: int,
                 reconnect: bool, replacements: dict[str, str]) -> None:
        super().__init__(daemon=True)
        self.client_id = client_id
        self.server_ip = server_ip
        self.port = port
        self.reconnect = reconnect
        self.replacements = replacements
        self.interval = random.randint(3, 60)  # unique per client
        self.sock: socket.socket | None = None

    # ── internal helpers ──────────────────────────────────────────────────────

    def _connect(self) -> bool:
        try:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            s.settimeout(10)
            s.connect((self.server_ip, self.port))
            s.settimeout(None)
            self.sock = s
            return True
        except OSError as e:
            print(f"[client {self.client_id}] connect error: {e}")
            return False

    def _send_phase(self, filename: str) -> None:
        if self.sock is None:
            return
        lines = load_conf(filename)
        if lines:
            parse_and_send(lines, self.sock, self.replacements,
                           self.client_id, self.server_ip, self.port,
                           self.interval)

    def _disconnect(self) -> None:
        if self.sock is None:
            return
        try:
            self._send_phase("disconnect.conf")
        finally:
            try:
                self.sock.close()
            except OSError:
                pass
            self.sock = None

    # ── main loop ─────────────────────────────────────────────────────────────

    def run(self) -> None:
        # staggered start: wait a random delay before first connect
        startup_delay = random.randint(1, self.interval)
        print(f"[client {self.client_id}] starting in {startup_delay}s "
              f"(loop interval={self.interval}s)")
        _shutdown.wait(startup_delay)

        while not _shutdown.is_set():
            # ── connect ───────────────────────────────────────────────────────
            if not _connect_retry(self):
                break

            self._send_phase("connect.conf")
            self._send_phase("after-connect.conf")

            if self.reconnect:
                # Option 2: send loop.conf once, then disconnect and repeat
                self._send_phase("loop.conf")
                _shutdown.wait(random.uniform(0.5, 2))
                self._disconnect()
                # wait the client's interval before reconnecting
                _shutdown.wait(self.interval)
            else:
                # Option 1 (default): loop sending loop.conf indefinitely
                while not _shutdown.is_set():
                    _shutdown.wait(self.interval)
                    if _shutdown.is_set():
                        break
                    self._send_phase("loop.conf")
                self._disconnect()
                break   # outer while; _shutdown is set

        # final disconnect on shutdown (if still connected)
        self._disconnect()
        print(f"[client {self.client_id}] terminated.")


def _connect_retry(client: IRCClient) -> bool:
    """Try to connect; retry up to 3 times before giving up."""
    for attempt in range(3):
        if _shutdown.is_set():
            return False
        if client._connect():
            return True
        print(f"[client {client.client_id}] retry {attempt+1}/3 …")
        _shutdown.wait(2)
    return False


# ── signal handling ───────────────────────────────────────────────────────────

def _signal_handler(signum, frame):
    print("\n[tester] shutdown signal received — closing all clients …")
    _shutdown.set()


# ── entry point ───────────────────────────────────────────────────────────────

def main() -> None:
    # ── argument parsing ──────────────────────────────────────────────────────
    # Split positional args from --flag [value] options
    positional: list[str] = []
    password: str | None = None
    reconnect = False
    idx = 1
    while idx < len(sys.argv):
        a = sys.argv[idx]
        if a == "--password":
            idx += 1
            if idx >= len(sys.argv):
                print("Error: --password requires a value.")
                sys.exit(1)
            password = sys.argv[idx]
        elif a == "--reconnect":
            reconnect = True
        else:
            positional.append(a)
        idx += 1

    if len(positional) < 3:
        print(__doc__)
        sys.exit(1)

    try:
        num_clients = int(positional[0])
        server_ip = positional[1]
        port = int(positional[2])
    except ValueError:
        print("Error: <num_clients> and <port> must be integers.")
        sys.exit(1)

    print(f"[tester] starting {num_clients} client(s) → {server_ip}:{port} "
          f"({'reconnect' if reconnect else 'persistent'} mode)")

    # ── register signals ──────────────────────────────────────────────────────
    signal.signal(signal.SIGINT, _signal_handler)
    signal.signal(signal.SIGTERM, _signal_handler)
    try:
        signal.signal(signal.SIGQUIT, _signal_handler)   # ctrl-\
    except AttributeError:
        pass  # Windows

    # ── load replacements (shared, read-only after this point) ───────────────
    replacements = load_replacements()
    if password is not None:
        replacements["<password>"] = password
        print(f"[tester] password set from command line")

    # ── spawn client threads ──────────────────────────────────────────────────
    for i in range(num_clients):
        c = IRCClient(i, server_ip, port, reconnect, replacements)
        _clients.append(c)
        c.start()

    # ── wait until shutdown ───────────────────────────────────────────────────
    try:
        while not _shutdown.is_set():
            time.sleep(0.5)
    except KeyboardInterrupt:
        _shutdown.set()

    # wait for all threads
    for c in _clients:
        c.join(timeout=5)

    print("[tester] all clients stopped. bye!")


if __name__ == "__main__":
    main()
