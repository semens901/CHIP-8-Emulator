#include "chip8/Chip8.h"
#include "Chip8.h"

void Emulator::Emulator_loop()
{
    while(true)
    {
        void Fetch();
        void Decode();
        void Execute();
    };
}

void Emulator::Fetch()
{
    opcode = cpu_.memory_.fetch_opcode(cpu_.registers_.PC);
    cpu_.registers_.PC += 0x2;
}

void Emulator::Execute()
{
}

void Emulator::Decode()
{
}
