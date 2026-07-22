# CHIP-8 Emulator

A full-featured CHIP-8 emulator written in C++20 using SDL2 for graphics. The project includes the core emulator module, a graphical interface, and a test suite.

## 📋 Table of Contents

- [What is CHIP-8?](#what-is-chip-8)
- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Installation and Build](#installation-and-build)
- [Usage](#usage)
- [Controls](#controls)
- [Architecture](#architecture)
- [Testing](#testing)
- [Development](#development)

## What is CHIP-8?

CHIP-8 is a virtual machine (interpreter) designed for simple 8-bit computer games from the 1970s. It is a fictional machine used for educational purposes and to understand the principles behind emulators.

### Key characteristics of CHIP-8:
- **Memory**: 4096 bytes
- **Registers**: 16 general-purpose registers (V0-VF)
- **Display**: 64×32 monochrome screen
- **Sound**: Built-in speaker
- **Instruction set**: 36 instructions
- **Stack**: 16 levels of subroutine nesting

## Features

✅ Full implementation of the CHIP-8 architecture  
✅ SDL2-based graphical interface  
✅ Support for loading ROM files  
✅ CPU emulation at 700 Hz  
✅ Delay and sound timers  
✅ 16-key keyboard  
✅ Full instruction set (35+ instructions)  
✅ Built-in component tests  

## Project Structure

```
.
├── chip8_core/                 # Core emulator module
│   └── chip8/
│       ├── CPU.h / CPU.cpp      # Processor (instruction execution)
│       ├── Memory.h / Memory.cpp # Memory (4096 bytes)
│       ├── Display.h / Display.cpp # Display (64×32)
│       ├── Keyboard.h / Keyboard.cpp # Keyboard (16 keys)
│       ├── Speaker.h / Speaker.cpp   # Sound
│       ├── Opcode.h / Opcode.cpp     # Instruction decoding
│       └── Font.h               # Built-in fonts
├── tests/                      # Unit tests
│   ├── CPUTests.cpp/h          # CPU tests
│   ├── DisplayTests.cpp/h      # Display tests
│   ├── OpcodeTests.cpp/h       # Opcode tests
│   └── CMakeLists.txt
├── roms/                       # Example ROM files
│   └── test.ch8
├── main.cpp                    # Main program
├── CMakeLists.txt              # CMake configuration
├── LICENSE
└── README.md                   # This file
```

## Requirements

### Dependencies:
- **C++20** or newer
- **CMake** 3.20 or newer
- **SDL2** (for graphics)
- **GCC/Clang** (C++ compiler)

### Installing dependencies

#### On Ubuntu/Debian:
```bash
sudo apt-get install build-essential cmake libsdl2-dev
```

#### On Fedora/RHEL:
```bash
sudo dnf install gcc-c++ cmake SDL2-devel
```

#### On macOS:
```bash
brew install cmake sdl2
```

## Installation and Build

### 1. Clone the repository
```bash
git clone https://github.com/yourname/CHIP-8-Emulator.git
cd CHIP-8-Emulator
```

### 2. Create a build directory
```bash
mkdir build
cd build
```

### 3. Configure CMake
```bash
cmake ..
```

### 4. Build the project
```bash
cmake --build .
```

### 5. Run tests (optional)
```bash
ctest --verbose
# or
cd tests && ./chip8_tests
```

After the build, the following files will be created:
- **chip8_emulator** — the main emulator executable
- **chip8_tests** — the test program

## Usage

### Run the emulator:
```bash
./chip8_emulator path/to/rom.ch8
```

### Example:
```bash
./chip8_emulator ../roms/test.ch8
```

### Command-line arguments:
The program requires one mandatory argument — the path to the ROM file.

Note: The CPU frequency is hard-coded to 700 Hz, which is the standard for most CHIP-8 programs.

## Controls

The CHIP-8 keyboard consists of 16 keys (0-9, A-F):

```
Original CHIP-8 keyboard:      Modern keyboard layout:
┌─────────────────────┐            ┌─────────────────────┐
│ 1 2 3 C             │            │ 1 2 3 4             │
│ 4 5 6 D             │            │ Q W E R             │
│ 7 8 9 E             │            │ A S D F             │
│ A 0 B F             │            │ Z X C V             │
└─────────────────────┘            └─────────────────────┘

0x1  = 1              0xA  = Z
0x2  = 2              0xB  = X
0x3  = 3              0xC  = C
0x4  = 4              0xD  = V
0x5  = Q              0xE  = F
0x6  = W              0xF  = R
0x7  = A              0x0  = Space
0x8  = S              (other keys)
0x9  = D
```

**Window controls:**
- `ESC` or closing the window — exits the emulator

## Architecture

### Components:

#### 1. **CPU**
- Executes 2-byte instructions
- Contains 16 general-purpose registers (V0-VF)
- Has a program counter (PC) and stack pointer (SP)
- Includes delay (DT) and sound (ST) timers

#### 2. **Memory**
- 4096 bytes of RAM
- Loads ROM files from address 0x200
- Stores built-in fonts in memory

#### 3. **Display**
- 64×32 monochrome display
- XOR-based sprite drawing
- Rendering through SDL2

#### 4. **Keyboard**
- Tracks the state of 16 keys
- Handles SDL2 events

#### 5. **Speaker**
- Produces sound when the sound timer (ST) is active
- Integrates with SDL2

#### 6. **Opcode**
- Parses and decodes 2-byte instructions
- Interprets all 35+ CHIP-8 instructions

### Execution loop:

```
┌─────────────────────────────────────┐
│  Fetch instruction from memory      │
├─────────────────────────────────────┤
│  Decode instruction                 │
├─────────────────────────────────────┤
│  Execute instruction                │
├─────────────────────────────────────┤
│  Update timers                      │
├─────────────────────────────────────┤
│  Render screen                      │
└─────────────────────────────────────┘
```

## Testing

The project includes a set of unit tests to validate its components:

### Run all tests:
```bash
cd build
ctest --verbose
```

### Run a specific test:
```bash
cd build/tests
./chip8_tests
```

### Test modules:
- **CPUTests** — validates CPU instructions
- **DisplayTests** — validates rasterization
- **OpcodeTests** — validates instruction decoding

## Development

### Code structure:

Each component is split into:
- **Header file (.h)** — interface declaration
- **Implementation file (.cpp)** — core logic

### Coding standards:

- C++20 standard
- Use `uint8_t` and `uint16_t` for type safety
- Comments in English
- Follow RAII principles

### Adding new functionality:

1. Modify the relevant component in `chip8_core/chip8/`
2. Add tests in `tests/`
3. Build the project: `cmake --build .`
4. Run the tests: `ctest --verbose`

### Useful resources:

- [CHIP-8 Wikipedia](https://en.wikipedia.org/wiki/CHIP-8)
- [CHIP-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
- [SDL2 Documentation](https://wiki.libsdl.org/)

## Known limitations

- Some CHIP-8 extensions (SUPER-CHIP) are not supported
- Sound is generated with a simple tone without advanced synthesis
- CPU frequency is fixed at 700 Hz

## License

The project is distributed under the license specified in [LICENSE](LICENSE).

---

**Author:** semens901  
**Last updated:** 2026  
**Version:** 1.0
