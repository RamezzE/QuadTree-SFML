CPP_DIR := src/cpp
HPP_DIR := src/hpp
OBJ_DIR := obj

MAIN_CPP    := main.cpp
MAIN_OBJ    := $(OBJ_DIR)/main.o

CPP_FILES   := $(wildcard $(CPP_DIR)/*.cpp)
OBJ_FILES   := $(CPP_FILES:$(CPP_DIR)/%.cpp=$(OBJ_DIR)/%.o)

QUAD_TREE   := $(wildcard $(HPP_DIR)/QuadTree.hpp)

CC          := g++
CFLAGS      := -std=c++14
LDLIBS      := -lsfml-graphics -lsfml-window -lsfml-system

ifeq ($(OS),Windows_NT)
    # Windows-specific settings
    CPPFLAGS    := -I"SFML\include"
    LDFLAGS     := -L"SFML\lib"
    TARGET      := "QuadTree.exe"
    RM          := del
    SLASH       := \\
else
    # Linux-specific settings
    CPPFLAGS    := -I/usr/include/SFML
    LDFLAGS     := -L/usr/lib
    TARGET      := "QuadTree"
    RM          := rm -f
    SLASH       := /
endif

.PHONY: all clean

all: build run

$(OBJ_FILES): $(OBJ_DIR)/%.o: $(CPP_DIR)/%.cpp $(HPP_DIR)/%.hpp $(QUAD_TREE)
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

$(MAIN_OBJ): $(MAIN_CPP)
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

build: $(OBJ_DIR) link

$(OBJ_DIR):
	@test -d "$(OBJ_DIR)" || mkdir $(OBJ_DIR)

link: $(OBJ_FILES) $(MAIN_OBJ)
	$(CC) $^ -o $(TARGET) $(LDFLAGS) $(LDLIBS)

run:
	./$(TARGET)

clean:
	$(RM) $(OBJ_DIR)$(SLASH)*.o
	$(RM) $(TARGET)
