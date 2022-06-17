FROM debian:buster

RUN groupadd -r mysql && useradd -r -g mysql mysql

RUN apt update
RUN apt install -y mariadb-server

RUN rm -rf /var/lib/mysql && mkdir -p /var/lib/mysql /var/run/mysqld \
&& chown -R mysql:mysql /var/lib/mysql /var/run/mysqld \
&& chmod 1777 /var/run/mysqld /var/lib/mysql

COPY conf/entrypoint.sh /

EXPOSE 3306

ENTRYPOINT ["sh", "/entrypoint.sh"]