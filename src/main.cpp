#include "Instr_IF.hpp"
#include "Instr_ID.hpp"
#include "Instr_WB.hpp"
#include "Instr_MEM.hpp"
#include "Instr_Exe.hpp"
#include "Update_State.hpp"
#include "cache.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include "Program1.hpp"
#include "Program2.hpp"
#include <iomanip>
using namespace std;

#define testing   0


unsigned int memory[1200];




bool counted = false;
int MISS_PENALTY = 8;
int MISS_PENALTY2 = 2;
unsigned int pc = 0x00000000;
unsigned int clock_cycles = 0;
unsigned int branch_pc = 0;
extern double cache_configuration_1;
unsigned int cycle = 0;
int Reg[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
struct ifid Shadow_IFID, IFID, IFID_1;
struct idex Shadow_IDEX, IDEX, IDEX_1;
struct exmem Shadow_EXMEM, EXMEM, EXMEM_1;
struct memwb Shadow_MEMWB, MEMWB, MEMWB_1;
unsigned int instr_count = 0;
unsigned int delay_cycles = 0;

bool WRITE_BACK = false;
int dCACHEON = 0;
int iCACHEON = 1;
int iCACHE_SIZE = 128;
int dCACHE_SIZE = 256;
int WORDS = 1;
cache icache(iCACHE_SIZE,WORDS);
cache dcache(dCACHE_SIZE,WORDS);

int main()
{
  // for(int i = 64; i < 257; i = i * 2){
  //   for(int j = 16; j > 0; j = j / 4){
  //     std::cout << "Using icache (" << i << "," << j <<')' << '\n';
  //     cache icache(i,j);
  //     if(i == 64){
  //       std::cout << "Using dcache (" << "1024," << j <<')' << '\n';
  //       cache dcache(1024,j);
  //     }
  //     else{
  //       std::cout << "Using dcache (" << "256," << j <<')' << '\n';
  //       cache dcache(256,j);
  //     }

  transfer_Program1();
    unsigned int clock_cycles = 0;
    int format = -1;

        unsigned int instruction = 0;
        int program_indicator = memory[5];
        pc = memory[5];
        Reg[29] = memory[0];
        Reg[30] = memory[1];
        Shadow_IDEX.branch = false;
        while(pc != 0)
        {
            std::cout << "pc is " << pc << '\n';
            if (iCACHEON){
              instruction = icache.read_icache(pc);
              Instr_IF(instruction);
            }
            else{
              Instr_IF(memory[pc]);
            }
            Instr_WB(format);
            format = Instr_ID();
            Instr_Exe(format);
            Instr_MEM();
            Update_State();
            clock_cycles++;
            if(Shadow_IDEX.branch == true)
            {
                branch_pc = pc;
                Instr_IF(memory[Shadow_IDEX.pcplus1]);
                format = Instr_ID();
                Instr_Exe(format);
                Instr_MEM();
                Instr_WB(format);
                Update_State();
                clock_cycles++;
                Shadow_IDEX.branch = false;
                EXMEM.pcplus1 = branch_pc;
                instr_count++;
            }
            //


            // cout << dec << pc << ' ' << endl;
            // cout << "$v0: " << Reg[2] << endl;
            // cout << "$v1: " << Reg[3] << endl;
            // cout << "$a0: " << Reg[4] << endl;
            // cout << "$a1: " << Reg[5] << endl;
            // cout << "$a2: " << Reg[6] << endl;
            // cout << "$a3: " << Reg[7] << endl;
            // cout << "$t0: " << Reg[8] << endl;
            // cout << "$t1: " << Reg[9] << endl;
            // cout << "$t2: " << Reg[10] << endl;
            // cout << "$t3: " << Reg[11] << endl;
            // cout << "$t4: " << Reg[12] << endl;
            // cout << "$t5: " << Reg[13] << endl;
            // cout << "$t6: " << Reg[14] << endl;
            // cout << "$t7: " << Reg[15] << endl;
            // cout << "$s0: " << Reg[16] << endl;
            // cout << "$s1: " << Reg[17] << endl;
            // cout << "$s2: " << Reg[18] << endl;
            // cout << "$s3: " << Reg[19] << endl;
            // cout << "$s4: " << Reg[20] << endl;
            // cout << "$s5: " << Reg[21] <<  endl;
            // cout << "$s6: " << Reg[22] <<  endl;
            // cout << "$s7: " << Reg[23] <<  endl;
            // cout << "$t8: " << Reg[24] <<  endl;
            // cout << "$t9: " << Reg[25] <<  endl;
            // cout << "$sp: " << Reg[29] <<  endl;
            // cout << "$fp: " << Reg[30] <<  endl;
            // cout << "$ra: " << Reg[31] << endl;
            // cout << "" << endl;
            //
            // cout << pc << ' ' << "\t";
            // cout << "$v0: " << Reg[2] << "\t";
            // cout << "$v1: " << Reg[3] << "\t";
            // cout << "$a0: " << Reg[4] << "\t";
            // cout << "$a1: " << Reg[5] << "\t";
            // cout << "$a2: " << Reg[6] << "\t";
            // cout << "$a3: " << Reg[7] << "\t";
            // cout << "$t0: " << Reg[8] << "\t";
            // cout << "$t1: " << Reg[9] << "\t";
            // cout << "$t2: " << Reg[10] << "\t";
            // cout << "$t3: " << Reg[11] << "\t";
            // cout << "$t4: " << Reg[12] << "\t";
            // cout << "$t5: " << Reg[13] << "\t";
            // cout << "$t6: " << Reg[14] << "\t";
            // cout << "$t7: " << Reg[15] << "\t";
            // cout << "$s0: " << Reg[16] << "\t";
            // cout << "$s1: " << Reg[17] << "\t";
            // cout << "$s2: " << Reg[18] << "\t";
            // cout << "$s3: " << Reg[19] << "\t";
            // cout << "$s4: " << Reg[20] << "\t";
            // cout << "$s5: " << Reg[21] <<  "\t";
            // cout << "$s6: " << Reg[22] <<  "\t";
            // cout << "$s7: " << Reg[23] <<  "\t";
            // cout << "$t8: " << Reg[24] <<  "\t";
            // cout << "$t9: " << Reg[25] <<  "\t";
            // cout << "$sp: " << Reg[29] <<  "\t";
            // cout << "$fp: " << Reg[30] <<  "\t";
            // cout << "$ra: " << Reg[31] << endl;

            pc = EXMEM.pcplus1;
            instr_count++;
        }
        if(program_indicator == 120)
        {
            double Icache_hitrate = 100 * (double) icache.cache_hit / (double) icache.cache_access;
            double Dcache_hitrate = 100 * (double) dcache.cache_hit / (double) dcache.cache_access;
            double CPI = ((double)cycle + (double)clock_cycles + (double)delay_cycles)/ (double)instr_count;
            cout << "Memory[6]: "<< hex << memory[6] << endl;
            cout << "Memory[7]: 0x"<< hex << memory[7] << endl;
            cout << "Memory[8]: 0x"<< hex << memory[8] << endl;
            cout << "Memory[9]: 0x"<< hex << memory[9] << endl;
            cout << "Total Clock Cycles: " << dec<< cycle + clock_cycles + delay_cycles << endl;
            cout << "CPI: " << fixed << setprecision(3) << CPI << endl;
            cout << "I-Cache Hit Rate: " << fixed << setprecision(2) << Icache_hitrate << endl;
            cout << "D-Cache Hit Rate: " << fixed << setprecision(2) << Dcache_hitrate << endl;
            std::cout << '\n';
            clock_cycles = 0;
            cycle = 0;
            delay_cycles = 0;
            instr_count = 0;
        }
        if(program_indicator == 140)
        {
            double Icache_hitrate = 100 * ((double) icache.cache_hit + cache_configuration_1) / (double) icache.cache_access;
            double Dcache_hitrate = 100 * (double) dcache.cache_hit / (double) dcache.cache_access;
            double CPI = (((double)cycle + (double)clock_cycles + (double)delay_cycles)/ (double)instr_count);
            cout << "Memory[6]: "<< dec << memory[6] << endl;
            cout << "Memory[7]: "<< dec << memory[7] << endl;
            cout << "Memory[8]: "<< dec << memory[8] << endl;
            cout << "Memory[9]: "<< dec << memory[9] << endl;
            cout << "Total Clock Cycles: " << dec<< cycle + clock_cycles + delay_cycles << endl;
            cout << "CPI: " << fixed << setprecision(3) << CPI << endl;
            cout << "I-Cache Hit Rate: " << fixed << setprecision(2) << Icache_hitrate << endl;
            cout << "D-Cache Hit Rate: " << fixed << setprecision(2) << Dcache_hitrate << endl;

            std::cout << '\n';
            clock_cycles = 0;
            cycle = 0;
            delay_cycles = 0;
            instr_count = 0;
        }

    //}
  //   }
  // }
}
