#ifndef CHIP8_H
#define CHIP8_H

#include "CPU.h"
#include "Display.h"
#include "Keyboard.h"
#include "Memory.h"

class Emulator
{
public:
    Emulator() = default;

    void Emulator_loop();
    
    void Fetch();
    void Decode();
    void Execute();
    

private:
    CPU cpu_;
    uint16_t opcode;
};

#endif // CHIP8_H