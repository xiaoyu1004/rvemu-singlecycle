#ifndef REGFILE_H
#define REGFILE_H

#include "common.h"

#include <cstdint>

namespace rvemu {
class regfile {
 public:
    std::int32_t load(std::uint32_t addr);
    void store(std::uint32_t addr, std::int32_t val);

 private:
    std::int32_t regs_[REG_NUM];
};
}  // namespace rvemu

#endif