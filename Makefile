# Compiler
CC = gcc
WIN_CC = x86_64-w64-mingw32-gcc

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source and header files
SRC = $(SRC_DIR)/webshop1.c $(SRC_DIR)/webshop2.c
HEADERS = $(SRC_DIR)/webshop.h

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Targets
LINUX_TARGET = $(BUILD_DIR)/webshop
WIN_TARGET = $(BUILD_DIR)/webshop.exe

# Default target (Linux)
all: $(LINUX_TARGET)

# Linux build
$(LINUX_TARGET): $(SRC) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(LINUX_TARGET)

# Windows build
windows: $(SRC) $(HEADERS)
	mkdir -p $(BUILD_DIR)
	$(WIN_CC) $(CFLAGS) $(SRC) -o $(WIN_TARGET)

# Run the Linux binary
run: $(LINUX_TARGET)
	./$(LINUX_TARGET)

# Clean build outputs
clean:
	rm -rf $(BUILD_DIR)
