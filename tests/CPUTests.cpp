#include "CPUTests.h"

static void configure_sdl_for_tests()
{
    // Use SDL's dummy video driver so the tests can create a display object without a real window.
    setenv("SDL_VIDEODRIVER", "dummy", 1);
}

static void test_cpu_read_instruction_fetches_opcode_from_memory()
{
    // Ensures that the CPU reads the expected opcode from the current program counter.
    configure_sdl_for_tests();

    Memory memory;
    Display display("Test Display");
    Keyboard keyboard;
    Speaker speaker;
    CPU cpu(memory, display, keyboard, speaker);

    memory.write(0x200, 0x12);
    memory.write(0x201, 0x34);

    cpu.read_instruction();

    assert(memory.fetch_opcode(0x200) == 0x1234);
}

static void test_cpu_ld_instruction_produces_bcd_output()
{
    // Ensures that LD Vx, byte followed by BCD conversion writes the expected digits to memory.
    configure_sdl_for_tests();

    Memory memory;
    Display display("Test Display");
    Keyboard keyboard;
    Speaker speaker;
    CPU cpu(memory, display, keyboard, speaker);

    memory.write(0x200, 0x60);
    memory.write(0x201, 0x07);
    memory.write(0x202, 0xA3);
    memory.write(0x203, 0x00);
    memory.write(0x204, 0xF0);
    memory.write(0x205, 0x33);

    cpu.read_instruction();
    cpu.execute_instruction();

    cpu.read_instruction();
    cpu.execute_instruction();

    cpu.read_instruction();
    cpu.execute_instruction();

    assert(memory.read(0x300) == 0x00);
    assert(memory.read(0x301) == 0x00);
    assert(memory.read(0x302) == 0x07);
}

static void test_cpu_add_instruction_updates_register_before_bcd_output()
{
    // Ensures that ADD Vx, byte changes the register value before the BCD instruction writes it.
    configure_sdl_for_tests();

    Memory memory;
    Display display("Test Display");
    Keyboard keyboard;
    Speaker speaker;
    CPU cpu(memory, display, keyboard, speaker);

    memory.write(0x200, 0x60);
    memory.write(0x201, 0x02);
    memory.write(0x202, 0x70);
    memory.write(0x203, 0x03);
    memory.write(0x204, 0xA3);
    memory.write(0x205, 0x00);
    memory.write(0x206, 0xF0);
    memory.write(0x207, 0x33);

    for (int i = 0; i < 4; ++i)
    {
        cpu.read_instruction();
        cpu.execute_instruction();
    }

    assert(memory.read(0x300) == 0x00);
    assert(memory.read(0x301) == 0x00);
    assert(memory.read(0x302) == 0x05);
}

void run_cpu_tests()
{
    test_cpu_read_instruction_fetches_opcode_from_memory();
    test_cpu_ld_instruction_produces_bcd_output();
    test_cpu_add_instruction_updates_register_before_bcd_output();
}