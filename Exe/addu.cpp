void addu()
{
    (unsigned int)Shadow_EXMEM.ALUResult = (unsigned int)Shadow_IDEX.RsValue + (unsigned int)Shadow_IDEX.RtValue;
}
