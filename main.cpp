#include "Instr_IF.h"
#include "Instr_ID.h"
#include "Instr_WB.h"
#include "Instr_MEM.h"
#include "Instr_Exe.h"
#include "Update_State.h"
#include <iostream>
#include <string>
using namespace std;

int nop_instr = 0x00000000;
// This holder array contains the machine code functions that we test.
//To add a function, put it at the bottom of this, with the function
//next to it
unsigned int holder[] = {
  0x00004020,  //add $t0, $zero, $zero
  0x21290FFF,  //addi $t1, $t1, 0x0FFF
  0x00095080,  //sll $t2, $t1, 2
  0x01495822,  //sub $t3, $t2, $t1
  0x3529F000,  //ori $t1, $t1, 0xF000
  0x21080002,  //addi $t0, $t0, 2
  0x010B682A,  //slt $t5, $t0, $t3
  0x31290010,  //andi $t1, $t1, 0x10
  0x00094902,  //srl $t1, $t1, 4
  0x00004020,  //add $t0, $zero, $zero
  0x01284826,  //xor $t1, $t1, $t0
  0x39290004,  //xori $t1, $t1, 0x4
  0x29290006,  //slti  $t1, $t1, 0x6
  0x2d29FFF0,  //sltiu $t1, $t1, 0xFFF0
  0x3508F00F,  //ori $t0, $t0, 0xF00F
  0x3529F00F,  //ori $t1, $t1, 0xF00F
  0x01284823,  //subu $t1, $t1, $t0
  0x00004020,  //add $t0, $zero, $zero
  0x2108FFFF,  //addi $t0, $t0, 0xFFFF
  0x01094827,  //nor $t1, $t0, $t1
  0x2108FFFF,  //addi $t0, $t0, 0xFFFF
  0x00005820,  //add $t3, $zero, $zero
  0x216B0004,  //addi, $t3, $t3, 0x4
  0xAD6B0000,  //sw $t3, 0($t3)
  0x8D680000,  //lw $t0, 0($t3)
  0x00004020,  //add $t0, $zero, $zero
  0x016B5820,  //add $t3, $t3, $t3
  0xA16B0022,  //sb $t3, 22($t3)
  0x81690022,  //lb $t1, 22($t3)
  0x218C000C,  //addi $t4, $t4, 0xC
  0x85890002  //lh $t1, 2($t4)
};

//This array contains the functions so that the user can visially
//debug each function. Once you add machine code to the top,
//add the function to the bottom of this array.
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
 "add $t3, $zero, $zero",
 "addi, $t3, $t3, 0x4",
 "sw $t3, 0($t3)",
 "lw $t0, 0($t3)",
 "add $t0, $zero, $zero",
 "add $t3, $t3, $t3",
 "sb $t3, 0x22($t3)",
 "lb $t1, 0x22($t3)",
 "addi $t4, $t4, 0xC",
 "lh $t1, 2($t4)"
};



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
    //Transfer holder array to memory
    for(i = 0; i < (sizeof(holder)/sizeof(*holder)); i++)
    {
        memory[$pc] = holder[i];
        $pc++;
    }
    $pc = 0;
    //Run pipeline
    for(i  = 0; i < (sizeof(holder)/sizeof(*holder)); i++)
    {
        Instr_IF(memory[$pc]);
        format = Instr_ID();
        Instr_Exe(format);
        Instr_MEM();
        Instr_WB(format);
        Update_State();
        clock_cycles++;
        if(i != 23  && i != 27) //Print out all except stores
            cout << names[$pc] << ":  " << Reg[MEMWB.DstReg] << endl;
        else if (i == 23 || i == 27)
            cout << names[$pc] << endl;
        else{}
        $pc = $pc + IFID.pcplus1;
    }

}
