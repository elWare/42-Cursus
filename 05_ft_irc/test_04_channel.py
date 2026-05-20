import socket
import threading
import time

SERVER = "127.0.0.1"
PORT = 6667
PASS = "test123"

def send(s, msg):
    print(f"--> {msg}")
    s.send((msg + "\r\n").encode())
    time.sleep(0.4) # Pausa para sincronización visual

def client_a():
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((SERVER, PORT))
        # 1. Registro
        send(s, f"PASS {PASS}")
        send(s, "NICK UserA")
        send(s, "USER usera 0 * :Operador")
        # 2. Creación de Canal (UserA será Operador)
        send(s, "JOIN #Sala42")
        # 3. Gestión de Canal
        send(s, "TOPIC #Sala42 :Bienvenidos a la prueba")
        send(s, "MODE #Sala42 +i") # Poner canal en modo invitación
        # 4. Esperar a que UserB intente entrar y fallé, luego invitarlo
        time.sleep(2)
        send(s, "INVITE UserB #Sala42")
        # 5. Chat
        time.sleep(2)
        send(s, "PRIVMSG UserB :Hola, te he tenido que invitar porque activé el modo +i")
        # 6. Kick (Prueba de poder)
        time.sleep(3)
        send(s, "KICK #Sala42 UserB :Prueba de expulsión terminada")
        send(s, "QUIT :Saliendo...")
        s.close()
    except Exception as e: print(f"Error A: {e}")

def client_b():
    try:
        time.sleep(0.5) # Empezar un poco después que A
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((SERVER, PORT))
        # 1. Registro
        send(s, f"PASS {PASS}")
        send(s, "NICK UserB")
        send(s, "USER userb 0 * :Invitado")
        # 2. Intento de JOIN fallido (por modo +i)
        time.sleep(1)
        send(s, "JOIN #Sala42") 
        # 3. Esperar invitación y entrar
        time.sleep(2)
        send(s, "JOIN #Sala42")
        # 4. Responder
        send(s, "PRIVMSG #Sala42 :Gracias por la invitación!")
        send(s, "PRIVMSG bot :Hola bot!") # Probar el bot también
        # 5. Intentar cambiar el topic sin ser OP (debe fallar si el modo +t está activo)
        send(s, "TOPIC #Sala42 :Hackeado por UserB")
        # 6. Salida
        time.sleep(4)
        s.close()
    except Exception as e: print(f"Error B: {e}")

# Ejecución simultánea
t1 = threading.Thread(target=client_a)
t2 = threading.Thread(target=client_b)
t1.start()
t2.start()
t1.join()
t2.join()
