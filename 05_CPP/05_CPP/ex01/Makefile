# Compilers and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror

# Source files and objects
SOURCES = main.cpp Bureaucrat.cpp Form.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Target executable
TARGET = form

# Default target
all: $(TARGET)
	@echo "Build complete."

# Linking the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation rule for .cpp files to .o object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Phony targets
.PHONY: all clean fclean re

# Clean up build artifacts
clean:
	rm -f $(OBJECTS)
	@echo "Cleaned object files."

# Full cleanup, including the executable
fclean: clean
	rm -f $(TARGET)
	@echo "Removed executable and cleaned object files."

# Rebuild everything from scratch
re: fclean all