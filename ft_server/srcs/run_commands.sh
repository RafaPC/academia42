docker run -p 80:80 -p 443:443 -d --rm --name test ft_server2
docker exec -it test bash
docker cp srcs/wordpress/wordpress.sql test:/