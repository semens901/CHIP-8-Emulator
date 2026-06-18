#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard
{
public:
    

    void key_down(int chip8_key);
    void key_up(int chip8_key);

    bool is_pressed(int chip8_key) const;
private:
    bool keys_[16] = {};
};

#endif //KEYBOARD_H