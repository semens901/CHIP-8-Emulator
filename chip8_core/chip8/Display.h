#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>
#include <SDL2/SDL.h>
#include <string>
#include <stdexcept>

static constexpr uint8_t WIDTH = 64;
static constexpr uint8_t HEIGHT = 32;
static constexpr int SCALE  = 10;

class Display
{
public:
    Display(const std::string& title);
    ~Display();

    void render_frame();

    void clear();
    void clear_renderer();
    void set_pixel(uint8_t x, uint8_t y, uint8_t value);
    uint8_t xor_pixel(const uint8_t& x, const uint8_t& y);
    uint8_t get_pixel(const uint8_t& x, const uint8_t& y) const;
    void draw_screen();
    void render();
    void poll_events();

    bool is_running() const;
private:
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;

    bool running_ = true;

    const int width_;
    const int height_;
    uint8_t screen_[HEIGHT][WIDTH] = {0};
};

#endif //DISPLAY_H