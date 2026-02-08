NAME 		= RPN
TITLE 		= "🔥 [CPP_09] [EX01] Array 💫"
SRC 		= main.cpp \
				RPN.cpp
OBJ 		= $(SRC:.cpp=.o)

CXX 		= c++
CXXFLAGS 	= -Wall -Wextra -Werror -std=c++98 -g

VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --quiet

DEF_COLOR 	= \033[0m
BROWN   	= \033[33;1m
MAGENTA 	= \033[35;1m
YELLOW  	= \033[33;1m
GREEN   	= \033[32;1m
RED     	= \033[31;1m
CYAN    	= \033[36;1m
BOLD    	= \033[1m

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)Compiling $(TITLE)...$(DEF_COLOR) 🛠️"
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ)
	@echo "$(GREEN)$(NAME) is ready!$(DEF_COLOR) ✅"

%.o: %.cpp
	@echo "$(YELLOW)Generating object file $@...$(DEF_COLOR)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "$(MAGENTA)Cleaning object files...$(DEF_COLOR) 🧹"
	@rm -f $(OBJ)

fclean: clean
	@echo "$(RED)Cleaning executable $(NAME)...$(DEF_COLOR) 🧹"
	@rm -f $(NAME)

re: fclean all

valgrind: all
	@echo "$(CYAN)Analyzing $(NAME) with Valgrind...$(DEF_COLOR) 🕵️‍♀️"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME)

run: all
	@echo "$(BROWN)Running $(NAME)...$(DEF_COLOR) ▶️"
	@./$(NAME)

.PHONY: all clean fclean re run valgrind
