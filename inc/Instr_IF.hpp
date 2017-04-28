//
//  Instr_IF.hpp
//
//
//  Created by Drew Lockwood on 3/1/17.
//
//

#ifndef Instr_IF_h
#define Instr_IF_h



void Instr_IF(unsigned int);

struct ifid {
    short immed16;
    unsigned int pcplus1;
    unsigned int instr;
};

struct idex {
    bool RegWrite;
    bool MemRead;
    bool MemWrite;
    bool MemtoReg;
    bool ALUSrc;
    int Rs;
    int RsValue;
    int Rd;
    int RdValue;
    int Rt;
    int RtValue;
    int immed16;
    int immed26;
    int opcode;
    int func;
    int shamt;
    unsigned int pcplus1;
    unsigned int instr;
    bool branch;
};

struct exmem {
    bool RegWrite;
    bool MemRead;
    bool MemWrite;
    bool MemtoReg;
    int DstReg;
    int RsValue;
    int RtValue;
    int ALUResult;
    unsigned int pcplus1;
    int mem;
    bool half;
};

struct memwb {
    bool RegWrite;
    bool MemtoReg;
    int ALUResult;
    int DstRegValue;
    int DstReg;
    unsigned int pcplus1;
};




//Type Determination
#define     rtype               0x00000000
#define     itype               0x00000001
#define     jtype               0x00000010
#define     special_opcode      0x00000011
#define     branchtype          0x00000100
//#define     special_opcode2l    0x00000100
//#define     special_opcode3l    0x00000101


//Masks for Determining Values
#define     opcode_mask             0xFC000000
#define     function_mask           0x0000003F
#define     rs_mask                 0x03E00000
#define     rt_mask                 0x001F0000
#define     rd_mask                 0x0000F800
#define     shamt_mask              0x000007C0
#define     immed16_mask            0x0000FFFF
#define     immed26_mask            0x03FFFFFF
#define     jump_mask               0xF0000000
//#define     br_coprocessor          0x00030000
//#define     spec_opcode3_mask       0x001F0000


//Opcodes for every MIPS function
#define     lw_opcode       0b100011
#define     addi_opcode     0b001000
#define     sw_opcode       0b101011
#define     slti_opcode     0b001010
#define     sltiu_opcode    0b001011
#define     addiu_opcode    0b001001
#define     andi_opcode     0b001100
#define     lui_opcode      0b001111
#define     ori_opcode      0b001101
#define     xori_opcode     0b001110
#define     lb_opcode       0b100000
#define     lbu_opcode      0b100100
#define     lh_opcode       0b100001
#define     sb_opcode       0b101000
#define     sh_opcode       0b101001
#define     beq_opcode      0b000100
#define     bne_opcode      0b000101
#define     j_opcode        0b000010
#define     jal_opcode      0b000011
#define     lhu_opcode      0b100101
#define     bgtz_opcode     0b000111
#define     blez_opcode     0b000110
#define     bltz_opcode     0b000001
#define     seb_opcode      0b011111

//Fucntions for R-format MIPS
#define     add_func        0b100000
#define     addu_func       0b100001
#define     and_func        0b100100
#define     nor_func        0b100111
#define     or_func         0b100101
#define     slt_func        0b101010
#define     sltu_func       0b101011
#define     sub_func        0b100010
#define     subu_func       0b100011
#define     xor_func        0b100110
#define     sll_func        0b000000
#define     srl_func        0b000010
#define     jr_func         0b001000
#define     movn_func       0b001011
#define     movz_func       0b001010



#endif /* IF_hpp */
