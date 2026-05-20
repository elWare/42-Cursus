import socket
import threading
import time
import random

SERVER = "127.0.0.1"
PORT = 6667
PASS = "test123"
NUM_CLIENTS = 500 # Sube este número hasta que el servidor explote o llegues al límite de tu SO

def simulate_client(client_id):
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect((SERVER, PORT))
        
        nick = f"User_{client_id}_{random.randint(100, 999)}"
        
        # Protocolo de Registro
        s.send(f"PASS {PASS}".encode())
        s.send(f"NICK {nick}".encode())
        s.send(f"USER {nick} 0 * :RealName".encode())
        time.sleep(0.1)
        
        # Unirse al canal común (Saturación de Broadcast)
        s.send(f"JOIN #Bienvenidos".encode())
        
        # Crear canales aleatorios (Fragmentación de Memoria)
        rand_chan = f"#canal_privado_{random.randint(1, 20)}"
        s.send(f"JOIN {rand_chan}".encode())
        
        # Bucle de actividad: Enviar mensajes para forzar POLLOUT en todos los demás
        for _ in range(10):
            s.send(f"PRIVMSG #Bienvenidos :Hola a todos, soy {nick} saturando el buffer!".encode())
            time.sleep(0.5) # Ritmo constante
            
        s.send(b"QUIT :Prueba finalizada")
        time.sleep(0.2)
        s.close()
        
    except Exception as e:
        print(f"Cliente {client_id} error: {e}")

threads = []
print(f"[*] Lanzando {NUM_CLIENTS} conexiones simultáneas...")

for i in range(NUM_CLIENTS):
    t = threading.Thread(target=simulate_client, args=(i,))
    threads.append(t)
    t.start()
    # Un pequeño delay de conexión para no bloquear el accept() del kernel de golpe
    time.sleep(0.05)

for t in threads:
    t.join()

print("[*] Ataque finalizado. Verifica el estado del servidor.")
