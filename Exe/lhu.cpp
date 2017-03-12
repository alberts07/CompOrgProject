void lhu()
{
    unsigned int byte = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2
        switch (byte % 2){
            case 0:
                {
                    Shadow_IDEX.ALUResult = 0xFFFF0000 & byte    
                }
            case 1:
                {
                    Shadow_IDEX.ALUResult = 0x0000FFFF & byte    
                }
        }
}
