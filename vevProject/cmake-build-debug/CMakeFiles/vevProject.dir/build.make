# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/set92/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/171.4694.4/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/set92/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/171.4694.4/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/set92/Documents/vevProject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/set92/Documents/vevProject/cmake-build-debug

# Utility rule file for vevProject.

# Include the progress variables for this target.
include CMakeFiles/vevProject.dir/progress.make

CMakeFiles/vevProject:
	make -C /home/set92/Documents/vevProject CLION_EXE_DIR=/home/set92/Documents/vevProject/cmake-build-debug

vevProject: CMakeFiles/vevProject
vevProject: CMakeFiles/vevProject.dir/build.make

.PHONY : vevProject

# Rule to build all files generated by this target.
CMakeFiles/vevProject.dir/build: vevProject

.PHONY : CMakeFiles/vevProject.dir/build

CMakeFiles/vevProject.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vevProject.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vevProject.dir/clean

CMakeFiles/vevProject.dir/depend:
	cd /home/set92/Documents/vevProject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/set92/Documents/vevProject /home/set92/Documents/vevProject /home/set92/Documents/vevProject/cmake-build-debug /home/set92/Documents/vevProject/cmake-build-debug /home/set92/Documents/vevProject/cmake-build-debug/CMakeFiles/vevProject.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vevProject.dir/depend

