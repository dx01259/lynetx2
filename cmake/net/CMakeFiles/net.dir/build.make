# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/xudeng/ClionProjects/lynetx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/xudeng/ClionProjects/lynetx/cmake

# Include any dependencies generated for this target.
include net/CMakeFiles/net.dir/depend.make

# Include the progress variables for this target.
include net/CMakeFiles/net.dir/progress.make

# Include the compile flags for this target's objects.
include net/CMakeFiles/net.dir/flags.make

net/CMakeFiles/net.dir/AsyncSocket.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/AsyncSocket.cpp.o: ../net/AsyncSocket.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xudeng/ClionProjects/lynetx/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object net/CMakeFiles/net.dir/AsyncSocket.cpp.o"
	cd /Users/xudeng/ClionProjects/lynetx/cmake/net && g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/net.dir/AsyncSocket.cpp.o -c /Users/xudeng/ClionProjects/lynetx/net/AsyncSocket.cpp

net/CMakeFiles/net.dir/AsyncSocket.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/AsyncSocket.cpp.i"
	cd /Users/xudeng/ClionProjects/lynetx/cmake/net && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xudeng/ClionProjects/lynetx/net/AsyncSocket.cpp > CMakeFiles/net.dir/AsyncSocket.cpp.i

net/CMakeFiles/net.dir/AsyncSocket.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/AsyncSocket.cpp.s"
	cd /Users/xudeng/ClionProjects/lynetx/cmake/net && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xudeng/ClionProjects/lynetx/net/AsyncSocket.cpp -o CMakeFiles/net.dir/AsyncSocket.cpp.s

net/CMakeFiles/net.dir/AsyncSocket.cpp.o.requires:

.PHONY : net/CMakeFiles/net.dir/AsyncSocket.cpp.o.requires

net/CMakeFiles/net.dir/AsyncSocket.cpp.o.provides: net/CMakeFiles/net.dir/AsyncSocket.cpp.o.requires
	$(MAKE) -f net/CMakeFiles/net.dir/build.make net/CMakeFiles/net.dir/AsyncSocket.cpp.o.provides.build
.PHONY : net/CMakeFiles/net.dir/AsyncSocket.cpp.o.provides

net/CMakeFiles/net.dir/AsyncSocket.cpp.o.provides.build: net/CMakeFiles/net.dir/AsyncSocket.cpp.o


net/CMakeFiles/net.dir/EpollService.cpp.o: net/CMakeFiles/net.dir/flags.make
net/CMakeFiles/net.dir/EpollService.cpp.o: ../net/EpollService.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/xudeng/ClionProjects/lynetx/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object net/CMakeFiles/net.dir/EpollService.cpp.o"
	cd /Users/xudeng/ClionProjects/lynetx/cmake/net && g++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/net.dir/EpollService.cpp.o -c /Users/xudeng/ClionProjects/lynetx/net/EpollService.cpp

net/CMakeFiles/net.dir/EpollService.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/net.dir/EpollService.cpp.i"
	cd /Users/xudeng/ClionProjects/lynetx/cmake/net && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/xudeng/ClionProjects/lynetx/net/EpollService.cpp > CMakeFiles/net.dir/EpollService.cpp.i

net/CMakeFiles/net.dir/EpollService.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/net.dir/EpollService.cpp.s"
	cd /Users/xudeng/ClionProjects/lynetx/cmake/net && g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/xudeng/ClionProjects/lynetx/net/EpollService.cpp -o CMakeFiles/net.dir/EpollService.cpp.s

net/CMakeFiles/net.dir/EpollService.cpp.o.requires:

.PHONY : net/CMakeFiles/net.dir/EpollService.cpp.o.requires

net/CMakeFiles/net.dir/EpollService.cpp.o.provides: net/CMakeFiles/net.dir/EpollService.cpp.o.requires
	$(MAKE) -f net/CMakeFiles/net.dir/build.make net/CMakeFiles/net.dir/EpollService.cpp.o.provides.build
.PHONY : net/CMakeFiles/net.dir/EpollService.cpp.o.provides

net/CMakeFiles/net.dir/EpollService.cpp.o.provides.build: net/CMakeFiles/net.dir/EpollService.cpp.o


# Object files for target net
net_OBJECTS = \
"CMakeFiles/net.dir/AsyncSocket.cpp.o" \
"CMakeFiles/net.dir/EpollService.cpp.o"

# External object files for target net
net_EXTERNAL_OBJECTS =

lynetx/lib/libnet.dylib: net/CMakeFiles/net.dir/AsyncSocket.cpp.o
lynetx/lib/libnet.dylib: net/CMakeFiles/net.dir/EpollService.cpp.o
lynetx/lib/libnet.dylib: net/CMakeFiles/net.dir/build.make
lynetx/lib/libnet.dylib: lynetx/lib/libbase.dylib
lynetx/lib/libnet.dylib: net/CMakeFiles/net.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/xudeng/ClionProjects/lynetx/cmake/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX shared library ../lynetx/lib/libnet.dylib"
	cd /Users/xudeng/ClionProjects/lynetx/cmake/net && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/net.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
net/CMakeFiles/net.dir/build: lynetx/lib/libnet.dylib

.PHONY : net/CMakeFiles/net.dir/build

net/CMakeFiles/net.dir/requires: net/CMakeFiles/net.dir/AsyncSocket.cpp.o.requires
net/CMakeFiles/net.dir/requires: net/CMakeFiles/net.dir/EpollService.cpp.o.requires

.PHONY : net/CMakeFiles/net.dir/requires

net/CMakeFiles/net.dir/clean:
	cd /Users/xudeng/ClionProjects/lynetx/cmake/net && $(CMAKE_COMMAND) -P CMakeFiles/net.dir/cmake_clean.cmake
.PHONY : net/CMakeFiles/net.dir/clean

net/CMakeFiles/net.dir/depend:
	cd /Users/xudeng/ClionProjects/lynetx/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/xudeng/ClionProjects/lynetx /Users/xudeng/ClionProjects/lynetx/net /Users/xudeng/ClionProjects/lynetx/cmake /Users/xudeng/ClionProjects/lynetx/cmake/net /Users/xudeng/ClionProjects/lynetx/cmake/net/CMakeFiles/net.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : net/CMakeFiles/net.dir/depend
