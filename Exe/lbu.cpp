void lbu()
{
     Shadow_EXMEM.ALUResult = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2;
     Shadow_EXMEM.mem = Shadow_EXMEM.ALUResult % 4;
     Shadow_EXMEM.half = false;
}
