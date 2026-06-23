#include "chip8/Keyboard.h"

/*
    characters table
    1   |   1      
    2   |   2      
    3   |   3      
    4   |   C      
    Q   |   4      
    W   |   5      
    E   |   6      
    R   |   D      
    A   |   7      
    S   |   8      
    D   |   9      
    F   |   E      
    Z   |   A      
    X   |   0      
    C   |   B      
    V   |   F      
*/

void Keyboard::key_down(SDL_Keycode key)
{
    switch(key)
    {
        case SDLK_1: keys_[0x1] = true; break;
        case SDLK_2: keys_[0x2] = true; break;
        case SDLK_3: keys_[0x3] = true; break;
        case SDLK_4: keys_[0xC] = true; break;
        case SDLK_q: keys_[0x4] = true; break;
        case SDLK_w: keys_[0x5] = true; break;
        case SDLK_e: keys_[0x6] = true; break;
        case SDLK_r: keys_[0xD] = true; break;
        case SDLK_a: keys_[0x7] = true; break;
        case SDLK_s: keys_[0x8] = true; break;
        case SDLK_d: keys_[0x9] = true; break;
        case SDLK_f: keys_[0xE] = true; break;
        case SDLK_z: keys_[0xA] = true; break;
        case SDLK_x: keys_[0x0] = true; break;
        case SDLK_c: keys_[0xB] = true; break;
        case SDLK_v: keys_[0xF] = true; break;
    }
}

void Keyboard::key_up(SDL_Keycode key)
{
    switch(key)
    {
        case SDLK_1: keys_[0x1] = false; break;
        case SDLK_2: keys_[0x2] = false; break;
        case SDLK_3: keys_[0x3] = false; break;
        case SDLK_4: keys_[0xC] = false; break;
        case SDLK_q: keys_[0x4] = false; break;
        case SDLK_w: keys_[0x5] = false; break;
        case SDLK_e: keys_[0x6] = false; break;
        case SDLK_r: keys_[0xD] = false; break;
        case SDLK_a: keys_[0x7] = false; break;
        case SDLK_s: keys_[0x8] = false; break;
        case SDLK_d: keys_[0x9] = false; break;
        case SDLK_f: keys_[0xE] = false; break;
        case SDLK_z: keys_[0xA] = false; break;
        case SDLK_x: keys_[0x0] = false; break;
        case SDLK_c: keys_[0xB] = false; break;
        case SDLK_v: keys_[0xF] = false; break;
    }
}

bool Keyboard::is_pressed(int key) const
{
    return keys_[key];
}

uint8_t Keyboard::get_pressed_key() const
{
    for (int i = 0; i < 16; ++i)
    {
        if (keys_[i])
            return i;
    }

    return -1;
}