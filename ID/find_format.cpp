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
    else 
    {
        return vector<int> format({jtype, opcode, 0});
    }
}
