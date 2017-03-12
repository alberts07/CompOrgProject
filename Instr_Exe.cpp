//
//  Instr_Exe.cpp
//  
//
//  Created by Drew Lockwood on 3/1/17.
//
//

#include "Instr_Exe.hpp"

void ex_pipe(int format)
{
    if(format == rtype)
    {
       switch(Shadow_IDEX.func)
           {
               case: add_func
               {
                   add();      
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
               /*
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
               */
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
                   /*
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
               }*/
           }
   }
    
   else if(format == itype){
        
       switch(Shadow_IDEX.opcode)
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
   }
    
   else if(format == jtype)
   {
        switch(Shadow_IDEX.opcode)
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
   else
   {
       std::cout("The format given did not match any message type");
   }
}
