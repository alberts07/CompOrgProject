#include "Instr_IF.hpp"
#include "Instr_ID.hpp"

extern struct memwb Shadow_MEMWB;
extern struct exmem Shadow_EXMEM;

void Instr_WB(int format)
{
    if((Shadow_MEMWB.RegWrite == true) && (format == itype) && (Shadow_MEMWB.MemtoReg == false))
    {
        Reg[Shadow_MEMWB.Rt] = Shadow_EXMEM.ALUResult;
    }
    if((Shadow_MEMWB.RegWrite == true) && (format == itype) && (Shadow_MEMWB.MemtoReg == true))
    {
        Reg[Shadow_MEMWB.Rt] = Shadow_MEMWB.RtValue;
    }
    if((Shadow_MEMWB.RegWrite == true) && (format == rtype))
    {
        Reg[Shadow_MEMWB.Rd] = Shadow_EXMEM.ALUResult;
    }
}
