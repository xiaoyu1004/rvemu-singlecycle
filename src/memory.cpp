#include "memory.h"

#include <cstring>

namespace rvemu {
memory::memory(size_t size) : size_(size) { mem_ = new int8_t[size]{}; }

memory::~memory() { delete[] mem_; }

void memory::init(const uint8_t* ptr, size_t size) { memcpy(mem_, ptr, size); }

std::int8_t memory::load_byte(std::uint32_t addr) { return mem_[addr]; }

void memory::store_byte(std::uint32_t addr, std::int8_t val) { mem_[addr] = val; }

std::int32_t memory::load_word(std::uint32_t addr) {
    return *reinterpret_cast<std::int32_t*>(mem_ + addr);
}

void memory::store_word(std::uint32_t addr, std::int32_t val) {
    *reinterpret_cast<std::int32_t*>(mem_ + addr) = val;
}
}  // namespace rvemu