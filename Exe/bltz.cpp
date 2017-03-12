void bltz()
{
    if(Shadow_IDEX.RsValue < 0)
    {
        Shadow_IDEX.ALUResult = Shadow_IDEX.pcplus1 + Shadow_IDEX.immed16;
    }
}
