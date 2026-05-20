import socket
import threading
import time

# Configuración
SERVER   = "127.0.0.1"
PORT     = 6667
PASSWORD = "test123"
CHANNEL  = "#Bienvenidos"
NUM_USERS = 50

def recv_until_quiet(s, timeout=1.5):
    """
    Lee respuestas del servidor hasta que no llegue nada durante `timeout` segundos.
    Necesario para asegurarse de que el servidor ha procesado el comando QUIT
    antes de cerrar el socket.
    """
    s.settimeout(timeout)
    data = b""
    try:
        while True:
            chunk = s.recv(4096)
            if not chunk:
                break
            data += chunk
    except socket.timeout:
        pass
    s.settimeout(None)
    return data.decode(errors="replace")

def connect_user(user_id):
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((SERVER, PORT))

        nick  = f"User{user_id}"
        ident = f"ident{user_id}"

        # ── Registro ──────────────────────────────────────────────────────────
        s.send(f"PASS {PASSWORD}\r\n".encode())
        s.send(f"NICK {nick}\r\n".encode())
        s.send(f"USER {ident} 0 * :Alumno 42\r\n".encode())

        # Esperar el welcome (001) antes de continuar
        recv_until_quiet(s, timeout=1.0)

        # ── Unirse al canal ───────────────────────────────────────────────────
        s.send(f"JOIN {CHANNEL}\r\n".encode())

        # Esperar confirmación del JOIN y los mensajes de los demás
        time.sleep(5)
        recv_until_quiet(s, timeout=0.5)

        # ── Desconexión limpia ────────────────────────────────────────────────
        # 1. Enviar QUIT con mensaje (obligatorio según RFC 1459)
        s.send(f"QUIT :Mision cumplida\r\n".encode())

        # 2. Leer hasta que el servidor cierre su extremo del socket.
        #    Esto garantiza que el servidor ha procesado el QUIT y ha enviado
        #    el ERROR de cierre antes de que nosotros cerremos el socket.
        #    Sin este paso, el close() puede llegar antes que el QUIT al servidor
        #    y el usuario queda como fantasma en el canal.
        recv_until_quiet(s, timeout=200)

        # 3. shutdown(SHUT_WR) antes de close() para un cierre TCP limpio (FIN)
        #    en lugar de un reset abrupto (RST) que puede perderse en el servidor.
        try:
            s.shutdown(socket.SHUT_WR)
        except OSError:
            pass
        s.close()

        print(f"[OK] {nick} finalizado.")

    except Exception as e:
        print(f"[ERROR] Cliente {user_id}: {e}")


# ── Lanzamiento de hilos ──────────────────────────────────────────────────────
threads = []
print(f"[*] Iniciando conexión de {NUM_USERS} usuarios...")

for i in range(1, NUM_USERS + 1):
    t = threading.Thread(target=connect_user, args=(i,))
    threads.append(t)
    t.start()
    time.sleep(0.2)

for t in threads:
    t.join()

print("[*] Prueba de carga finalizada.")
