void sltu()
{
    if((unsigned int)Shadow_IDEX.RsValue < (unsigned int)Shadow_IDEX.RtValue)
        Shadow_EXMEM.ALUResult = 1;
    else 
        Shadow_EXMEM.ALUResult = 0;
}
