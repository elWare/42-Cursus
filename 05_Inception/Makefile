# Makefile

.PHONY: all build up clean re

all: build up

build:
	@echo "Construyendo las imágenes Docker..."
	docker compose -f srcs/docker-compose.yml build --no-cache

up:
	@echo "Levantando los contenedores..."
	docker compose -f srcs/docker-compose.yml up -d

clean:
	@echo "Deteniendo y eliminando contenedores, imágenes y volúmenes..."
	docker compose -f srcs/docker-compose.yml down -v --rmi all
	rm -rf /home/${USER}/srcs/data/*

re: clean all
