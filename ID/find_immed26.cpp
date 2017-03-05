int find_immed26(unsigned int instr)
{
    return instr && immed26_mask;
}
    
