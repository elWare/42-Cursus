FROM debian:bookworm

# Configuración básica
ARG DEBIAN_FRONTEND=noninteractive

# Actualizar repositorios e instalar dependencias necesarias
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        curl \
        wget \
        git \
        ca-certificates \
        openssl \
        python3 \
        python3-pip \
        libgl1-mesa-glx \
        libglib2.0-0 \
		zstd \
    && rm -rf /var/lib/apt/lists/*

# Descargar e instalar Ollama
RUN curl -fsSL https://ollama.com/install.sh | sh

# Añadir usuario no root para seguridad (opcional)
RUN useradd -m ollama && chown -R ollama:ollama /usr/local/bin /home/ollama && mkdir -p /root/.ollama && chown -R root:ollama /root

# Expor el puerto de Ollama por defecto
EXPOSE 11434

# Comandos para iniciar Ollama
ENTRYPOINT ["ollama", "serve"]
