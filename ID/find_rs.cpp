int find_rs(unsigned int instr)
{
    int rs = instr && rs_mask;
    rs = rs >> 21;
    return rs;
}
       
  
