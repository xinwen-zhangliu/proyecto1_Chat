# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_SOURCE_DIR = /home/xinwen/proyecto1_Chat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/xinwen/proyecto1_Chat

# Include any dependencies generated for this target.
include Server/CMakeFiles/Server.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Server/CMakeFiles/Server.dir/compiler_depend.make

# Include the progress variables for this target.
include Server/CMakeFiles/Server.dir/progress.make

# Include the compile flags for this target's objects.
include Server/CMakeFiles/Server.dir/flags.make

Server/CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o: Server/CMakeFiles/Server.dir/flags.make
Server/CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o: Server/Server_autogen/mocs_compilation.cpp
Server/CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o: Server/CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xinwen/proyecto1_Chat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Server/CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Server/CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o -MF CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o -c /home/xinwen/proyecto1_Chat/Server/Server_autogen/mocs_compilation.cpp

Server/CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.i"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xinwen/proyecto1_Chat/Server/Server_autogen/mocs_compilation.cpp > CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.i

Server/CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.s"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xinwen/proyecto1_Chat/Server/Server_autogen/mocs_compilation.cpp -o CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.s

Server/CMakeFiles/Server.dir/servermain.cpp.o: Server/CMakeFiles/Server.dir/flags.make
Server/CMakeFiles/Server.dir/servermain.cpp.o: Server/servermain.cpp
Server/CMakeFiles/Server.dir/servermain.cpp.o: Server/CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xinwen/proyecto1_Chat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Server/CMakeFiles/Server.dir/servermain.cpp.o"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Server/CMakeFiles/Server.dir/servermain.cpp.o -MF CMakeFiles/Server.dir/servermain.cpp.o.d -o CMakeFiles/Server.dir/servermain.cpp.o -c /home/xinwen/proyecto1_Chat/Server/servermain.cpp

Server/CMakeFiles/Server.dir/servermain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/servermain.cpp.i"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xinwen/proyecto1_Chat/Server/servermain.cpp > CMakeFiles/Server.dir/servermain.cpp.i

Server/CMakeFiles/Server.dir/servermain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/servermain.cpp.s"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xinwen/proyecto1_Chat/Server/servermain.cpp -o CMakeFiles/Server.dir/servermain.cpp.s

Server/CMakeFiles/Server.dir/Sources/chatserver.cpp.o: Server/CMakeFiles/Server.dir/flags.make
Server/CMakeFiles/Server.dir/Sources/chatserver.cpp.o: Server/Sources/chatserver.cpp
Server/CMakeFiles/Server.dir/Sources/chatserver.cpp.o: Server/CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xinwen/proyecto1_Chat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Server/CMakeFiles/Server.dir/Sources/chatserver.cpp.o"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Server/CMakeFiles/Server.dir/Sources/chatserver.cpp.o -MF CMakeFiles/Server.dir/Sources/chatserver.cpp.o.d -o CMakeFiles/Server.dir/Sources/chatserver.cpp.o -c /home/xinwen/proyecto1_Chat/Server/Sources/chatserver.cpp

Server/CMakeFiles/Server.dir/Sources/chatserver.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Sources/chatserver.cpp.i"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xinwen/proyecto1_Chat/Server/Sources/chatserver.cpp > CMakeFiles/Server.dir/Sources/chatserver.cpp.i

Server/CMakeFiles/Server.dir/Sources/chatserver.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Sources/chatserver.cpp.s"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xinwen/proyecto1_Chat/Server/Sources/chatserver.cpp -o CMakeFiles/Server.dir/Sources/chatserver.cpp.s

Server/CMakeFiles/Server.dir/Sources/room.cpp.o: Server/CMakeFiles/Server.dir/flags.make
Server/CMakeFiles/Server.dir/Sources/room.cpp.o: Server/Sources/room.cpp
Server/CMakeFiles/Server.dir/Sources/room.cpp.o: Server/CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xinwen/proyecto1_Chat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Server/CMakeFiles/Server.dir/Sources/room.cpp.o"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Server/CMakeFiles/Server.dir/Sources/room.cpp.o -MF CMakeFiles/Server.dir/Sources/room.cpp.o.d -o CMakeFiles/Server.dir/Sources/room.cpp.o -c /home/xinwen/proyecto1_Chat/Server/Sources/room.cpp

Server/CMakeFiles/Server.dir/Sources/room.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Sources/room.cpp.i"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xinwen/proyecto1_Chat/Server/Sources/room.cpp > CMakeFiles/Server.dir/Sources/room.cpp.i

Server/CMakeFiles/Server.dir/Sources/room.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Sources/room.cpp.s"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xinwen/proyecto1_Chat/Server/Sources/room.cpp -o CMakeFiles/Server.dir/Sources/room.cpp.s

Server/CMakeFiles/Server.dir/Sources/serverwindow.cpp.o: Server/CMakeFiles/Server.dir/flags.make
Server/CMakeFiles/Server.dir/Sources/serverwindow.cpp.o: Server/Sources/serverwindow.cpp
Server/CMakeFiles/Server.dir/Sources/serverwindow.cpp.o: Server/CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xinwen/proyecto1_Chat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object Server/CMakeFiles/Server.dir/Sources/serverwindow.cpp.o"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Server/CMakeFiles/Server.dir/Sources/serverwindow.cpp.o -MF CMakeFiles/Server.dir/Sources/serverwindow.cpp.o.d -o CMakeFiles/Server.dir/Sources/serverwindow.cpp.o -c /home/xinwen/proyecto1_Chat/Server/Sources/serverwindow.cpp

Server/CMakeFiles/Server.dir/Sources/serverwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Sources/serverwindow.cpp.i"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xinwen/proyecto1_Chat/Server/Sources/serverwindow.cpp > CMakeFiles/Server.dir/Sources/serverwindow.cpp.i

Server/CMakeFiles/Server.dir/Sources/serverwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Sources/serverwindow.cpp.s"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xinwen/proyecto1_Chat/Server/Sources/serverwindow.cpp -o CMakeFiles/Server.dir/Sources/serverwindow.cpp.s

Server/CMakeFiles/Server.dir/Sources/serverworker.cpp.o: Server/CMakeFiles/Server.dir/flags.make
Server/CMakeFiles/Server.dir/Sources/serverworker.cpp.o: Server/Sources/serverworker.cpp
Server/CMakeFiles/Server.dir/Sources/serverworker.cpp.o: Server/CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xinwen/proyecto1_Chat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object Server/CMakeFiles/Server.dir/Sources/serverworker.cpp.o"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Server/CMakeFiles/Server.dir/Sources/serverworker.cpp.o -MF CMakeFiles/Server.dir/Sources/serverworker.cpp.o.d -o CMakeFiles/Server.dir/Sources/serverworker.cpp.o -c /home/xinwen/proyecto1_Chat/Server/Sources/serverworker.cpp

Server/CMakeFiles/Server.dir/Sources/serverworker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Sources/serverworker.cpp.i"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xinwen/proyecto1_Chat/Server/Sources/serverworker.cpp > CMakeFiles/Server.dir/Sources/serverworker.cpp.i

Server/CMakeFiles/Server.dir/Sources/serverworker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Sources/serverworker.cpp.s"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xinwen/proyecto1_Chat/Server/Sources/serverworker.cpp -o CMakeFiles/Server.dir/Sources/serverworker.cpp.s

Server/CMakeFiles/Server.dir/Sources/user.cpp.o: Server/CMakeFiles/Server.dir/flags.make
Server/CMakeFiles/Server.dir/Sources/user.cpp.o: Server/Sources/user.cpp
Server/CMakeFiles/Server.dir/Sources/user.cpp.o: Server/CMakeFiles/Server.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/xinwen/proyecto1_Chat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object Server/CMakeFiles/Server.dir/Sources/user.cpp.o"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Server/CMakeFiles/Server.dir/Sources/user.cpp.o -MF CMakeFiles/Server.dir/Sources/user.cpp.o.d -o CMakeFiles/Server.dir/Sources/user.cpp.o -c /home/xinwen/proyecto1_Chat/Server/Sources/user.cpp

Server/CMakeFiles/Server.dir/Sources/user.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Server.dir/Sources/user.cpp.i"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/xinwen/proyecto1_Chat/Server/Sources/user.cpp > CMakeFiles/Server.dir/Sources/user.cpp.i

Server/CMakeFiles/Server.dir/Sources/user.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Server.dir/Sources/user.cpp.s"
	cd /home/xinwen/proyecto1_Chat/Server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/xinwen/proyecto1_Chat/Server/Sources/user.cpp -o CMakeFiles/Server.dir/Sources/user.cpp.s

# Object files for target Server
Server_OBJECTS = \
"CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/Server.dir/servermain.cpp.o" \
"CMakeFiles/Server.dir/Sources/chatserver.cpp.o" \
"CMakeFiles/Server.dir/Sources/room.cpp.o" \
"CMakeFiles/Server.dir/Sources/serverwindow.cpp.o" \
"CMakeFiles/Server.dir/Sources/serverworker.cpp.o" \
"CMakeFiles/Server.dir/Sources/user.cpp.o"

# External object files for target Server
Server_EXTERNAL_OBJECTS =

Server/Server-1.0.0: Server/CMakeFiles/Server.dir/Server_autogen/mocs_compilation.cpp.o
Server/Server-1.0.0: Server/CMakeFiles/Server.dir/servermain.cpp.o
Server/Server-1.0.0: Server/CMakeFiles/Server.dir/Sources/chatserver.cpp.o
Server/Server-1.0.0: Server/CMakeFiles/Server.dir/Sources/room.cpp.o
Server/Server-1.0.0: Server/CMakeFiles/Server.dir/Sources/serverwindow.cpp.o
Server/Server-1.0.0: Server/CMakeFiles/Server.dir/Sources/serverworker.cpp.o
Server/Server-1.0.0: Server/CMakeFiles/Server.dir/Sources/user.cpp.o
Server/Server-1.0.0: Server/CMakeFiles/Server.dir/build.make
Server/Server-1.0.0: /usr/lib/libQt6Widgets.so.6.3.2
Server/Server-1.0.0: /usr/lib/libQt6Network.so.6.3.2
Server/Server-1.0.0: /usr/lib/libQt6Gui.so.6.3.2
Server/Server-1.0.0: /usr/lib/libGLX.so
Server/Server-1.0.0: /usr/lib/libOpenGL.so
Server/Server-1.0.0: /usr/lib/libQt6Core.so.6.3.2
Server/Server-1.0.0: Server/CMakeFiles/Server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/xinwen/proyecto1_Chat/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable Server"
	cd /home/xinwen/proyecto1_Chat/Server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Server.dir/link.txt --verbose=$(VERBOSE)
	cd /home/xinwen/proyecto1_Chat/Server && $(CMAKE_COMMAND) -E cmake_symlink_executable Server-1.0.0 Server

Server/Server: Server/Server-1.0.0

# Rule to build all files generated by this target.
Server/CMakeFiles/Server.dir/build: Server/Server
.PHONY : Server/CMakeFiles/Server.dir/build

Server/CMakeFiles/Server.dir/clean:
	cd /home/xinwen/proyecto1_Chat/Server && $(CMAKE_COMMAND) -P CMakeFiles/Server.dir/cmake_clean.cmake
.PHONY : Server/CMakeFiles/Server.dir/clean

Server/CMakeFiles/Server.dir/depend:
	cd /home/xinwen/proyecto1_Chat && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/xinwen/proyecto1_Chat /home/xinwen/proyecto1_Chat/Server /home/xinwen/proyecto1_Chat /home/xinwen/proyecto1_Chat/Server /home/xinwen/proyecto1_Chat/Server/CMakeFiles/Server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Server/CMakeFiles/Server.dir/depend

