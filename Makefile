# cc and flags
CC = g++
CXXFLAGS = -std=c++11 -g -Wall

INCLUDE_FOLDER = include
BIN_FOLDER = bin
OBJ_FOLDER = obj
SRC_FOLDER = src

TARGET = tp3.out
BIN_TARGET = $(BIN_FOLDER)/$(TARGET)

# sources and objects
SRC = $(wildcard $(SRC_FOLDER)/*.cpp) \
      $(wildcard $(SRC_FOLDER)/consultas/*.cpp) \
      $(wildcard $(SRC_FOLDER)/auxi/*.cpp)

OBJ = $(patsubst $(SRC_FOLDER)/%.cpp,$(OBJ_FOLDER)/%.o,$(SRC))

# default target
.PHONY: all clean
all: $(BIN_TARGET)

# build
$(BIN_TARGET): $(OBJ)
	@mkdir -p $(BIN_FOLDER)
	$(CC) $(CXXFLAGS) -o $@ $(OBJ)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@ -I$(INCLUDE_FOLDER)

clean:
	@rm -rf $(OBJ_FOLDER) $(BIN_FOLDER)
