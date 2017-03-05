//
//  Single_Cycle.cpp
//  
//
//  Created by Drew Lockwood on 3/1/17.
//
//
#include "Instr_Decode.hpp"
#include "IF.hpp"

std::vector<int> Instr_Decode(unsigned int instr)
{
    std::vector<int> format = find_format(instr);
    if(format[0] == rtype)
    {
        switch(format[3])
        {
            case: add_func
            {
                   
                break;
            }
            case: addu_func
            {

                break;
            }
            case: and_func
            {

                break;
            }
            case: nor_func
            {

                break;
            }
            case: or_func
            {

                break;
            }
            case: slt_func
            {

                break;
            }
            case: sltu_func
            {

                break;
            }
            case: sub_func
            {

                break;
            }
            case: subu_func
            {

                break;
            }
            case: xor_func
            {

                break;
            }
            case: sll_func
            {

                break;
            }
            case: sllv_func
            {

                break;
            }
            case: srl_func
            {

                break;
            }
            case: srlv_func
            {

                break;
            }
            case: sra_func
            {

                break;
            }
            case: srav_func
            {

                break;
            }
            case: div_func
            {

                break;
            }
            case: divu_func
            {

                break;
            }
            case: mfhi_func
            {

                break;
            }
            case: mflo_func
            {

                break;
            }
            case: mthi_func
            {

                break;
            }
            case: mtlo_func
            {

                break;
            }
            case: mult_func
            {

                break;
            }
            case: mutlu_func:
            {

                break;
            }
            case: break_func:
            {

                break;
            }
            case: jrs_func:
            {

                break;
            }
            case: jalrs_func:
            {

                break;
            }
            case: syscall_func:
            {

                break;
            }
        }
    }
    if(format[0] = itype)
    {
        switch(format[1])
        {
            case: lw_opcode
            {
            
                break;
            }
            case: addi_opcode
            {
            
                break;
            }
            case: sw_opcode
            {
            
                break;
            }
            case: slti_opcode
            {

                break;
            }
            case: sltiu_opcode
            {

                break;
            }
            case: addiu_opcode
            {

                break;
            }
            case: andi_opcode
            {

                break;
            }
            case: lui_opcode
            {

                break;
            }
            case: ori_opcode
            {

                break;
            }
            case: xori_opcode
            {

                break;
            }
            case: lb_opcode
            {

                break;
            }
            case: lh_opcode
            {

                break;
            }
            case: sb_opcode
            {

                break;
            }
            case: sh_opcode
            {

                break;
            }
            case: beq_opcode
            {

                break;
            }
            case: bne_opcode
            {

                break;
            }
            case: lhu_opcode
            {

                break;
            }
        }
        if(format[0] = jtype)
        {
            case: j_opcode
            {
            
                break;
            }
            case: jal_opcode
            {
            
                break;
            }
        }
    }
}
        
        
    
        

                
 
 
