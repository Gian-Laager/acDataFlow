# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild

# Include any dependencies generated for this target.
include CMakeFiles/cmake-test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cmake-test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cmake-test.dir/flags.make

CMakeFiles/cmake-test.dir/main.c.o: CMakeFiles/cmake-test.dir/flags.make
CMakeFiles/cmake-test.dir/main.c.o: main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cmake-test.dir/main.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cmake-test.dir/main.c.o   -c /Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild/main.c

CMakeFiles/cmake-test.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cmake-test.dir/main.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild/main.c > CMakeFiles/cmake-test.dir/main.c.i

CMakeFiles/cmake-test.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cmake-test.dir/main.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild/main.c -o CMakeFiles/cmake-test.dir/main.c.s

# Object files for target cmake-test
cmake__test_OBJECTS = \
"CMakeFiles/cmake-test.dir/main.c.o"

# External object files for target cmake-test
cmake__test_EXTERNAL_OBJECTS =

cmake-test: CMakeFiles/cmake-test.dir/main.c.o
cmake-test: CMakeFiles/cmake-test.dir/build.make
cmake-test: /usr/local/lib/libGLEW.2.1.0.dylib
cmake-test: CMakeFiles/cmake-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cmake-test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cmake-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cmake-test.dir/build: cmake-test

.PHONY : CMakeFiles/cmake-test.dir/build

CMakeFiles/cmake-test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cmake-test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cmake-test.dir/clean

CMakeFiles/cmake-test.dir/depend:
	cd /Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild /Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild /Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild /Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild /Users/gianlaager/Documents/code/C++/clionProjects/GLEWInit/deps/glew/build/cmake/testbuild/CMakeFiles/cmake-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cmake-test.dir/depend

