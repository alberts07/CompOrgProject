#include "Instr_IF.h"
#include "Instr_ID.h"
#include "Instr_WB.h"
#include "Instr_MEM.h"
#include "Instr_Exe.h"
#include "Update_State.h"
#include <iostream>

unsigned int holder[] = {0x00004020, 0x21290FFF, 0x00095080, 0x01495822, 0x3529F000, 0x21080002, 0x010B682A, 0x31290010, 0x000948C2};
//0x00004020 = add $t0, 0, 0
//0x2009000F = addi $t1, $t1, 0x0FFF
//0x00095080 = sll t2, t1, 2
//0x01495822 = sub t3, t2, t1
//0x3529001f = ori t1, t1, 0xF000
//0x21080002 = addi t0, t0, 2
//0x010b682A = slt t5, t0, t3
//0x31290010 = andi t1, t1, 0x10
//0x000948C2 = srl t1, t1, 3


//Every time one is added to holder, change the for loop size


unsigned int memory[1000];
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

    $pc = 0;
    unsigned int clock_cycles = 0;
    int format = 10;
    int i = 0;
    for(i = 0; i < (sizeof(holder)/sizeof(*holder)); i++)
    {
        memory[$pc] = holder[i];
        $pc++;
    }
    $pc = 0;
    for(i  = 0; i < (sizeof(holder)/sizeof(*holder)); i++)
    {
        Instr_IF(memory[$pc]);
        format = Instr_ID();
        Instr_Exe(format);
        Instr_MEM();
        Instr_WB(format);
        Update_State();
        clock_cycles++;
        std::cout << "ALU Result # ";
        std::cout << $pc;
        std::cout << ":  ";
        std::cout << Reg[EXMEM.DstReg];
        std::cout << "   ";
        std::cout << std::endl;
        $pc = $pc + IFID.pcplus1;
    }
}
