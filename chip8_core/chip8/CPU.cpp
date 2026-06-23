#include "chip8/CPU.h"
#include "CPU.h"

void CPU::read_instruction()
{
    opcode_ = get_opcode(memory_.fetch_opcode(registers_.PC));
}

bool CPU::execute_instruction()
{
    bool pc_modified = false;

    if (waiting_for_key_)
    {
        int key = keyboard_.get_pressed_key();

        if (key != -1)
        {
            registers_.ur.V[waiting_register_] = key;
            waiting_for_key_ = false;
        }

        return true;
    }

    switch (opcode_.op)
    {
        // ─────────────────────────────
        // SYSTEM
        // ─────────────────────────────
        case 0x0:
        {
            std::cout << "opcode 0x0\n";
            switch (opcode_.nn)
            {
                case 0xE0:
                {
                    std::cout << "opcode 0x0 \t0xE0\n";
                    display_.clear();
                    std::cout << "display cleared\n";
                    break;
                }

                case 0xEE:
                {
                    std::cout << "opcode 0x0 \t0xEE\n";
                    registers_.PC = stack_[registers_.SP--];
                    pc_modified = true;
                    break;
                }
                
                default:
                {
                    std::cout << "Unknown opcode: "
                        << std::hex
                        << memory_.fetch_opcode(registers_.PC)
                        << "\n"
                        << "PC = "
                        << registers_.PC
                        << '\n';
                    throw;
                } 
                
            }
            break;
        }

        // ─────────────────────────────
        // JP addr
        // ─────────────────────────────
        case 0x1:
        {
            std::cout << "opcode 0x1\n";
            std::cout << "Register PC before jp = " << registers_.PC << std::endl;
            registers_.PC = opcode_.nnn;
            std::cout << "Register PC after jp = " << registers_.PC << std::endl;
            pc_modified = true;
            break;
        }

        // ─────────────────────────────
        // CALL
        // ─────────────────────────────
        case 0x2:
        {
            std::cout << "opcode 0x2\n";
            stack_[++registers_.SP] = registers_.PC + 2;
            registers_.PC = opcode_.nnn;
            pc_modified = true;
            break;
        }

        // ─────────────────────────────
        // SE Vx, byte
        // ─────────────────────────────
        case 0x3:
        {
            std::cout << "opcode 0x3\n";
            if (registers_.ur.V[opcode_.x] == opcode_.nn)
                registers_.PC += 2;
            break;
        }

        // ─────────────────────────────
        // SNE Vx, byte
        // ─────────────────────────────
        case 0x4:
        {
            std::cout << "opcode 0x4\n";
            if (registers_.ur.V[opcode_.x] != opcode_.nn)
                registers_.PC += 2;
            break;
        }

        // ─────────────────────────────
        // SE Vx, Vy
        // ─────────────────────────────
        case 0x5:
        {
            std::cout << "opcode 0x5\n";
            if (registers_.ur.V[opcode_.x] == registers_.ur.V[opcode_.y])
                registers_.PC += 2;
            break;
        }

        // ─────────────────────────────
        // LD Vx, byte
        // ─────────────────────────────
        case 0x6:
        {
            std::cout << "opcode 0x6\n";
            registers_.ur.V[opcode_.x] = opcode_.nn;
            break;
        }

        // ─────────────────────────────
        // ADD Vx, byte
        // ─────────────────────────────
        case 0x7:
        {
            std::cout << "opcode 0x7\n";
            registers_.ur.V[opcode_.x] += opcode_.nn;
            break;
        }

        // ─────────────────────────────
        // 8XY*
        // ─────────────────────────────
        case 0x8:
        {
            std::cout << "opcode 0x8\n";
            switch (opcode_.n)
            {
                case 0x0: // LD Vx, Vy
                {
                    std::cout << "opcode 0x8 \t0x0\n";
                    registers_.ur.V[opcode_.x] = registers_.ur.V[opcode_.y];
                    break;
                }

                case 0x1: // OR
                {
                    std::cout << "opcode 0x8 \t0x1\n";
                    registers_.ur.V[opcode_.x] |= registers_.ur.V[opcode_.y];
                    break;
                }

                case 0x2: // AND
                {
                    std::cout << "opcode 0x8 \t0x2\n";
                    registers_.ur.V[opcode_.x] &= registers_.ur.V[opcode_.y];
                    break;
                }

                case 0x3: // XOR
                {
                    std::cout << "opcode 0x8 \t0x3\n";
                    registers_.ur.V[opcode_.x] ^= registers_.ur.V[opcode_.y];
                    break;
                }

                case 0x4: // ADD with carry
                {
                    std::cout << "opcode 0x8 \t0x4\n";
                    uint16_t sum =
                        registers_.ur.V[opcode_.x] +
                        registers_.ur.V[opcode_.y];

                    registers_.ur.V[0xF] = (sum > 0xFF);
                    registers_.ur.V[opcode_.x] = (uint8_t)sum;
                    break;
                }

                case 0x5: // SUB Vx = Vx - Vy
                {
                    std::cout << "opcode 0x8 \t0x5\n";
                    uint8_t flag =
                        (registers_.ur.V[opcode_.x] >= registers_.ur.V[opcode_.y]);

                    registers_.ur.V[opcode_.x] -= registers_.ur.V[opcode_.y];
                    registers_.ur.V[0xF] = flag;
                    break;
                }

                case 0x6: // SHR
                {
                    std::cout << "opcode 0x8 \t0x6\n";
                    uint8_t value = registers_.ur.V[opcode_.y];

                    registers_.ur.V[0xF] = value & 0x1;
                    registers_.ur.V[opcode_.x] = value >> 1;
                    break;
                }

                case 0x7: // SUBN
                {
                    std::cout << "opcode 0x8 \t0x7\n";
                    uint8_t flag =
                        (registers_.ur.V[opcode_.y] > registers_.ur.V[opcode_.x]);

                    registers_.ur.V[opcode_.x] =
                        registers_.ur.V[opcode_.y] - registers_.ur.V[opcode_.x];

                    registers_.ur.V[0xF] = flag;
                    break;
                }

                case 0xE: // SHL
                {
                    std::cout << "opcode 0x8 \t0xE\n";
                    uint8_t value = registers_.ur.V[opcode_.y];

                    registers_.ur.V[0xF] = (value & 0x80) >> 7;
                    registers_.ur.V[opcode_.x] = value << 1;
                    break;
                }
            }
            break;
        }

        // ─────────────────────────────
        // SNE Vx, Vy
        // ─────────────────────────────
        case 0x9:
        {
            std::cout << "opcode 0x9\n";
            if (registers_.ur.V[opcode_.x] != registers_.ur.V[opcode_.y])
                registers_.PC += 2;
            break;
        }

        // ─────────────────────────────
        // LD I, addr
        // ─────────────────────────────
        case 0xA:
        {
            std::cout << "opcode 0xA\n";
            std::cout << "register I before modification = " << registers_.I << std::endl;
            registers_.I = opcode_.nnn;
            std::cout << "register I after modification = " << registers_.I << std::endl;
            break;
        }

        // ─────────────────────────────
        // JP V0, addr
        // ─────────────────────────────
        case 0xB:
        {
            std::cout << "opcode 0xB\n";
            registers_.PC = opcode_.nnn + registers_.ur.V[0x0];
            pc_modified = true;
            break;
        }

        // ─────────────────────────────
        // RND Vx, byte
        // ─────────────────────────────
        case 0xC:
        {
            std::cout << "opcode 0xC\n";
            uint8_t rnd = std::rand() % 256;
            registers_.ur.V[opcode_.x] = rnd & opcode_.nn;
            break;
        }

        // ─────────────────────────────
        // DRAW
        // ─────────────────────────────
        case 0xD:
        {
            std::cout << "opcode 0xD\n";
            uint8_t vx = registers_.ur.V[opcode_.x];
            uint8_t vy = registers_.ur.V[opcode_.y];

            registers_.ur.V[0xF] = 0;

            for (int row = 0; row < opcode_.n; ++row)
            {
                uint8_t sprite = memory_.read(registers_.I + row);

                for (int col = 0; col < 8; ++col)
                {
                    uint8_t sprite_bit = sprite & (0x80 >> col);
                    if (!sprite_bit)
                        continue;

                    uint8_t x = (vx + col) % 64;
                    uint8_t y = (vy + row) % 32;

                    uint8_t old_pixel = display_.get_pixel(x, y);

                    if (old_pixel)
                        registers_.ur.V[0xF] = 1;

                    display_.xor_pixel(x, y);
                }
            }
            break;
        }

        // ─────────────────────────────
        // KEY INPUT
        // ─────────────────────────────
        case 0xE:
        {
            
            std::cout << "opcode 0xE\n";
            switch (opcode_.nn)
            {
                case 0x9E:
                {
                    std::cout << "opcode 0xE \t0x9E\n";
                    uint8_t key = registers_.ur.V[opcode_.x];

                    if (keyboard_.is_pressed(key))
                        registers_.PC += 2;

                    break;
                }

                case 0xA1:
                {
                    std::cout << "opcode 0xE \t0xA1\n";
                    uint8_t key = registers_.ur.V[opcode_.x];

                    if (!keyboard_.is_pressed(key))
                        registers_.PC += 2;

                    break;
                }
            }
                
            break;
        }

        // ─────────────────────────────
        // MISC (FX..)
        // ─────────────────────────────
        case 0xF:
        {
            std::cout << "opcode 0xF\n";
            switch(opcode_.nn)
            {
                case 0x07:
                {
                    std::cout << "opcode 0xF \t0x07\n";
                    registers_.ur.V[opcode_.x] = registers_.DT;
                    break;
                }
                case 0x0A:
                {
                    std::cout << "opcode 0xF \t0x0A\n";
                    waiting_for_key_ = true;
                    waiting_register_ = opcode_.x;

                    pc_modified = true;

                    break;
                }
                case 0x15:
                {
                    std::cout << "opcode 0xF \t0x15\n";
                    registers_.DT = registers_.ur.V[opcode_.x];
                    break;
                }
                case 0x18:
                {
                    std::cout << "opcode 0xF \t0x18\n";
                    registers_.ST = registers_.ur.V[opcode_.x];
                    break;
                }
                case 0x1E:
                {
                    std::cout << "opcode 0xF \t0x1E\n";
                    registers_.I += registers_.ur.V[opcode_.x];
                    break;
                }
                case 0x29:
                {
                    std::cout << "opcode 0xF \t0x29\n";
                    uint8_t digit = registers_.ur.V[opcode_.x] & 0x0F;

                    registers_.I = FONT_START + digit * 5;
                    break;
                }
                case 0x33:
                {
                    std::cout << "opcode 0xF \t0x33\n";
                    uint8_t value = registers_.ur.V[opcode_.x];

                    memory_.write(registers_.I,     value / 100);
                    memory_.write(registers_.I + 1, (value / 10) % 10);
                    memory_.write(registers_.I + 2, value % 10);
                    break;
                }
                case 0x55:
                {
                    std::cout << "opcode 0xF \t0x55\n";
                    for (uint8_t i = 0; i <= opcode_.x; ++i)
                    {
                        memory_.write(
                            registers_.I + i,
                            registers_.ur.V[i]
                        );
                    }
                    break;
                }
                case 0x65:
                {
                    std::cout << "opcode 0xF \t0x65\n";
                    for (uint8_t i = 0; i <= opcode_.x; ++i)
                    {
                        registers_.ur.V[i] = memory_.read(registers_.I + i);
                    }
                    break;
                }
            };
            break;
        }
    }

    // ─────────────────────────────
    // GLOBAL PC STEP
    // ─────────────────────────────
    if (!pc_modified)
    {
        std::cout << "register PC = " << registers_.PC << std::endl;
        registers_.PC += 2;
        std::cout << "register PC = " << registers_.PC << " After step = 2" << std::endl;
    }

    return true;
}

void CPU::cycle()
{
    read_instruction();
    execute_instruction();
}

void CPU::reset()
{
    registers_.PC = 0x200;
    registers_.I = 0;
    registers_.SP = 0;
}

void CPU::update_timers()
{
    if (registers_.DT > 0)
        --registers_.DT;

    if (registers_.ST > 0)
    {
        std::cout << "BBBBBBBBEEEEEEEEEEEEEEEEEEEPPPPPPPPPPPPPPPPPPPPP!!!!!!!!!!!!\n";
        speaker_.start();
        --registers_.ST;
    }
    else
    {
        speaker_.stop();
    }
}
