#Define base image
FROM debian:buster

# Declare AUTOINDEX environment variable
ENV AUTOINDEX=on

#Install packages
RUN apt-get update && apt-get upgrade -y && apt-get install -y \
nginx \
mariadb-server \
php-fpm php-mysql php-mbstring php-imagick php-curl php-zip php-dom \
wget

#Copy the nginx configuration
COPY srcs/server_confs /server_confs
COPY srcs/server_confs/ft_server_autoindex_on /etc/nginx/sites-available/ft_server
#Copy the bash script for changing the autoindex
COPY srcs/change_autoindex.sh /

RUN ln -s /etc/nginx/sites-available/ft_server /etc/nginx/sites-enabled/ft_server && \
	rm -rf /etc/nginx/sites-enabled/default

#Wordpress download and setup
RUN wget https://wordpress.org/latest.tar.gz && tar -xzf latest.tar.gz && mv wordpress /var/www/html/wordpress && rm -f latest.tar.gz && \
rm -rf /var/www/html/wordpress/wp-content/plugins/* && rm -rf /var/www/html/wordpress/wp-content/themes/twentynineteen && rm -rf /var/www/html/wordpress/wp-content/themes/twentytwenty
COPY srcs/wordpress/wp-config.php /var/www/html/wordpress/
COPY srcs/wordpress/wordpress.sql /
# Copy images to uploads directory
COPY srcs/wordpress/content/* /var/www/html/wordpress/wp-content/uploads/2021/03/
#PhpMyAdmin download and setup
RUN wget https://files.phpmyadmin.net/phpMyAdmin/5.0.4/phpMyAdmin-5.0.4-english.tar.gz && \
tar -xzf phpMyAdmin-5.0.4-english.tar.gz && mv phpMyAdmin-5.0.4-english /var/www/html/phpmyadmin && rm -f phpMyAdmin-5.0.4-english.tar.gz

# CERTIFICADO PARA SSL
RUN mkdir ssl && openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes -out /etc/ssl/certs/ft_server.crt -keyout /etc/ssl/private/ft_server.key \
-subj "/C=ES/ST=Madrid/L=Madrid/O=FT_SERVER_SL/OU=IT Department/CN=www.ft_server.com"

#permisos al grupo de nginx -> www-data
RUN	chown -R www-data:www-data /var/www/html/*

#copy the file that starts the services
COPY srcs/start.sh /

#Exposes port 80
EXPOSE 80 443

#Execute .sh to start the services
CMD ["bash", "start.sh"]