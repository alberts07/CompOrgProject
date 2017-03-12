void beq()
{
    if(Shadow_IDEX.RsValue == Shadow_IDEX.RtValue)
        Shadow_EXMEM.ALUResult = Shadow_IDEX.pcplus1 + Shadow_IDEX.immed16;
}
