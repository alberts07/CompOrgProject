void jal()
{
    Reg[31] = $pc+2;
    $pc = ((jump_mask & $pc) >> 2) | Shadow_IDEX.immed26
}
