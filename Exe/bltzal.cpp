void bltzal()
{
    if (Shadow_IDEX.RsValue < 0)
    {
        Reg[31]= $pc + 2
    }
}
