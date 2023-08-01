#ifndef PC_H
#define PC_H

#include "common.h"

#include <cstdint>

namespace rvemu {
class pc {
 public:
    pc();

 public:
    std::uint32_t get_pc();

 private:
    std::uint32_t pc_;
};
}  // namespace rvemu

#endif