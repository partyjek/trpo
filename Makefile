# Makefile for project

#Define directories and flags
BIN_DIR = ./bin
BUILD_DIR = ./build
SRC_DIR = ./src
TEST_DIR = ./test
FLAGS =-Wall

# Default target
all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(BUILD_DIR)/main.o $(BUILD_DIR)/functions.o
	g++ $(FLAGS) $(BUILD_DIR)/main.o $(BUILD_DIR)/functions.o -o $(BIN_DIR)/main

$(BUILD_DIR)/main.o:
	g++ $(FLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/functions.o:
	g++ $(FLAGS) -c $(SRC_DIR)/functions.cpp -o $(BUILD_DIR)/functions.o

# Clean target
clean:
	rm -f build/*.o
	rm -f bin/main
