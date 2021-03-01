#!/bin/bash

# check if nginx already started, if yes make changes and reload, 
# if not (first attempt -> during building the container) just copy files


if [ "$AUTOINDEX" = "on" ]
        then cp /ft_server_confs/server_autoindex_on /etc/nginx/sites-available/ft_server
        else cp /ft_server_confs/server_autoindex_off /etc/nginx/sites-available/ft_server
fi
if (( $(ps -ef | grep nginx | wc -l) > 0 ))
        service nginx reload
fi