void sw()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.mem = 4;
    Shadow_EXMEM.half = false;
}
