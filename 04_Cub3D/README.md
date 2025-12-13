# Cub3D

Proyecto obligatorio del nivel 4 de 42. Implementación de un motor de renderizado 3D en primera persona utilizando el algoritmo de raycasting y la biblioteca miniLibX.

## Características

- Representación 3D realista del interior de un laberinto desde una perspectiva en primera persona
- Movimiento del jugador con las teclas W, A, S, D
- Rotación de la vista con las flechas izquierda y derecha
- Cierre del programa con ESC o haciendo clic en la cruz roja
- Configuración de colores para el suelo y el techo
- Carga de mapas desde archivos con extensión .cub

## Requisitos

- Sistema operativo Linux
- miniLibX
- Biblioteca math (-lm)
- Funciones de sistema: open, close, read, write, printf, malloc, free, perror, strerror, exit, gettimeofday

## Instalación

```bash
git clone --recursive https://github.com/tu_usuario/cub3D.git
cd cub3D
make
./cub3D map.cub
```

## Controles

- W, A, S, D: Movimiento
- Flechas izquierda/derecha: Rotación de vista
- ESC: Cerrar programa
- Click en la cruz roja: Cerrar programa

## Estructura del Proyecto

- Implementación del algoritmo de raycasting
- Gestión de ventanas y eventos con miniLibX
- Manejo de mapas y archivos de configuración
- Renderizado 3D con proyección de rayos

## 🧑‍💻Autor

Este proyecto fue desarrollado como parte del currículo del nivel 4 de la escuela 42.
Nombre: Juan Jesús Marquez
GitHub: https://github.com/elWare
42 Profile: https://profile-v3.intra.42.fr/users/jumarque
