# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.16.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.16.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cc/Desktop/HelloPass-LLVM-master/Pass/Transforms/LivenessAnalysis

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cc/Desktop/HelloPass-LLVM-master/Pass/build

# Include any dependencies generated for this target.
include CMakeFiles/LLVMLivenessAnalysisPass.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LLVMLivenessAnalysisPass.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LLVMLivenessAnalysisPass.dir/flags.make

CMakeFiles/LLVMLivenessAnalysisPass.dir/LivenessAnalysis.cpp.o: CMakeFiles/LLVMLivenessAnalysisPass.dir/flags.make
CMakeFiles/LLVMLivenessAnalysisPass.dir/LivenessAnalysis.cpp.o: /Users/cc/Desktop/HelloPass-LLVM-master/Pass/Transforms/LivenessAnalysis/LivenessAnalysis.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cc/Desktop/HelloPass-LLVM-master/Pass/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LLVMLivenessAnalysisPass.dir/LivenessAnalysis.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LLVMLivenessAnalysisPass.dir/LivenessAnalysis.cpp.o -c /Users/cc/Desktop/HelloPass-LLVM-master/Pass/Transforms/LivenessAnalysis/LivenessAnalysis.cpp

CMakeFiles/LLVMLivenessAnalysisPass.dir/LivenessAnalysis.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LLVMLivenessAnalysisPass.dir/LivenessAnalysis.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cc/Desktop/HelloPass-LLVM-master/Pass/Transforms/LivenessAnalysis/LivenessAnalysis.cpp > CMakeFiles/LLVMLivenessAnalysisPass.dir/LivenessAnalysis.cpp.i

CMakeFiles/LLVMLivenessAnalysisPass.dir/LivenessAnalysis.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LLVMLivenessAnalysisPass.dir/LivenessAnalysis.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cc/Desktop/HelloPass-LLVM-master/Pass/Transforms/LivenessAnalysis/LivenessAnalysis.cpp -o CMakeFiles/LLVMLivenessAnalysisPass.dir/LivenessAnalysis.cpp.s

# Object files for target LLVMLivenessAnalysisPass
LLVMLivenessAnalysisPass_OBJECTS = \
"CMakeFiles/LLVMLivenessAnalysisPass.dir/LivenessAnalysis.cpp.o"

# External object files for target LLVMLivenessAnalysisPass
LLVMLivenessAnalysisPass_EXTERNAL_OBJECTS =

libLLVMLivenessAnalysisPass.so: CMakeFiles/LLVMLivenessAnalysisPass.dir/LivenessAnalysis.cpp.o
libLLVMLivenessAnalysisPass.so: CMakeFiles/LLVMLivenessAnalysisPass.dir/build.make
libLLVMLivenessAnalysisPass.so: CMakeFiles/LLVMLivenessAnalysisPass.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/cc/Desktop/HelloPass-LLVM-master/Pass/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared module libLLVMLivenessAnalysisPass.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LLVMLivenessAnalysisPass.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LLVMLivenessAnalysisPass.dir/build: libLLVMLivenessAnalysisPass.so

.PHONY : CMakeFiles/LLVMLivenessAnalysisPass.dir/build

CMakeFiles/LLVMLivenessAnalysisPass.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LLVMLivenessAnalysisPass.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LLVMLivenessAnalysisPass.dir/clean

CMakeFiles/LLVMLivenessAnalysisPass.dir/depend:
	cd /Users/cc/Desktop/HelloPass-LLVM-master/Pass/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cc/Desktop/HelloPass-LLVM-master/Pass/Transforms/LivenessAnalysis /Users/cc/Desktop/HelloPass-LLVM-master/Pass/Transforms/LivenessAnalysis /Users/cc/Desktop/HelloPass-LLVM-master/Pass/build /Users/cc/Desktop/HelloPass-LLVM-master/Pass/build /Users/cc/Desktop/HelloPass-LLVM-master/Pass/build/CMakeFiles/LLVMLivenessAnalysisPass.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LLVMLivenessAnalysisPass.dir/depend

