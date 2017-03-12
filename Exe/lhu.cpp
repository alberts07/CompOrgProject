void lhu()
{
    unsigned int halfword = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2
        switch (halfword % 2){
            case 0:
                {
                    Shadow_EXMEM.ALUResult = 0xFFFF0000 & halfword;
                    break;
                }
            case 1:
                {
                    Shadow_EXMEM.ALUResult = 0x0000FFFF & halfword;
                    break;
                }
        }
}
