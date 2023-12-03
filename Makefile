CPP_DIR := src/cpp
HPP_DIR := src/hpp
OBJ_DIR := obj

MAIN_CPP 	  := main.cpp
MAIN_OBJ := $(OBJ_DIR)/main.o)

CPP_FILES       := $(wildcard $(CPP_DIR)/*.cpp)
OBJ_FILES     := $(CPP_FILES:$(CPP_DIR)/%.cpp=$(OBJ_DIR)/%.o)

QUAD_TREE := $(wildcard $(HPP_DIR)/QuadTree.hpp)

CC = g++

# CFLAGS       := -std=c++14 -g -gdwarf-2 -fno-omit-frame-pointer
CFLAGS 		 := -std=c++14

CPPFLAGS  := -I"SFML\include" -DSFML_STATIC

LDFLAGS := -L"SFML\lib"

# LDLIBS := -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d -lopengl32 -lwinmm -lgdi32 -lsfml-main-d -lfreetype
LDLIBS := -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lsfml-main -lfreetype
# APP_NAME := "FlarkyBird"
TARGET := "myApp"

.PHONY: all clean

all: build run

$(OBJ_FILES): $(OBJ_DIR)/%.o: $(CPP_DIR)/%.cpp $(HPP_DIR)/%.hpp $(QUAD_TREE)
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

#handle main.cpp error (no .h file)
$(MAIN_OBJ): $(MAIN_CPP)
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

build: $(OBJ_DIR) link

$(OBJ_DIR):
	@test -d "$(OBJ_DIR)" || mkdir $(OBJ_DIR)

link: $(OBJ_FILES) $(MAIN_OBJ)
	$(CC) $^ -o $(TARGET) $(LDFLAGS) $(LDLIBS)

run:
	$(TARGET)

clean:
	del $(OBJ_DIR)\*.o
	del $(TARGET).exe