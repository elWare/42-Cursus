CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

SOURCES = main.cpp Bureaucrat.cpp Form.cpp
OBJECTS = $(SOURCES:.cpp=.o)

TARGET = form

all: $(TARGET)
	@echo "Build complete."

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: all clean fclean re

clean:
	rm -f $(OBJECTS)
	@echo "Cleaned object files."

fclean: clean
	rm -f $(TARGET)
	@echo "Removed executable and cleaned object files."

re: fclean all