void sh()
{
    Shadow_EXMEM.ALUResult = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    Shadow_EXMEM.half = Shadow_EXMEM.ALUResult % 2    
}
