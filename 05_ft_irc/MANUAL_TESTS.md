# Manual de Tests — ft_irc

> Suite completa de pruebas para verificar el correcto funcionamiento, robustez y ausencia de fugas de memoria del servidor IRC.

---

## Índice

1. [Estructura de ficheros](#1-estructura-de-ficheros)
2. [Requisitos previos](#2-requisitos-previos)
3. [Configuración inicial](#3-configuración-inicial)
4. [test\_00\_interactive.py — Tester interactivo IRC](#4-test_00_interactivepy--tester-interactivo-irc)
5. [test\_01\_broken.py — Pruebas de borde y seguridad](#5-test_01_brokenpy--pruebas-de-borde-y-seguridad)
6. [test\_02\_overbooking.py — Estrés masivo de conexiones](#6-test_02_overbookingpy--estrés-masivo-de-conexiones)
7. [test\_03\_normal.py — Carga normal de usuarios](#7-test_03_normalpy--carga-normal-de-usuarios)
8. [test\_04\_channel.py — Flujo completo de canal](#8-test_04_channelpy--flujo-completo-de-canal)
9. [test\_05\_leaks.sh — Análisis de fugas de memoria](#9-test_05_leakssh--análisis-de-fugas-de-memoria)
10. [test\_06\_nc.sh — Tester con netcat (nc)](#10-test_06_ncsh--tester-con-netcat-nc)
11. [Orden de ejecución recomendado](#11-orden-de-ejecución-recomendado)
11. [Interpretación de resultados](#11-interpretación-de-resultados)
12. [Problemas frecuentes](#12-problemas-frecuentes)

---

## 1. Estructura de ficheros

```
ft_irc/
├── ircserv                      ← binario compilado del servidor
├── conf/
│   ├── replace.conf             ← sustituciones de variables
│   ├── connect.conf             ← comandos al conectar
│   ├── after-connect.conf       ← comandos tras conectar
│   ├── loop.conf                ← comandos en bucle
│   └── disconnect.conf          ← comandos al desconectar
├── test_00_interactive.py
├── test_01_broken.py
├── test_02_overbooking.py
├── test_03_normal.py
├── test_04_channel.py
├── test_05_leaks.sh
├── test_06_nc.sh
└── valgrind_logs/               ← generado automáticamente por test_05
    ├── valgrind_TIMESTAMP.log
    └── summary_TIMESTAMP.log
```

---

## 2. Requisitos previos

| Herramienta | Versión mínima | Instalación |
|-------------|---------------|-------------|
| Python 3    | 3.9+          | `sudo apt install python3` |
| Valgrind    | 3.18+         | `sudo apt install valgrind` |
| ss / netstat | cualquiera   | incluido en `iproute2` |

Verificar que están disponibles:

```bash
python3 --version
valgrind --version
```

El servidor debe estar **compilado** antes de ejecutar cualquier test:

```bash
make
```

---

## 3. Configuración inicial

Todos los tests que usan `test_00_interactive.py` leen el directorio `./conf/`. Revisar que los valores coincidan con los del servidor antes de lanzar:

**`conf/replace.conf`**
```
<password>  test123        # debe coincidir con el arranque del servidor
<nick>      client
<channel>   #Bienvenidos
```

**`conf/connect.conf`**
```
PASS <password>
NICK <nick>{2}
USER <nick>{2} 0 * :Bot de prueba {2}
```

**`conf/after-connect.conf`**
```
JOIN <channel>
[800]
PRIVMSG <channel> :¡Hola! Soy <nick>{2} y acabo de unirme al canal 👋
```

**`conf/loop.conf`**
```
PRIVMSG <channel> :{MSG}
```

**`conf/disconnect.conf`**
```
PRIVMSG <channel> :Hasta luego desde <nick>{2}! 👋
PART <channel> :Cerrando conexión
QUIT :Adiós desde <nick>{2}
```

---

## 4. test\_00\_interactive.py — Tester interactivo IRC

### Propósito

Simula múltiples clientes IRC reales que se conectan, se registran, se unen a `#Bienvenidos` y envían mensajes aleatorios en bucle. Es el test de funcionamiento general y el motor interno que usa `test_05_leaks.sh`.

### Arranque del servidor

```bash
./ircserv 6667 test123
```

### Uso

```bash
# Forma básica: 5 clientes persistentes
python3 test_00_interactive.py 5 127.0.0.1 6667 --password test123

# Modo reconnect: cada cliente conecta, envía y desconecta en bucle
python3 test_00_interactive.py 5 127.0.0.1 6667 --password test123 --reconnect
```

### Parámetros

| Parámetro | Descripción |
|-----------|-------------|
| `<num_clients>` | Número de clientes simultáneos a lanzar |
| `<server_ip>` | IP del servidor (normalmente `127.0.0.1`) |
| `<port>` | Puerto del servidor |
| `--password <pass>` | Contraseña del servidor (sobreescribe `replace.conf`) |
| `--reconnect` | Activa el modo conectar → enviar → desconectar → repetir |

### Variables especiales en los `.conf`

| Variable | Se reemplaza por |
|----------|-----------------|
| `{0}` | IP del servidor |
| `{1}` | Puerto |
| `{2}` | ID del cliente (0 … n-1) |
| `{3}` | Intervalo aleatorio del cliente (3–60 s) |
| `{4}` | Número de file descriptor del socket |
| `{MSG}` | Mensaje aleatorio del pool interno |
| `[1000]` | Pausa de 1000 ms antes del siguiente comando |

### Qué observar

- Que todos los clientes completan el registro (`NICK` + `USER` + `PASS`).
- Que los mensajes llegan a `#Bienvenidos` sin errores en el log del servidor.
- Que al hacer Ctrl+C los clientes envían `QUIT` limpiamente.

### Detener

```
Ctrl+C
```

---

## 5. test\_01\_broken.py — Pruebas de borde y seguridad

### Propósito

Verifica que el servidor maneja correctamente entradas malformadas, inyecciones de protocolo y condiciones límite sin crashear ni comportarse de forma inesperada.

### Arranque del servidor

```bash
./ircserv 6667 test123
```

### Uso

```bash
python3 test_01_broken.py
```

No acepta parámetros. El servidor y puerto están definidos en las primeras líneas del script. Si usas un puerto diferente, edítalas:

```python
SERVER = "127.0.0.1"
PORT   = 6667
PASS   = "test123"
```

### Pruebas que ejecuta

| Test | Qué hace | Comportamiento esperado |
|------|----------|------------------------|
| **1 — Buffer overflow** | Envía un `NICK` de 10.000 caracteres y un `USER` de 5.000 | El servidor trunca o rechaza; no crashea |
| **2 — Inyección de protocolo** | Inserta `\n` dentro de un parámetro para colar comandos extra y envía bytes nulos `\x00` | El servidor ignora o rechaza sin procesar los comandos inyectados |
| **3 — Bypass de registro** | Envía `JOIN`, `TOPIC` y `KICK` sin haberse registrado antes | El servidor responde con `ERR_NOTREGISTERED (451)` |
| **4 — Stress de canales** | Un cliente crea 50 canales distintos y envía mensajes a todos | El servidor los gestiona sin agotar recursos |
| **5 — Fuzzing de parámetros** | Envía comandos con parámetros incorrectos: límites negativos, parámetros ausentes, canales inexistentes | El servidor responde con el código de error IRC correcto en cada caso |

### Qué observar

- El servidor sigue respondiendo tras todas las pruebas (`ping` con un cliente IRC normal).
- El uso de CPU y RAM permanece estable.
- El log del servidor muestra los errores gestionados, no un crash.

---

## 6. test\_02\_overbooking.py — Estrés masivo de conexiones

### Propósito

Abre 500 conexiones simultáneas para detectar límites del servidor: agotamiento de file descriptors, degradación del rendimiento del `poll()`, gestión del broadcast masivo en `#Bienvenidos` y fugas de memoria por ciclos rápidos de conexión/desconexión.

### Arranque del servidor

```bash
./ircserv 6667 test123
```

### Uso

```bash
python3 test_02_overbooking.py
```

El número de clientes y los parámetros de conexión están en las primeras líneas:

```python
SERVER      = "127.0.0.1"
PORT        = 6667
PASS        = "test123"
NUM_CLIENTS = 500          # ajustar según la capacidad del sistema
```

### Qué hace cada cliente

1. Se conecta y completa el registro (`PASS` + `NICK` + `USER`).
2. Se une a `#Bienvenidos` (broadcast a todos los demás).
3. Se une a un canal privado aleatorio entre `#canal_privado_1` y `#canal_privado_20`.
4. Envía 10 mensajes a `#Bienvenidos` con pausa de 0,5 s entre cada uno.
5. Envía `QUIT` y cierra el socket.

### Qué observar

- Cuántas conexiones acepta el servidor antes de empezar a rechazar (límite de FDs del proceso).
- Que no hay **memory leaks** acumulativos tras cada ciclo de conexión/desconexión.
- Que el servidor sigue respondiendo al finalizar el test.

### Nota sobre el límite del sistema

El límite por defecto de FDs por proceso en Linux es 1024. Para subir el límite temporalmente:

```bash
ulimit -n 4096
./ircserv 6667 test123
```

---

## 7. test\_03\_normal.py — Carga normal de usuarios

### Propósito

Simula un uso real del servidor: 50 usuarios se conectan en ráfaga, se unen a `#Bienvenidos`, permanecen conectados 5 segundos recibiendo todos los `JOIN` de los demás (lo que fuerza al servidor a gestionar `POLLOUT` en todos los sockets simultáneamente) y luego salen ordenadamente con `QUIT`.

### Arranque del servidor

```bash
./ircserv 6667 test123
```

### Uso

```bash
python3 test_03_normal.py
```

Parámetros en las primeras líneas:

```python
SERVER   = "127.0.0.1"
PORT     = 6667
PASSWORD = "test123"
CHANNEL  = "#Bienvenidos"
NUM_USERS = 50
```

### Flujo de cada usuario

```
Conectar → PASS → NICK → USER → esperar 0.2s → JOIN #Bienvenidos → esperar 5s → QUIT
```

### Qué observar

- Que todos los `JOIN` se propagan correctamente a todos los miembros del canal.
- Que el servidor gestiona el pico de `POLLOUT` sin descartar mensajes.
- Que todos los clientes reciben `[OK] UserN finalizado.` al terminar.
- Que el servidor no muestra errores en su salida estándar.

---

## 8. test\_04\_channel.py — Flujo completo de canal

### Propósito

Prueba el ciclo completo de gestión de canal con dos clientes (`UserA` operador y `UserB` invitado), verificando que todos los comandos de canal funcionan en el orden y con los permisos correctos.

### Arranque del servidor

```bash
./ircserv 6667 test123
```

### Uso

```bash
python3 test_04_channel.py
```

### Secuencia de acciones

```
UserA (operador)                          UserB (invitado)
─────────────────────────────────────     ────────────────────────────────────
PASS / NICK UserA / USER                  PASS / NICK UserB / USER
JOIN #Sala42  ← crea el canal
TOPIC #Sala42 :Bienvenidos a la prueba
MODE #Sala42 +i  ← modo invitación        JOIN #Sala42  ← debe fallar (ERR_INVITEONLYCHAN)
espera 2s
INVITE UserB #Sala42                      recibe INVITE → JOIN #Sala42  ← ahora entra
PRIVMSG UserB :Hola...                    PRIVMSG #Sala42 :Gracias!
                                          TOPIC #Sala42 :Hackeado  ← debe fallar (sin permisos)
espera 3s
KICK #Sala42 UserB :Prueba terminada      (es expulsado)
QUIT
```

### Qué verificar

| Acción | Respuesta esperada del servidor |
|--------|--------------------------------|
| `JOIN #Sala42` sin invitación | `473 ERR_INVITEONLYCHAN` |
| `JOIN #Sala42` tras `INVITE` | Entra correctamente, todos reciben el `JOIN` |
| `TOPIC` sin ser operador | `482 ERR_CHANOPRIVSNEEDED` (si `+t` activo) |
| `KICK` por el operador | `UserB` recibe el `KICK` y sale del canal |

---

## 9. test\_05\_leaks.sh — Análisis de fugas de memoria

### Propósito

Arranca el servidor bajo **Valgrind Memcheck**, ejecuta tres fases de carga usando `test_00_interactive.py`, para el servidor limpiamente y genera un informe detallado de fugas de memoria, errores de acceso y file descriptors sin cerrar.

### Requisitos adicionales

- `valgrind` instalado (`sudo apt install valgrind`).
- `test_00_interactive.py` y `./conf/` en el mismo directorio que el script.
- El binario del servidor compilado **con símbolos de depuración** para obtener trazas de pila completas:

```bash
# Añadir al Makefile:
CXXFLAGS += -g
make re
```

### Uso

```bash
chmod +x test_05_leaks.sh
./test_05_leaks.sh <binario> <puerto> <password> [num_clientes]

# Ejemplo con valores por defecto:
./test_05_leaks.sh ./ircserv 6667 test123 10
```

### Fases del test

| Fase | Modo | Clientes | Duración | Objetivo |
|------|------|----------|----------|---------|
| 1 | Persistente (loop de mensajes) | `NUM_CLIENTS` | 15 s | Detectar leaks en conexiones largas |
| 2 | Reconnect (conecta → envía → desconecta) | `NUM_CLIENTS` | 15 s | Detectar leaks en ciclos de conexión |
| 3 | Stress (reconnect masivo) | `NUM_CLIENTS × 3` | 20 s | Detectar leaks bajo carga alta |

Duración total aproximada: **~55 segundos** más el tiempo de arranque.

### Ficheros generados

Los informes se guardan automáticamente en `./valgrind_logs/`:

| Fichero | Contenido |
|---------|-----------|
| `valgrind_TIMESTAMP.log` | Log completo de Valgrind con todas las trazas de pila |
| `summary_TIMESTAMP.log` | Resumen legible con el veredicto final |

### Secciones del informe

**Heap Summary** — memoria en uso al salir:
```
in use at exit: 0 bytes in 0 blocks   ← perfecto
total heap usage: 11,344 allocs, 11,344 frees
```

**Leak Summary** — tipos de leak:

| Categoría | Significado |
|-----------|-------------|
| `definitely lost` | Memoria perdida sin ningún puntero que apunte a ella. **Leak real.** |
| `possibly lost` | Memoria con punteros internos pero sin puntero al inicio del bloque. Generalmente leak. |
| `still reachable` | Memoria accesible al salir pero no liberada. Habitual en singletons o variables globales. Aceptable. |
| `indirectly lost` | Perdida porque un bloque `definitely lost` la referenciaba. |

**File Descriptors** — clasificación de FDs abiertos al salir:

| Tipo | Severidad | Explicación |
|------|-----------|-------------|
| `stdin / stdout / stderr` | Normal | FDs 0, 1, 2 siempre están abiertos |
| `Valgrind internal` | Normal | FD del propio log de Valgrind, no es tuyo |
| `TCP socket (server listen)` | ⚠ Revisar | Socket de escucha no cerrado en el destructor |
| `TCP socket (client connection)` | ✗ Leak real | Socket de cliente no cerrado al desconectarse |
| `Pipe / Unix socket` | ✗ Leak real | Recursos no liberados |

**Verdict** — resumen final con código de color:

```
[ OK ] Definitely lost : 0 bytes
[ OK ] Possibly lost   : 0 bytes
[ OK ] Still reachable : 0 bytes
[ OK ] FD leaks        : none (FD reported is Valgrind's own log file — harmless)
[ OK ] Memory errors   : none

  ✓ No memory leaks or errors detected.
```

---

## 10. test\_06\_nc.sh — Tester con netcat (nc)

### Propósito

Verifica el funcionamiento básico del servidor IRC usando **netcat (nc)** como cliente ligero sin dependencias de Python. Prueba todos los comandos IRC fundamentales: registro, join, privmsg, topic, mode, invite, kick, part, quit, ping/pong y comportamiento con entradas malformadas.

### Requisitos

- `netcat-openbsd` instalado: `sudo apt install netcat-openbsd`
- El servidor debe estar escuchando en el puerto configurado (por defecto 7777)

### Arranque del servidor

```bash
./ircserv 7777 test123
```

### Uso

```bash
chmod +x test_06_nc.sh
./test_06_nc.sh
```

No acepta parámetros. Los valores de servidor (IP, puerto, contraseña) están en las primeras líneas del script.

### Tests que ejecuta

| Nº | Test | Comando(s) | Respuesta esperada |
|----|------|-------------|---------------------|
| 1 | Registro básico | `PASS` + `NICK` + `USER` → `JOIN` | `001` RPL_WELCOME |
| 2 | Contraseña incorrecta | `PASS` mal | `464 ERR_PASSWDMISMATCH` |
| 3 | Comando antes de registro | `JOIN` sin registrarse | `451 ERR_NOTREGISTERED` |
| 4 | JOIN a canal | `JOIN #bienvenidos` | Echo del servidor con `JOIN` |
| 5 | PRIVMSG a canal | `PRIVMSG #bienvenidos :mensaje` | Echo del mensaje |
| 6 | TOPIC | `TOPIC #canal :tema` → `TOPIC #canal` | `332` RPL_TOPIC o echo |
| 7 | MODE +i | `MODE #canal +i` | Echo con `MODE` |
| 8 | MODE +k (clave) | `MODE #canal +k clave123` | Echo con `MODE` |
| 9 | MODE +l (límite usuarios) | `MODE #canal +l 10` | Echo con `MODE` |
| 10 | PART | `PART #canal :motivo` | Echo con `PART` |
| 11 | KICK sin permisos → 482 | `KICK #canal usuario` sin ser operador | `482 ERR_CHANOPRIVSNEEDED` |
| 12 | INVITE | `INVITE usuario #canal` | `341 RPL_INVITING` |
| 13 | PING | `PING :token` | `PONG` |
| 14 | Comando desconocido | `COMANDOFALSO` | `421 ERR_UNKNOWNCOMMAND` |
| 15 | Cambio de NICK | `NICK NuevoNick` | Echo con `NICK` |
| 16 | NICK oversized | `NICK` con 600 caracteres | Maneja sin crash (echo o `432`) |
| 17 | PRIVMSG a usuario inexiste | `PRIVMSG UsuarioFantasma` | `401 ERR_NOSUCHNICK` |
| 18 | KICK sin parámetros | `KICK #canal` | `461 ERR_NEEDMOREPARAMS` |

### Mécanismo de test

Cada `run_test` ejecuta una secuencia de comandos separados por `\n` y usa `timeout` para evitar colgues eternos (el servidor no cierra el socket tras `QUIT`, así que `nc` podría colgarse si no hay timeout).

```bash
response=$(printf "%s\n" "${cmds[@]}" | timeout ${NC_TIMEOUT}s nc "$SERVER" "$PORT" 2>&1)
if echo "$response" | grep -q "$expect"; then
    ok "$label"
else
    fail "$label"
fi
```

### Variables especiales

| Variable | Valor por defecto |
|----------|-------------------|
| `SERVER` | `127.0.0.1` |
| `PORT`   | `7777` |
| `PASS`   | `test123` |
| `DELAY`  | `0.4` segundos |
| `NC_TIMEOUT` | `3` segundos |

### Qué observar

- Que cada test imprime `[  OK  ]` o `[ FAIL ]` según la respuesta del servidor.
- En los fallos, ver el **"Server response:"** para comparar con lo esperado.
- El test 11 (KICK) y el 12 (INVITE) espían a un cliente "víctima" o "invitado" en segundo plano.
- El test 16 (buffer overflow) envía un NICK de 600 caracteres para verificar robustez.

### Diferencias con test_00_interactive.py

| Característica | test_00_interactive.py | test_06_nc.sh |
|----------------|------------------------|---------------|
| Idioma | Python 3 | Bash puro |
| Cliente | Script Python con clases IRC | netcat (nc) nativo |
| Dependenecias | Python + dependencias del test | Solo `nc` del sistema |
| Modo persiste | Sí (loop de mensajes) | No (conexiones puntuales) |
| Pruebas de borde | No | Sí (buffer overflow, commands malformados) |
| Prueba KICK | Indirectamente (a través del tester) | Directo (dos nc en paralelo) |
| Prueba INVITE | Indirectamente | Directo |

---

## 11. Orden de ejecución recomendado

Seguir este orden garantiza que cada test parte de un servidor limpio y en estado conocido:

```bash
1. test_03_normal.py    → verificar que el flujo básico funciona
2. test_04_channel.py   → verificar que los comandos de canal son correctos
3. test_06_nc.sh        → verificar que todos los comandos funcionen
4. test_01_broken.py    → verificar que el servidor aguanta entradas malformadas
5. test_02_overbooking  → verificar comportamiento bajo carga extrema
6. test_05_leaks.sh     → verificar que no hay fugas de memoria
```

> Reiniciar el servidor entre cada test para partir de un estado limpio.

---

## 12. Interpretación de resultados

### Servidor sano — señales positivas

- Responde a nuevas conexiones tras cada test.
- CPU vuelve a 0% cuando no hay clientes conectados.
- No hay mensajes de error en la salida del servidor tras `test_01`.
- Valgrind reporta `0 bytes in use at exit` y `0 errors`.

### Señales de problema

| Síntoma | Causa probable | Test que lo detecta |
|---------|----------------|---------------------|
| El servidor deja de aceptar conexiones | Agotamiento de FDs | `test_02` |
| CPU al 100% sin clientes | Bucle infinito en `poll()` o `recv()` | `test_02`, `test_03` |
| `definitely lost > 0` en Valgrind | `new` sin `delete` en algún comando | `test_05` |
| `Invalid read` en Valgrind | Acceso a memoria liberada (use-after-free) | `test_05` |
| `ERR_INVITEONLYCHAN` no se devuelve | `MODE +i` no implementado correctamente | `test_04` |
| `JOIN` sin `PASS` previo no falla | `requiresRegistration()` no cubre ese comando | `test_01` |

---

## 12. Problemas frecuentes

**El puerto ya está en uso:**
```bash
# Ver qué proceso lo ocupa
ss -tlnp | grep 6667
# Matarlo
kill -9 <PID>
```

**`test_05_leaks.sh` falla en preflight:**
```bash
# Dar permisos de ejecución
chmod +x test_05_leaks.sh
# Comprobar que el binario es ejecutable
chmod +x ircserv
```

**Valgrind es muy lento:**
El servidor bajo Valgrind es entre 10x y 50x más lento que en ejecución normal. Es esperado. Los timeouts del tester están ajustados para compensarlo.

**`test_02` falla con "connection refused" a partir de cierto número:**
El sistema operativo tiene un límite de FDs por proceso. Subirlo antes de arrancar el servidor:
```bash
ulimit -n 4096
./ircserv 6667 test123
```

**Los clientes de `test_00` no se registran:**
Comprobar que `conf/replace.conf` tiene la contraseña correcta, o usar `--password`:
```bash
python3 test_00_interactive.py 5 127.0.0.1 6667 --password mipassword
```
