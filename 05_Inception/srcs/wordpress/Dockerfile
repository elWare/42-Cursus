# Dockerfile
FROM wordpress:6.5.4-fpm-alpine
# Intenta instalar solo imagemagick. Las extensiones de PHP relacionadas
# con GD, MySQLi, Opcache y Redis a menudo ya están incluidas
# o se llaman de otra manera en la imagen oficial de WordPress FPM.
RUN apk add --no-cache imagemagick mariadb-client php-mysqlnd php-zip php-gd php-opcache php-redis  && docker-php-ext-install pdo_mysql

EXPOSE 9000
