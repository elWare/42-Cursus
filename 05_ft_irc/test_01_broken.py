import socket
import time

SERVER = "127.0.0.1"
PORT = 6667
PASS = "test123"

def send_payload(s, payload):
    try:
        s.send(payload.encode() + b"\r\n")
        # Pequeño delay para no saturar el socket local, 
        # pero suficiente para estresar el poll()
        time.sleep(0.01) 
    except Exception as e:
        print(f"Error enviando: {e}")

def run_security_tests():
    print(f"[*] Iniciando ataque de pruebas de borde contra {SERVER}:{PORT}...")
    
    # 1. PRUEBA DE DESBORDAMIENTO DE BUFFER (Buffer Overflow)
    # El RFC dice 512 bytes, enviamos 10,000 para ver si el buffer de lectura falla.
    s1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s1.connect((SERVER, PORT))
    print("[!] Test 1: Desbordamiento de buffer en registro")
    send_payload(s1, "PASS " + PASS)
    send_payload(s1, "NICK " + ("A" * 10000)) # Nickname gigante
    send_payload(s1, "USER " + ("B" * 5000) + " 0 * :realname")
    
    # 2. PRUEBA DE INYECCIÓN DE COMANDOS Y CARACTERES NULOS
    # Intentamos meter saltos de línea dentro de parámetros y bytes nulos (\0)
    print("[!] Test 2: Inyección de protocolos")
    s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s2.connect((SERVER, PORT))
    send_payload(s2, f"PASS {PASS}")
    send_payload(s2, "NICK Inyector")
    send_payload(s2, "USER iny 0 * :Inyeccion\nPRIVMSG #canal :Mensaje_Inyectado")
    send_payload(s2, "PRIVMSG #canal :\x00\x01\x02\x03\xff") # Bytes maliciosos

    # 3. PRUEBA DE LÓGICA: ACCIONES SIN REGISTRO
    # Intentar romper el CommandExecutor llamando comandos antes de PASS
    print("[!] Test 3: Bypass de registro")
    s3 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s3.connect((SERVER, PORT))
    send_payload(s3, "JOIN #secreto")
    send_payload(s3, "TOPIC #secreto :Hackeado")
    send_payload(s3, "KICK #canal victima")

    # 4. PRUEBA DE AGOTAMIENTO DE RECURSOS (DoS ligero)
    # Creamos 50 canales y enviamos mensajes masivos
    print("[!] Test 4: Stress de canales")
    s4 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s4.connect((SERVER, PORT))
    send_payload(s4, f"PASS {PASS}")
    send_payload(s4, "NICK Flooder")
    send_payload(s4, "USER flood 0 * :Flood")
    for i in range(50):
        send_payload(s4, f"JOIN #canal_{i}")
        send_payload(s4, f"PRIVMSG #canal_{i} :Saturando canal...")

    # 5. PRUEBA DE COMANDOS CON PARÁMETROS MALFORMADOS
    print("[!] Test 5: Fuzzing de parámetros")
    commands = [
        "MODE #canal +l -5",           # Límite negativo
        "MODE #canal +o",              # Falta nick
        "KICK #canal",                 # Falta usuario
        "PRIVMSG #canal",              # Falta mensaje (sin :)
        "PART #canal_que_no_existe",   # Canal inexistente
        "INVITE bot #canal",           # Invitar al bot (si existe logicamente)
        "NICK 12345678901234567890"    # Nick extra largo
    ]
    for cmd in commands:
        send_payload(s4, cmd)

    print("[*] Pruebas finalizadas. Revisa si el servidor sigue vivo (CPU/RAM).")
    s1.close()
    s2.close()
    s3.close()
    s4.close()

if __name__ == "__main__":
    run_security_tests()
