#include "exe.hpp"
#include "Instr_IF.hpp"
#include "Instr_ID.hpp"
#include "decode.hpp"
#include "Instr_MEM.hpp"
#include "Instr_Exe.hpp"
#include "Instr_WB.hpp"
#include "Update_State.hpp"
#include <iostream>
using namespace std;

extern int Reg[32];
extern int memory[1200];
extern struct exmem Shadow_EXMEM;
extern struct idex Shadow_IDEX;
extern struct ifid  Shadow_IFID;
extern unsigned int pc;

void add()
{
#if testing
    cout << "add" << endl;
#endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue + Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void addi()
{
  #if testing
      cout << "addi" << endl;
  #endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue + Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void addiu()
{
  #if testing
      //cout << "addiu" << endl;
  #endif

    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue + Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void addu()
{
  #if testing
      cout << "addu" << endl;
  #endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue + Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void andd()
{
  #if testing
      cout << "and" << endl;
  #endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue & Shadow_IDEX.RsValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void andi()
{
  #if testing
      cout << "andi" << endl;
  #endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue & Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void beq()
{
  #if testing
      cout << "beq" << endl;
  #endif
    if(Shadow_IDEX.RsValue == Shadow_IDEX.RtValue)
    {
        Shadow_IDEX.branch = true;
        pc = Shadow_EXMEM.pcplus1 + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = pc;
    }
}
void bgtz()
{
  #if testing
      cout << "bgtz" << endl;
  #endif
    if(Shadow_IDEX.RsValue > 0)
    {
        Shadow_IDEX.branch = true;
        pc = Shadow_EXMEM.pcplus1 + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = pc;
    }
}

void blez()
{
  #if testing
      cout << "blez" << endl;
  #endif
    if(Shadow_IDEX.RsValue == 0 || ((Shadow_IDEX.RsValue & 0x80000000) >> 31) == 1)
    {
        Shadow_IDEX.branch = true;
        pc = Shadow_EXMEM.pcplus1 + Shadow_IDEX.immed16;
        //pc = pc  + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = pc;
    }
}

void bltz()
{
  #if testing
      cout << "bltz" << endl;
  #endif
    if(Shadow_IDEX.RsValue < 0)
    {
        pc = Shadow_EXMEM.pcplus1 + Shadow_IDEX.immed16;
        Shadow_IDEX.branch = true;
        //pc = pc  + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = pc;
    }
}

void bne()
{
  #if testing
      cout << "bne" << endl;
  #endif
    if(Shadow_IDEX.RsValue != Shadow_IDEX.RtValue)
    {
        pc = Shadow_EXMEM.pcplus1 + Shadow_IDEX.immed16;
        Shadow_IDEX.branch = true;
        //pc = pc  + Shadow_IDEX.immed16;
        Shadow_EXMEM.pcplus1 = pc;
    }
}

void j()
{
  #if testing
      cout << "j" << endl;
  #endif
    pc = ((Shadow_IFID.pcplus1 & jump_mask) >> 2) | Shadow_IDEX.immed26;
    Shadow_EXMEM.pcplus1 = pc;
}

void jal()
{
  #if testing
      cout << "jal" << endl;
  #endif
    Reg[31] = pc+1;
    pc = ((jump_mask & Shadow_IFID.pcplus1) >> 2) | Shadow_IDEX.immed26;
    Shadow_EXMEM.pcplus1 = pc;
}

void jr()
{
  #if testing
      cout << "jr" << endl;
  #endif
    pc = Shadow_IDEX.RsValue;
    Shadow_EXMEM.pcplus1 = pc;
}

void lb()
{
  #if testing
      cout << "lb" << endl;
  #endif
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) % 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
    cout << "Result: " << dec << Shadow_EXMEM.ALUResult << endl;
    cout << "Result: " << dec << Shadow_EXMEM.mem << endl;
}
void lbu()
{
  #if testing
      cout << "lbu" << endl;
  #endif
     Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
     Shadow_EXMEM.mem = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) % 4;
     Shadow_EXMEM.half = false;
     Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void lh()
{
  #if testing
      cout << "lh" << endl;
  #endif
    Shadow_EXMEM.ALUResult  = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) % 2;
    Shadow_EXMEM.half = true;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}
void lui()
{
  #if testing
      cout << "lui" << endl;
  #endif
  Shadow_EXMEM.ALUResult  =  (Shadow_IDEX.immed16 << 16);
  Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void lhu()
{
  #if testing
      cout << "lhu" << endl;
  #endif
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) % 2;
    Shadow_EXMEM.half = true;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void lw()
{
  #if testing
      cout << "lw" << endl;
  #endif
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void nor()
{
  #if testing
      cout << "nor" << endl;
  #endif
    Shadow_EXMEM.ALUResult = ~(Shadow_IDEX.RsValue | Shadow_IDEX.RtValue);
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void orr()
{
  #if testing
      cout << "or" << endl;
  #endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue | Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void ori()
{
  #if testing
      cout << "ori" << endl;
  #endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue | Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void sb()
{
  #if testing
      cout << "sb" << endl;
  #endif
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) % 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.RsValue = Shadow_IDEX.RsValue;

}

void sh()
{
  #if testing
      cout << "sh" << endl;
  #endif
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) % 2;
    Shadow_EXMEM.half = true;
    Shadow_EXMEM.RsValue = Shadow_IDEX.RsValue;
}

void sll()
{
  #if testing
      cout << "sll" << endl;
  #endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue << Shadow_IDEX.shamt;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}
void slt()
{
  #if testing
      cout << "slt" << endl;
  #endif
    if(Shadow_IDEX.RsValue < Shadow_IDEX.RtValue)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void slti()
{
  #if testing
      cout << "slti" << endl;
  #endif
    if(Shadow_IDEX.RsValue < Shadow_IDEX.immed16)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void sltiu()
{
  #if testing
      cout << "sltiu" << endl;
  #endif
    if((unsigned int)Shadow_IDEX.RsValue < (unsigned int)Shadow_IDEX.immed16)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
    Shadow_EXMEM.RegWrite = true;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void sltu()
{
  #if testing
      cout << "sltu" << endl;
  #endif
    if((unsigned int)Shadow_IDEX.RsValue < (unsigned int)Shadow_IDEX.RtValue)
        Shadow_EXMEM.ALUResult = 1;
    else
        Shadow_EXMEM.ALUResult = 0;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}


void srl()
{
  #if testing
      cout << "srl" << endl;
  #endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue >> Shadow_IDEX.shamt;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}


void sub()
{
  #if testing
      cout << "sub" << endl;
  #endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue - Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void subu()
{
  #if testing
      cout << "subu" << endl;
  #endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue - Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void sw()
{
  #if testing
      cout << "sw" << endl;
  #endif
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = 4;
    Shadow_EXMEM.half = false;
    Shadow_EXMEM.RsValue = Shadow_IDEX.RsValue;
}

void xorr(void)
{
  #if testing
      cout << "xor" << endl;
  #endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue ^ Shadow_IDEX.RtValue;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
}

void xori()
{
  #if testing
      cout << "xori" << endl;
  #endif
    Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue ^ Shadow_IDEX.immed16;
    Shadow_EXMEM.DstReg = Shadow_IDEX.Rt;
}

void movn()
{
  #if testing
      cout << "movn" << endl;
  #endif
    if(Shadow_IDEX.RtValue != 0)
    {
        Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue;
        Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
    }
    else
    {
      Shadow_EXMEM.ALUResult = Shadow_IDEX.RdValue;
      Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
    }
}

void movz()
{
  #if testing
      cout << "movz" << endl;
  #endif
    if(Shadow_IDEX.RtValue == 0)
    {
        Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue;
        Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
    }
    else
    {
      Shadow_EXMEM.ALUResult = Shadow_IDEX.RdValue;
      Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;
    }
}

void seb()
{
  #if testing
      cout << "seb" << endl;
  #endif
  if((Shadow_IDEX.RtValue & 0x00000080) != 0)
      Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue | 0xFFFFFF00;
  else
      Shadow_EXMEM.ALUResult = Shadow_IDEX.RtValue & 0x000000FF;

  //cout << "Result: " << dec << Shadow_EXMEM.ALUResult << endl;
  Shadow_EXMEM.DstReg = Shadow_IDEX.Rd;

}
