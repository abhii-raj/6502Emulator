cmake_minimum_required(VERSION 3.24)
project(6502Emulator)

set(CMAKE_CXX_STANDARD 17)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

set(Headers src/processor.hpp src/memory.hpp src/instructionCycle.hpp src/codeLoad.hpp src/dataView.hpp)
add_executable(6502Emulator ${PROJECT_SOURCE_DIR}/ src/main.cpp src/processor.cpp src/memory.cpp src/instructionCycle.cpp
        src/codeLoad.cpp src/dataView.cpp src/ui_render.cpp src/ui_render.hpp)
target_link_libraries(6502Emulator ${GTK3_LIBRARIES})