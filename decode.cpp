
#include <vector>
#include "Instr_IF.h"
#include "decode.h"
#include <iostream>

extern struct idex Shadow_IDEX;

int find_format(unsigned int instr)
{
    Shadow_IDEX.opcode = find_opcode(instr);
    if(Shadow_IDEX.opcode == 0)
    {
        Shadow_IDEX.func = find_func(instr);
        return rtype;
    }
    if((Shadow_IDEX.opcode == 0x2) || (Shadow_IDEX.opcode == 0x3))
    {
      return jtype;
    }

     if((Shadow_IDEX.opcode == sw_opcode) || (Shadow_IDEX.opcode == andi_opcode)\
      || (Shadow_IDEX.opcode == lw_opcode) || (Shadow_IDEX.opcode == addi_opcode)\
      || (Shadow_IDEX.opcode == slti_opcode) || (Shadow_IDEX.opcode == sltiu_opcode)\
      || (Shadow_IDEX.opcode == addiu_opcode) || (Shadow_IDEX.opcode == lui_opcode)\
      || (Shadow_IDEX.opcode == ori_opcode) || (Shadow_IDEX.opcode == xori_opcode)\
      || (Shadow_IDEX.opcode == lb_opcode) || (Shadow_IDEX.opcode == lbu_opcode)\
      ||(Shadow_IDEX.opcode == lh_opcode) || (Shadow_IDEX.opcode == sb_opcode)\
      ||(Shadow_IDEX.opcode == sh_opcode) || (Shadow_IDEX.opcode == beq_opcode)\
      ||(Shadow_IDEX.opcode == bne_opcode) || (Shadow_IDEX.opcode == j_opcode)\
      ||(Shadow_IDEX.opcode == jal_opcode) || (Shadow_IDEX.opcode == lhu_opcode)\
      ||(Shadow_IDEX.opcode == lwcl_opcode) || (Shadow_IDEX.opcode == lwl_opcode)\
      ||(Shadow_IDEX.opcode == lwr_opcode) || (Shadow_IDEX.opcode == ll_opcode)\
      ||(Shadow_IDEX.opcode == swcl_opcode) || (Shadow_IDEX.opcode == sdcl_opcode)\
      ||(Shadow_IDEX.opcode == swl_opcode) || (Shadow_IDEX.opcode == swr_opcode)\
      ||(Shadow_IDEX.opcode == sc_opcode) || (Shadow_IDEX.opcode == bgtz_opcode)\
      ||(Shadow_IDEX.opcode == blez_opcode))
      {
        return itype;
      }
                                        /*
    if(opcode == special_opcode1)
    {
        Shadow_IDEX.func = find_func(instr);
        return std::vector<int> format({special_opcode1l, Shadow_IDEX.opcode, Shadow_IDEX.func)};
    }
    if(opcode == special_opcode2)
    {
        return std::vector<int> format({special_opcode2l, Shadow_IDEX.opcode, (Shadow_IFID.instr && br_coprocessor_mask)>> 16});
    }
    if(opcode == special_opcode3)
    {
        return std::vector<int> format({special_opcode3l, Shadow_IDEX.opcode, (Shadow_IFID.instr && spec_opcode3_mask) >> 16});
    }
*/
return -1;
}


int find_func(unsigned int instr)
{
    return instr & function_mask;
}


short find_immed16(unsigned int instr)
{
    return instr & immed16_mask;
}


int find_immed26(unsigned int instr)
{
    return instr & immed26_mask;
}

int find_opcode(unsigned int instr)
{
    int opcode = instr & opcode_mask;
    return (unsigned int)opcode >> 26;
}


int find_rd(unsigned int instr)
{
    int rd = instr & rd_mask;
    rd = rd >> 11;
    return rd;
}

int find_rs(unsigned int instr)
{
    int rs = instr & rs_mask;
    rs = rs >> 21;
    return rs;
}

int find_rt(unsigned int instr)
{
    int rt = instr & rt_mask;
    rt = rt >> 16;
    return rt;
}

int find_shamt(unsigned int instr)
{
    int shamt = instr & shamt_mask;
    return shamt >> 6;
}
