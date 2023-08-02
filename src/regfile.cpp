#include "regfile.h"

#include <iostream>

namespace rvemu {
std::int32_t regfile::load(std::uint32_t addr) {
    if (addr < 0 || addr >= REG_NUM) {
        printf("error: invalid access index for regfile: %d \n", addr);
        exit(-1);
    }
    return regs_[addr];
}

void regfile::store(std::uint32_t addr, std::int32_t val) {
    if (addr < 0 || addr >= REG_NUM) {
        printf("error: invalid access index for regfile: %d \n", addr);
        exit(-1);
    }
    regs_[addr] = val;
}
}  // namespace rvemu