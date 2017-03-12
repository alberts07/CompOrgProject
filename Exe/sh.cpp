void sh()
{
    int halfword = (Shadow_IDEX.RsValue + Shadow_IDEX.immed16) >> 2;
    switch(halfword % 2)
    {
        case 0: 
        {
            Shadow_EXMEM.ALUResult = halfword & 0xFFFF0000;
            break;
        }
        case 1: 
        {
            Shadow_EXMEM.ALUResult = halfword & 0x0000FFFF;            
            break;
        }
    }
}
