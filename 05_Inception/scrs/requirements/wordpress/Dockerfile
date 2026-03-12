FROM debian:bookworm

RUN apt-get update && apt-get -y install wget curl bash php php-cgi php-mysql php-fpm php-pdo php-gd php-cli php-mbstring redis	php-redis mariadb-client && rm -rf /var/lib/apt/lists/*

# I need to install wp_cli command and put it in the right directory /usr/local/bin
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
  && chmod +x wp-cli.phar \
  && mv wp-cli.phar /usr/local/bin/wp

# Copy the .conf in the html directory
COPY ./conf/www.conf /etc/php/8.2/fpm/pool.d/

#Create the folder to enable php start
RUN mkdir -p /run/php

#we copy the script, give the right to launch it in local on our computer
COPY ./tools/create_wordpress.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/create_wordpress.sh
ENTRYPOINT ["/usr/local/bin/create_wordpress.sh"]

#We go the html directory
WORKDIR /var/www/html/
RUN mkdir -p /var/www/html/adminer
RUN chown -R www-data:www-data /var/www/html
RUN chmod -R 755 /var/www/html

#We expose the 9000 port
EXPOSE 9000

#Launch PHP FPM in foreground and ignore deamonize from conf file (-F)
CMD ["/usr/sbin/php-fpm8.2", "-F"]

