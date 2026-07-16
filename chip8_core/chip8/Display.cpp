#include "Display.h"

Display::Display(const std::string& title) : width_(WIDTH*10), height_(HEIGHT*10)
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

    // black background immediately
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
}

Display::~Display()
{
    if (renderer_) SDL_DestroyRenderer(renderer_);
    if (window_) SDL_DestroyWindow(window_);

    SDL_Quit();
}

bool Display::render_frame()
{
    /*
        This function is responsible for rendering a frame to the display. 
        It first clears the renderer, then draws the current state of the screen, 
        and finally presents the rendered frame. 
        If any errors occur during these operations, 
        they are caught and logged, and the function returns false to indicate failure.
        The function returns true if the frame was rendered successfully.
    */
    try
    {
        clear_renderer();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error clearing renderer: " << e.what() << std::endl;
        return false;
    }
    
    try
    {
        draw_screen();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error drawing screen: " << e.what() << std::endl;
        return false;
    }

    try
    {
        render();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error presenting renderer: " << e.what() << std::endl;
        return false;
    }

    return true;
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
    if(SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255))
    {
        throw std::runtime_error(SDL_GetError());
    }
    if(SDL_RenderClear(renderer_))
    {
        throw std::runtime_error(SDL_GetError());
    }
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
    if(SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255))
    {
        throw std::runtime_error(SDL_GetError());
    }

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

            if(SDL_RenderFillRect(renderer_, &pixel))
            {
                throw std::runtime_error(SDL_GetError());
            }
        }
    }
}

void Display::render()
{
    try
    {
        SDL_RenderPresent(renderer_);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error presenting renderer: " << e.what() << std::endl;
        throw; // Re-throw the exception to be handled by the caller
    }
}

bool Display::poll_events(Keyboard& keyboard) const
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            return false;
        if (event.type == SDL_KEYDOWN)
            keyboard.key_down(event.key.keysym.sym);

        if (event.type == SDL_KEYUP)
            keyboard.key_up(event.key.keysym.sym);
    }

    return true;
}

uint8_t Display::get_pixel(const uint8_t &x, const uint8_t &y) const
{
    if (x >= 64 || y >= 32)
        return false;

    return screen_[y][x];
}
