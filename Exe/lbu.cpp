void lbu()
{
    unsigned int byte = ((unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.immed16) >> 2
        switch (byte % 4){
            case 0:
                {
                    Shadow_IDEX.ALUResult = 0xFF000000 & byte;
                    break;
                }
            case 1:
                {
                    Shadow_IDEX.ALUResult = 0x00FF0000 & byte;
                    break;
                }
            case 2:
                {
                    Shadow_IDEX.ALUResult = 0x0000FF00 & byte;
                    break;
                }
            case 3:
                {
                    Shadow_IDEX.ALUResult = 0x000000FF & byte;
                    break;
                }
        }
}
