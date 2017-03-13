#include <iostream>
#include <vector>
#include <Instr_IF_hpp>
#include <Instr_ID_hpp>
#include <Instr_WB_hpp>
#include <Instr_MEM_hpp>
#include <Instr_Exe_hpp>
#include <Update_State_hpp>

int holder[4] = {0x00004020, 0x2009000F, 0x0800000C, 0x00095080};
//0x00004020 = add $t0, 0, 0
//0x2009000F = addi t1, zero, 15
//0x08000004 = j 0x00C
//0x00095080 = sll t2, t1, 2

int memory[0x50000000];
unsigned int $pc = 0x00000000;
unsigned int $fp = 0x00000000;
unsigned int $gp = 0x00000000;
int Reg[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};



int main()
{
    for(int i = 0; i < 4; i++)
    {
        memory[$pc] = holder[i];
        $pc++;
    }
    $pc = 0;
    for($pc = 0; $pc < 4; $pc++)
    {
        Instr_IF(memory[$pc]);
        Instr_WB();
        Instr_ID();
        Instr_Exe();
        Instr_Mem();
        Update_State();
    }
}
