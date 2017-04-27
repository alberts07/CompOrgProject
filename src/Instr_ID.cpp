
#include "Instr_ID.hpp"
#include "Instr_IF.hpp"
#include <iostream>
#include "decode.hpp"
using namespace std;

extern struct  ifid Shadow_IFID;
extern struct  idex Shadow_IDEX;
extern struct exmem EXMEM;
extern struct idex IDEX;
extern unsigned int clock_cycles;
extern int Reg[32];

int Instr_ID()
{


    Shadow_IDEX.instr = Shadow_IFID.instr;
    Shadow_IDEX.pcplus1 = Shadow_IFID.pcplus1;

    int format = find_format(Shadow_IDEX.instr);
    if(format == rtype)
    {
        Shadow_IDEX.Rs = find_rs(Shadow_IDEX.instr);
        Shadow_IDEX.RsValue = Reg[Shadow_IDEX.Rs];
        Shadow_IDEX.Rt = find_rt(Shadow_IDEX.instr);
        Shadow_IDEX.RtValue = Reg[Shadow_IDEX.Rt];
        Shadow_IDEX.Rd = find_rd(Shadow_IDEX.instr);
        Shadow_IDEX.RdValue = Reg[Shadow_IDEX.Rd];
        Shadow_IDEX.shamt = find_shamt(Shadow_IDEX.instr);
        if(Shadow_IDEX.func != jr_func)
        {
            Shadow_IDEX.RegWrite = true;
            Shadow_IDEX.MemWrite = false;
            Shadow_IDEX.MemRead = false;
            Shadow_IDEX.MemtoReg = false;
            Shadow_IDEX.ALUSrc = true;
        }
        else
        {
            Shadow_IDEX.RegWrite = false;
            Shadow_IDEX.MemWrite = false;
            Shadow_IDEX.MemRead = false;
            Shadow_IDEX.MemtoReg = false;
            Shadow_IDEX.ALUSrc = true;
        }
        return rtype;
    }
    if(format == itype)
    {
        Shadow_IFID.immed16 = find_immed16(Shadow_IDEX.instr);
        Shadow_IDEX.immed16 = Shadow_IFID.immed16;
        Shadow_IDEX.Rs = find_rs(Shadow_IDEX.instr);
        Shadow_IDEX.RsValue = Reg[Shadow_IDEX.Rs];
        Shadow_IDEX.Rt = find_rt(Shadow_IDEX.instr);
        Shadow_IDEX.RtValue = Reg[Shadow_IDEX.Rt];
        // if (Shadow_IDEX.Rt == 29|| Shadow_IDEX.Rs == 29 ||  Shadow_IDEX.Rs == 29 ){
        //   Shadow_IDEX.immed16 = Shadow_IDEX.immed16 / 4;
        // }
        return itype;
    }
    if(format == jtype)
    {
        Shadow_IDEX.RegWrite = false;
        Shadow_IDEX.MemWrite = false;
        Shadow_IDEX.MemRead = false;
        Shadow_IDEX.MemtoReg = false;
        Shadow_IDEX.ALUSrc = false;
        Shadow_IDEX.immed26 = find_immed26(Shadow_IDEX.instr);
        return jtype;
    }
    if(format == special_opcode)
    {
        Shadow_IDEX.RegWrite = true;
        Shadow_IDEX.MemWrite = false;
        Shadow_IDEX.MemRead = false;
        Shadow_IDEX.MemtoReg = false;
        Shadow_IDEX.ALUSrc = true;
        Shadow_IDEX.Rt = find_rt(Shadow_IDEX.instr);
        Shadow_IDEX.RtValue = Reg[Shadow_IDEX.Rt];
        Shadow_IDEX.Rd = find_rd(Shadow_IDEX.instr);
        return special_opcode;
    }


    return -1;
}
