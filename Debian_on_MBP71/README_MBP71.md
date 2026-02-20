Aquí tienes un archivo `README.md` profesional y bien estructurado para que lo subas a tu repositorio de GitHub. Está diseñado para ser la guía definitiva para cualquiera que rescate un MacBook Pro 7,1.

---

```markdown
# Debian 13 (Trixie) en MacBook Pro 7,1 (Mid-2010) 🐧💻

Este repositorio contiene una guía completa de post-instalación para configurar **Debian 13** en un **MacBook Pro 7,1** (13 pulgadas, Mid-2010). El objetivo es lograr un sistema estable, optimizado para el desarrollo de software y totalmente compatible con los estándares de **École 42**.

---

## 🚀 1. Repositorios Iniciales
Para instalar controladores propietarios (Wi-Fi, Firmware), primero activa los repositorios `non-free`.

1. Edita `/etc/apt/sources.list`:
   ```bash
   sudo nano /etc/apt/sources.list

```

2. Asegúrate de que las líneas incluyan: `main contrib non-free non-free-firmware`.
3. Actualiza el sistema:
```bash
sudo apt update && sudo apt upgrade -y

```



---

## 🔧 2. Hardware y Drivers

### 📶 Wi-Fi (Broadcom BCM4322)

Instala el controlador `wl` (propietario):

```bash
sudo apt install linux-headers-$(uname -r) broadcom-sta-dkms
sudo modprobe -r b44 b43 b43legacy ssb brcmsmac bcma
sudo modprobe wl

```

### ❄️ Control del Ventilador (mbpfan)

Evita el sobrecalentamiento gestionando las RPM de forma inteligente:

```bash
sudo apt install mbpfan
sudo systemctl enable mbpfan
sudo systemctl start mbpfan

```

### 🖱️ Touchpad (Gestos y Clic)

Para una sensación "macOS" con desplazamiento natural y clic derecho con dos dedos:

```bash
sudo apt install xserver-xorg-input-libinput touchegg
sudo systemctl enable --now touchegg

```

*Tip: Configura el "Desplazamiento Natural" en los ajustes de Ratón/Panel Táctil de tu entorno de escritorio.*

---

## 🛠️ 3. Entorno de Desarrollo (Estilo École 42)

Todo lo necesario para superar la **Piscine** y el **Common Core**.

### Herramientas Core y Compilación

```bash
sudo apt install build-essential valgrind gdb lldb clang zsh git

```

### Librerías para Proyectos Gráficos (MLX)

Indispensables para proyectos como *so_long*, *FdF* o *fract-ol*:

```bash
sudo apt install libx11-dev libxext-dev libbsd-dev

```

### Software de Apoyo

* **Norminette:** `python3 -m pip install norminette`
* **Docker:** Para proyectos como *Inception*.
```bash
sudo apt install docker.io docker-compose

```



---

## ⌨️ 4. Atajos y Teclado

Para controlar la retroiluminación del teclado:

```bash
sudo apt install light brightd

```

### Header de 42

Si usas **VS Code**, instala la extensión `42 Header` y configura tu login:

1. `Ctrl + Shift + P` -> "42 Header: Settings"
2. Define tu `User` y `Email`.
3. Inserta el header con `Ctrl + Alt + H`.

---

## 📝 Notas Adicionales

* **Gráficos:** El MacBook 7,1 usa la **NVIDIA GeForce 320M**. El driver libre `nouveau` funciona bien en Debian 13, pero si necesitas el driver privativo `nvidia-340xx`, ten en cuenta que es "legacy" y requiere parches para kernels modernos.
* **Audio:** Si el micrófono interno no funciona, añade `options snd-hda-intel model=mbp71` a `/etc/modprobe.d/alsa-base.conf`.

---

*Guía creada para la comunidad de 42 y entusiastas de Linux en hardware antiguo.* 🚀

```

---

### ¿Qué te parece este README?
Si quieres que añada algo específico de tu campus (como algún script de limpieza de memoria que uséis), dímelo y lo incluimos. **¿Te gustaría que te explique cómo subir esto a GitHub paso a paso?**

```