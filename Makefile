# Compiler
CC = gcc

# Output directory and target binary
BUILD_DIR = build
TARGET = $(BUILD_DIR)/webshop

# Source and header files
SRC = Webshop1.c Webshop2.c
HEADERS = Webshop.h

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Default rule
all: $(TARGET)

# Ensure build directory and build the executable
$(TARGET): $(SRC) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -rf $(BUILD_DIR)
