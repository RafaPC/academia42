#!/bin/sh
if [ ! -f /var/www/wordpress/index.php ]; then

	cp -r /wordpress /var/www

	wp config create --skip-check --path="/var/www/wordpress" --dbname=$WP_DATABASE --dbuser=$MYSQL_USER --dbpass=$MYSQL_PASSWORD --dbhost="mariadb" --allow-root
	for i in {1..10}
	do
		if ! wp core install --path="/var/www/wordpress" --url="https://$DOMAIN_NAME" --title=$WP_TITLE --admin_user=$WP_ADMIN --admin_password=$WP_ADMIN_PASSWORD --admin_email=$WP_ADMIN_EMAIL --skip-email --allow-root ; then
			break 1
		fi
		sleep 3;
	done
	wp user create $WP_USER $WP_USER_EMAIL --path="/var/www/wordpress" --role=author --user_pass=$WP_USER_PASSWORD --allow-root
fi

echo "PHP FPM started on port 9000"

exec /usr/sbin/php-fpm7.3 --nodaemonize