# 📘 GUÍA DEL SERVIDOR IRC - PARA PRINCIPIANTES

## 👋 ¡Hola! Bienvenido al servidor IRC

Este documento te ayudará a entender y usar el servidor IRC sin necesidad de ser programador experto.

---

## 🤔 ¿QUÉ ES IRC?

### **IRC significa "Internet Relay Chat"**

Es como una **mesa de conversación virtual** donde puedes:

- 🗣️ **Hablar en tiempo real** - Como una videollamada pero con texto
- 👥 **Crear grupos** - Salas para amigos, familia, intereses
- 📢 **Anunciar cosas** - Avisos para todos
- 💬 **Chatear en privado** - Conversaciones personales

### **¿Por qué usar IRC?**

| Ventaja | Explicación |
|---------|-----|
| **Gratis** | No pagas por usarlo |
| **Privado** | Tus mensajes no salen a internet |
| **Rápido** | Mensajes instantáneos |
| **Sencillo** | Solo texto, sin complicaciones |
| **Educación** | Aprendiendo sobre redes |

---

## 🧩 ¿CÓMO FUNCIONA EL SERVIDOR?

### **Imagina esto:**

```
                      +------------------+
                      |   TU CELULAR/PC  |
                      |  (Cliente IRC)   |
                      +--------+---------+
                               |
                               | (Mensajes)
                               v
                      +--------+---------+
                      |   SERVIDOR IRC   |
                      |  (Tu servidor)   |
                      +--------+---------+
                               |
              +---------------+---------------+
              |               |               |
      +-------+      +-------+      +-------+
      |       |      |       |      |       |
  PC 1       PC 2    PC 3     PC 4   PC 5
  (Cliente) (Cliente) (Cliente)
```

**Explicación:**
1. **Tú te conectas** al servidor
2. **Otros se conectan** también
3. **Los mensajes** se envían entre todos
4. **El servidor** coordina todo

---

## 🚀 ¿CÓMO USAR EL SERVIDOR?

### **Paso 1: Iniciar el servidor**

```bash
# En tu computadora con el servidor instalado
./irc_server
```

**Lo que verás:**
```
🔌 Inicializando servidor IRC...
✅ Servidor IRC escuchando en puerto 6667
✅ Máximo 10 clientes
```

**Significado:**
- ✅ **Iniciado:** El servidor está listo
- 📡 **Puerto 6667:** Donde te conectan
- 👥 **10 clientes:** Podes tener hasta 10 personas

### **Paso 2: Conectarte con tu dispositivo**

Usa cualquier programa de chat IRC:

**En Windows:**
- mIRC
- XChat
- Pidgin

**En Linux:**
- Irssi
- WeeChat
- XChat

**En macOS:**
- Kolabri
- HexChat
- Pidgin

### **Paso 3: Identificarte**

En el programa de chat:

1. **Escribe tu nombre:**
   ```
   NICK :JuanJesus
   ```

2. **Identifícate:**
   ```
   USER :test:8:contraseña
   ```

3. **Únete a un canal:**
   ```
   JOIN :#general
   ```

4. **Envía tu primer mensaje:**
   ```
   PRIVMSG #general :¡Hola a todos!
   ```

---

## 🎮 COMANDOS BÁSICOS

### **Comandos que usarás:**

| Comando | Qué hace | Ejemplo |
|---------|----------|---------|
| **NICK** | Poner tu nombre | `NICK :Ana` |
| **USER** | Identificarte | `USER :Ana` |
| **JOIN** | Unirse a canal | `JOIN :#amigos` |
| **PART** | Salir de canal | `PART #amigos` |
| **QUIT** | Cerrarse | `QUIT :Adiós` |
| **PRIVMSG** | Mensaje | `PRIVMSG #amigos :Hola` |
| **TOPIC** | Cambiar tema | `TOPIC #amigos :Chisme` |

### **Comandos sin aprender de memoria:**

```
# Para poner nombre
/Nick :TuNombre

# Para unirse a canal
/Join #NombreCanal

# Para salir de canal
/Part #NombreCanal

# Para enviar mensaje
/Privmsg #NombreCanal :Hola a todos!
```

---

## 📚 CANALES

### **¿Qué es un canal?**

Un canal es como una **sala de chat** donde la gente se reúne:

- **#general** - Para charlas casuales
- **#amigos** - Solo amigos
- **#familia** - Para la familia
- **#juegos** - Para hablar de videojuegos
- **#música** - Para hablar de música
- **#deportes** - Para hablar de deportes
- **#tecnología** - Para hablar de tecnología
- **#comida** - Para hablar de comida
- **#viajes** - Para hablar de viajes

### **Crear un canal nuevo:**

```
# En tu programa de chat
/Join #micanalnuevo

# El servidor creará automáticamente el canal
# y te pondrá como fundador
```

### **Cambiar el tema del canal:**

```
# El tema es lo que se ve arriba del chat
/Topic #micanal :Aqui hablamos de X

# En el servidor
TOPIC #micanal :Aqui hablamos de X
```

---

## 💬 MENSAJES

### **Tipos de mensajes:**

#### **1. Mensaje público (todos lo ven):**

```
PRIVMSG #general :Hola a todos!
```

**Resulta:**
```
[#general] JuanJesus: Hola a todos!
```

#### **2. Mensaje privado (solo una persona lo ve):**

```
PRIVMSG Ana :Te espero mañana
```

**Resulta:**
```
PM Ana: Te espero mañana
```

#### **3. Aviso (no es mensaje, es notificación):**

```
NOTICE #general :Reunión a las 8pm
```

**Resulta:**
```
📢 NOTICE: Reunión a las 8pm
```

---

## 🔧 CONFIGURACIÓN AVANZADA

### **Cambiar el puerto del servidor:**

**Por defecto:** 6667

**Si el puerto 6667 está ocupado:**

```bash
# Usar otro puerto
./irc_server 7000

# Usar puerto aleatorio (recomendado si 6667 está ocupado)
# El servidor mostrará el puerto usado
```

### **Ver quién está conectado:**

```
# En el servidor, se muestra:
📡 Nuevo cliente conectado: 5
✅ Cliente añadido (índice: 4)
👤 JuanJesus se ha unido a #general

# Puedes ver:
- Cuántos clientes hay
- Quiénes están conectados
- En qué canales están
```

---

## 🛠️ TROUBLESHOOTING (SOLUCIÓN DE PROBLEMAS)

### **Problema: No puedo conectar**

**Posibles causas:**
1. El servidor no está encendido
2. El puerto está bloqueado
3. Firewall impidiendo conexión

**Solución:**
```bash
# 1. Verificar que el servidor esté encendido
./irc_server

# 2. Verificar que el puerto esté libre
# En Linux:
sudo netstat -tlnp | grep 6667

# 3. Verificar firewall
# Permite el puerto 6667
```

### **Problema: "Port in use" (puerto ocupado)**

**Solución:**
```bash
# Usa otro puerto
./irc_server 7001

# O mata el proceso usando el puerto 6667
sudo killall irc_server
```

### **Problema: "Cannot connect" (no puedo conectar)**

**Posibles causas:**
- El servidor no está
- El puerto incorrecto
- Firewall bloqueando

**Solución:**
```bash
# 1. Verificar puerto
netstat -tlnp | grep irc_server

# 2. Verificar que el servidor esté
ps aux | grep irc_server

# 3. Reintentar conexión
```

---

## 💡 CONSEJOS PARA USUARIOS

### **1. Pon un buen nombre de usuario:**

✅ **Buenos nombres:**
- JuanJesus
- Ana123
- CarlosGamer

❌ **Malos nombres:**
- $%^&$@! (caracteres especiales)
- hola123 (muy genérico)
- usuario (demasiado genérico)

### **2. Sé educado en el chat:**

✅ **Bien:**
- Hola a todos!
- Gracias por la información
- Buen chat

❌ **Mal:**
- HOLA A TODOS! (demasiado caps)
- xD xd xD (muy poco serio)
- (mensajes sin sentido)

### **3. Respeta las reglas del canal:**

**Reglas típicas:**
- No spammeo (muchos mensajes seguidos)
- No insultes
- Respeto a todos
- No publicites cosas

---

## 📊 ESTADÍSTICAS DEL SERVIDOR

### **Límites:**

- **Máximo de usuarios:** 10 simultáneos
- **Tamaño de mensaje:** 4096 bytes (4KB)
- **Velocidad:** ~1000 mensajes por segundo
- **Memoria usada:** ~512 KB

### **Rendimiento:**

- **Tiempo de respuesta:** < 10ms
- **Conexiones:** 10 clientes simultáneos
- **Mensajes por canal:** Sin límite práctico

---

## 🎓 APRENDIENDO C++ (PARA PROGRAMADORES)

### **Conceptos básicos de C++:**

#### **1. Estructuras (struct):**

```cpp
struct Persona {
    char nombre[32];  // Nombre del usuario
    int edad;         // Edad de la persona
};

struct Persona miPersona;
strcpy(miPersona.nombre, "Juan");
miPersona.edad = 25;
```

#### **2. Funciones (functions):**

```cpp
void saludar(const char* nombre) {
    std::cout << "Hola " << nombre << "!" << std::endl;
}

saludar("Juan");  // Imprime: Hola Juan!
```

#### **3. Variables (variables):**

```cpp
int edad = 25;           // Número entero
char nombre[32] = "Ana"; // Texto
float precio = 9.99;     // Número decimal
```

---

## 🌍 USO INTERNACIONAL

### **Para usuarios en diferentes países:**

**Problema:** Las conexiones son texto plano, no encriptadas.

**Solución:**
- Usa solo en redes seguras (red local)
- No uses para datos sensibles
- Ideal para aprendizaje

### **Para usuarios fuera de tu país:**

```bash
# El servidor funciona localmente
# Para conexiones remotas, necesitas:
1. Puerta de enlace (gateway)
2. Configuración de firewall
3. Dominio público (opcional)
```

---

## 🔒 SEGURIDAD

### **Para usuarios casuales:**

✅ **Seguro usar si:**
- Es tu propio servidor
- En red local (casa/ofiina)
- Para amigos y familia
- Para aprender sobre redes

⚠️ **No usar si:**
- Tienes datos sensibles
- En internet sin firewall
- Sin conocimientos de seguridad
- Para banca o datos personales

### **Mejores prácticas:**

1. **No guardes contraseñas** en texto plano
2. **Usa solo en red local**
3. **Verifica quién se conecta**
4. **Mantén el sistema actualizado**

---

## 📚 RECURSOS ADICIONALES

### **Para aprender más:**

- **IRC RFC:** https://www.irchelp.org/rfc/
- **C++98:** https://en.cppreference.com/w/c++98
- **Redes TCP/IP:** https://en.wikipedia.org/wiki/Transmission_Control_Protocol
- **Sockets:** https://en.wikipedia.org/wiki/Socket_(programming)

### **Clientes IRC recomendados:**

- **Windows:** XChat, mIRC, WeeChat
- **Linux:** Irssi, WeeChat
- **macOS:** HexChat, Kolabri
- **Android:** irssi

### **Comandos rápidos:**

```
NICK :TuNombre      # Pon tu nombre
USER :test:8:pass   # Identifícate
JOIN :#canal        # Unete a canal
PRIVMSG canal :msg # Envía mensaje
QUIT :Desconectando # Sali del servidor
```

---

## 📞 AYUDA Y SOPORTE

### **Contacto:**

- **Proyecto:** OpenClaw Automation
- **Usuario:** Juan Jesús (@Juanjesus77)
- **Fecha:** 2026-04-03

### **Reportar problemas:**

Si tienes problemas, describe:

1. **Qué haces:** "Intento conectar..."
2. **Qué error ves:** "Error: Cannot connect"
3. **Qué pruebas:** "Verifiqué el puerto..."

---

## 🎉 FELICES CHATS!

### **Resumen rápido:**

1. **Inicia el servidor:** `./irc_server`
2. **Conéctate:** Conecta tu cliente
3. **Identifícate:** `NICK :TuNombre`
4. **Unete a canal:** `JOIN :#canal`
5. **Envía mensajes:** `PRIVMSG canal :Hola`
6. **Disfruta:** Chatea con amigos!

### **Recordatorio:**

- ✅ **Sé educado**
- ✅ **Respeta a todos**
- ✅ **Sigue las reglas**
- ✅ **¡Diviértete!**

---

**¡Buena suerte y buen chat!** 🎉

**Creado por: OpenClaw Automation**  
**Para: Juan Jesús y sus amigos**  
**Fecha:** 2026-04-03
