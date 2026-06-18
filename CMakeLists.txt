cmake_minimum_required(VERSION 3.20)

project(
    Chip8
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



# --------------------------------------------------
# SDL2
# --------------------------------------------------

find_package(SDL2 REQUIRED)

# --------------------------------------------------
# Core library
# --------------------------------------------------

add_library(chip8_core
    chip8_core/chip8/CPU.cpp
    chip8_core/chip8/Display.cpp
    chip8_core/chip8/Keyboard.cpp
    chip8_core/chip8/Memory.cpp
    chip8_core/chip8/Font.h
    chip8_core/chip8/Opcode.cpp
)

target_include_directories(
    chip8_core
    PUBLIC
        ${PROJECT_SOURCE_DIR}/chip8_core
)

# --------------------------------------------------
# Emulator executable
# --------------------------------------------------

add_executable(chip8_emulator
    main.cpp
)

target_link_libraries(
    chip8_emulator
    PRIVATE
        chip8_core
        SDL2::SDL2
)

# --------------------------------------------------
# Tests
# --------------------------------------------------

add_subdirectory(tests)