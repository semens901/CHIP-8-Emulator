add_executable(chip8_tests
    main.cpp
    CPUTests.cpp
    DisplayTests.cpp
)

target_link_libraries(
    chip8_tests
    PRIVATE
        chip8_core
)

target_include_directories(
    chip8_tests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/chip8_core
)