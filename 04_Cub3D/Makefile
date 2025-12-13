# ----- Makefile for Cub3D project ------------------------------------------- #

MAKEFLAGS += --no-print-directory

NAME = cub3D
NAME_BNS = cub3D_bonus

# ----- Values --------------------------------------------------------------- #

CC = gcc
RM = rm -rf

# ----- Flags -----------------------------------------------------------------#

FLAGS = -g -Wall -Werror -Wextra -Iinclude #-fsanitize=address
MLX_FLAGS = -ldl -lglfw -pthread -lm -Ofast

# ----- Librairies ----------------------------------------------------------- #

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a
MLX_PATH = ./MLX42/build
MLX = $(MLX_PATH)/libmlx42.a

# ----- Files ---------------------------------------------------------------- #

FILES =	cube3D \
					parse/ft_check_1 \
					parse/ft_check_2 \
					parse/ft_check_4 \
					parse/ft_check_5 \
					parse/ft_check_6 \
					parse/ft_parse_1 \
					parse/ft_parse_2 \
					exec/ft_action \
					exec/ft_impact_ray \
					exec/ft_moves \
					exec/ft_paint \
					exec/ft_ray \
					common/ft_walls \
					common/ft_colors_1 \
					common/ft_colors_2 \
					common/ft_errors \
					common/ft_init \
					common/ft_remove \
					common/ft_tools \
					common/ft_calculations \
					common/ft_check_3 \


# ----- Rules ---------------------------------------------------------------- #

SRCS_DIR = ./src/
OBJS_DIR = ./src/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

# ----- Compilation ---------------------------------------------------------- #

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@$(CC) $(FLAGS) -c $< -o $@

$(OBJ_DIR):
	@if [ ! -d "$@" ]; then \
		echo "Creating directory '$@'..."; \
		mkdir -p $@; \
	fi

all: $(NAME)

$(MLX):
	@echo "Compiling MLX42 library..."
	@cd MLX42 && cmake -B build && cmake --build build -j4

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@$(CC) $(OBJS) $(MLX) $(LIBFT) $(FLAGS) $(MLX_FLAGS) -o $(NAME)
	@echo " "
	@echo "${DARK_GREEN}${BOLD}Compilation of ${NAME} is done!${DEF_COLOR}"
	@echo " "
	@echo "${BLUE}                  █     ${YELLOW}█████ █████"
	@echo "${BLUE}      █████       █     ${YELLOW}    █ █    █"
	@echo "${BLUE}      █     █   █ █████ ${YELLOW}█████ █    █"
	@echo "${BLUE}      █     █   █ █   █ ${YELLOW}    █ █    █"
	@echo "${BLUE}      █████ █████ █████ ${YELLOW}█████ █████"
	@echo " "
	@echo "${DARK_GREEN}	  By: Nico and JJ"
	@echo " "
	@echo "${YELLOW}  🤪 Welcome to the ${NAME} experience! 🤪"
	@echo " "

$(LIBFT):
	@make -C $(LIBFT_PATH) all

clean: 
	@$(RM) $(OBJS)
	@make -C $(LIBFT_PATH) clean
	@make -C $(MLX_PATH) clean
	@$(RM) $(OBJS_DIR)/charge_flag_makefile/bonus.flag:
	@echo
	@echo "$(RED)🧹 Cleaning Cub3D objects 🧹 $(RESET)"
	$(shell rm -rf ./src/obj)
	@echo "$(DARK_GREEN)🌪️💥 Cleaned Cub3D objects ✅ $(RESET)"

# ----- Fclean --------------------------------------------------------------- #

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(MLX)
	@make -C $(LIBFT_PATH) fclean
	@echo
	@echo "$(RED)🧹 Cleaning Cub3D executables 🧹$(RESET)"
	@echo "$(DARK_GREEN)🌪️💥 Cleaned Cub3D executables ✅$(RESET)"
	@echo

# ----- Recompilation -------------------------------------------------------- #

re: fclean all $(NAME)

# ----- Phony ---------------------------------------------------------------- #

.PHONY: clean fclean re all

# ----- Colors --------------------------------------------------------------- #

DARK_GREEN = \033[32;1m
DEF_COLOR = \033[0m
BROWN   = \033[38;2;184;143;29m
MAGENTA = \033[35;1m
YELLOW  = \033[33;1m
GREEN   = \033[32;1m
WHITE   = \033[37;1m
RESET   = \033[0m
GRAY    = \033[0;90m
BLUE    = \033[34;1m
CYAN    = \033[37;1m
BOLD    = \033[1m
RED     = \033[31;1m

# ----- Rule for the charging bar -------------------------------------------- #

$(OBJS_DIR)/charge_flag_makefile/charge.flag:
	@echo
	@echo -n "$(GREEN)Compiling: $(RESET)["
	@for i in $$(seq 1 2); do \
		echo -n "##"; \
		sleep 0.20; \
	done
	@for i in $$(seq 1 6); do \
		echo -n "####"; \
		sleep 0.10; \
	done
	@echo "] $(GREEN)Done!$(RESET)"
	@touch $(OBJS_DIR)/charge_flag_makefile/charge.flag

# ----- Rule for the bonus charging bar -------------------------------------- #

$(OBJS_DIR)/charge_flag_makefile/bonus.flag:
	@echo
	@echo -n "$(YELLOW)Compiling bonus: $(RESET)["
	@for i in $$(seq 1 2); do \
		echo -n "##"; \
		sleep 0.20; \
	done
	@for i in $$(seq 1 6); do \
		echo -n "####"; \
		sleep 0.10; \
	done
	@echo "] $(YELLOW)Done!$(RESET)"
	@touch $(OBJS_DIR)/charge_flag_makefile/bonus.flag

# ----- End of Makefile ------------------------------------------------------ #