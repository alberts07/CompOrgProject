void sltu()
{
    if((unsigned int)Shadow_IDEX.RsValue < (unsigned int)Shadow_IDEX.RtValue)
        Shadow_IDEX.ALUResult = 1;
    else 
        Shadow_IDEX.ALUResult = 0;
}
