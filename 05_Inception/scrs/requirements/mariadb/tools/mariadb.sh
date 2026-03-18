#!/bin/sh

# 1. Inicializar si está vacío
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing MariaDB data directory..."
    mysql_install_db --user=mysql --datadir=/var/lib/mysql --skip-test-db
fi

# 2. Arrancar en modo seguro para configurar
echo "Starting MariaDB in safe mode..."
/usr/sbin/mysqld --user=mysql --datadir=/var/lib/mysql --skip-grant-tables --skip-networking &
PID=$!

# Esperar al socket (importante)
until mysqladmin ping --silent; do
    sleep 1
done

# 3. Aplicar configuraciones
mysql -u root << _EOF_
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';
CREATE DATABASE IF NOT EXISTS \`$MYSQL_DATABASE\`;
CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';
GRANT ALL PRIVILEGES ON \`$MYSQL_DATABASE\`.* TO '$MYSQL_USER'@'%';
FLUSH PRIVILEGES;
_EOF_

# 4. Apagar proceso temporal CON FUERZA
kill -s TERM "$PID"
wait "$PID"

# 5. EJECUCIÓN FINAL (Aquí es donde estaba el fallo)
echo "Starting MariaDB normally..."
exec /usr/sbin/mysqld --user=mysql --datadir=/var/lib/mysql --bind-address=0.0.0.0
