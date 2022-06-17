FROM debian:buster

RUN apt update
RUN apt install -y php7.3-fpm php7.3-mysql

# Sets php-fpm configuration to listen on port 9000
RUN sed 's/listen = \/run\/php\/php7.3-fpm.sock/listen = 0.0.0.0:9000/' -i /etc/php/7.3/fpm/pool.d/www.conf

# ADD command
ADD conf/latest.tar.gz /
COPY conf/wp-cli.phar /
COPY conf/entrypoint.sh /

RUN mkdir --parents /var/www && chmod +x wp-cli.phar && cp wp-cli.phar usr/bin/wp

RUN cp wp-cli.phar /usr/bin/wp

EXPOSE 9000/tcp

RUN mkdir /run/php

ENTRYPOINT [ "bash", "/entrypoint.sh" ]
