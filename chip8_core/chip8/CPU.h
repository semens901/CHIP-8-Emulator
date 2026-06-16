#ifndef CPU_H
#define CPU_H
#include <cstdint>
#include <iomanip>

#include "Memory.h"
class CPU
{
public:
    friend class Emulator;

    CPU() : registers_{
        .PC = memory_.get_address_from_mem_bendian(0x200), 
        .I = 0x0, 
        .SP = 0x0, 
        .DT = 0x0, 
        .ST = 0x0, 
        .universal_registers.V = {0}} {};
private:
    struct Registers
    {
        Registers() = default;
        struct UniversalRegisters
        {
            UniversalRegisters() = default;
            /*
                The VF register should not be used by any program because it is used as a flag by some instructions.
            */
            uint8_t V[16];
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

        UniversalRegisters universal_registers;
        
    };

    Memory memory_;
    Registers registers_;
};

#endif //CPU_H