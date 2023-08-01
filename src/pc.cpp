#include "pc.h"

namespace rvemu {
pc::pc() : pc_(RESET_PC) {}

std::uint32_t pc::get_pc() {
    std::uint32_t pre_pc = pc_;
    pc_ += 4;
    return pre_pc;
}
}  // namespace rvemu