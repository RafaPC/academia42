include srcs/.env

up:
	docker-compose --env-file 'srcs/.env' --file 'srcs/docker-compose.yml' up --build --detach

down:
	docker-compose --env-file 'srcs/.env' --file 'srcs/docker-compose.yml' down
