#include "Instr_IF_hpp"
#include "Instr_ID_hpp"

extern struct memwb Shadow_MEMWB;
extern struct idex Shadow_IDEX;

void Instr_WB(int format)
{
    if((Shadow_MEMWB.RegWrite == true) && (format == itype))
    {
        Reg[Shadow_IDEX.Rt] = Shadow_EXMEM.ALUResult;
    }
    if((Shadow_MEMWB.RegWrite == true) && (format == rtype))
    {
        Reg[Shadow_IDEX.Rd] = Shadow_EXMEM.ALUResult;
    }
}
