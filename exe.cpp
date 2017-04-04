#include "exe.hpp"
#include "Instr_IF.hpp"
#include "Instr_ID.hpp"
#include <iostream>
using namespace std;

extern int Reg[32];

extern struct exmem Shadow_EXMEM;
extern struct idex Shadow_IDEX;
extern struct ifid  Shadow_IFID;

extern unsigned int $pc;

void add()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue + Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void addi()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue + Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void addiu()
{
    Shadow_EXMEM.ALUResult = (unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void addu()
{
    Shadow_EXMEM.ALUResult = (unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void andd()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue & Shadow_IDEX.RsValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void andi()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue & Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void beq()
{
    if(Shadow_IDEX.RsValue == Shadow_IDEX.RtValue)
    {
        $pc = Shadow_EXMEM.pcplus1  + Shadow_IDEX.immed16;
        //$pc = $pc  + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = $pc;
    }
}
/*

void bltzal()
{
    if (Shadow_IDEX.RsValue < 0)
    {
        Reg[31]= $pc + 2;
        $pc = Shadow_IDEX.pcplus1 + Shadow_IDEX.immed16;
    }
}
void bgez()
{
    if(Shadow_IDEX.RsValue >= 0)
    {
        Shadow_EXMEM.ALUResult = Shadow_IDEX.pcplus1 + Shadow_IDEX.immed16;
    }
}

void bgezal()
{
    if(Shadow_IDEX.RsValue >= 0)
    {
        Reg[31] = $pc + 2;
        $pc = Shadow_IDEX.pcplus1 + Shadow_IDEX.immed16;
    }
}
*/
void bgtz()
{
    if(Shadow_IDEX.RsValue > 0)
    {
        $pc = Shadow_EXMEM.pcplus1  + Shadow_IDEX.immed16;
        //$pc = $pc  + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = $pc;
    }
}

void blez()
{
    if(Shadow_IDEX.RsValue == 0 || ((Shadow_IDEX.RsValue & 0x80000000) >> 31) == 1)
    {
        $pc = Shadow_EXMEM.pcplus1  + Shadow_IDEX.immed16;
        //$pc = $pc  + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = $pc;
    }
}

void bltz()
{
    if(Shadow_IDEX.RsValue < 0)
    {
        $pc = Shadow_EXMEM.pcplus1  + Shadow_IDEX.immed16;
        //$pc = $pc  + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = $pc;
    }
}

void bne()
{
    if(Shadow_IDEX.RsValue != Shadow_IDEX.RtValue)
    {
        $pc = Shadow_EXMEM.pcplus1 + Shadow_IDEX.immed16;
        //$pc = $pc  + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = $pc;
    }
}

void j()
{
    $pc = ((Shadow_IFID.pcplus1 & jump_mask) >> 2) | Shadow_IDEX.immed26;
    Shadow_EXMEM.pcplus1 = $pc;
}

void jal()
{
    Reg[31] = $pc+2;
    $pc = ((jump_mask & Shadow_IFID.pcplus1) >> 2) | Shadow_IDEX.immed26;
    Shadow_EXMEM.pcplus1 = $pc;
}

void jr()
{
    $pc = Shadow_IDEX.RsValue;
    Shadow_EXMEM.pcplus1 = $pc;
}

void lb()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_IDEX.immed16 % 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}
void lbu()
{
     Shadow_EXMEM.ALUResult = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2;
     Shadow_EXMEM.mem = Shadow_IDEX.immed16 % 4;
     Shadow_EXMEM.half = false;
     Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void lh()
{
    Shadow_EXMEM.ALUResult  = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_IDEX.immed16 % 2;
    Shadow_EXMEM.half = true;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}
void lui()
{
  Shadow_EXMEM.ALUResult  =  Shadow_IDEX.immed16 << 16;
  Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void lhu()
{
    Shadow_EXMEM.ALUResult = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_IDEX.immed16 % 2;
    Shadow_EXMEM.half = true;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void lw()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;

}

void nor()
{
    Shadow_EXMEM.ALUResult = ~(Shadow_IDEX.RsValue | Shadow_IDEX.RtValue);
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void orr()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue | Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void ori()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue | Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void sb()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_IDEX.immed16 % 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.RsValue = Shadow_IDEX.RsValue;

}

void sh()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_IDEX.immed16 % 2;
    Shadow_EXMEM.half = true;
    Shadow_EXMEM.RsValue = Shadow_IDEX.RsValue;
}

void sll()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue << Shadow_IDEX.shamt;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}
/*
void sllv()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue << Shadow_IDEX.RsValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}*/

void slt()
{
    if(Shadow_IDEX.RsValue < Shadow_IDEX.RtValue)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void slti()
{
    if(Shadow_IDEX.RsValue < Shadow_IDEX.immed16)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void sltiu()
{
    if((unsigned int)Shadow_IDEX.RsValue < (unsigned int)Shadow_IDEX.immed16)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void sltu()
{
    if((unsigned int)Shadow_IDEX.RsValue < (unsigned int)Shadow_IDEX.RtValue)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}


void srl()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue >> Shadow_IDEX.shamt;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}
/*
void srlv()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue >> Shadow_IDEX.RsValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}*/

void sub()
{
  Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue - Shadow_IDEX.RtValue;
  Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void subu()
{
    Shadow_EXMEM.ALUResult = (unsigned int)Shadow_IDEX.RsValue - (unsigned int)Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void sw()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.RsValue = Shadow_IDEX.RsValue;
}

void xorr(void)
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue ^ Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void xori()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue ^ Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void movn()
{
    if(Shadow_IDEX.RtValue != 0)
    {
        Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue;
        Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
    }
}

void movz()
{
    if(Shadow_IDEX.RtValue == 0)
    {
        Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue;
        Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
    }
}
