void sltiu(){
    if((unsigned int)Shadow_IDEX.RsValue < (unsigned int)Shadow_IDEX.immed16)
        Shadow_EXMEM.ALUResult = 1;
    else 
        Shadow_EXMEM.ALUResult = 0;
}
