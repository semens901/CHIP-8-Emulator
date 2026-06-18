#include <iostream>
#include <chrono>
#include <thread>

#include "chip8/Display.h"
#include "chip8/Memory.h"
#include "chip8/Keyboard.h"
#include "chip8/CPU.h"
#include <filesystem>

constexpr int CPU_HZ = 700;
constexpr double CPU_STEP = 1.0 / CPU_HZ;

double accumulator = 0.0;
auto last_time = std::chrono::steady_clock::now();

int main()
{
    Memory memory;
    Keyboard keyboard;
    Display display("CHIP8");
    
    std::cout << std::filesystem::current_path() << std::endl;
    if(!memory.load_rom("../roms/test.ch8"))
    {
        std::cout << "Failed load rom\n";
        return 1;
    }
    CPU cpu(memory, display, keyboard);

    using clock = std::chrono::steady_clock;

    auto last_time = clock::now();

    double cpu_accumulator = 0.0;
    double timer_accumulator = 0.0;

    const double cpu_step = 1.0 / 700.0;   // ~700 Hz
    const double timer_step = 1.0 / 60.0;   // 60 Hz

    while (display.is_running())
    {
        auto now = clock::now();
        std::chrono::duration<double> delta = now - last_time;
        last_time = now;

        double dt = delta.count();

        // ─────────────────────────────
        // INPUT
        // ─────────────────────────────
        display.poll_events();

        // ─────────────────────────────
        // CPU (fixed rate)
        // ─────────────────────────────
        cpu_accumulator += dt;

        int safety = 1000;

        while (cpu_accumulator >= cpu_step && safety--)
        {
            cpu.cycle();
            cpu_accumulator -= cpu_step;
        }

        // ─────────────────────────────
        // TIMERS (60 Hz)
        // ─────────────────────────────
        timer_accumulator += dt;

        while (timer_accumulator >= timer_step)
        {
            cpu.update_timers();
            timer_accumulator -= timer_step;
        }

        // ─────────────────────────────
        // RENDER (можно 60 FPS или free)
        // ─────────────────────────────
        display.render_frame();

        // optional: убирает 100% CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    return 0;
}