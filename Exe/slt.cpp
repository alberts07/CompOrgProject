void slt()
{
    if(Shadow_IDEX.RsValue < Shadow_IDEX.RtValue)
        Shadow_EXMEM.ALUResult = 1;
    else 
        Shadow_EXMEM.ALUResult = 0;
}
