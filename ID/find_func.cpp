int find_func(unsigned int instr)
{
    return instr & func_mask;
}
