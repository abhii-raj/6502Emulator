cmake_minimum_required(VERSION 3.24)
project(6502Emulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(6502Emulator main.cpp processor.cpp processor.hpp memory.cpp memory.hpp instructionCycle.cpp instructionCycle.hpp codeLoad.cpp codeLoad.hpp)
