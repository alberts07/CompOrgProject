//
//  Instr_Exe.cpp
//
//
//  Created by Drew Lockwood on 3/1/17.
//
//
#include <iostream>
#include "Instr_Exe.h"
#include "Instr_IF.h"
#include "exe.h"

extern struct idex Shadow_IDEX;
extern struct exmem Shadow_EXMEM;

void Instr_Exe(int format)
{
    if(format == rtype)
    {
       switch(Shadow_IDEX.func)
           {
               case add_func:
               {
                   add();
                   break;
               }
               case addu_func:
               {
                   addu();
                   break;
               }
               case and_func:
               {
                   andd();
                   break;
               }
               case nor_func:
               {
                   nor();
                   break;
               }
               case or_func:
               {
                   orr();
                   break;
               }
               case slt_func:
               {
                   slt();
                   break;
               }
               case sltu_func:
               {
                   sltu();
                   break;
               }
               case sub_func:
               {
                   sub();
                   break;
               }
               case subu_func:
               {
                   subu();
                   break;
               }
               case xor_func:
               {
                   xorr();
                   break;
               }
               case sll_func:
               {
                   sll();
                   break;
               }
               case srl_func:
               {
                   srl();
                   break;
               }
               /*
               case sllv_func:
               {
                   sllv();
                   break;
               }
               case srav_func:
               {
                   srav();
                   break;
               }

               case srlv_func:
               {
                   srlv();
                   break;
               }

               case sra_func:
               {
                   sra();
                   break;
               }

               case div_func:
               {
                   div();
                   break;
               }
               case divu_func:
               {
                   divu();
                   break;
               }
               case mult_func:
               {
                   mult();
                   break;
               }
               case mutlu_func:
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
               */
               case jr_func:
               {
                   jr();
                   break;
               }
               /*
               case jalr_func:
               {
                   jalr();
                   break;
               }*/
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

       Shadow_IDEX.ALUSrc = true ;
       Shadow_IDEX.MemtoReg = false;
       Shadow_IDEX.RegWrite = true;
       Shadow_IDEX.MemRead = false;
       Shadow_IDEX.MemWrite = false;

       switch(Shadow_IDEX.opcode)
       {
           case lw_opcode:
           {
               Shadow_IDEX.ALUSrc = true;
               Shadow_IDEX.MemtoReg = true;
               Shadow_IDEX.RegWrite = true;
               Shadow_IDEX.MemRead = true;
               Shadow_IDEX.MemWrite = false;

               lw();
               break;
           }
           case addi_opcode:
           {
               addi();
               break;
           }
           case sw_opcode:
           {

               Shadow_IDEX.ALUSrc = true;
               Shadow_IDEX.MemtoReg = false;
               Shadow_IDEX.RegWrite = false;
               Shadow_IDEX.MemRead = false;
               Shadow_IDEX.MemWrite = true;

               sw();
               break;
           }
           case slti_opcode:
           {
               slti();
               break;
           }
           case sltiu_opcode:
           {
               sltiu();
               break;
           }
           case addiu_opcode:
           {
               addiu();
               break;
           }
           case andi_opcode:
           {
               andi();
               break;
           }
           /*
           case lui_opcode:
           {
               Shadow_IDEX.ALUSrc = true;
               Shadow_IDEX.MemtoReg = true;
               Shadow_IDEX.RegWrite = true;
               Shadow_IDEX.MemRead = true;
               Shadow_IDEX.MemWrite = false;

               lui();
               break;
           }
           */
           case ori_opcode:
           {
               ori();
               break;
           }
           case xori_opcode:
           {
               xori();
               break;
           }
           case lb_opcode:
           {

               Shadow_IDEX.ALUSrc = true;
               Shadow_IDEX.MemtoReg = true;
               Shadow_IDEX.RegWrite = true;
               Shadow_IDEX.MemRead = true;
               Shadow_IDEX.MemWrite = false;

               lb();
               break;
           }
           case lh_opcode:
           {

               Shadow_IDEX.ALUSrc = true;
               Shadow_IDEX.MemtoReg = true;
               Shadow_IDEX.RegWrite = true;
               Shadow_IDEX.MemRead = true;
               Shadow_IDEX.MemWrite = false;

               lh();
               break;
           }
           case sb_opcode:
           {

               Shadow_IDEX.ALUSrc = true;
               Shadow_IDEX.MemtoReg = false;
               Shadow_IDEX.RegWrite = false;
               Shadow_IDEX.MemRead = false;
               Shadow_IDEX.MemWrite = true;

               sb();
               break;
           }
           case sh_opcode:
           {

               Shadow_IDEX.ALUSrc = true;
               Shadow_IDEX.MemtoReg = false;
               Shadow_IDEX.RegWrite = false;
               Shadow_IDEX.MemRead = false;
               Shadow_IDEX.MemWrite = true;

               sh();
               break;
           }
           case beq_opcode:
           {

               Shadow_IDEX.ALUSrc = false;
               Shadow_IDEX.MemtoReg = false;
               Shadow_IDEX.RegWrite = false;
               Shadow_IDEX.MemRead = false;
               Shadow_IDEX.MemWrite = false;

               beq();
               break;
           }
           case bne_opcode:
           {
               Shadow_IDEX.ALUSrc = false;
               Shadow_IDEX.MemtoReg = false;
               Shadow_IDEX.RegWrite = false;
               Shadow_IDEX.MemRead = false;
               Shadow_IDEX.MemWrite = false;

               bne();
               break;
           }
           case lhu_opcode:
           {

               Shadow_IDEX.ALUSrc = true;
               Shadow_IDEX.MemtoReg = true;
               Shadow_IDEX.RegWrite = true;
               Shadow_IDEX.MemRead = true;
               Shadow_IDEX.MemWrite = false;

               lhu();
               break;
           }
       }
   }

   else if(format == jtype)
   {
        switch(Shadow_IDEX.opcode)
           {
               case j_opcode:
               {
                   j();
                   break;
               }
               case jal_opcode:
               {
                   jal();
                   break;
               }
           }
   }
   else
   {
       std::cout << "The format given did not match any message type";
   }
   Shadow_EXMEM.MemtoReg = Shadow_IDEX.MemtoReg;
   Shadow_EXMEM.RegWrite = Shadow_IDEX.RegWrite;
   Shadow_EXMEM.MemRead = Shadow_IDEX.MemRead;
   Shadow_EXMEM.MemWrite = Shadow_IDEX.MemWrite;
}
