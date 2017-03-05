int find_rt(unsigned int instr)
{
    int rt = instr & rt_mask;
    rt = rt >> 16;
    return rt;
}
