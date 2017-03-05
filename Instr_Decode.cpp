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
        int rs = find_rs(instr);
        int rt = find_rt(instr);
        int rd = find_rd(instr);
        int shamt = find_shamt(instr);
        switch(format[3])
        {
            case: add_func
            {
                add();      
                break;
            }
            case: clo_func
            {
                clo();      
                break;
            }
            case: clz_func
            {
                clz();      
                break;
            }
                
            case: addu_func
            {
                addu();
                break;
            }
            case: and_func
            {
                and();
                break;
            }
            case: nor_func
            {
                nor();
                break;
            }
            case: or_func
            {
                or();
                break;
            }
            case: slt_func
            {
                slt();
                break;
            }
            case: sltu_func
            {
                sltu();
                break;
            }
            case: sub_func
            {
                sub();
                break;
            }
            case: subu_func
            {
                subu();
                break;
            }
            case: xor_func
            {
                xor();
                break;
            }
            case: sll_func
            {
                sll();
                break;
            }
            case: srl_func
            {
                srl();
                break;
            }
            case: sllv_func
            {
                sllv();
                break;
            }
            case: srav_func
            {
                srav();
                break;
            }
            case: srlv_func
            {
                srlv();
                break;
            }
            case: sra_func
            {
                sra();
                break;
            }
            case: div_func
            {
                div();
                break;
            }
            case: divu_func
            {
                divu();
                break;
            }
            case: mult_func
            {
                mult();
                break;
            }
            case: mutlu_func:
            {
                multu();
                break;
            }
            case: mul_func
            {
                mul();      
                break;
            }
            case: madd_func
            {
                madd();      
                break;
            }
            case: maddu_func
            {
                maddu();      
                break;
            }
            case: msub_func
            {
                msub();      
                break;
            }
            case: msubu_func
            {
                msubu();      
                break;
            }
            case: jr_func:
            {
                jr();
                break;
            }
            case: jalr_func:
            {
                jalr();
                break;
            }
            case: teq_func
            {
                teq();
                break;
            }
            case: tne_func
            {
                tne();
                break;
            }
            case: tge_func
            {
                tge();
                break;
            }
            case: tgeu_func
            {
                tgeu();
                break;
            }
            case: tlt_func
            {
                tlt();
                break;
            }
            case: tltu_func
            {
                tltu();
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
                lw();
                break;
            }
            case: addi_opcode
            {
                addi();
                break;
            }
            case: sw_opcode
            {
                sw();
                break;
            }
            case: slti_opcode
            {
                slti();
                break;
            }
            case: sltiu_opcode
            {
                sltiu();
                break;
            }
            case: addiu_opcode
            {
                addiu();
                break;
            }
            case: andi_opcode
            {
                andi();
                break;
            }
            case: lui_opcode
            {
                lui();
                break;
            }
            case: ori_opcode
            {
                ori();
                break;
            }
            case: xori_opcode
            {
                xori();
                break;
            }
            case: lb_opcode
            {
                lb();
                break;
            }
            case: lh_opcode
            {
                lh();
                break;
            }
            case: sb_opcode
            {
                sb();
                break;
            }
            case: sh_opcode
            {
                sh();
                break;
            }
            case: beq_opcode
            {
                beq();
                break;
            }
            case: bne_opcode
            {
                bne();
                break;
            }
            case: lhu_opcode
            {
                lhu();
                break;
            }
        }
        if(format[0] = jtype)
        {
            case: j_opcode
            {
                j();
                break;
            }
            case: jal_opcode
            {
                jal();
                break;
            }
        }
    }
}
        
        
    
        

                
 
 
