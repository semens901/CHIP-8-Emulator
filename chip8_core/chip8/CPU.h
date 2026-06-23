#ifndef CPU_H
#define CPU_H
#include <cstdint>
#include <iomanip>
#include <stack>
#include <iostream>


#include "Memory.h"
#include "Opcode.h"
#include "Display.h"
#include "Font.h"
#include "Keyboard.h"
#include "Font.h"
#include "Speaker.h"

static constexpr uint8_t STACK_SIZE = 16;

class CPU
{
public:
    CPU(Memory& memory, Display& display, Keyboard& keyboard, Speaker& speaker) : registers_{
        .I = 0x0,
        .PC = 0x200,  
        .SP = 0x0, 
        .DT = 0x0, 
        .ST = 0x0,
        .ur= {}},
        memory_(memory),
        display_(display),
        keyboard_(keyboard),
        speaker_(speaker),
        stack_{0} {};

    void read_instruction();
    bool execute_instruction();
    void cycle();
    void reset();

    void update_timers();

private:
    struct Registers
    {
        struct UR
        {
            /*
                The VF register should not be used by any program because it is used as a flag by some instructions.
            */
            uint8_t V[16] = {0};
        };

        // This register is used to store memory addresses.
        uint16_t I; 

        // Used to store the current execution address.
        uint16_t PC; 

        // The stack pointer (SP) can be 8-bit and is used to point to the topmost level of the stack.
        uint8_t SP; 

        // delay timer
        uint16_t DT;

        // Sound timer
        uint16_t ST;

        UR ur;
        
    };

    
    Registers registers_;
    bool waiting_for_key_ = false;
    uint8_t waiting_register_;
    Opcode opcode_;
    uint16_t stack_[STACK_SIZE];
    Memory& memory_;
    Display& display_;
    Keyboard& keyboard_;
    Speaker& speaker_;
};

#endif //CPU_H