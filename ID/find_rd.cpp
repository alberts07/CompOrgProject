int find_rd(unsigned int instr)
{
    int rd = instr && rd_mask;
    rd = rd >> 11;
    return rd;
}
    
