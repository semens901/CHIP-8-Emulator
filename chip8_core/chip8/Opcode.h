#ifndef OPCODE_H
#define OPCODE_H
#include <cstdint>

struct Opcode
{
    // Raw 16-bit CHIP-8 instruction fetched from memory.
    uint8_t op;

    // X operand (second nibble).
    // Selects one of the general-purpose registers V0-VF.
    uint8_t x;

    // Y operand (third nibble).
    // Selects one of the general-purpose registers V0-VF.
    uint8_t y;

    // N operand (fourth nibble).
    // Represents a 4-bit immediate value.
    uint8_t n;

    // NN operand (last two nibbles).
    // Represents an 8-bit immediate value.
    uint8_t nn;

    // NNN operand (last three nibbles).
    // Represents a 12-bit memory address.
    uint16_t nnn;
};

Opcode get_opcode(uint16_t opcode);


#endif //OPCODE_H