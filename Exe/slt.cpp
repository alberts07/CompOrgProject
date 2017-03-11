void slt()
{
    if(Shadow_IDEX.RsValue < Shadow_IDEX.RtValue)
        Shadow_IDEX.ALUResult = 1;
    else 
        Shadow_IDEX.ALUResult = 0;
}
