//
//  Instr_WB.cpp
//
//
//  Created by Austin Alberts on 3/11/17.
//
//

void Instr_WB(int format)
{
    if((Shadow_MEMWB.RegWrite == true) && (format == itype))
    {
        Reg[Shadow_IDEX.Rt] = Shadow_IDEX.ALUResult;
    }
    if((Shadow_MEMWB.RegWrite == true) && (format == rtype))
    {
        Reg[Shadow_IDEX.Rd] = Shadow_IDEX.ALUResult;
    }
}
