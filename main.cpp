#include "Instr_IF.h"
#include "Instr_ID.h"
#include "Instr_WB.h"
#include "Instr_MEM.h"
#include "Instr_Exe.h"
#include "Update_State.h"
#include <iostream>
#include <string>

int nop_instr = 0x00000000;
unsigned int holder[] = {
  0x00004020,  //0x00004020 = add $t0, $zero, $zero
  0x21290FFF,  //0x20090FFF = addi $t1, $t1, 0x0FFF
  0x00095080,  //0x00095080 = sll $t2, $t1, 2
  0x01495822,  //0x01495822 = sub $t3, $t2, $t1
  0x3529F000,  //0x3529001f = ori $t1, $t1, 0xF000
  0x21080002,  //0x21080002 = addi $t0, $t0, 2
  0x010B682A,  //0x010b682A = slt $t5, $t0, $t3
  0x31290010,  //0x31290010 = andi $t1, $t1, 0x10
  0x00094902,  //0x00094902 = srl $t1, $t1, 4
  0x00004020,  //0x00004020 = add $t0, $zero, $zero
  0x01284826,  //0x01284826 = xor $t1, $t1, $t0
  0x39290004,  //0x35290004 = xori $t1, $t1, 0x4
  0x29290006,  //0x29290006 = slti  $t1, $t1, 0x6
  0x2d29FFF0,  //0x2d29FFFF = sltiu $t1, $t1, 0xFFF0
  0x3508F00F,  //0x3508F00F = ori $t0, $t0, 0xF00F
  0x3529F00F,  //0x3529F00F = ori $t1, $t1, 0xF00F
  0x01284823,  //0x01284823 = subu $t1, $t1, $t0
  0x00004020,  //0x00004020 = add $t0, $zero, $zero
  0x2108FFFF,  //0x20090FFF = addi $t0, $t0, 0xFFFF
  0x01094827,  //0x01094825 = nor $t1, $t0, $t1
  0x2108FFFF,  //0x20090FFF = addi $t0, $t0, 0xFFFF
  0x01094825,  //0x01094825 = or $t1, $t0, $t1
  0x00005820,  //0x00005820 = add $t3, $zero, $zero
  0x216B0004,  //0x216B0001 = addi, $t3, $t3, 0x4
  0xAD690000,  //0xAD690000 = sw $t1, 0($t3)
  0x8D680000,  //0x8D680000 = lw $t0, 0($t3)
  0x00004020,  //0x00004020 = add $t0, $zero, $zero
  0x00005820,  //0x216B0003 = add $t3, $zero, $zero
  0xA1680000,  //0xA1680002 = sb $t0, 0($t3)
  0x81690000  //0x81690002 = lb $t1, 0($t3)
};


std::string names[(sizeof(holder)/sizeof(*holder))] = {
 "add $t0, $zero, $zero",
 "addi $t1, $t1, 0x0FFF",
 "sll $t2, $t1, 2",
 "sub $t3, $t2, $t1",
 "ori $t1, $t1, 0xF000",
 "addi $t0, $t0, 2",
 "slt $t5, $t0, $t3",
 "andi $t1, $t1, 0x10",
 "srl $t1, $t1, 4",
 "add $t0, $zero, $zero",
 "xor $t1, $t1, $t0",
 "xori $t1, $t1, 0x4",
 "slti  $t1, $t1, 0x6",
 "sltiu $t1, $t1, 0xFFF0",
 "ori $t0, $t0, 0xF00F",
 "ori $t1, $t1, 0xF00F",
 "subu $t1, $t1, $t0",
 "add $t0, $zero, $zero",
 "addi $t0, $t0, 0xFFFF",
 "nor $t1, $t0, $t1",
 "addi $t0, $t0, 0xFFFF",
 "or $t1, $t0, $t1",
 "add $t3, $zero, $zero",
 "addi, $t3, $t3, 0x4",
 "sw $t1, 0($t3)",
 "lw $t0, 0($t3)",
 "add $t0, $zero, $zero",
 "add $t3, $zero, zero",
 "sb $t0, 0($t3)",
 "lb $t1, 0($t3)"
};

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
        if(i != 24 && i > 19 && i != 28)
            std::cout << names[$pc] << ":  " << Reg[MEMWB.DstReg] << std::endl;
        else if (i == 24 || i == 28)
            std::cout << names[$pc] << std::endl;
        else{}
        $pc = $pc + IFID.pcplus1;
    }
}
