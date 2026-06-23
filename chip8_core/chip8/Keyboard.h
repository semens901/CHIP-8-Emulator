#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SDL2/SDL_keycode.h>

class Keyboard
{
public:
    Keyboard() = default;

    void key_down(SDL_Keycode key);
    void key_up(SDL_Keycode key);

    bool is_pressed(int chip8_key) const;
    uint8_t get_pressed_key() const;
private:
    uint8_t keys_[16] = {};
};

#endif //KEYBOARD_H