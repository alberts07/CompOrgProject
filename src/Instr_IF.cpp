#include "Instr_IF.hpp"
#include <iostream>

extern unsigned int pc;
extern struct ifid Shadow_IFID;
using namespace std;

void Instr_IF(unsigned int instruction)
{
    Shadow_IFID.instr = instruction;
    Shadow_IFID.pcplus1 = pc + 1;
}
