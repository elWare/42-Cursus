#!/bin/sh

# Verifica si el directorio de datos de MariaDB está vacío
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Inicializando MariaDB..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql

    # Iniciar el servidor MariaDB en segundo plano
    /usr/bin/mysqld_safe --datadir='/var/lib/mysql' &
    MYSQL_PID=$!

    # Esperar a que el servidor MariaDB esté listo
    echo "Esperando a que MariaDB arranque..."
    until mysqladmin ping -hlocalhost --silent; do
        sleep 1
    done
    echo "MariaDB ha arrancado."

    # Configurar el usuario root y la base de datos
    # Las variables de entorno se pasarán desde docker-compose.yml
    mysql -hlocalhost -u root <<EOF
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF

    # Crear el usuario administrador de WordPress (nombre que no contenga "admin")
    # y el segundo usuario de WordPress.
    # Usaremos variables de entorno específicas para estos usuarios de WordPress.
    mysql -hlocalhost -u root -p"${MYSQL_ROOT_PASSWORD}" <<EOF
CREATE USER IF NOT EXISTS '${WORDPRESS_ADMIN_USER}'@'%' IDENTIFIED BY '${WORDPRESS_ADMIN_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${WORDPRESS_ADMIN_USER}'@'%';
CREATE USER IF NOT EXISTS '${WORDPRESS_USER}'@'%' IDENTIFIED BY '${WORDPRESS_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${WORDPRESS_USER}'@'%';
FLUSH PRIVILEGES;
EOF

    echo "Configuración inicial de MariaDB completada."
    kill $MYSQL_PID
    wait $MYSQL_PID
fi

# Iniciar MariaDB en primer plano para que el contenedor siga ejecutándose
exec /usr/bin/mysqld_safe --datadir='/var/lib/mysql'
