#include "DisplayTests.h"
#include "chip8/Display.h"
#include <cassert>
#include <cstdlib>

static void configure_sdl_for_tests()
{
    // Use SDL's dummy video driver so the tests can instantiate the display without a real window.
    setenv("SDL_VIDEODRIVER", "dummy", 1);
}

static void test_display_clear_resets_all_pixels()
{
    // Ensures that clear removes every pixel from the display buffer.
    configure_sdl_for_tests();

    Display display("Test Display");
    display.set_pixel(10, 5, 1);
    display.set_pixel(20, 15, 1);

    display.clear();

    assert(display.get_pixel(10, 5) == 0);
    assert(display.get_pixel(20, 15) == 0);
}

static void test_display_set_pixel_and_get_pixel_round_trip()
{
    // Ensures that a pixel written through set_pixel is readable through get_pixel.
    configure_sdl_for_tests();

    Display display("Test Display");

    display.set_pixel(3, 4, 1);

    std::cout << "Pixel at (3, 4): " << static_cast<int>(display.get_pixel(3, 4)) << std::endl;

    assert(display.get_pixel(4, 3) == 1);
    assert(display.get_pixel(3, 4) == 0);
}

static void test_display_xor_pixel_flips_state_and_reports_previous_value()
{
    // Ensures that xor_pixel toggles a pixel and returns whether the pixel was turned off.
    configure_sdl_for_tests();

    Display display("Test Display");

    assert(display.xor_pixel(1, 1) == 0);
    assert(display.get_pixel(1, 1) == 1);
    assert(display.xor_pixel(1, 1) == 1);
    assert(display.get_pixel(1, 1) == 0);
}

static void test_display_xor_pixel_ignores_out_of_bounds_coordinates()
{
    // Ensures that out-of-bounds coordinates are ignored safely.
    configure_sdl_for_tests();

    Display display("Test Display");

    assert(display.xor_pixel(64, 0) == 0);
    assert(display.xor_pixel(0, 32) == 0);
    assert(display.get_pixel(64, 0) == 0);
}

void run_display_tests()
{
    test_display_clear_resets_all_pixels();
    test_display_set_pixel_and_get_pixel_round_trip();
    test_display_xor_pixel_flips_state_and_reports_previous_value();
    test_display_xor_pixel_ignores_out_of_bounds_coordinates();
}