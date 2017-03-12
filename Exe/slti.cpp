void slti()
{
    if(Shadow_IDEX.RsValue < Shadow_IDEX.immed16)
        Shadow_EXMEM.ALUResult = 1;
    else 
        Shadow_EXMEM.ALUResult = 0;
}
