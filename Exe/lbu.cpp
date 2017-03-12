void lbu()
{
     Shadow_EXMEM.ALUResult = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2
     Shadow_EXMEM.byte = Shadow_EXMEM.ALUResult % 4
}
