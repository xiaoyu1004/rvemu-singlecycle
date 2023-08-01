#include "cpu.h"

#include <iostream>

int main(int argc, const char** argv) {

    std::int32_t dumy_inst[4] = {0x12345678, 0x12345672, 0x12345673, 0x12345679};

    rvemu::cpu cpu;
    cpu.load_inst(reinterpret_cast<uint8_t*>(dumy_inst), sizeof(dumy_inst));
    cpu.start();

    return 0;
}