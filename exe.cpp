#include "exe.h"
#include "Instr_IF.h"
#include "Instr_ID.h"
#include <iostream>

extern int Reg[32];
extern struct exmem Shadow_EXMEM;
extern struct idex Shadow_IDEX;
extern unsigned int $pc;

void add()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue + Shadow_IDEX.RtValue;
}

void addi()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue + Shadow_IDEX.immed16;
}

void addiu()
{
    Shadow_EXMEM.ALUResult = (unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16;
}

void addu()
{
    Shadow_EXMEM.ALUResult = (unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.RtValue;
}

void andd()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue & Shadow_IDEX.RsValue;
}

void andi()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue & Shadow_IDEX.immed16;
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
}
void lbu()
{
     Shadow_EXMEM.ALUResult = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2;
     Shadow_EXMEM.mem = Shadow_EXMEM.ALUResult % 4;
     Shadow_EXMEM.half = false;
}

void lh()
{
    Shadow_EXMEM.ALUResult  = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_EXMEM.ALUResult % 2;
    Shadow_EXMEM.half = true;
}

void lhu()
{
    Shadow_EXMEM.ALUResult = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_EXMEM.ALUResult % 2;
    Shadow_EXMEM.half = true;
}

void lw()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = 4;
    Shadow_EXMEM.half = false;
}

void nor()
{
    Shadow_EXMEM.ALUResult = ~(Shadow_IDEX.RsValue | Shadow_IDEX.RtValue);
}

void orr()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue | Shadow_IDEX.RtValue;
}

void ori()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue | Shadow_IDEX.immed16;
}

void sb()
{
    Shadow_EXMEM.ALUResult = ((Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2);
    Shadow_EXMEM.mem = Shadow_EXMEM.ALUResult % 4;
    Shadow_EXMEM.half = false;
}

void sh()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_EXMEM.ALUResult % 2;
    Shadow_EXMEM.half = true;
}

void sll()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue << Shadow_IDEX.shamt;
}

void sllv()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue << Shadow_IDEX.RsValue;
}

void slt()
{
    if(Shadow_IDEX.RsValue < Shadow_IDEX.RtValue)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
}

void slti()
{
    if(Shadow_IDEX.RsValue < Shadow_IDEX.immed16)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
}

void sltiu()
{
    if((unsigned int)Shadow_IDEX.RsValue < (unsigned int)Shadow_IDEX.immed16)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
}

void sltu()
{
    if((unsigned int)Shadow_IDEX.RsValue < (unsigned int)Shadow_IDEX.RtValue)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
}

void srl()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue >> Shadow_IDEX.shamt;
}

void srlv()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue >> Shadow_IDEX.RsValue;
}

void sub()
{
  Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue - Shadow_IDEX.RtValue;
}

void subu()
{
    Shadow_EXMEM.ALUResult = (unsigned int)Shadow_IDEX.RsValue - (unsigned int)Shadow_IDEX.RtValue;
}

void sw()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = 4;
    Shadow_EXMEM.half = false;
}

void xorr(void)
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue ^ Shadow_IDEX.RtValue;
}

void xori()
{
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue ^ Shadow_IDEX.immed16;
}
