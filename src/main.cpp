#include "Instr_IF.hpp"
#include "Instr_ID.hpp"
#include "Instr_WB.hpp"
#include "Instr_MEM.hpp"
#include "Instr_Exe.hpp"
#include "Update_State.hpp"
#include "cache.hpp"
#include <iostream>
using namespace std;


cache dcache(256, 16);
cache icache(128, 16);



#define testing   1

unsigned int memory[5000] = {
  0x00000fa0,	// $sp = 4000
  0x00000fa0,	// $fp = 4000
  0x00000000,
  0x00000000,
  0x00000000,
  0x00000078,	// $pc = 120
  0x00000000,	// reserved for answer
  0x00000000,     // reserved for answer
  0x00000000,     // reserved for answer
  0x00000000,   	// reserved for answer
  0x27bdfff0,    // addiu	sp,sp,-16 <load_arrays>
  0xafbe000c,    // sw	s8,12(sp)
  0x03a0f025,    // move	s8,sp
  0xafc40010,    // sw	a0,16(s8)
  0xafc50014,    // sw	a1,20(s8)
  0xafc00004,    // sw	zero,4(s8)
  0x1000001c,    // b	4008bc <load_arrays+0x8c>
  0x00000000,    // nop
  0x8fc20004,    // lw	v0,4(s8)
  0x00021080,    // sll	v0,v0,0x2
  0x8fc30010,    // lw	v1,16(s8)
  0x00621021,    // addu	v0,v1,v0
  0x8fc30004,    // lw	v1,4(s8)
  0x00031880,    // sll	v1,v1,0x2
  0x8fc40010,    // lw	a0,16(s8)
  0x00831821,    // addu	v1,a0,v1
  0x8c640000,    // lw	a0,0(v1)
  0x8fc30004,    // lw	v1,4(s8)
  0x00831821,    // addu	v1,a0,v1
  0xac430000,    // sw	v1,0(v0)
  0x8fc20004,    // lw	v0,4(s8)
  0x00021080,    // sll	v0,v0,0x2
  0x8fc30014,    // lw	v1,20(s8)
  0x00621021,    // addu	v0,v1,v0
  0x8fc30004,    // lw	v1,4(s8)
  0x00031880,    // sll	v1,v1,0x2
  0x8fc40014,    // lw	a0,20(s8)
  0x00831821,    // addu	v1,a0,v1
  0x8c640000,    // lw	a0,0(v1)
  0x8fc30004,    // lw	v1,4(s8)
  0x00831821,    // addu	v1,a0,v1
  0xac430000,    // sw	v1,0(v0)
  0x8fc20004,    // lw	v0,4(s8)
  0x24420001,    // addiu	v0,v0,1
  0xafc20004,    // sw	v0,4(s8)
  0x8fc20004,    // lw	v0,4(s8)
  0x28420064,    // slti	v0,v0,100
  0x1440ffe2,    // bnez	v0,400850 <load_arrays+0x20>
  0x00000000,    // nop
  0x00000000,    // nop
  0x03c0e825,    // move	sp,s8
  0x8fbe000c,    // lw	s8,12(sp)
  0x27bd0010,    // addiu	sp,sp,16
  0x03e00008,    // jr	ra
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x27bdffe8,    // 	addiu	sp,sp,-24 <check_result>
  0xafbe0014,    // sw	s8,20(sp)
  0x03a0f025,    // move	s8,sp
  0xafc40018,    // sw	a0,24(s8)
  0xafc5001c,    // sw	a1,28(s8)
  0xafc00000,    // sw	zero,0(s8)
  0xafc00008,    // sw	zero,8(s8)
  0x1000001d,    // b	400978 <check_result+0x94>
  0x00000000,    // nop
  0x8fc20008,    // lw	v0,8(s8)
  0x00021080,    // sll	v0,v0,0x2
  0x8fc30018,    // lw	v1,24(s8)
  0x00621021,    // addu	v0,v1,v0
  0x8c430000,    // lw	v1,0(v0)
  0x8fc20008,    // lw	v0,8(s8)
  0x00021080,    // sll	v0,v0,0x2
  0x8fc4001c,    // lw	a0,28(s8)
  0x00821021,    // addu	v0,a0,v0
  0x8c420000,    // lw	v0,0(v0)
  0x00621026,    // xor	v0,v1,v0
  0xafc2000c,    // sw	v0,12(s8)
  0x8fc2000c,    // lw	v0,12(s8)
  0x10400003,    // beqz	v0,40094c <check_result+0x68>
  0x00000000,    // nop
  0x24020001,    // li	v0,1
  0xafc20000,    // sw	v0,0(s8)
  0x8fc20008,    // lw	v0,8(s8)
  0x00021080,    // sll	v0,v0,0x2
  0x8fc30018,    // lw	v1,24(s8)
  0x00621021,    // addu	v0,v1,v0
  0x8c420000,    // lw	v0,0(v0)
  0x8fc30004,    // lw	v1,4(s8)
  0x00621021,    // addu	v0,v1,v0
  0xafc20004,    // sw	v0,4(s8)
  0x8fc20008,    // lw	v0,8(s8)
  0x24420001,    // addiu	v0,v0,1
  0xafc20008,    // sw	v0,8(s8)
  0x8fc20008,    // lw	v0,8(s8)
  0x28420064,    // slti	v0,v0,100
  0x1440ffe1,    // bnez	v0,400908 <check_result+0x24>
  0x00000000,    // nop
  0x8fc20000,    // lw	v0,0(s8)
  0x14400003,    // bnez	v0,40099c <check_result+0xb8>
  0x00000000,    // nop
  0x8fc20004,    // lw	v0,4(s8)
  0xafc20000,    // sw	v0,0(s8)
  0x00000000,    // nop
  0x03c0e825,    // move	sp,s8
  0x8fbe0014,    // lw	s8,20(sp)
  0x27bd0018,    // addiu	sp,sp,24
  0x03e00008,    // jr	ra
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x27bdfcb8,    // addiu	sp,sp,-840 <main>
  0xafbf0344,    // sw	ra,836(sp)
  0xafbe0340,    // sw	s8,832(sp)
  0x03a0f025,    // move	s8,sp
  0x27c301ac,    // addiu	v1,s8,428
  0x27c2001c,    // addiu	v0,s8,28
  0x00602825,    // move	a1,v1
  0x00402025,    // move	a0,v0
  0x0c00000a,    // jal	10 <load_arrays>
  0x00000000,    // nop
  0x27c301ac,    // addiu	v1,s8,428
  0x27c2001c,    // addiu	v0,s8,28
  0x00602825,    // move	a1,v1
  0x00402025,    // move	a0,v0
  0x0c00003c,    // jal	60 <check_result>
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x03c0e825,    // move	sp,s8
  0x8fbf0344,    // lw	ra,836(sp)
  0x8fbe0340,    // lw	s8,832(sp)
  0x27bd0348,    // addiu	sp,sp,840
  0x00004020,		// add $t0, $zero, $zero
  0x8d090c44,		// lw $t1, 3140($t0)
  0xad090020,		// sw $t1, 32($t0)
  0x8d080420,		//lw $t0, 1056($t0)
  0x8d090c4c,		// lw $t1, 3148($t0)
  0xad09001c,		// sw $t1, 28($t0)
  0x8d08041c,		//lw $t0, 1054($t0)
  0x8d090f90,		//lw $t1, 3984($t0)
  0xad090018,		//sw $t1, 24($t0)
  0x8d080418,		//lw $t0, 1048($t0)
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000008,    // jr	$zero
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop
  0x00000000,    // nop

};

unsigned int pc = 0x00000000;
unsigned int clock_cycles = 0;
unsigned int branch_pc = 0;
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
    pc = memory[5];
    Reg[29] = memory[0];
    Reg[30] = memory[1];
    //Run pipeline
    Shadow_IDEX.branch = false;
    while(pc != 0)
    {
        Instr_IF(memory[pc]);
        format = Instr_ID();
        Instr_Exe(format);
        if(Shadow_IDEX.branch == true)
        {
#if testing
            if(Shadow_IDEX.opcode == bltz_opcode)
              cout << "opcode = bltz_opcode" << endl;
            if(Shadow_IDEX.opcode == blez_opcode)
              cout << "opcode = blez_opcode" << endl;
            if(Shadow_IDEX.opcode == bgtz_opcode)
              cout << "opcode = bgtz_opcode" << endl;
            if(Shadow_IDEX.opcode == beq_opcode)
              cout << "opcode = beq_opcode" << endl;
            if(Shadow_IDEX.opcode == bne_opcode)
              cout << "opcode = bne_opcode" << endl;
#endif
            branch_pc = Shadow_EXMEM.pcplus1;
            Instr_IF(memory[Shadow_IFID.pcplus1]);
            format = Instr_ID();
            Instr_Exe(format);
            Instr_MEM();
            Instr_WB(format);
            Update_State();
            clock_cycles++;

            #if testing
              cout << "instr after branch: "<< Shadow_IFID.pcplus1 - 2 << endl;
            #endif

            pc = branch_pc;

            #if testing
              cout << pc << endl;
            #endif

            Shadow_IDEX.branch = false;
        }
        Instr_MEM();
        Instr_WB(format);
        Update_State();
        clock_cycles++;
        pc = EXMEM.pcplus1;
        #if testing
          cout << pc << endl;
        #endif
    }
    cout << "Answer: "<< memory[6] << endl;
    cout << "Bubble Passes: "<< memory[7] << endl;
    cout << "Insertion Passes: "<< memory[8] << endl;
    cout << "Identical: "<< memory[9] << endl;
    cout << "CPI: " << clock_cycles/clock_cycles << endl;
}
