extern unsigned int $pc;
extern int memory[10000];
#include "Instr_IF.h"

extern struct ifid Shadow_IFID;

void Instr_IF(unsigned int instruction)
{
    Shadow_IFID.instr = instruction;
    Shadow_IFID.pcplus1 = $pc + 1;
}
