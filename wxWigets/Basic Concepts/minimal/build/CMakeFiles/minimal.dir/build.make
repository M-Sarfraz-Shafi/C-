# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /snap/cmake/619/bin/cmake

# The command to remove a file.
RM = /snap/cmake/619/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/msarfrazshafi/wxWidgets/samples/minimal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/msarfrazshafi/wxWidgets/samples/minimal/build

# Include any dependencies generated for this target.
include CMakeFiles/minimal.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/minimal.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/minimal.dir/flags.make

CMakeFiles/minimal.dir/minimal.cpp.o: CMakeFiles/minimal.dir/flags.make
CMakeFiles/minimal.dir/minimal.cpp.o: ../minimal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/msarfrazshafi/wxWidgets/samples/minimal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/minimal.dir/minimal.cpp.o"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/minimal.dir/minimal.cpp.o -c /home/msarfrazshafi/wxWidgets/samples/minimal/minimal.cpp

CMakeFiles/minimal.dir/minimal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/minimal.dir/minimal.cpp.i"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/msarfrazshafi/wxWidgets/samples/minimal/minimal.cpp > CMakeFiles/minimal.dir/minimal.cpp.i

CMakeFiles/minimal.dir/minimal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/minimal.dir/minimal.cpp.s"
	/usr/bin/x86_64-linux-gnu-g++-7 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/msarfrazshafi/wxWidgets/samples/minimal/minimal.cpp -o CMakeFiles/minimal.dir/minimal.cpp.s

# Object files for target minimal
minimal_OBJECTS = \
"CMakeFiles/minimal.dir/minimal.cpp.o"

# External object files for target minimal
minimal_EXTERNAL_OBJECTS =

minimal: CMakeFiles/minimal.dir/minimal.cpp.o
minimal: CMakeFiles/minimal.dir/build.make
minimal: CMakeFiles/minimal.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/msarfrazshafi/wxWidgets/samples/minimal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable minimal"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/minimal.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/minimal.dir/build: minimal

.PHONY : CMakeFiles/minimal.dir/build

CMakeFiles/minimal.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/minimal.dir/cmake_clean.cmake
.PHONY : CMakeFiles/minimal.dir/clean

CMakeFiles/minimal.dir/depend:
	cd /home/msarfrazshafi/wxWidgets/samples/minimal/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/msarfrazshafi/wxWidgets/samples/minimal /home/msarfrazshafi/wxWidgets/samples/minimal /home/msarfrazshafi/wxWidgets/samples/minimal/build /home/msarfrazshafi/wxWidgets/samples/minimal/build /home/msarfrazshafi/wxWidgets/samples/minimal/build/CMakeFiles/minimal.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/minimal.dir/depend

