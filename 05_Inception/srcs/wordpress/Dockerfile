# Dockerfile
FROM debian:trixie
<<<<<<< HEAD
RUN	apt update && apt install -y php-fpm php-mysql curl mariadb-client
=======
RUN	apt update && apt install -y php8.4-fpm php8.4-mysql curl mariadb-client
>>>>>>> 666bc0c326c271723244ef48d687f7537587e2f3

RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x wp-cli.phar && \
    mv wp-cli.phar /usr/local/bin/wp

<<<<<<< HEAD
COPY	conf/www.conf /etc/php/fpm/pool.d/www.conf
COPY	tools/wp.sh /usr/local/bin/wp.sh
=======
#COPY	conf/www.conf /etc/php/fpm/pool.d/www.conf
#COPY	tools/wp.sh /usr/local/bin/wp.sh
>>>>>>> 666bc0c326c271723244ef48d687f7537587e2f3

#RUN chmod +x /usr/local/bin/wp.sh

EXPOSE 8080
