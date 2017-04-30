//User created .hpp's
#include "Instr_IF.hpp"
#include "Instr_ID.hpp"
#include "Instr_WB.hpp"
#include "Instr_MEM.hpp"
#include "Instr_Exe.hpp"
#include "Update_State.hpp"
#include "cache.hpp"
#include "Program1.hpp"
#include "Program2.hpp"

//C++ Libraries used
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iomanip>
using namespace std;

unsigned int memory[1200];
int MISS_PENALTY = 8;
int MISS_PENALTY2 = 2;
unsigned int pc = 0x00000000;
unsigned int clock_cycles = 0;
unsigned int branch_pc = 0;
unsigned int cycle = 0;
int Reg[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
struct ifid Shadow_IFID, IFID, IFID_1;
struct idex Shadow_IDEX, IDEX, IDEX_1;
struct exmem Shadow_EXMEM, EXMEM, EXMEM_1;
struct memwb Shadow_MEMWB, MEMWB, MEMWB_1;
unsigned int instr_count = 0;
unsigned int delay_cycles = 0;

//###########################  Cache Parameters #########################################################################################
bool EARLY_START = true;
bool WRITE_BACK = false;
int dCACHEON = 0;
int iCACHEON = 1;
int iCACHE_SIZE = 256;
int dCACHE_SIZE =128;
int WORDS = 1;
cache icache(iCACHE_SIZE,WORDS);
cache dcache(dCACHE_SIZE,WORDS);
//#######################################################################################################################################

int main()
{
  transfer_Program2();
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
      // std::cout << "pc is " << pc << '\n';
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
      double Icache_hitrate = 100 * ((double) icache.cache_hit) / (double) icache.cache_access;
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
}
