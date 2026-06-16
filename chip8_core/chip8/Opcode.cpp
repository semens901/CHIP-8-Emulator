#include "Opcode.h"

Opcode get_opcode(uint16_t opcode)
{
    Opcode result;
    result.x   = (opcode & 0x0F00) >> 8;
    result.y   = (opcode & 0x00F0) >> 4;
    result.n   = opcode & 0x000F;
    result.nn  = opcode & 0x00FF;
    result.nnn = opcode & 0x0FFF;
    return result;
}
