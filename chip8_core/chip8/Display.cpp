#include "chip8/Display.h"
#include "Display.h"

Display::Display(const std::string &title) : width_(WIDTH*10), height_(HEIGHT*10)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        throw std::runtime_error(SDL_GetError());
    }

    window_ = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width_,
        height_,
        SDL_WINDOW_SHOWN
    );

    if (!window_)
    {
        throw std::runtime_error(SDL_GetError());
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer_)
    {
        throw std::runtime_error(SDL_GetError());
    }

    // чёрный фон сразу
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
}

Display::~Display()
{
    if (renderer_) SDL_DestroyRenderer(renderer_);
    if (window_) SDL_DestroyWindow(window_);

    SDL_Quit();
}

void Display::render_frame()
{
    clear_renderer();
    draw_screen();
    render();
}

void Display::clear()
{
    for(size_t i = 0; i < HEIGHT; ++i)
    {
        for(size_t j = 0; j < WIDTH; ++j)
            screen_[i][j] = 0;
    }
}

void Display::clear_renderer()
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

void Display::set_pixel(uint8_t x, uint8_t y, uint8_t value)
{
    screen_[x][y] = value;
}

uint8_t Display::xor_pixel(const uint8_t &x, const uint8_t &y)
{
    if (x >= 64 || y >= 32)
        return false;

    uint8_t& pixel = screen_[y][x];

    uint8_t old = pixel;

    pixel ^= 1;

    return old && !pixel;
}

void Display::draw_screen()
{
    // Рисовать включенные пиксели белым цветом
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);

    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            if (!screen_[y][x])
                continue;

            SDL_Rect pixel;
            pixel.x = x * SCALE;
            pixel.y = y * SCALE;
            pixel.w = SCALE;
            pixel.h = SCALE;

            SDL_RenderFillRect(renderer_, &pixel);
        }
    }
}

void Display::render()
{
    SDL_RenderPresent(renderer_);
}

void Display::poll_events()
{

}

bool Display::is_running() const
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return false;
        }
    }

    return true;
}

uint8_t Display::get_pixel(const uint8_t &x, const uint8_t &y) const
{
    if (x >= 64 || y >= 32)
        return false;

    return screen_[y][x];
}
