# Compiler
CC = gcc

# Executable name
TARGET = build/webshop

# Source files
SRC = webshop1.c webshop2.c

# Header files
HEADERS = webshop.h

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Default build target
$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Run the program after building
run: $(TARGET)
	./$(TARGET)

# Clean up compiled files
clean:
	rm -f $(TARGET)
