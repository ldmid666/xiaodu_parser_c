# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /root/temp/grpc_demo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/temp/grpc_demo

# Include any dependencies generated for this target.
include proto/CMakeFiles/proto.dir/depend.make

# Include the progress variables for this target.
include proto/CMakeFiles/proto.dir/progress.make

# Include the compile flags for this target's objects.
include proto/CMakeFiles/proto.dir/flags.make

proto/CMakeFiles/proto.dir/parser.grpc-c.c.o: proto/CMakeFiles/proto.dir/flags.make
proto/CMakeFiles/proto.dir/parser.grpc-c.c.o: proto/parser.grpc-c.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/temp/grpc_demo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object proto/CMakeFiles/proto.dir/parser.grpc-c.c.o"
	cd /root/temp/grpc_demo/proto && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/proto.dir/parser.grpc-c.c.o   -c /root/temp/grpc_demo/proto/parser.grpc-c.c

proto/CMakeFiles/proto.dir/parser.grpc-c.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/proto.dir/parser.grpc-c.c.i"
	cd /root/temp/grpc_demo/proto && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/temp/grpc_demo/proto/parser.grpc-c.c > CMakeFiles/proto.dir/parser.grpc-c.c.i

proto/CMakeFiles/proto.dir/parser.grpc-c.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/proto.dir/parser.grpc-c.c.s"
	cd /root/temp/grpc_demo/proto && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/temp/grpc_demo/proto/parser.grpc-c.c -o CMakeFiles/proto.dir/parser.grpc-c.c.s

proto/CMakeFiles/proto.dir/parser.grpc-c.c.o.requires:

.PHONY : proto/CMakeFiles/proto.dir/parser.grpc-c.c.o.requires

proto/CMakeFiles/proto.dir/parser.grpc-c.c.o.provides: proto/CMakeFiles/proto.dir/parser.grpc-c.c.o.requires
	$(MAKE) -f proto/CMakeFiles/proto.dir/build.make proto/CMakeFiles/proto.dir/parser.grpc-c.c.o.provides.build
.PHONY : proto/CMakeFiles/proto.dir/parser.grpc-c.c.o.provides

proto/CMakeFiles/proto.dir/parser.grpc-c.c.o.provides.build: proto/CMakeFiles/proto.dir/parser.grpc-c.c.o


proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o: proto/CMakeFiles/proto.dir/flags.make
proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o: proto/parser.grpc-c.service.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/temp/grpc_demo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o"
	cd /root/temp/grpc_demo/proto && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/proto.dir/parser.grpc-c.service.c.o   -c /root/temp/grpc_demo/proto/parser.grpc-c.service.c

proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/proto.dir/parser.grpc-c.service.c.i"
	cd /root/temp/grpc_demo/proto && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /root/temp/grpc_demo/proto/parser.grpc-c.service.c > CMakeFiles/proto.dir/parser.grpc-c.service.c.i

proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/proto.dir/parser.grpc-c.service.c.s"
	cd /root/temp/grpc_demo/proto && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /root/temp/grpc_demo/proto/parser.grpc-c.service.c -o CMakeFiles/proto.dir/parser.grpc-c.service.c.s

proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o.requires:

.PHONY : proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o.requires

proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o.provides: proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o.requires
	$(MAKE) -f proto/CMakeFiles/proto.dir/build.make proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o.provides.build
.PHONY : proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o.provides

proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o.provides.build: proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o


# Object files for target proto
proto_OBJECTS = \
"CMakeFiles/proto.dir/parser.grpc-c.c.o" \
"CMakeFiles/proto.dir/parser.grpc-c.service.c.o"

# External object files for target proto
proto_EXTERNAL_OBJECTS =

proto/libproto.a: proto/CMakeFiles/proto.dir/parser.grpc-c.c.o
proto/libproto.a: proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o
proto/libproto.a: proto/CMakeFiles/proto.dir/build.make
proto/libproto.a: proto/CMakeFiles/proto.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/temp/grpc_demo/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libproto.a"
	cd /root/temp/grpc_demo/proto && $(CMAKE_COMMAND) -P CMakeFiles/proto.dir/cmake_clean_target.cmake
	cd /root/temp/grpc_demo/proto && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proto.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
proto/CMakeFiles/proto.dir/build: proto/libproto.a

.PHONY : proto/CMakeFiles/proto.dir/build

proto/CMakeFiles/proto.dir/requires: proto/CMakeFiles/proto.dir/parser.grpc-c.c.o.requires
proto/CMakeFiles/proto.dir/requires: proto/CMakeFiles/proto.dir/parser.grpc-c.service.c.o.requires

.PHONY : proto/CMakeFiles/proto.dir/requires

proto/CMakeFiles/proto.dir/clean:
	cd /root/temp/grpc_demo/proto && $(CMAKE_COMMAND) -P CMakeFiles/proto.dir/cmake_clean.cmake
.PHONY : proto/CMakeFiles/proto.dir/clean

proto/CMakeFiles/proto.dir/depend:
	cd /root/temp/grpc_demo && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/temp/grpc_demo /root/temp/grpc_demo/proto /root/temp/grpc_demo /root/temp/grpc_demo/proto /root/temp/grpc_demo/proto/CMakeFiles/proto.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : proto/CMakeFiles/proto.dir/depend

