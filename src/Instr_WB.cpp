#include "Instr_IF.hpp"
#include "Instr_ID.hpp"

extern struct memwb Shadow_MEMWB;
extern struct exmem Shadow_EXMEM;
extern struct idex Shadow_IDEX;
extern int Reg[32];



//This is where the values get written back to the regsiters
void Instr_WB(int format)
{

    if((Shadow_MEMWB.RegWrite == true) && (format == itype) && (Shadow_MEMWB.MemtoReg == false))
    {
        Reg[Shadow_MEMWB.DstReg] = Shadow_MEMWB.ALUResult;
    }
    if((Shadow_MEMWB.RegWrite == true) && (format == itype) && (Shadow_MEMWB.MemtoReg == true))
    {
        Reg[Shadow_MEMWB.DstReg] = Shadow_MEMWB.DstRegValue;
    }
    if((Shadow_MEMWB.RegWrite == true) && (format == rtype))
    {
        Reg[Shadow_MEMWB.DstReg] = Shadow_MEMWB.ALUResult;
    }
    if((Shadow_MEMWB.RegWrite == true) && (format == special_opcode))
    {
        Reg[Shadow_MEMWB.DstReg] = Shadow_MEMWB.ALUResult;
    }
    if(format == branchtype)
    {
        //DO NOTHING
    }
}
