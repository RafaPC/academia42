service php7.3-fpm start
service mysql start
mysql -u root << MYSQL_SCRIPT
CREATE DATABASE IF NOT EXISTS wordpress;
CREATE USER 'wordpress'@'localhost' IDENTIFIED BY 'password';
GRANT ALL PRIVILEGES ON wordpress.* TO 'wordpress'@'localhost';
FLUSH PRIVILEGES;
MYSQL_SCRIPT
mysql wordpress -u wordpress -ppassword < /wordpress.sql
rm /wordpress.sql
nginx -g 'daemon off;'