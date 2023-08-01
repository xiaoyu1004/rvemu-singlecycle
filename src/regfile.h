#ifndef REGFILE_H
#define REGFILE_H

#include "common.h"

#include <cstdint>

namespace rvemu {
class regfile {
 private:
    std::int32_t regs_[REG_NUM];
};
}  // namespace rvemu

#endif