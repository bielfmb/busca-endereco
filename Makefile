# cc and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall

INCLUDE_FOLDER = include
BIN_FOLDER = bin
OBJ_FOLDER = obj
SRC_FOLDER = src
TESTS_FOLDER = tests

MAIN_TARGET = $(BIN_FOLDER)/tp3.out
TEST_TARGET = $(BIN_FOLDER)/tests.out

# sources and objects
SRC = $(wildcard $(SRC_FOLDER)/*.cpp) \
      $(wildcard $(SRC_FOLDER)/consultas/*.cpp) \
      $(wildcard $(SRC_FOLDER)/auxi/*.cpp)

SRC_OBJ = $(patsubst $(SRC_FOLDER)/%.cpp,$(OBJ_FOLDER)/%.o,$(SRC))

# tests and tests objects
TESTS = $(wildcard $(TESTS_FOLDER)/*.cpp)

TESTS_OBJ = $(patsubst $(TESTS_FOLDER)/%.cpp,$(OBJ_FOLDER)/%.o,$(TESTS))

# targets
.PHONY: all tests clean

# default
all: $(MAIN_TARGET)

# tests
tests: $(TEST_TARGET)
	./$(TEST_TARGET)

# build
$(MAIN_TARGET): $(SRC_OBJ)
	@mkdir -p $(BIN_FOLDER)
	$(CC) $(CXXFLAGS) -o $@ $(SRC_OBJ)

$(TEST_TARGET): $(TESTS_OBJ) $(filter-out $(OBJ_FOLDER)/Main.o, $(SRC_OBJ))
	@mkdir -p $(BIN_FOLDER)
	$(CC) $(CXXFLAGS) -o $@ $^

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp 
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

$(OBJ_FOLDER)/%.o: $(TESTS_FOLDER)/%.cpp 
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER) -I.

clean:
	@rm -rf $(OBJ_FOLDER) $(BIN_FOLDER)
