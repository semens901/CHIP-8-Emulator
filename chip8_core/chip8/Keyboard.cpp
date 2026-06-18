#include "chip8/Keyboard.h"

void Keyboard::key_down(int key)
{
    keys_[key] = true;
}

void Keyboard::key_up(int key)
{
    keys_[key] = false;
}

bool Keyboard::is_pressed(int key) const
{
    return keys_[key];
}