#ifndef DISPLAY_H
#define DISPLAY_H
#include <cstdint>

constexpr uint8_t WIDTH = 64;
constexpr uint8_t HEIGHT = 32;



class Display
{
private:
    uint8_t pixels[WIDTH * HEIGHT] = {0};
};

#endif //DISPLAY_H