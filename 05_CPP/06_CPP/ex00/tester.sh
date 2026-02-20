#!/bin/bash

# Colores para el output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
RESET='\033[0m'

NAME="./convert"

# Compilar el proyecto
echo -e "${YELLOW}Compilando proyecto...${RESET}"
make re > /dev/null

if [ ! -f "$NAME" ]; then
    echo -e "${RED}Error: El ejecutable '$NAME' no se ha creado.${RESET}"
    exit 1
fi

run_test() {
    echo -e "${CYAN}Prueba: $NAME \"$1\"${RESET}"
    $NAME "$1"
    echo -e "${GRAY}-----------------------------------${RESET}"
}

# 1. Pruebas de CHAR
echo -e "\n${GREEN}--- SECCIÓN: CHAR ---${RESET}"
run_test "a"
run_test "Z"
run_test "*"

# 2. Pruebas de INT
echo -e "\n${GREEN}--- SECCIÓN: INT ---${RESET}"
run_test "0"
run_test "42"
run_test "-42"
run_test "2147483647" # Max Int
run_test "-2147483648" # Min Int

# 3. Pruebas de FLOAT
echo -e "\n${GREEN}--- SECCIÓN: FLOAT ---${RESET}"
run_test "0.0f"
run_test "42.42f"
run_test "-4.2f"
run_test "nanf"
run_test "+inff"
run_test "-inff"

# 4. Pruebas de DOUBLE
echo -e "\n${GREEN}--- SECCIÓN: DOUBLE ---${RESET}"
run_test "0.0"
run_test "42.42"
run_test "3.14159"
run_test "nan"
run_test "+inf"
run_test "-inf"

# 5. Casos de ERROR y LÍMITES
echo -e "\n${GREEN}--- SECCIÓN: CASOS LÍMITE Y ERRORES ---${RESET}"
run_test "2147483648" # Int overflow (debería detectarlo ft_atoi)
run_test "hola"       # Invalid input
run_test ""           # Empty input
run_test "42.42.42f"  # Invalid float
run_test "   "        # Spaces

echo -e "${YELLOW}Tester finalizado.${RESET}"