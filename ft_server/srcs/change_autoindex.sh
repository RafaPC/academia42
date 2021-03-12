#!/bin/bash

read -p "Set autoindex to on/off: " ANSWER
if [ "$ANSWER" = "on" ]; then
        cp /server_confs/ft_server_autoindex_on /etc/nginx/sites-available/ft_server
		service nginx reload
elif [ "$ANSWER" = 'off' ]; then
        cp /server_confs/ft_server_autoindex_off /etc/nginx/sites-available/ft_server
		service nginx reload
else
        echo 'Wrong input'
fi