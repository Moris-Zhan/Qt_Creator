# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/leyan/User/Triangle-ChangCol

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/leyan/User/Triangle-ChangCol/build-Triangle-ChangCol-Desktop-Default

# Include any dependencies generated for this target.
include CMakeFiles/Triangle-ChangCol.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Triangle-ChangCol.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Triangle-ChangCol.dir/flags.make

CMakeFiles/Triangle-ChangCol.dir/main.cpp.o: CMakeFiles/Triangle-ChangCol.dir/flags.make
CMakeFiles/Triangle-ChangCol.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/leyan/User/Triangle-ChangCol/build-Triangle-ChangCol-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Triangle-ChangCol.dir/main.cpp.o"
	/usr/bin/g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Triangle-ChangCol.dir/main.cpp.o -c /home/leyan/User/Triangle-ChangCol/main.cpp

CMakeFiles/Triangle-ChangCol.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Triangle-ChangCol.dir/main.cpp.i"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/leyan/User/Triangle-ChangCol/main.cpp > CMakeFiles/Triangle-ChangCol.dir/main.cpp.i

CMakeFiles/Triangle-ChangCol.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Triangle-ChangCol.dir/main.cpp.s"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/leyan/User/Triangle-ChangCol/main.cpp -o CMakeFiles/Triangle-ChangCol.dir/main.cpp.s

CMakeFiles/Triangle-ChangCol.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Triangle-ChangCol.dir/main.cpp.o.requires

CMakeFiles/Triangle-ChangCol.dir/main.cpp.o.provides: CMakeFiles/Triangle-ChangCol.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Triangle-ChangCol.dir/build.make CMakeFiles/Triangle-ChangCol.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Triangle-ChangCol.dir/main.cpp.o.provides

CMakeFiles/Triangle-ChangCol.dir/main.cpp.o.provides.build: CMakeFiles/Triangle-ChangCol.dir/main.cpp.o


# Object files for target Triangle-ChangCol
Triangle__ChangCol_OBJECTS = \
"CMakeFiles/Triangle-ChangCol.dir/main.cpp.o"

# External object files for target Triangle-ChangCol
Triangle__ChangCol_EXTERNAL_OBJECTS =

Triangle-ChangCol: CMakeFiles/Triangle-ChangCol.dir/main.cpp.o
Triangle-ChangCol: CMakeFiles/Triangle-ChangCol.dir/build.make
Triangle-ChangCol: /usr/lib/x86_64-linux-gnu/libGLU.so
Triangle-ChangCol: /usr/lib/x86_64-linux-gnu/libGL.so
Triangle-ChangCol: CMakeFiles/Triangle-ChangCol.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/leyan/User/Triangle-ChangCol/build-Triangle-ChangCol-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Triangle-ChangCol"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Triangle-ChangCol.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Triangle-ChangCol.dir/build: Triangle-ChangCol

.PHONY : CMakeFiles/Triangle-ChangCol.dir/build

CMakeFiles/Triangle-ChangCol.dir/requires: CMakeFiles/Triangle-ChangCol.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Triangle-ChangCol.dir/requires

CMakeFiles/Triangle-ChangCol.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Triangle-ChangCol.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Triangle-ChangCol.dir/clean

CMakeFiles/Triangle-ChangCol.dir/depend:
	cd /home/leyan/User/Triangle-ChangCol/build-Triangle-ChangCol-Desktop-Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/leyan/User/Triangle-ChangCol /home/leyan/User/Triangle-ChangCol /home/leyan/User/Triangle-ChangCol/build-Triangle-ChangCol-Desktop-Default /home/leyan/User/Triangle-ChangCol/build-Triangle-ChangCol-Desktop-Default /home/leyan/User/Triangle-ChangCol/build-Triangle-ChangCol-Desktop-Default/CMakeFiles/Triangle-ChangCol.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Triangle-ChangCol.dir/depend

