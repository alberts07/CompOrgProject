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


//Type Determination 
#define     rtype           0x00000000
#define     itype           0x00000001
#define     jtype           0x00000010
#define     trap_i_type     0x00000011
#define     br_coprocessor  0x00000100


//Masks for Determining Values
#define     opcode_mask     0xFC000000
#define     function_mask   0x0000003F
#define     rs_mask         0x03E00000
#define     rt_mask         0x001F0000
#define     rd_mask         0x0000F800
#define     shamt_mask      0x000007C0
#define     immed16_mask    0x0000FFFF
#define     immed26_mask    0x03FFFFFF
#define     br_coprocessor  0x00030000


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
#define     lwcl_opcode     0b110001
#define     lwl_opcode      0b100010
#define     lwr_opcode      0b100110
#define     ll_opcode       0b110000
#define     swcl_opcode     0b110001
#define     sdcl_opcode     0b111101
#define     swl_opcode      0b101010
#define     swr_opcode      0b101110
#define     sc_opcode       0b111000
//#define     bclf_opcode     0b010001
//#define     bclt_opcode     0b
//#define     bgez_opcode
#define     bgtz_opcode     0b000111
#define     blez_opcode     0b000110
//#define     bltzal          0b
//#define     bltz            0b
#define     


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
#define     special_opcode1 0b011100      //0x1C
#define     clo_func        0b100001
#define     clz_func        0b100000
#define     mul_func        0b000010
#define     madd_func       0b000000
#define     maddu_func      0b000001
#define     msub_func       0b000100
#define     msubu_func      0b000101

#define     special_opcode2 0b010001
#define     bclt_func       0b000001
#define     bclf_func       0b000000


#endif /* IF_hpp */
