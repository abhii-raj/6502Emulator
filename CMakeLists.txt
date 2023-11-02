cmake_minimum_required(VERSION 3.24)
project(6502Emulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(6502Emulator src/main.cpp src/processor.cpp src/processor.hpp src/memory.cpp src/memory.hpp src/instructionCycle.cpp src/instructionCycle.hpp src/codeLoad.cpp src/codeLoad.hpp)
