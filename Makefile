# Makefile for project

#Define directories and flags
CC = g++
EXE = ipcalc
BIN_DIR = ./bin
BUILD_DIR = ./build
SRC_DIR = ./src
TEST_DIR = ./test
FLAGS =-Wall

#Pre-define targets
.PHONY: all clean

# Default target
all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(BUILD_DIR)/main.o $(BUILD_DIR)/functions.o
	$(CC) $(FLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/functions.o -o $(BIN_DIR)/$(EXE)

$(BUILD_DIR)/main.o:
	$(CC) $(FLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/functions.o:
	$(CC) $(FLAGS) -c $(SRC_DIR)/functions.cpp -o $(BUILD_DIR)/functions.o

# Clean target
clean:
	rm -f build/*.o
	rm -f bin/main

# Run target
run:
	$(BIN_DIR)/$(EXE)
