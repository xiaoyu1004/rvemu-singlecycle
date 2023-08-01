#ifndef CPU_H
#define CPU_H

#include "alu.h"
#include "memory.h"
#include "pc.h"
#include "regfile.h"

#include <iostream>
#include <string>

namespace rvemu {
class cpu {
 public:
    cpu();
    ~cpu();
    void load_inst(const std::string inst_file);
    void load_data(const std::string data_file);

    void load_inst(const uint8_t* bin_ptr, size_t size);
    void load_data(const uint8_t* data_ptr, size_t size);

    void start();

 private:
    void fetch();
    void decode();
    void execute();
    void access_memory();
    void writeback();

 private:
    std::uint32_t cycles_;
    bool running_;
    std::uint32_t inst_;

 private:
    pc* pc_;
    memory* imem_;
    regfile* reg_;
    alu* alu_;
    memory* dmem_;
};
}  // namespace rvemu

#endif