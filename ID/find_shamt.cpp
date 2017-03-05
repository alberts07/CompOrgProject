int find_shamt(unsigned int instr)
{
    int shamt = instr && shamt_mask;
    return shamt >> 6;
}
