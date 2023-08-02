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
            printf("exited(%d)\n", reg_->load(10));  // a0
            return;
        }
        decode();
        execute();
        access_memory();
        writeback();
    }
}

void cpu::fetch() {
    std::uint32_t pc = pc_->get_pc();
    inst_            = imem_->load_word(pc);
    if (inst_ == 0) {
        running_ = false;
    }
    printf("cpu fetch pc=0x%x; inst=0x%x\n", pc, inst_);
}

void cpu::decode() {
    // std::cout << "cpu decode" << std::endl;

    decode_info_.opcode = inst_ & 0x0000007F;
    decode_info_.funct3 = (inst_ >> 12) & 0b111;
    decode_info_.funct7 = inst_ >> 25;

    decode_info_.rR1 = (inst_ >> 15) & 0b11111;
    decode_info_.rR2 = (inst_ >> 20) & 0b11111;
    decode_info_.wR  = (inst_ >> 7) & 0b11111;

    decode_info_.imm_i = (inst_ >> 20);
    decode_info_.imm_s = ((inst_ >> 25) << 5) | ((inst_ >> 7) & 0b11111);
    decode_info_.imm_b = ((inst_ >> 31) << 11) | (((inst_ >> 7) & 0b1) << 10) |
                         (inst_ >> 25 & 0b111111 << 4) | (inst_ >> 8 & 0xFF);
    decode_info_.imm_u = inst_ >> 12;
    decode_info_.imm_j =
        (inst_ >> 31) | (inst_ >> 12 & 0xFF) | (inst_ >> 20 & 0b1) | (inst_ >> 21 & 0x3FF);

    if (decode_info_.opcode == 0b0110011 && decode_info_.funct7 == 0b0000000 &&
        decode_info_.funct3 == 0b000) {
        instr_type_     = ADD;
        decode_info_.wE = true;
    } else if (decode_info_.opcode == 0b0110011 && decode_info_.funct7 == 0b0000000 &&
               decode_info_.funct3 == 0b100) {
        instr_type_     = XOR;
        decode_info_.wE = true;
    } else if (decode_info_.opcode == 0b0010011 && decode_info_.funct3 == 0b000) {
        instr_type_     = ADDI;
        decode_info_.wE = true;
    } else {
        printf("error: invalid instruction: %x\n", inst_);
        exit(-1);
    }
}

void cpu::execute() {
    // std::cout << "cpu execute" << std::endl;
    if (instr_type_ == ADD) {
        std::int32_t rR1_data = reg_->load(decode_info_.rR1);
        std::int32_t rR2_data = reg_->load(decode_info_.rR2);
        rf_wdata              = rR1_data + rR2_data;
    } else if (instr_type_ == XOR) {
        std::int32_t rR1_data = reg_->load(decode_info_.rR1);
        std::int32_t rR2_data = reg_->load(decode_info_.rR2);
        rf_wdata              = rR1_data ^ rR2_data;
    } else if (instr_type_ == ADDI) {
        std::int32_t rR1_data = reg_->load(decode_info_.rR1);
        rf_wdata              = rR1_data + decode_info_.imm_i;
    }
}

void cpu::access_memory() {
    // std::cout << "cpu access_memory" << std::endl;
}

void cpu::writeback() {
    // std::cout << "cpu writeback\n" << std::endl;
    reg_->store(decode_info_.wR, rf_wdata);
}

}  // namespace rvemu