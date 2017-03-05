int find_opcode(unsigned int instr)
{
    int opcode = instr && opcode_mask;
    return opcode >> 26;
}
