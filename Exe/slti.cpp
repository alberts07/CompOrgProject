void slti()
{
    if(Shadow_IDEX.RsValue < Shadow_IDEX.immed16)
        Shadow_IDEX.ALUResult = 1;
    else 
        Shadow_IDEX.ALUResult = 0;
}
