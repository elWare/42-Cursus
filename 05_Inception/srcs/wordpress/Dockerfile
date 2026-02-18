# Dockerfile
FROM debian:trixie
RUN	apt update && apt install -y php-fpm php-mysql curl mariadb-client

RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && \
    chmod +x wp-cli.phar && \
    mv wp-cli.phar /usr/local/bin/wp

COPY	conf/www.conf /etc/php/fpm/pool.d/www.conf
COPY	tools/wp.sh /usr/local/bin/wp.sh

RUN chmod +x /usr/local/bin/wp.sh

EXPOSE 8080
