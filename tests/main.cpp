#include <iostream>
#include "CPUTests.h"
#include "DisplayTests.h"
#include "OpcodeTests.h"

int main()
{
    run_opcode_tests();
    run_cpu_tests();
    run_display_tests();
    std::cout << "All tests passed." << std::endl;
    return 0;
}