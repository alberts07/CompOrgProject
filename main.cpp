#include "Instr_IF.hpp"
#include "Instr_ID.hpp"
#include "Instr_WB.hpp"
#include "Instr_MEM.hpp"
#include "Instr_Exe.hpp"
#include "Update_State.hpp"
#include <iostream>
#include <string>
using namespace std;

int nop_instr = 0x00000000;
// This holder array contains the machine code functions that we test.
//To add a function, put it at the bottom of this, with the function
//next to it
/*
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
  0x2D29FFF0,  //sltiu $t1, $t1, 0xFFF0
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
  0x85890002,  //lh $t1, 2($t4)
  0x0128780A,  //movz $t7, $t1, $t0
  0x0109780B,  //movn $t7, $t0, $t1
//  0x08000004,  //j 0x04
//  0x01800008  //jr $t4
  0x1000000F,
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000000,
  0x240D8000, //addu $t5, $zero,      43
  0x05A00001, //if less than zero, fail, go to 46 in an endless loop
  0x08000032, //else jump to end
  0x1D20FFFC, //go back 3 instructions
  0x19E0FFFE, //testing branches
  0x152FFFFE, //48
  0x00000000,
  0x00000000  //50
};*/

unsigned int holder[] = {
  0x00000fa0, // $sp = 4000
  0x00000fa0, // $fp = 4000
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000078, // $pc = 120
  0x00000000, // reserved for answer
  0x00000000,     // reserved for answer
  0x00000000,     // reserved for answer
  0x00000000,     // reserved for answer
  0x27bdfff0,    // addiu sp,sp,-16 <load_arrays>
  0xafbe000c,    // sw    s8,12(sp)
  0x03a0f025,    // move  s8,sp
  0xafc40010,    // sw    a0,16(s8)
  0xafc50014,    // sw    a1,20(s8)
  0xafc00004,    // sw    zero,4(s8)
  0x1000001c,    // b 4008bc <load_arrays+0x8c>
  0x00000000,    // nop
  0x8fc20004,    // lw    v0,4(s8)
  0x00021080,    // sll   v0,v0,0x2
  0x8fc30010,    // lw    v1,16(s8)
  0x00621021,    // addu  v0,v1,v0
  0x8fc30004,    // lw    v1,4(s8)
  0x00031880,    // sll   v1,v1,0x2
  0x8fc40010,    // lw    a0,16(s8)
  0x00831821,    // addu  v1,a0,v1
  0x8c640000,    // lw    a0,0(v1)
  0x8fc30004,    // lw    v1,4(s8)
  0x00831821,    // addu  v1,a0,v1
  0xac430000,    // sw    v1,0(v0)
  0x8fc20004,    // lw    v0,4(s8)
  0x00021080,    // sll   v0,v0,0x2
  0x8fc30014,    // lw    v1,20(s8)
  0x00621021,    // addu  v0,v1,v0
  0x8fc30004,    // lw    v1,4(s8)
  0x00031880,    // sll   v1,v1,0x2
  0x8fc40014,    // lw    a0,20(s8)
  0x00831821,    // addu  v1,a0,v1
  0x8c640000,    // lw    a0,0(v1)
  0x8fc30004,    // lw    v1,4(s8)
  0x00831821,    // addu  v1,a0,v1
  0xac430000,    // sw    v1,0(v0)
  0x8fc20004,    // lw    v0,4(s8)
  0x24420001,    // addiu v0,v0,1
  0xafc20004,    // sw    v0,4(s8)
  0x8fc20004,    // lw    v0,4(s8)
  0x28420064,    // slti  v0,v0,100
  0x1440ffe2,    // bnez  v0,400850 <load_arrays+0x20>
  0x00000000,    // nop
  0x00000000,    // nop
  0x03c0e825,    // move  sp,s8
  0x8fbe000c,    // lw    s8,12(sp)
  0x27bd0010,    // addiu sp,sp,16
  0x03e00008,    // jr    ra
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x27bdffe8,    //   addiu   sp,sp,-24 <check_result>
  0xafbe0014,    // sw    s8,20(sp)
  0x03a0f025,    // move  s8,sp
  0xafc40018,    // sw    a0,24(s8)
  0xafc5001c,    // sw    a1,28(s8)
  0xafc00000,    // sw    zero,0(s8)
  0xafc00008,    // sw    zero,8(s8)
  0x1000001d,    // b 400978 <check_result+0x94>
  0x00000000,    // nop
  0x8fc20008,    // lw    v0,8(s8)
  0x00021080,    // sll   v0,v0,0x2
  0x8fc30018,    // lw    v1,24(s8)
  0x00621021,    // addu  v0,v1,v0
  0x8c430000,    // lw    v1,0(v0)
  0x8fc20008,    // lw    v0,8(s8)
  0x00021080,    // sll   v0,v0,0x2
  0x8fc4001c,    // lw    a0,28(s8)
  0x00821021,    // addu  v0,a0,v0
  0x8c420000,    // lw    v0,0(v0)
  0x00621026,    // xor   v0,v1,v0
  0xafc2000c,    // sw    v0,12(s8)
  0x8fc2000c,    // lw    v0,12(s8)
  0x10400003,    // beqz  v0,40094c <check_result+0x68>
  0x00000000,    // nop
  0x24020001,    // li    v0,1
  0xafc20000,    // sw    v0,0(s8)
  0x8fc20008,    // lw    v0,8(s8)
  0x00021080,    // sll   v0,v0,0x2
  0x8fc30018,    // lw    v1,24(s8)
  0x00621021,    // addu  v0,v1,v0
  0x8c420000,    // lw    v0,0(v0)
  0x8fc30004,    // lw    v1,4(s8)
  0x00621021,    // addu  v0,v1,v0
  0xafc20004,    // sw    v0,4(s8)
  0x8fc20008,    // lw    v0,8(s8)
  0x24420001,    // addiu v0,v0,1
  0xafc20008,    // sw    v0,8(s8)
  0x8fc20008,    // lw    v0,8(s8)
  0x28420064,    // slti  v0,v0,100
  0x1440ffe1,    // bnez  v0,400908 <check_result+0x24>
  0x00000000,    // nop
  0x8fc20000,    // lw    v0,0(s8)
  0x14400003,    // bnez  v0,40099c <check_result+0xb8>
  0x00000000,    // nop
  0x8fc20004,    // lw    v0,4(s8)
  0xafc20000,    // sw    v0,0(s8)
  0x00000000,    // nop
  0x03c0e825,    // move  sp,s8
  0x8fbe0014,    // lw    s8,20(sp)
  0x27bd0018,    // addiu sp,sp,24
  0x03e00008,    // jr    ra
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x27bdfcb8,    // addiu sp,sp,-840 <main>
  0xafbf0344,    // sw    ra,836(sp)
  0xafbe0340,    // sw    s8,832(sp)
  0x03a0f025,    // move  s8,sp
  0x27c301ac,    // addiu v1,s8,428
  0x27c2001c,    // addiu v0,s8,28
  0x00602825,    // move  a1,v1
  0x00402025,    // move  a0,v0
  0x0c00000a,    // jal   10 <load_arrays>
  0x00000000,    // nop
  0x27c301ac,    // addiu v1,s8,428
  0x27c2001c,    // addiu v0,s8,28
  0x00602825,    // move  a1,v1
  0x00402025,    // move  a0,v0
  0x0c00003c,    // jal   60 <check_result>
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x03c0e825,    // move  sp,s8
  0x8fbf0344,    // lw    ra,836(sp)
  0x8fbe0340,    // lw    s8,832(sp)
  0x27bd0348,    // addiu sp,sp,840
  0x00004020,     // add $t0, $zero, $zero
  0x8d090c44,     // lw $t1, 3140($t0)
  0xad090020,     // sw $t1, 32($t0)
  0x8d080420,     //lw $t0, 1056($t0)
  0x8d090c4c,     // lw $t1, 3148($t0)
  0xad09001c,     // sw $t1, 28($t0)
  0x8d08041c,     //lw $t0, 1054($t0)
  0x8d090f90,     //lw $t1, 3984($t0)
  0xad090018,     //sw $t1, 24($t0)
  0x8d080418,     //lw $t0, 1048($t0)
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000008,    // jr    $zero
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
};
/*
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
 "lh $t1, 2($t4)",
 "movz $t7, $t1, $t0",
 "movn $t7, $t0, $t1",
 //"j 0x04",
// "jr $t4"
  //"jal 0x05"
  "beq $zero, $zero, 0xE",
  "nop",
  "nop",
  "nop",
  "nop",
  "nop",
  "nop",
  "nop",
  "nop",
  "nop",
  "nop",
  "nop",
  "j 0x32",
  "bgtz $t1, 0xFFFE",
  "blez $t7, 0xFFFE",
  "bne $t1, $t7, 0xFFFE",
  "nop",
  "nop"
};
*/
unsigned int memory[10000];
unsigned int $pc = 0x00000000;
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
    int format = -1;
    int i = 0;
    //Transfer holder array to memory
    for(i = 0; i < (sizeof(holder)/sizeof(*holder)); i++)
    {
        memory[i] = holder[i];
    }
    $pc = memory[5];
    Reg[29] = memory[0];
    Reg[30] = memory[1];
    //Run pipeline
    while($pc != 0)
    {
        Instr_IF(memory[$pc]);
        format = Instr_ID();
        Instr_Exe(format);
        Instr_MEM();
        Instr_WB(format);
        Update_State();
        clock_cycles++;
        $pc = EXMEM.pcplus1;
        cout << $pc << endl;
    }

    cout << "Answer: "<< memory[6] << endl;
    cout << "Bubble Passes: "<< memory[7] << endl;
    cout << "Insertion Passes: "<< memory[8] << endl;
    cout << "Identical: "<< memory[9] << endl;
}
