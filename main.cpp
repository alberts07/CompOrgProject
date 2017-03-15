#include "Instr_IF.hpp"
#include "Instr_ID.hpp"
#include "Instr_WB.hpp"
#include "Instr_MEM.hpp"
#include "Instr_Exe.hpp"
#include "Update_State.hpp"
#include <iostream>

int holder[4] = {0x00004020, 0x2009000F, 0x08000004, 0x00095080};
//0x00004020 = add $t0, 0, 0
//0x2009000F = addi t1, zero, 15
//0x08000004 = j 0x004
//0x00095080 = sll t2, t1, 2

int memory[0x50000000];
unsigned int $pc = 0x00000000;
unsigned int $fp = 0x00000000;
unsigned int $gp = 0x00000000;
int Reg[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};



int main()
{
    unsigned int clock_cycles = 0;
    int format = 0;
    for(int i = 0; i < 4; i++)
    {
        memory[$pc] = holder[i];
        $pc++;
    }
    $pc = 0;
    for($pc = 0; $pc < 4; $pc++)
    {
        Instr_IF(memory[$pc]);
        if($pc != 0)
        {
            Instr_WB(format);
        }
        format = Instr_ID();
        Instr_Exe(format);
        Instr_MEM();
        Update_State();
        clock_cycles++;
    }
    std::cout >> clock_cycles;
}
