#include "OpcodeTests.h"
#include "chip8/Opcode.h"
#include <cassert>

static void test_opcode_decoding_from_complex_instruction()
{
    // Ensures that all opcode fields are decoded from a mixed instruction.
    const uint16_t instruction = 0xA23F;
    const Opcode opcode = get_opcode(instruction);

    assert(opcode.op == 0xA);
    assert(opcode.x == 0x2);
    assert(opcode.y == 0x3);
    assert(opcode.n == 0xF);
    assert(opcode.nn == 0x3F);
    assert(opcode.nnn == 0x23F);
}

static void test_opcode_decoding_from_zero_instruction()
{
    // Ensures that a zero instruction produces zeroed operands and flags.
    const uint16_t instruction = 0x0000;
    const Opcode opcode = get_opcode(instruction);

    assert(opcode.op == 0x0);
    assert(opcode.x == 0x0);
    assert(opcode.y == 0x0);
    assert(opcode.n == 0x0);
    assert(opcode.nn == 0x0);
    assert(opcode.nnn == 0x0);
}

static void test_opcode_decoding_from_low_byte_instruction()
{
    // Ensures that the low-byte operand is preserved without shifting.
    const uint16_t instruction = 0x00E4;
    const Opcode opcode = get_opcode(instruction);

    assert(opcode.op == 0x0);
    assert(opcode.x == 0x0);
    assert(opcode.y == 0xE);
    assert(opcode.n == 0x4);
    assert(opcode.nn == 0xE4);
    assert(opcode.nnn == 0x0E4);
}

void run_opcode_tests()
{
    test_opcode_decoding_from_complex_instruction();
    test_opcode_decoding_from_zero_instruction();
    test_opcode_decoding_from_low_byte_instruction();
}