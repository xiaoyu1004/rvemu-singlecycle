#include "cpu.h"

namespace rvemu {
cpu::cpu() {
    running_ = true;
    cycles_  = 0;

    pc_   = new pc;
    imem_ = new memory(IROM_SIZE);
    dmem_ = new memory(DRAM_SIZE);
}

cpu::~cpu() {
    delete pc_;
    delete imem_;
    delete dmem_;
}

void cpu::load_inst(const std::string inst_file) {}

void cpu::load_data(const std::string data_file) {}

void cpu::load_inst(const uint8_t* bin_ptr, size_t size) {
    if (size % 4 != 0) {
        std::cout << "invalid inst size: " << size << std::endl;
        exit(-1);
    }
    for (size_t i = RESET_PC; i < (RESET_PC + size); ++i) {
        imem_->store_byte(i, bin_ptr[i - RESET_PC]);
    }
}

void cpu::load_data(const uint8_t* data_ptr, size_t size) {}

void cpu::start() {
    while (true) {
        fetch();
        if (!running_) {
            return;
        }
        decode();
        execute();
        access_memory();
        writeback();
    }
}

void cpu::fetch() {
    std::uint32_t pc  = pc_->get_pc();
    std::int32_t inst = imem_->load_word(pc);
    if (inst == 0) {
        running_ = false;
    }
    std::cout << "cpu fetch pc=0x" << pc << "; inst=0x" << std::hex << inst << std::endl;
}

void cpu::decode() { std::cout << "cpu decode" << std::endl; }

void cpu::execute() { std::cout << "cpu execute" << std::endl; }

void cpu::access_memory() { std::cout << "cpu access_memory" << std::endl; }

void cpu::writeback() { std::cout << "cpu writeback\n" << std::endl; }

}  // namespace rvemu