
#include <vector>
#include "Instr_IF.h"
#include "decode.h"

extern struct idex Shadow_IDEX;

std::vector<int> find_format(unsigned int instr)
{
    Shadow_IDEX.opcode = find_opcode(instr);
    if(Shadow_IDEX.opcode == 0)
    {
        Shadow_IDEX.func = find_func(instr);
        return std::vector<int> format ({rtype, Shadow_IDEX.opcode, Shadow_IDEX.func});
    }
    if(((Shadow_IDEX.opcode >= 0x5) && (Shadow_IDEX.opcode <= 0xF)) || (Shadow_IDEX.opcode == 4) || ((Shadow_IDEX.opcode >= 0x20) && (Shadow_IDEX.opcode <= 0x26)) || ((Shadow_IDEX.opcode >= 0x28) && (Shadow_IDEX.opcode <= 0x2B)) || (Shadow_IDEX.opcode == 0x2E) || (Shadow_IDEX.opcode == 0x30) || (Shadow_IDEX.opcode == 0x31) || (Shadow_IDEX.opcode == 0x38) || (Shadow_IDEX.opcode == 0x3D))
    {
        return std::vector<int> format ({itype, Shadow_IDEX.opcode, 0)};
    }
    if((opcode == 2) || (opcode == 3))
    {
        return std::vector<int> format({jtype, Shadow_IDEX.opcode, 0});
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
    return opcode >> 26;
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
