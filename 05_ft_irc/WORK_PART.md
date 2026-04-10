# 📋 Propuesta de División del Proyecto: ft_irc

---

## 👤 Persona 1: Infraestructura y Comunicación Básica

### 📂 Archivos a desarrollar
* `src/main.cpp` - Punto de entrada, inicialización.
* `src/server.cpp` - Lógica principal del servidor.
* `src/client.cpp` - Clase Cliente.
* `src/utils.cpp` - Utilidades y funciones auxiliares.

### ⚙️ Funcionalidades
* **Manejo de conexiones TCP.**
* **Autenticación básica:** `PASS`, `USER`.
* **Registro de clientes.**
* **Comandos básicos:** `NICK`, `USER`, `PING`.
* **Manejo de desconexiones.**
* **Configuración de sockets:** `epoll`, `non-blocking`.
* **Sistema de mensajería:** `sendReply`, `sendError`.

> **Objetivo:** Encargarse de toda la infraestructura de conexión, red (I/O) y el flujo inicial de autenticación del protocolo.

---

## 👤 Persona 2: Gestión de Canales y Comandos Avanzados

### 📂 Archivos a desarrollar
* `src/channel.cpp` - Clase Canal (con todos sus modos).
* `src/handle.cpp` - Manejador de comandos (excepto los básicos).
* `src/replies.cpp` - Definición de respuestas `RPL_*`.
* `src/errors.cpp` - Definición de errores `ERR_*`.
* `src/mode.cpp` - Lógica extendida de modos de canal.
* `src/operators.cpp` - Comandos de operador (`KICK`, `INVITE`, `TOPIC`).

### ⚙️ Funcionalidades
* **Gestión de canales:** Creación y destrucción.
* **Modos de canal:** `+i` (invite-only), `+t` (topic), `+k` (key), `+o` (operator), `+l` (limit).
* **Mensajería de canal:** `JOIN`, `PART`, `PRIVMSG`.
* **Comandos de operador:** `KICK`, `INVITE`, `TOPIC`.
* **Gestión de miembros:** Listas de usuarios y permisos.
* **Broadcast:** Difusión de mensajes a múltiples clientes.

> **Objetivo:** Implementar toda la lógica de negocio, la gestión de estados de los canales y la interacción avanzada entre usuarios.

---

## 🔗 Puntos de Integración

### Comunicación entre módulos
1.  **`src/server.cpp` (P1) llamará a:**
    * `channel.cpp` → `getChannelByName()`, `addChannel()`.
    * `handle.cpp` → `handleJoin()`, `handlePrivmsg()`, etc.
    * `replies.cpp` / `errors.cpp` → Llamado a constantes y formateadores.
2.  **`src/handle.cpp` (P2) necesitará:**
    * Referencia a la instancia de `Server`.
    * Acceso a la lista de canales (`_channels`).
3.  **Dependencias de Headers:**
    * **P1:** Requiere `server.hpp`, `client.hpp`, `utils.hpp`.
    * **P2:** Requiere `channel.hpp`, `server.hpp`, `replies.hpp`, `errors.hpp`.

---

## 📂 Estructura de Carpetas Sugerida

```text
ft_irc/
├── include/
│   ├── server.hpp      # Persona 1
│   ├── client.hpp      # Persona 1
│   ├── utils.hpp       # Persona 1
│   ├── channel.hpp     # Persona 2
│   ├── handle.hpp      # Persona 2
│   ├── replies.hpp     # Persona 2
│   └── errors.hpp      # Persona 2
├── src/
│   ├── main.cpp        # Persona 1
│   ├── server.cpp      # Persona 1
│   ├── client.cpp      # Persona 1
│   ├── utils.cpp       # Persona 1
│   ├── channel.cpp     # Persona 2
│   ├── handle.cpp      # Persona 2
│   ├── replies.cpp     # Persona 2
│   ├── errors.cpp      # Persona 2
│   ├── mode.cpp        # Persona 2
│   └── operators.cpp   # Persona 2
├── Makefile
└── README.md
```

---

## 🔗 Puntos de Integración (Crucial)

Para que el proyecto encaje sin conflictos, se establecen las siguientes reglas:

1.  **Acceso a Datos:** Persona 1 (Server) debe proporcionar métodos públicos (Getters) para que Persona 2 pueda buscar clientes por Nickname o acceder al mapa de canales.
2.  **API de Comandos:** Persona 2 diseñará funciones en `handle.cpp` que reciban la instancia del servidor y el cliente que envía el comando (ej: `void handleJoin(Server &serv, Client &user, Vector params)`).
3.  **Headers:**
    * **P1** necesita incluir: `server.hpp`, `client.hpp`, `utils.hpp`.
    * **P2** necesita incluir: `channel.hpp`, `server.hpp`, `replies.hpp`, `errors.hpp`.

---

## ⚠️ Consideraciones Importantes
### Para Persona 1
    Implementar la clase Server con atributos clave: _clients, _channels, _socket_fd, _epoll_fd.

    Proveer getters para que Persona 2 acceda a la lista de canales y clientes.

### Para Persona 2
    Debe diseñar una API limpia en handle.cpp que sea fácil de invocar desde el bucle principal del servidor.

**Asegurar** que las respuestas cumplan estrictamente con el formato del protocolo IRC (RFC).

---

## 🚀 Cronograma de Ejecución

### Fase 1: Cimentación (Persona 1)
* Creación del socket y loop de `epoll`.
* Aceptación de múltiples clientes simultáneos.

### Fase 2: Lógica y Respuestas (Persona 2)
* Creación de la clase `Channel`.
* Estandarización de mensajes de error según el RFC.

### Fase 3: Integración y Comandos
* Persona 1 conecta los eventos de lectura con los "handlers" de Persona 2.
* Pruebas de comandos `JOIN` y `PRIVMSG`.

### Fase 4: Pulido
* Implementación de modos complejos y comandos de operador.
* Pruebas con clientes reales (WeeChat, HexChat).

---

## 💡 Ventajas de esta división
* **Paralelismo:** Ambos pueden programar al mismo tiempo con pocos conflictos de Git.
* **Modularidad:** La lógica de red está separada de la lógica de "juego" (canales).
* **Balance:** La carga de trabajo es equitativa en cuanto a complejidad técnica y líneas de código.
