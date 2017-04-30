#include "Instr_IF.hpp"
#include <iostream>
#include "cache.hpp"

extern unsigned int pc;
extern struct ifid Shadow_IFID;
using namespace std;
extern cache icache;
extern unsigned int pc;


//This is where the instruciton is fecthed for the Shadow register
void Instr_IF(unsigned int instruction)
{
    Shadow_IFID.instr = instruction;
    Shadow_IFID.pcplus1 = pc + 1;
}
