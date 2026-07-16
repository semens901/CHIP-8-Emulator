add_executable(chip8_tests
    main.cpp
    CPUTests.cpp
    DisplayTests.cpp
    OpcodeTests.cpp
)

find_package(SDL2 REQUIRED)

target_link_libraries(
    chip8_tests
    PRIVATE
        chip8_core
        ${SDL2_LIBRARIES}
)

target_include_directories(
    chip8_tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/chip8_core
)

add_test(NAME chip8_tests COMMAND chip8_tests)