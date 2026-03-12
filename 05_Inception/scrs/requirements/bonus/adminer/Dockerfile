FROM debian:bookworm

# install prerequisites
# https://wordpress.com/support/php-environment/
RUN apt-get update && apt-get install -y \
    php8.2-fpm \
    php8.2-mysql \
    php8.2-curl \
    php8.2-gd \
    php8.2-intl \
    php8.2-mbstring \
    php8.2-xml \
    php8.2-zip \
    php8.2-redis \
    mariadb-client \
    wget \
    curl

#RUN the adminer part, create html directory, move the adminer directory and add user
WORKDIR /var/www/html/
RUN mkdir -p adminer
RUN wget "https://www.adminer.org/latest.php" -O /var/www/html/adminer/index.php
RUN echo "Ya he descargado adminer"

COPY /conf/www.conf /etc/php8.2/php-fpm.d/www.conf


EXPOSE 8080
STOPSIGNAL SIGQUIT

CMD ["php-fpm8.2", "--nodaemonize"]