#include "Instr_IF.h"
#include "Instr_ID.h"
#include "Instr_WB.h"
#include "Instr_MEM.h"
#include "Instr_Exe.h"
#include "Update_State.h"
#include <iostream>

unsigned int holder[3] = {0x00004020, 0x2009000F, 0x00095080};
//0x00004020 = add $t0, 0, 0
//0x2009000F = addi t1, zero, 15
//0x00095080 = sll t2, t1, 2

unsigned int memory[4];
unsigned int $pc = 0x00000000;
unsigned int $fp = 0x00000000;
unsigned int $gp = 0x00000000;
int Reg[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

struct ifid Shadow_IFID;
struct ifid IFID;
struct idex Shadow_IDEX;
struct idex IDEX;
struct exmem Shadow_EXMEM;
struct exmem EXMEM;
struct memwb Shadow_MEMWB;
struct memwb MEMWB;




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
    Instr_IF(memory[1]);
/*
    if($pc != 0)
    {
        Instr_WB(format);
    }*/
    format = Instr_ID();
    std::cout << "Type: ";
    std::cout << format;
    std::cout << "    ";
    Instr_Exe(format);
    Instr_MEM();
    Update_State();
    clock_cycles++;
    std::cout << "ALU Result: ";
    std::cout << Shadow_EXMEM.ALUResult;
    std::cout << "   ";
    /*std::cout << clock_cycles;
    std::cout << clock_cycles/4;*/
}
