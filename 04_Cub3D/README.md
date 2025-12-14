# Cub3D

[![Build Status](https://img.shields.io/badge/status-working-green)](https://img.shields.io/badge/status-working-green)

## 🚀 Descripción

El proyecto Cub3D es una recreación en 3D de un laberinto desde una perspectiva en primera persona, inspirándose en el juego Wolfenstein 3D [2]. El objetivo es aplicar conceptos matemáticos y algoritmos para crear una representación gráfica "realista" del interior de un laberinto [2].

## 📖 Índice

1.  [Introducción](#-introducción)
2.  [Requisitos](#-requisitos)
3.  [Instalación](#-instalación)
4.  [Uso](#-uso)
5.  [Compilación](#-compilación)
6.  [Objetivos del Proyecto](#-objetivos-del-proyecto)
7.  [Limitaciones y Desafíos](#-limitaciones-y-desafíos)
8.  [Documentación](#-documentación)
9.  [Créditos](#-créditos)

## 🚀 Introducción

Este proyecto busca replicar la experiencia de un juego tipo Wolfenstein 3D utilizando el principio de ray-casting [2].  Se pretende aplicar el algoritmo Digital Differential Analyzer (DDA) para el cálculo de intersecciones de rayos con las paredes del mapa [3].

## 🎯 Requisitos

*   Entorno de desarrollo C
*   Biblioteca miniLibX (ya sea la versión del sistema operativo o compilada desde la fuente)
*   Biblioteca libft (proporcionada)
*   Conocimientos básicos de programación en C

## 🛠️ Instalación

1.  Clonar el repositorio:
    ```bash
    git clone --recursive https://github.com/tu_usuario/cub3D.git
    ```
2.  Instalar las dependencias (si es necesario, dependiendo de cómo se gestione libft y miniLibX).  Consultar la documentación de libft y miniLibX para obtener instrucciones específicas.

## 💻 Uso

Para ejecutar el programa, simplemente compila el código y ejecuta el ejecutable generado.
```bash
./cub3D [archivo_mapa.cub]
```

## ⚙️ Compilación

Para compilar el proyecto:

```bash
make
```

Para ejecutar el programa compilado:
```bash
./cub3d
```

## 🎯 Objetivos del Proyecto

*   Aplicar conceptos de rigor, uso de C y algoritmos básicos [2].
*   Mejorar habilidades en ventanas, colores, eventos y manejo de gráficos [2].
*   Experimentar con aplicaciones prácticas de la matemática [2].
*   Implementar el algoritmo Digital Differential Analyzer (DDA) [3].

## 🚧 Limitaciones y Desafíos

*   Uso obligatorio de la biblioteca miniLibX [2].
*   Gestión fluida de la ventana (cambios, minimización) [2].

## 📚 Documentación

Para una documentación más detallada, consulta el código fuente y los archivos de encabezado.

## 🤝 Créditos

*   [Enlace al juego original](http://users.atw.hu/wolf3d/)

## 🧑‍💻Autor

Este proyecto fue desarrollado como parte del currículo del nivel 4 de la escuela 42.
Nombre: Juan Jesús Marquez
GitHub: https://github.com/elWare
42 Profile: https://profile-v3.intra.42.fr/users/jumarque
