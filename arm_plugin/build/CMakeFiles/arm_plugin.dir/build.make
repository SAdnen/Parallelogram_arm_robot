# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/adnen/workspace/arm_plugin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/adnen/workspace/arm_plugin/build

# Include any dependencies generated for this target.
include CMakeFiles/arm_plugin.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/arm_plugin.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/arm_plugin.dir/flags.make

CMakeFiles/arm_plugin.dir/arm_plugin.cc.o: CMakeFiles/arm_plugin.dir/flags.make
CMakeFiles/arm_plugin.dir/arm_plugin.cc.o: ../arm_plugin.cc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/adnen/workspace/arm_plugin/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/arm_plugin.dir/arm_plugin.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/arm_plugin.dir/arm_plugin.cc.o -c /home/adnen/workspace/arm_plugin/arm_plugin.cc

CMakeFiles/arm_plugin.dir/arm_plugin.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/arm_plugin.dir/arm_plugin.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/adnen/workspace/arm_plugin/arm_plugin.cc > CMakeFiles/arm_plugin.dir/arm_plugin.cc.i

CMakeFiles/arm_plugin.dir/arm_plugin.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/arm_plugin.dir/arm_plugin.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/adnen/workspace/arm_plugin/arm_plugin.cc -o CMakeFiles/arm_plugin.dir/arm_plugin.cc.s

CMakeFiles/arm_plugin.dir/arm_plugin.cc.o.requires:
.PHONY : CMakeFiles/arm_plugin.dir/arm_plugin.cc.o.requires

CMakeFiles/arm_plugin.dir/arm_plugin.cc.o.provides: CMakeFiles/arm_plugin.dir/arm_plugin.cc.o.requires
	$(MAKE) -f CMakeFiles/arm_plugin.dir/build.make CMakeFiles/arm_plugin.dir/arm_plugin.cc.o.provides.build
.PHONY : CMakeFiles/arm_plugin.dir/arm_plugin.cc.o.provides

CMakeFiles/arm_plugin.dir/arm_plugin.cc.o.provides.build: CMakeFiles/arm_plugin.dir/arm_plugin.cc.o

# Object files for target arm_plugin
arm_plugin_OBJECTS = \
"CMakeFiles/arm_plugin.dir/arm_plugin.cc.o"

# External object files for target arm_plugin
arm_plugin_EXTERNAL_OBJECTS =

libarm_plugin.so: CMakeFiles/arm_plugin.dir/arm_plugin.cc.o
libarm_plugin.so: CMakeFiles/arm_plugin.dir/build.make
libarm_plugin.so: /opt/ros/indigo/lib/libroscpp.so
libarm_plugin.so: /usr/lib/x86_64-linux-gnu/libboost_signals.so
libarm_plugin.so: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
libarm_plugin.so: /opt/ros/indigo/lib/librosconsole.so
libarm_plugin.so: /opt/ros/indigo/lib/librosconsole_log4cxx.so
libarm_plugin.so: /opt/ros/indigo/lib/librosconsole_backend_interface.so
libarm_plugin.so: /usr/lib/liblog4cxx.so
libarm_plugin.so: /usr/lib/x86_64-linux-gnu/libboost_regex.so
libarm_plugin.so: /opt/ros/indigo/lib/libroscpp_serialization.so
libarm_plugin.so: /opt/ros/indigo/lib/librostime.so
libarm_plugin.so: /usr/lib/x86_64-linux-gnu/libboost_date_time.so
libarm_plugin.so: /opt/ros/indigo/lib/libxmlrpcpp.so
libarm_plugin.so: /opt/ros/indigo/lib/libcpp_common.so
libarm_plugin.so: /usr/lib/x86_64-linux-gnu/libboost_system.so
libarm_plugin.so: /usr/lib/x86_64-linux-gnu/libboost_thread.so
libarm_plugin.so: /usr/lib/x86_64-linux-gnu/libpthread.so
libarm_plugin.so: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so
libarm_plugin.so: CMakeFiles/arm_plugin.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libarm_plugin.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/arm_plugin.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/arm_plugin.dir/build: libarm_plugin.so
.PHONY : CMakeFiles/arm_plugin.dir/build

CMakeFiles/arm_plugin.dir/requires: CMakeFiles/arm_plugin.dir/arm_plugin.cc.o.requires
.PHONY : CMakeFiles/arm_plugin.dir/requires

CMakeFiles/arm_plugin.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/arm_plugin.dir/cmake_clean.cmake
.PHONY : CMakeFiles/arm_plugin.dir/clean

CMakeFiles/arm_plugin.dir/depend:
	cd /home/adnen/workspace/arm_plugin/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/adnen/workspace/arm_plugin /home/adnen/workspace/arm_plugin /home/adnen/workspace/arm_plugin/build /home/adnen/workspace/arm_plugin/build /home/adnen/workspace/arm_plugin/build/CMakeFiles/arm_plugin.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/arm_plugin.dir/depend

