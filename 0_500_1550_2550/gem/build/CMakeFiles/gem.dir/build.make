# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/d/Project/0_500_1550_2550/gem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/d/Project/0_500_1550_2550/gem/build

# Include any dependencies generated for this target.
include CMakeFiles/gem.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/gem.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/gem.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gem.dir/flags.make

CMakeFiles/gem.dir/gem.C.o: CMakeFiles/gem.dir/flags.make
CMakeFiles/gem.dir/gem.C.o: ../gem.C
CMakeFiles/gem.dir/gem.C.o: CMakeFiles/gem.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/d/Project/0_500_1550_2550/gem/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gem.dir/gem.C.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/gem.dir/gem.C.o -MF CMakeFiles/gem.dir/gem.C.o.d -o CMakeFiles/gem.dir/gem.C.o -c /mnt/d/Project/0_500_1550_2550/gem/gem.C

CMakeFiles/gem.dir/gem.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gem.dir/gem.C.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/d/Project/0_500_1550_2550/gem/gem.C > CMakeFiles/gem.dir/gem.C.i

CMakeFiles/gem.dir/gem.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gem.dir/gem.C.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/d/Project/0_500_1550_2550/gem/gem.C -o CMakeFiles/gem.dir/gem.C.s

# Object files for target gem
gem_OBJECTS = \
"CMakeFiles/gem.dir/gem.C.o"

# External object files for target gem
gem_EXTERNAL_OBJECTS =

gem: CMakeFiles/gem.dir/gem.C.o
gem: CMakeFiles/gem.dir/build.make
gem: /home/surfer/garfieldpp/install/lib/libGarfield.so.0.3.0
gem: /home/surfer/root_cern/root/lib/libGdml.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libGeom.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libXMLIO.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libGraf3d.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libGpad.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libGraf.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libHist.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libMatrix.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libMathCore.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libImt.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libMultiProc.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libNet.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libRIO.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libThread.so.6.26.06
gem: /home/surfer/root_cern/root/lib/libCore.so.6.26.06
gem: /usr/lib/x86_64-linux-gnu/libgsl.so
gem: /usr/lib/x86_64-linux-gnu/libgslcblas.so
gem: /home/surfer/garfieldpp/install/lib/libmagboltz.so.11
gem: CMakeFiles/gem.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/d/Project/0_500_1550_2550/gem/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable gem"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gem.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gem.dir/build: gem
.PHONY : CMakeFiles/gem.dir/build

CMakeFiles/gem.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gem.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gem.dir/clean

CMakeFiles/gem.dir/depend:
	cd /mnt/d/Project/0_500_1550_2550/gem/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/d/Project/0_500_1550_2550/gem /mnt/d/Project/0_500_1550_2550/gem /mnt/d/Project/0_500_1550_2550/gem/build /mnt/d/Project/0_500_1550_2550/gem/build /mnt/d/Project/0_500_1550_2550/gem/build/CMakeFiles/gem.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gem.dir/depend

