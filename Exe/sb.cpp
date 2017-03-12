void sb()
{
    Shadow_EXMEM.ALUResult = ((Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2);
    Shadow_EXMEM.byte = Shadow_EXMEM.ALUResult % 4
}
    
