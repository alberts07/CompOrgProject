void bltzal()
{
    if (Shadow_IDEX.RsValue < 0)
    {
        Reg[31]= $pc + 2;
        Shadow_EXMEM.ALUResult = Shadow_IDEX.RsValue + Shadow_IDEX.immed16;
    }
}
