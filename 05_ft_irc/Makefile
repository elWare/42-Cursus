
DEF_COLOR      	= \033[0;39m
ORANGE         	= \033[38;5;209m
MID_GRAY       	= \033[38;5;245m
DARK_GREEN     	= \033[38;2;75;179;82m

NAME 			:= ircserv
CC 				:= c++
CFLAGS 			:= -Wall -Wextra -Werror -std=c++98

INCLUDE_DIR 	:= ./includes
INCLUDE			:= -I$(INCLUDE_DIR)

# SRC --------------------------------------------------------------------------------
SRC_DIR			:= ./src
SRC_FILES 		:= $(addprefix $(SRC_DIR)/, main.cpp) 
OBJ_FILES 		:= $(SRC_FILES:%.cpp=%.o)

# MODELO IRC --------------------------------------------------------------------------------
MODEL_DIR		:= ./src/model
MODEL_FILES 	:= $(addprefix $(MODEL_DIR)/, \
					IRCModel.cpp 	\
					Client.cpp 		\
					Channel.cpp		\
					Bot.cpp 		\
				)
OBJ_FILES 		+= $(MODEL_FILES:%.cpp=%.o)

# SERVER TCP --------------------------------------------------------------------------------
SERVER_DIR		:= ./src/server
SERVER_FILES 	:= $(addprefix $(SERVER_DIR)/, \
					Server.cpp \
					Parser.cpp \
					Signal.cpp \
				)
OBJ_FILES 		+= $(SERVER_FILES:%.cpp=%.o)

# LOGIC CHAT --------------------------------------------------------------------------------
CONTROLLER_DIR		:= ./src/controller
CONTROLLER_FILES 	:= $(addprefix $(CONTROLLER_DIR)/, \
						CommandExecutor.cpp \
						IRCMessage.cpp 		\
					)
OBJ_FILES 		+= $(CONTROLLER_FILES:%.cpp=%.o)


all: $(NAME)

%.o: %.cpp
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME):  $(OBJ_FILES)
	@echo "$(ORANGE)🚀​ Compiling $(NAME)... $(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(INCLUDE) -o $(NAME)
	@echo "$(DARK_GREEN)📚 $(NAME) has been created	\t\t OK$(DEF_COLOR)"

clean:
	@rm -f $(OBJ_FILES)	
	@echo "${MID_GRAY}Cleaning objects $(NAME) \t\t	 OK$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(MID_GRAY)Cleaning $(NAME) \t\t\t\t OK$(DEF_COLOR)"

re: fclean all
	@echo "$(DARK_GREEN)🔁 Cleaning and recompiled -> $(NAME) \t\t OK$(DEF_COLOR)"	
	@make -s clean

debug: CFLAGS 		+= -g -fsanitize=address
debug: re

valgrind: $(NAME)
	@echo "$(ORANGE)🔍 Running Valgrind memory check...$(DEF_COLOR)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(PORT) $(PASS)

# make valgrind PORT=6669 PASS=asd

.PHONY: all library clean fclean re debug valgrind
