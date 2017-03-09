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
    if(((opcode >= 0x5) && (opcode <= 0xF)) || (opcode == 4) || ((opcode >= 0x20) && (opcode <= 0x26)) || ((opcode >= 0x28) && (opcode <= 0x2B)) || (opcode == 0x2E) || (opcode == 0x30) || opcode == 0x31) || (opcode == 0x38) || (opcode == 0x3D))
    {
        return vector<int> format ({itype, opcode, 0)};
    }
    if((opcode == 2) || (opcode == 3)) 
    {
        return vector<int> format({jtype, opcode, 0});
    }
    if(opcode == special_opcode1)                                  
    {
        int func = find_func(instr);
        return vector<int> format({special_opcode1l, opcode, func)};
    }
    if(opcode == special_opcode2)
    {
        return vector<int> format({special_opcode2l, opcode, (instr && br_coprocessor_mask)>> 16});
    }
    if(opcode == special_opcode3)
    {
        return vector<int> format({special_opcode3l, opcode, (instr && spec_opcode3_mask) >> 16});

                                   
}
