void divu()
{
  Shadow_IDEX.ALUResult = (((unsigned int)Shadow_IDEX.RsValue % (unsigned int)Shadow_IDEX.RtValue) << 16) | ((unsigned int)Shadow_IDEX.RsValue / (unsigned int)Shadow_IDEX.RtValue);
}
