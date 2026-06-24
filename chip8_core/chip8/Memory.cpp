#include "chip8/Memory.h"
#include "Memory.h"

Memory::Memory()
{
    // ─────────────────────────────
    // LOAD FONT IN MEMORY
    // ─────────────────────────────
    for(uint8_t i = FONT_START; i <= FONT_END; ++i)
    {
        memory_[i] = FONT[i-FONT_START];
    }
}

uint8_t Memory::read(uint16_t address) const
{
    return memory_[address];
}

void Memory::write(uint16_t address, uint8_t value)
{
    memory_[address] = value;
}

uint16_t Memory::fetch_opcode(uint16_t emulated_address)
{
    if (emulated_address + 1 >= 4096) return 0; // Защита от вылета

    // CHIP-8 — это Big Endian! 
    // Объединяем два байта: первый сдвигаем влево, второй добавляем через OR
    uint16_t opcode = (memory_[emulated_address] << 8) | memory_[emulated_address + 1];
    
    return opcode;
}

bool Memory::load_rom(const std::string &path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file)
        return false;

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (size > (4096 - 0x200))
        return false; // ROM too big

    file.read(reinterpret_cast<char*>(&memory_[0x200]), size);

    return true;

}
