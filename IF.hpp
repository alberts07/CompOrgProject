//
//  IF.hpp
//  
//
//  Created by Drew Lockwood on 3/1/17.
//
//

#ifndef IF_hpp
#define IF_hpp

#include <stdio.h>
//Masks for Determining Values
#define     opcode_mask     0xFC000000
#define     function_mask   0x0000003F
#define     rs_mask         0x03E00000
#define     rt_mask         0x001F0000
#define     rd_mask         0x0000F800
#define     shamt_mask      0x000007C0
#define     immed16_mask    0x0000FFFF
#define     immed26_mask    0x03FFFFFF

//Opcodes for every MIPS function
#define     lw_opcode       0b100011
#define     r-format        0b000000
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
#define     lh_opcode       0b100001
#define     sb_opcode       0b101000
#define     sh_opcode       0b101001
#define     beq_opcode      0b000100
#define     bne_opcode      0b000101
#define     j_opcode        0b000010
#define     jal_opcode      0b000011
#define     lhu_opcode      0b100101


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
#define     sllv_func       0b000100
#define     srl_func        0b100010
#define     srlv_func       0b100110
#define     sra_func        0b100011
#define     srav_func       0b100111
#define     div_func        0b100010
#define     divu_func       0b100010
#define     mult_func       0b100010
#define     multu_func      0b100010
#define     break_func      0b001101
#define     jr_func         0b001000
#define     jalrs_func      0b001001
#define     teq_func        0b110100
#define     tne_func        0b110110
#define     tge_func        0b110000
#define     tgeu_func       0b110001
#define     tlt_func        0b110010
#define     tltu_func       0b110011

//Special Functions 
#define     special_opcode  0b011100
#define     clo_func        0b100001
#define     clz_func        0b100000
#define     mul_func        0b000010
#define     madd_func       0b000000
#define     maddu_func      0b000001
#define     msub_func       0b000100
#define     msubu_func      0b000101

#endif /* IF_hpp */
