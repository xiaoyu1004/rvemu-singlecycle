#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <cstring>

namespace rvemu {
class memory {
 public:
    memory(size_t size);
    ~memory();
    void init(const uint8_t* ptr, size_t size);

 public:
    std::int8_t load_byte(std::uint32_t addr);
    void store_byte(std::uint32_t addr, std::int8_t val);

    std::int32_t load_word(std::uint32_t addr);
    void store_word(std::uint32_t addr, std::int32_t val);

 private:
    size_t size_;
    std::int8_t* mem_;
};
}  // namespace rvemu

#endif