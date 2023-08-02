#include "cpu.h"

#include <iostream>

int main(int argc, const char** argv) {

    std::int32_t dumy_inst[5] = {0x00a54533,   // xor a0, a0, a0
                                 0x00650513,   // addi a0, a0, 6
                                 0x00b5c5b3,   // xor a1, a1, a1
                                 0x00258593,   // addi a1, a1, 2
                                 0x00b50533};  // add a0, a0, a1

    rvemu::cpu cpu;
    cpu.load_inst(reinterpret_cast<uint8_t*>(dumy_inst), sizeof(dumy_inst));
    cpu.start();

    return 0;
}