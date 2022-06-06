include srcs/.env

up:
	docker-compose --env-file 'srcs/.env' --file 'srcs/docker-compose.yml' up --build --detach

down:
	docker-compose --file 'srcs/docker-compose.yml' down --timeout 2

clean:
	docker-compose --file 'srcs/docker-compose.yml' down --timeout 2
	# docker prune
	@rm -rf ${VOLUMES_PATH}
	echo "Volumes on ${VOLUMES_PATH} were removed"