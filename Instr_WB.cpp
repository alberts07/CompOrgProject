#include "Instr_IF.h"
#include "Instr_ID.h"

extern struct memwb Shadow_MEMWB;
extern struct exmem Shadow_EXMEM;
extern struct idex Shadow_IDEX;
extern int Reg[32];

void Instr_WB(int format)
{
    //if((Shadow_MEMWB.RegWrite == true) && (format == itype) && (Shadow_MEMWB.MemtoReg == false))
    if(format == itype)
    {
        Reg[Shadow_EXMEM.DstReg] = Shadow_EXMEM.ALUResult;
    }
    if((Shadow_MEMWB.RegWrite == true) && (format == itype) && (Shadow_MEMWB.MemtoReg == true))
    {
        Reg[Shadow_EXMEM.DstReg] = Shadow_MEMWB.RtValue;
    }
    //if((Shadow_MEMWB.RegWrite == true) && (format == rtype))
    if(format == rtype)
    {
        Reg[Shadow_EXMEM.DstReg] = Shadow_EXMEM.ALUResult;
    }
}
