void lhu()
{
    Shadow_EXMEM.ALUResult = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2;
    Shadow_EXEMEM.mem = Shadow_EXMEM.ALUResult % 2;
    Shadow_EXEMEM.half = true;
}
