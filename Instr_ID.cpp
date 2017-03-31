//
//  Single_Cycle.cpp
//
//
//  Created by Drew Lockwood on 3/1/17.
//
//
#include "Instr_ID.h"
#include "Instr_IF.h"
#include <iostream>
#include "decode.h"

extern struct  ifid Shadow_IFID;
extern struct  idex Shadow_IDEX;
extern int Reg[31];

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
        Shadow_IDEX.RegWrite = true;
        Shadow_IDEX.MemWrite = false;
        Shadow_IDEX.MemRead = false;
        Shadow_IDEX.MemtoReg = false;
        Shadow_IDEX.ALUSrc = true;
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
    return 2;
}
