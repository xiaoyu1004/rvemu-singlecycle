#ifndef CPU_H
#define CPU_H

#include "alu.h"
#include "memory.h"
#include "pc.h"
#include "regfile.h"

namespace rvemu {
class cpu {
 public:
    void start();

 private:
    void fetch();
    void decode();
    void execute();
    void access_memory();
    void writeback();

 private:
    std::uint32_t cycles_;

 private:
    pc pc_;
    memory imem_;
    regfile reg_;
    alu alu_;
    memory dmem_;
};
}  // namespace rvemu

#endif