void div()
{
    Shadow_IDEX.ALUResult = ((Shadow_IDEX.RsValue % Shadow_IDEX.RtValue) << 16) | (Shadow_IDEX.RsValue / Shadow_IDEX.RtValue);
}