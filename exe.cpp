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
    cout << "add" << endl;
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue + Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void addi()
{
    cout << "addi" << endl;
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue + Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void addiu()
{
    cout << "addiu" <<endl;
    Shadow_EXMEM.ALUResult = (unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void addu()
{
    cout << "addu" << endl;
    Shadow_EXMEM.ALUResult = (unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void andd()
{
    cout << "and" << endl;
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue & Shadow_IDEX.RsValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void andi()
{
    cout << "andi" << endl;
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue & Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void beq()
{
    cout << "beq" << endl;
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
    cout << "bgtz" << endl;
    if(Shadow_IDEX.RsValue > 0)
    {
        $pc = Shadow_EXMEM.pcplus1  + Shadow_IDEX.immed16;
        //$pc = $pc  + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = $pc;
    }
}

void blez()
{
    cout << "blez" << endl;
    if(Shadow_IDEX.RsValue == 0 || ((Shadow_IDEX.RsValue & 0x80000000) >> 31) == 1)
    {
        $pc = Shadow_EXMEM.pcplus1  + Shadow_IDEX.immed16;
        //$pc = $pc  + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = $pc;
    }
}

void bltz()
{
    cout << "bltz" << endl;
    if(Shadow_IDEX.RsValue < 0)
    {
        $pc = Shadow_EXMEM.pcplus1  + Shadow_IDEX.immed16;
        //$pc = $pc  + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = $pc;
    }
}

void bne()
{
    cout << "bne" << endl;
    if(Shadow_IDEX.RsValue != Shadow_IDEX.RtValue)
    {
        $pc = Shadow_EXMEM.pcplus1 + Shadow_IDEX.immed16;
        //$pc = $pc  + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = $pc;
    }
}

void j()
{
    cout << "j" << endl;
    $pc = ((Shadow_IFID.pcplus1 & jump_mask) >> 2) | Shadow_IDEX.immed26;
    Shadow_EXMEM.pcplus1 = $pc;
}

void jal()
{
    cout << "jal" << endl;
    Reg[31] = $pc+2;
    $pc = ((jump_mask & Shadow_IFID.pcplus1) >> 2) | Shadow_IDEX.immed26;
    Shadow_EXMEM.pcplus1 = $pc;
}

void jr()
{
    cout << "jr" << endl;
    $pc = Shadow_IDEX.RsValue;
    Shadow_EXMEM.pcplus1 = $pc;
}

void lb()
{
    cout << "lb" << endl;
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_IDEX.immed16 % 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}
void lbu()
{
    cout << "lbu" << endl;
     Shadow_EXMEM.ALUResult = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2;
     Shadow_EXMEM.mem = Shadow_IDEX.immed16 % 4;
     Shadow_EXMEM.half = false;
     Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void lh()
{
    cout << "lh" << endl;
    Shadow_EXMEM.ALUResult  = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_IDEX.immed16 % 2;
    Shadow_EXMEM.half = true;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}
void lui()
{
  cout << "lui" << endl;
  Shadow_EXMEM.ALUResult  =  Shadow_IDEX.immed16 << 16;
  Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void lhu()
{
    cout << "lhu"  << endl;
    Shadow_EXMEM.ALUResult = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_IDEX.immed16 % 2;
    Shadow_EXMEM.half = true;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void lw()
{
    cout << "lw" << endl;
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;

}

void nor()
{
    cout << "nor" << endl;
    Shadow_EXMEM.ALUResult = ~(Shadow_IDEX.RsValue | Shadow_IDEX.RtValue);
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void orr()
{
    cout << "or" << endl;
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
    cout << "sb" << endl;
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_IDEX.immed16 % 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.RsValue = Shadow_IDEX.RsValue;

}

void sh()
{
    cout << "sh" << endl;
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = Shadow_IDEX.immed16 % 2;
    Shadow_EXMEM.half = true;
    Shadow_EXMEM.RsValue = Shadow_IDEX.RsValue;
}

void sll()
{
    cout << "sll" << endl;
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
    cout << "slt" << endl;
    if(Shadow_IDEX.RsValue < Shadow_IDEX.RtValue)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void slti()
{
    cout << "slti" << endl;
    if(Shadow_IDEX.RsValue < Shadow_IDEX.immed16)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void sltiu()
{
    cout << "sltiu" << endl;
    if((unsigned int)Shadow_IDEX.RsValue < (unsigned int)Shadow_IDEX.immed16)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void sltu()
{
    cout << "sltu" << endl;

    if((unsigned int)Shadow_IDEX.RsValue < (unsigned int)Shadow_IDEX.RtValue)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}


void srl()
{
    cout << "srl " << endl;
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
    cout << "sub" << endl;
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue - Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void subu()
{
    cout << "subu" << endl;
    Shadow_EXMEM.ALUResult = (unsigned int)Shadow_IDEX.RsValue - (unsigned int)Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void sw()
{
    cout << "sw" << endl;
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.RsValue = Shadow_IDEX.RsValue;
}

void xorr(void)
{
    cout << "xor" << endl;
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue ^ Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void xori()
{
    cout << "xori " << endl;
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue ^ Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void movn()
{
    cout << "movn" << endl;
    if(Shadow_IDEX.RtValue != 0)
    {
        Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue;
        Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
    }
}

void movz()
{
    cout << "movz" << endl;
    if(Shadow_IDEX.RtValue == 0)
    {
        Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue;
        Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
    }
}
