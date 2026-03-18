#!/bin/sh

while ! mariadb-admin ping -h"mariadb" --silent; do
    echo "Esperando a MariaDB..."
    sleep 10
done

# Ir al directorio de trabajo
cd /var/www/html

if [ -f "/var/www/html/wp-config.php" ]
then
    echo "WordPress ya configurado. Verificando actualizaciones de DB..."
else
    echo "Configurando WordPress por primera vez..."
    
    # 2. Asegurar que WP-CLI existe (si no se puso en el Dockerfile)
    if ! command -v wp >/dev/null 2>&1; then
        wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
        chmod +x wp-cli.phar
        mv wp-cli.phar /usr/local/bin/wp
    fi

    # 3. Descargar e instalar
    wp core download --allow-root --force

    wp config create --allow-root \
        --dbname=$MYSQL_DATABASE \
        --dbuser=$MYSQL_USER \
        --dbpass=$MYSQL_PASSWORD \
        --dbhost=$MYSQL_HOSTNAME

    wp core install --allow-root \
        --url=$DOMAIN_NAME \
        --title="Inception" \
        --admin_user=$WP_ADMIN_USER \
        --admin_password=$WP_ADMIN_PASSWORD \
        --admin_email=$WP_ADMIN_EMAIL

    # 4. Segundo usuario (Requisito 42)
    wp user create $WP_USER $WP_EMAIL \
        --role=author \
        --user_pass=$WP_PASSWORD \
        --allow-root

    # 5. Forzar la última versión del tema por defecto
    wp theme install twentytwentyfour --activate --allow-root
	

    # 6. Bonus: Redis (Descomenta cuando tu contenedor Redis esté listo)
    wp plugin install redis-cache --activate --allow-root
    wp config set WP_REDIS_HOST redis --allow-root
    wp config set WP_REDIS_PORT 6379 --raw --allow-root
    wp redis enable --allow-root
	wp plugin install alpaca-bot --activate --allow-root
	wp plugin install ai-engine --activate --allow-root
	wp plugin list --allow-root
fi

# ESTO SOLUCIONA TU ERROR: Actualiza la base de datos si hay discrepancia de versión
wp core update-db --allow-root
wp theme activate twentytwentyfour --allow-root
wp config set FS_METHOD direct --allow-root
# ... (al final de tu script)
echo "WordPress listo y escuchando..."
exec php-fpm8.2 -F