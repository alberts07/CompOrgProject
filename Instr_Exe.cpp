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
    Shadow_EXMEM.MemtoReg = Shadow_IDEX.MemtoReg;
    Shadow_EXMEM.RegWrite = Shadow_IDEX.RegWrite;
    Shadow_EXMEM.MemRead = Shadow_IDEX.MemRead;
    Shadow_EXMEM.MemWrite = Shadow_IDEX.MemWrite;
    Shadow_EXMEM.RsValue = Shadow_IDEX.RsValue;
    Shadow_EXMEM.pcplus1 = Shadow_IDEX.pcplus1;
    Shadow_EXMEM.RtValue = Shadow_IDEX.RtValue;
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
         }
   }

   else if(format == itype)
   {
       Shadow_IDEX.ALUSrc = true ;
       Shadow_IDEX.MemtoReg = false;
       Shadow_IDEX.RegWrite = true;
       Shadow_IDEX.MemRead = false;
       Shadow_IDEX.MemWrite = false;

       switch(Shadow_IDEX.opcode)
       {
           case lw_opcode:
           {
               Shadow_EXMEM.MemtoReg = true;
               Shadow_EXMEM.RegWrite = true;
               Shadow_EXMEM.MemRead = true;
               Shadow_EXMEM.MemWrite = false;
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
               Shadow_EXMEM.MemtoReg = false;
               Shadow_EXMEM.RegWrite = false;
               Shadow_EXMEM.MemRead = false;
               Shadow_EXMEM.MemWrite = true;
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
               Shadow_EXMEM.MemtoReg = true;
               Shadow_EXMEM.RegWrite = true;
               Shadow_EXMEM.MemRead = true;
               Shadow_EXMEM.MemWrite = false;

               lb();
               break;
           }
           case lh_opcode:
           {
               Shadow_EXMEM.MemtoReg = true;
               Shadow_EXMEM.RegWrite = true;
               Shadow_EXMEM.MemRead = true;
               Shadow_EXMEM.MemWrite = false;

               lh();
               break;
           }
           case sb_opcode:
           {
               Shadow_EXMEM.MemtoReg = false;
               Shadow_EXMEM.RegWrite = false;
               Shadow_EXMEM.MemRead = false;
               Shadow_EXMEM.MemWrite = true;
               sb();
               break;
           }
           case sh_opcode:
           {
               Shadow_EXMEM.MemtoReg = false;
               Shadow_EXMEM.RegWrite = false;
               Shadow_EXMEM.MemRead = false;
               Shadow_EXMEM.MemWrite = true;

               sh();
               break;
           }
           case beq_opcode:
           {
               Shadow_EXMEM.MemtoReg = false;
               Shadow_EXMEM.RegWrite = false;
               Shadow_EXMEM.MemRead = false;
               Shadow_EXMEM.MemWrite = false;

               beq();
               break;
           }
           case bne_opcode:
           {
               Shadow_EXMEM.MemtoReg = false;
               Shadow_EXMEM.RegWrite = false;
               Shadow_EXMEM.MemRead = false;
               Shadow_EXMEM.MemWrite = false;

               bne();
               break;
           }
           case lhu_opcode:
           {
               Shadow_EXMEM.MemtoReg = true;
               Shadow_EXMEM.RegWrite = true;
               Shadow_EXMEM.MemRead = true;
               Shadow_EXMEM.MemWrite = false;

               lhu();
               break;
           }
           default:
           {
              std::cout << "Did not find function" << std::endl;
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
}
