cmake_minimum_required(VERSION 3.24)
project(6502Emulator)

set(CMAKE_CXX_STANDARD 17)
set(Headers src/processor.hpp src/memory.hpp src/instructionCycle.hpp src/codeLoad.hpp src/dataView.hpp)
add_executable(6502Emulator ${PROJECT_SOURCE_DIR}/ src/main.cpp src/processor.cpp src/memory.cpp src/instructionCycle.cpp
        src/codeLoad.cpp src/dataView.cpp)
