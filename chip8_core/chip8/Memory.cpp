#include "chip8/Memory.h"
#include "Memory.h"

uint8_t Memory::read(uint16_t address) const
{
    return 0;
}

void Memory::write(uint16_t address, uint8_t value)
{
}

uint8_t *Memory::get_address(uint16_t emulated_address)
{
    if (emulated_address >= 4096) 
    {
        return nullptr; // Защита: адрес вне диапазона
    }
    // Арифметика указателей: базовый адрес массива + смещение
    return memory + emulated_address;
}

const uint8_t *Memory::get_address(uint16_t emulated_address) const
{
    if (emulated_address >= 4096) return nullptr;
        return memory + emulated_address;
}

uint16_t Memory::get_address_from_mem_lendian(uint16_t emulated_address) const
{
    if (emulated_address + 1 >= 4096) return 0; // Защита от выхода за границы

    // Вариант А: Для архитектуры Little Endian (младший байт первый)
    // Если в памяти лежат байты [0x34, 0x12], функция вернет 0x1234
    return memory[emulated_address] | (memory[emulated_address + 1] << 8);
}

uint16_t Memory::get_address_from_mem_bendian(uint16_t emulated_address) const
{
    if (emulated_address + 1 >= 4096) return 0; // Защита от выхода за границы
    // Вариант Б: Для архитектуры Big Endian (старший байт первый)
    // Если в памяти лежат байты [0x12, 0x34], функция вернет 0x1234
    return (memory[emulated_address] << 8) | memory[emulated_address + 1];
}

uint16_t Memory::fetch_opcode(uint16_t emulated_address)
{
    if (emulated_address + 1 >= 4096) return 0; // Защита от вылета

        // CHIP-8 — это Big Endian! 
        // Объединяем два байта: первый сдвигаем влево, второй добавляем через OR
        uint16_t opcode = (memory[emulated_address] << 8) | memory[emulated_address + 1];
        
        return opcode;
}
