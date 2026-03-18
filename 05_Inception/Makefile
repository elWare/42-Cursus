all:
	@docker compose -f ./scrs/docker-compose.yml up -d --build

down:
	@docker compose -f ./scrs/docker-compose.yml down

re:
	@docker compose -f scrs/docker-compose.yml up -d --build

clean:
	@docker compose -f ./scrs/docker-compose.yml down --volumes --rmi all
	@docker system prune -a --force
	@# Solo borramos si existen para evitar errores de sintaxis
	@if [ -n "$$(docker ps -qa)" ]; then docker stop $$(docker ps -qa); docker rm $$(docker ps -qa); fi
	@if [ -n "$$(docker images -qa)" ]; then docker rmi -f $$(docker images -qa); fi
	@if [ -n "$$(docker volume ls -q)" ]; then docker volume rm $$(docker volume ls -q); fi
	@# Borrar solo redes personalizadas
	@if [ -n "$$(docker network ls --filter "type=custom" -q)" ]; then \
		docker network rm $$(docker network ls --filter "type=custom" -q); \
	fi
	@sudo rm -rf data/mysql/*
	@sudo rm -rf data/wordpress/*
	@sudo rm -rf data/ollama/*

.PHONY: all re down clean
