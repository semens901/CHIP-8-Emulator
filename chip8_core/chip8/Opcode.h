#ifndef OPCODE_H
#define OPCODE_H
#include <cstdint>

struct Opcode
{
    uint8_t x;
    uint8_t y;
    uint8_t n;
    uint8_t nn;
    uint16_t nnn;
};

Opcode get_opcode(uint16_t opcode);

#endif //OPCODE_H