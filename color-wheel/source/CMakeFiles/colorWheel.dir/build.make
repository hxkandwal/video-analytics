# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_SOURCE_DIR = /Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous

# Include any dependencies generated for this target.
include CMakeFiles/colorWheel.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/colorWheel.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/colorWheel.dir/flags.make

CMakeFiles/colorWheel.dir/colorWheel.cpp.o: CMakeFiles/colorWheel.dir/flags.make
CMakeFiles/colorWheel.dir/colorWheel.cpp.o: colorWheel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/colorWheel.dir/colorWheel.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/colorWheel.dir/colorWheel.cpp.o -c /Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous/colorWheel.cpp

CMakeFiles/colorWheel.dir/colorWheel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/colorWheel.dir/colorWheel.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous/colorWheel.cpp > CMakeFiles/colorWheel.dir/colorWheel.cpp.i

CMakeFiles/colorWheel.dir/colorWheel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/colorWheel.dir/colorWheel.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous/colorWheel.cpp -o CMakeFiles/colorWheel.dir/colorWheel.cpp.s

CMakeFiles/colorWheel.dir/colorWheel.cpp.o.requires:

.PHONY : CMakeFiles/colorWheel.dir/colorWheel.cpp.o.requires

CMakeFiles/colorWheel.dir/colorWheel.cpp.o.provides: CMakeFiles/colorWheel.dir/colorWheel.cpp.o.requires
	$(MAKE) -f CMakeFiles/colorWheel.dir/build.make CMakeFiles/colorWheel.dir/colorWheel.cpp.o.provides.build
.PHONY : CMakeFiles/colorWheel.dir/colorWheel.cpp.o.provides

CMakeFiles/colorWheel.dir/colorWheel.cpp.o.provides.build: CMakeFiles/colorWheel.dir/colorWheel.cpp.o


# Object files for target colorWheel
colorWheel_OBJECTS = \
"CMakeFiles/colorWheel.dir/colorWheel.cpp.o"

# External object files for target colorWheel
colorWheel_EXTERNAL_OBJECTS =

colorWheel: CMakeFiles/colorWheel.dir/colorWheel.cpp.o
colorWheel: CMakeFiles/colorWheel.dir/build.make
colorWheel: /usr/local/lib/libopencv_core.a
colorWheel: /usr/local/lib/libopencv_flann.a
colorWheel: /usr/local/lib/libopencv_imgproc.a
colorWheel: /usr/local/lib/libopencv_highgui.a
colorWheel: /usr/local/lib/libopencv_features2d.a
colorWheel: /usr/local/lib/libopencv_calib3d.a
colorWheel: /usr/local/lib/libopencv_ml.a
colorWheel: /usr/local/lib/libopencv_video.a
colorWheel: /usr/local/lib/libopencv_legacy.a
colorWheel: /usr/local/lib/libopencv_objdetect.a
colorWheel: /usr/local/lib/libopencv_photo.a
colorWheel: /usr/local/lib/libopencv_gpu.a
colorWheel: /usr/local/lib/libopencv_videostab.a
colorWheel: /usr/local/lib/libopencv_ts.a
colorWheel: /usr/local/lib/libopencv_ocl.a
colorWheel: /usr/local/lib/libopencv_superres.a
colorWheel: /usr/local/lib/libopencv_nonfree.a
colorWheel: /usr/local/lib/libopencv_stitching.a
colorWheel: /usr/local/lib/libopencv_contrib.a
colorWheel: /usr/local/lib/libopencv_nonfree.a
colorWheel: /usr/local/lib/libopencv_gpu.a
colorWheel: /usr/local/lib/libopencv_legacy.a
colorWheel: /usr/local/lib/libopencv_photo.a
colorWheel: /usr/local/lib/libopencv_ocl.a
colorWheel: /usr/local/lib/libopencv_calib3d.a
colorWheel: /usr/local/lib/libopencv_features2d.a
colorWheel: /usr/local/lib/libopencv_flann.a
colorWheel: /usr/local/lib/libopencv_ml.a
colorWheel: /usr/local/lib/libopencv_video.a
colorWheel: /usr/local/lib/libopencv_objdetect.a
colorWheel: /usr/local/lib/libopencv_highgui.a
colorWheel: /usr/local/lib/libopencv_imgproc.a
colorWheel: /usr/local/lib/libopencv_core.a
colorWheel: /usr/local/share/OpenCV/3rdparty/lib/liblibjpeg.a
colorWheel: /usr/local/share/OpenCV/3rdparty/lib/liblibpng.a
colorWheel: /usr/local/share/OpenCV/3rdparty/lib/liblibtiff.a
colorWheel: /usr/local/share/OpenCV/3rdparty/lib/liblibjasper.a
colorWheel: /usr/local/share/OpenCV/3rdparty/lib/libIlmImf.a
colorWheel: /usr/local/share/OpenCV/3rdparty/lib/libzlib.a
colorWheel: CMakeFiles/colorWheel.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable colorWheel"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/colorWheel.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/colorWheel.dir/build: colorWheel

.PHONY : CMakeFiles/colorWheel.dir/build

CMakeFiles/colorWheel.dir/requires: CMakeFiles/colorWheel.dir/colorWheel.cpp.o.requires

.PHONY : CMakeFiles/colorWheel.dir/requires

CMakeFiles/colorWheel.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/colorWheel.dir/cmake_clean.cmake
.PHONY : CMakeFiles/colorWheel.dir/clean

CMakeFiles/colorWheel.dir/depend:
	cd /Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous /Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous /Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous /Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous /Users/Heman/Documents/workstation/College/Homework/VA/Miscellaneous/CMakeFiles/colorWheel.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/colorWheel.dir/depend
