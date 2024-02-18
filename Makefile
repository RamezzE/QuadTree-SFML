# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jjoe/sfml-quadtree/QuadTree-SFML

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jjoe/sfml-quadtree/QuadTree-SFML

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jjoe/sfml-quadtree/QuadTree-SFML/CMakeFiles /home/jjoe/sfml-quadtree/QuadTree-SFML//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/jjoe/sfml-quadtree/QuadTree-SFML/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named QuadTree

# Build rule for target.
QuadTree: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 QuadTree
.PHONY : QuadTree

# fast build rule for target.
QuadTree/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/build
.PHONY : QuadTree/fast

main.o: main.cpp.o
.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i
.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s
.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/main.cpp.s
.PHONY : main.cpp.s

src/cpp/Button.o: src/cpp/Button.cpp.o
.PHONY : src/cpp/Button.o

# target to build an object file
src/cpp/Button.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/Button.cpp.o
.PHONY : src/cpp/Button.cpp.o

src/cpp/Button.i: src/cpp/Button.cpp.i
.PHONY : src/cpp/Button.i

# target to preprocess a source file
src/cpp/Button.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/Button.cpp.i
.PHONY : src/cpp/Button.cpp.i

src/cpp/Button.s: src/cpp/Button.cpp.s
.PHONY : src/cpp/Button.s

# target to generate assembly for a file
src/cpp/Button.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/Button.cpp.s
.PHONY : src/cpp/Button.cpp.s

src/cpp/Common.o: src/cpp/Common.cpp.o
.PHONY : src/cpp/Common.o

# target to build an object file
src/cpp/Common.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/Common.cpp.o
.PHONY : src/cpp/Common.cpp.o

src/cpp/Common.i: src/cpp/Common.cpp.i
.PHONY : src/cpp/Common.i

# target to preprocess a source file
src/cpp/Common.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/Common.cpp.i
.PHONY : src/cpp/Common.cpp.i

src/cpp/Common.s: src/cpp/Common.cpp.s
.PHONY : src/cpp/Common.s

# target to generate assembly for a file
src/cpp/Common.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/Common.cpp.s
.PHONY : src/cpp/Common.cpp.s

src/cpp/Game.o: src/cpp/Game.cpp.o
.PHONY : src/cpp/Game.o

# target to build an object file
src/cpp/Game.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/Game.cpp.o
.PHONY : src/cpp/Game.cpp.o

src/cpp/Game.i: src/cpp/Game.cpp.i
.PHONY : src/cpp/Game.i

# target to preprocess a source file
src/cpp/Game.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/Game.cpp.i
.PHONY : src/cpp/Game.cpp.i

src/cpp/Game.s: src/cpp/Game.cpp.s
.PHONY : src/cpp/Game.s

# target to generate assembly for a file
src/cpp/Game.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/Game.cpp.s
.PHONY : src/cpp/Game.cpp.s

src/cpp/MainScreen.o: src/cpp/MainScreen.cpp.o
.PHONY : src/cpp/MainScreen.o

# target to build an object file
src/cpp/MainScreen.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/MainScreen.cpp.o
.PHONY : src/cpp/MainScreen.cpp.o

src/cpp/MainScreen.i: src/cpp/MainScreen.cpp.i
.PHONY : src/cpp/MainScreen.i

# target to preprocess a source file
src/cpp/MainScreen.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/MainScreen.cpp.i
.PHONY : src/cpp/MainScreen.cpp.i

src/cpp/MainScreen.s: src/cpp/MainScreen.cpp.s
.PHONY : src/cpp/MainScreen.s

# target to generate assembly for a file
src/cpp/MainScreen.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/MainScreen.cpp.s
.PHONY : src/cpp/MainScreen.cpp.s

src/cpp/Particle.o: src/cpp/Particle.cpp.o
.PHONY : src/cpp/Particle.o

# target to build an object file
src/cpp/Particle.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/Particle.cpp.o
.PHONY : src/cpp/Particle.cpp.o

src/cpp/Particle.i: src/cpp/Particle.cpp.i
.PHONY : src/cpp/Particle.i

# target to preprocess a source file
src/cpp/Particle.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/Particle.cpp.i
.PHONY : src/cpp/Particle.cpp.i

src/cpp/Particle.s: src/cpp/Particle.cpp.s
.PHONY : src/cpp/Particle.s

# target to generate assembly for a file
src/cpp/Particle.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/Particle.cpp.s
.PHONY : src/cpp/Particle.cpp.s

src/cpp/TextBox.o: src/cpp/TextBox.cpp.o
.PHONY : src/cpp/TextBox.o

# target to build an object file
src/cpp/TextBox.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/TextBox.cpp.o
.PHONY : src/cpp/TextBox.cpp.o

src/cpp/TextBox.i: src/cpp/TextBox.cpp.i
.PHONY : src/cpp/TextBox.i

# target to preprocess a source file
src/cpp/TextBox.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/TextBox.cpp.i
.PHONY : src/cpp/TextBox.cpp.i

src/cpp/TextBox.s: src/cpp/TextBox.cpp.s
.PHONY : src/cpp/TextBox.s

# target to generate assembly for a file
src/cpp/TextBox.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/QuadTree.dir/build.make CMakeFiles/QuadTree.dir/src/cpp/TextBox.cpp.s
.PHONY : src/cpp/TextBox.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... QuadTree"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... src/cpp/Button.o"
	@echo "... src/cpp/Button.i"
	@echo "... src/cpp/Button.s"
	@echo "... src/cpp/Common.o"
	@echo "... src/cpp/Common.i"
	@echo "... src/cpp/Common.s"
	@echo "... src/cpp/Game.o"
	@echo "... src/cpp/Game.i"
	@echo "... src/cpp/Game.s"
	@echo "... src/cpp/MainScreen.o"
	@echo "... src/cpp/MainScreen.i"
	@echo "... src/cpp/MainScreen.s"
	@echo "... src/cpp/Particle.o"
	@echo "... src/cpp/Particle.i"
	@echo "... src/cpp/Particle.s"
	@echo "... src/cpp/TextBox.o"
	@echo "... src/cpp/TextBox.i"
	@echo "... src/cpp/TextBox.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

