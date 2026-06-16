#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <iomanip>
#include <stack>

class Memory
{
public:
    friend class CPU;

    Memory() = default;

    uint8_t read(uint16_t address) const;
    void write(uint16_t address, uint8_t value);

    uint8_t* get_address(uint16_t emulated_address);
    const uint8_t* get_address(uint16_t emulated_address) const;
    uint16_t get_address_from_mem_lendian(uint16_t emulated_address) const;
    uint16_t get_address_from_mem_bendian(uint16_t emulated_address) const;

    uint16_t fetch_opcode(uint16_t emulated_address);

private:
    uint8_t memory[4096] = {0};
    uint16_t programCounter;
    
    // The stack is an array of 16 16-bit values ​​used to store the address to which the interpreter should return after a subroutine completes.
    std::stack<uint16_t> stack_; 
};


#endif //MEMORY_H