#include "exe.h"
#include "Instr_IF.h"
#include "Instr_ID.h"
#include <iostream>

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
        Shadow_EXMEM.ALUResult = Shadow_IDEX.pcplus1 + Shadow_IDEX.immed16;
}

void bgez()
{
    if(Shadow_IDEX.RsValue >= 0)
    {
        Shadow_EXMEM.ALUResult = Shadow_IDEX.pcplus1+Shadow_IDEX.immed16;
    }
}

void bgezal()
{
    if(Shadow_IDEX.RsValue >= 0)
    {
        Reg[31] = $pc + 2;
        Shadow_EXMEM.ALUResult = Shadow_IDEX.pcplus1 + Shadow_IDEX.immed16;
    }
}

void bgtz()
{
    if(Shadow_IDEX.RsValue > 0)
    {
        Shadow_EXMEM.ALUResult = Shadow_IDEX.pcplus1+Shadow_IDEX.immed16;
    }
}

void blez()
{
    if(Shadow_IDEX.RsValue <= 0)
    {
        Shadow_EXMEM.ALUResult = Shadow_IDEX.pcplus1 + Shadow_IDEX.immed16;
    }
}

void bltz()
{
    if(Shadow_IDEX.RsValue < 0)
    {
        Shadow_EXMEM.ALUResult = Shadow_IDEX.pcplus1 + Shadow_IDEX.immed16;
    }
}

void bltzal()
{
    if (Shadow_IDEX.RsValue < 0)
    {
        Reg[31]= $pc + 2;
        Shadow_EXMEM.ALUResult = Shadow_IDEX.pcplus1 + Shadow_IDEX.immed16;
    }
}

void bne()
{
    if(Shadow_IDEX.RsValue != 0)
    {
        Shadow_EXMEM.ALUResult = Shadow_IDEX.pcplus1+Shadow_IDEX.immed16;
    }
}

void j()
{
    Shadow_IFID.pcplus1 = 0;
    $pc = (($pc & jump_mask) >> 2) | Shadow_IDEX.immed26;
}

void jal()
{
    Reg[31] = $pc+2;
    $pc = ((jump_mask & $pc) >> 2) | Shadow_IDEX.immed26;
}

void jr()
{
    $pc = Shadow_IDEX.RsValue;
}

void lb()
{
    Shadow_EXMEM.ALUResult = ((Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2);
    Shadow_EXMEM.mem = Shadow_EXMEM.ALUResult % 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}
void lbu()
{
     Shadow_EXMEM.ALUResult = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2;
     Shadow_EXMEM.mem = Shadow_EXMEM.ALUResult % 4;
     Shadow_EXMEM.half = false;
     Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void lh()
{
    Shadow_EXMEM.ALUResult  = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_EXMEM.ALUResult % 2;
    Shadow_EXMEM.half = true;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;


}

void lhu()
{
    Shadow_EXMEM.ALUResult = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_EXMEM.ALUResult % 2;
    Shadow_EXMEM.half = true;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void lw()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
    std::cout << Shadow_EXMEM.ALUResult << std::endl;
    std::cout << Shadow_EXMEM.DstReg << std::endl;

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
    Shadow_EXMEM.mem = Shadow_EXMEM.ALUResult % 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.RsValue = Shadow_IDEX.RsValue;
    std:: cout << Shadow_EXMEM.ALUResult << std::endl;
}

void sh()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_EXMEM.ALUResult % 2;
    Shadow_EXMEM.half = true;
    Shadow_EXMEM.RsValue = Shadow_IDEX.RsValue;
    std:: cout << Shadow_EXMEM.ALUResult << std::endl;
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
    std::cout << Shadow_EXMEM.ALUResult << std::endl;
    std::cout << Shadow_EXMEM.DstReg << std::endl;
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
