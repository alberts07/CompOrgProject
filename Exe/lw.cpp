void lw()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
}
