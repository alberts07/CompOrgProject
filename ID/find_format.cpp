#include <vector>
#include <iostream>
std::vector<int> find_format(unsigned int instr)
{
    int opcode = find_opcode(instr);
    if(opcode == 0)
    {
        int func = find_func(instr)
        return vector<int> format ({rtype, opcode, func}); 
    }
    if(opcode > 0x3)
    {
        return vector<int> format ({itype, opcode, 0)};
    }
    if((opcode == 2) || (opcode == 3)) 
    {
        return vector<int> format({jtype, opcode, 0});
    }
    if(opcode == special_opcode2)
    {
        return vector<int> format({br_coprocessor, opcode, 0)};
    }
    if(opcode == special_opcode1)
    {
        return vector<int> format({trap_i_type, opcode, 0});
    }
                                   
}
