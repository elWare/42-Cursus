FROM debian:Trixie

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y mariadb-server && \
    rm -rf /var/lib/apt/lists/*

# Copiamos un script de inicialización opcional (se ejecutará al inicio de la primera ejecución).
# Este script puede ser útil para crear usuarios y bases de datos iniciales.
COPY tools/setup_mariadb.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/setup_mariadb.sh

# Exponemos el puerto estándar de MariaDB
EXPOSE 3306

# Cuando se inicia el contenedor, este script será el punto de entrada.
# Se asegura de que MariaDB se inicialice y se ejecute.
ENTRYPOINT ["/usr/local/bin/setup_mariadb.sh"]
