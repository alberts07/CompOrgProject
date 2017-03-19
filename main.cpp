#include "Instr_IF.h"
#include "Instr_ID.h"
#include "Instr_WB.h"
#include "Instr_MEM.h"
#include "Instr_Exe.h"
#include "Update_State.h"
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

struct ifid {
    short immed16;
    unsigned int pcplus1;
    unsigned int instr;
}Shadow_IFID, IFID;

struct idex {
    bool RegWrite;
    bool MemRead;
    bool MemWrite;
    bool MemtoReg;
    bool ALUSrc;
    int Rs;
    int RsValue;
    int Rd;
    int RdValue;
    int Rt;
    int RtValue;
    int immed16;
    int immed26;
    int opcode;
    int func;
    int shamt;
    unsigned int pcplus1;
    unsigned int instr;
}, Shadow_IDEX, IDEX;

struct exmem {
    bool RegWrite;
    bool MemRead;
    bool MemWrite;
    bool MemtoReg;
    int Rt;
    int Rs;
    int Rd;
    int RsValue;
    int ALUResult;
    unsigned int pcplus1;
    int mem;
    bool half;
}Shadow_EXMEM, EXMEM;

struct memwb {
    bool RegWrite;
    bool MemtoReg;
    int ALUResult;
    int Rd;
    int Rs;
    int RsValue;
    int RtValue;
    int Rt;
    unsigned int pcplus1;
}Shadow_MEMWB, MEMWB;




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
    std::cout << clock_cycles;
    std::cout << clock_cycles/4;
}
