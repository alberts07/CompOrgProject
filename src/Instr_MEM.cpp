
#include "Instr_ID.hpp"
#include "Instr_IF.hpp"
#include "cache.hpp"
#include <iostream>

extern struct idex Shadow_IDEX;
extern struct memwb Shadow_MEMWB;
extern struct exmem Shadow_EXMEM;
extern struct memwb MEMWB;
extern struct exmem EXMEM;
extern struct idex IDEX;
extern unsigned int pc;
extern cache dcache;
using namespace std;
extern unsigned int delay_cycles;

extern int memory[1200];

void Instr_MEM()
{

  int taken = 0;

  if(EXMEM.MemRead && (MEMWB.DstReg != 0)  && ((EXMEM.DstReg == Shadow_IDEX.Rs) || (EXMEM.DstReg == Shadow_IDEX.Rt))\
   && ((Shadow_IDEX.opcode == blez_opcode) || (Shadow_IDEX.opcode == bltz_opcode)\
    || (Shadow_IDEX.opcode == bgtz_opcode) || (Shadow_IDEX.opcode == beq_opcode) || (Shadow_IDEX.opcode == bne_opcode))\
    && (taken == 0))
  {

        // cout << "Entered Forwarding Stall 3: Load and Branch Issue: " << endl;
        // cout << pc + 1<< endl;
        delay_cycles = delay_cycles + 1;
        taken = 1;
  }

  if(EXMEM.RegWrite && (MEMWB.DstReg != 0)  && ((EXMEM.DstReg == Shadow_IDEX.Rs) || (EXMEM.DstReg == Shadow_IDEX.Rt))\
    && ((Shadow_IDEX.opcode == blez_opcode) || (Shadow_IDEX.opcode == bltz_opcode)\
    || (Shadow_IDEX.opcode == bgtz_opcode) || (Shadow_IDEX.opcode == beq_opcode) || (Shadow_IDEX.opcode == bne_opcode))\
    && (taken == 0))
  {
        // if((pc +1 != 28) && (pc + 1 != 18) && (pc + 1 != 38)){
        // cout << "Entered Forwarding Stall 3: Instr and Branch Issue:  " << endl;
        // cout << pc + 1 << endl;}
        delay_cycles++;
        taken = 1;
  }
  if(EXMEM.MemRead && (MEMWB.DstReg != 0)  && ((EXMEM.DstReg == Shadow_IDEX.Rt) || (EXMEM.DstReg == Shadow_IDEX.Rs))\
    && ((Shadow_IDEX.opcode != blez_opcode) || (Shadow_IDEX.opcode != bltz_opcode)\
    || (Shadow_IDEX.opcode != bgtz_opcode) || (Shadow_IDEX.opcode != beq_opcode) || (Shadow_IDEX.opcode != bne_opcode))\
    && (taken == 0))
  {
        // if(pc + 1 != 127)
        // {
        //   cout << "Entered Forwarding Stall 4: Load ahead of instr using result. Issue: " << endl;
        //   cout << pc + 1<< endl;
        // }
        delay_cycles++;
        taken = 1;
  }

  if((MEMWB.RegWrite) && (MEMWB.DstReg != 0) && ((MEMWB.DstReg == Shadow_IDEX.Rs) || (MEMWB.DstReg == Shadow_IDEX.Rt))\
    && !((EXMEM.RegWrite) && (EXMEM.DstReg == Shadow_IDEX.Rs) && (EXMEM.DstReg != 0))\
    && (taken == 0))
  {
        // cout << "Entered Forwarding Stall 1: " << endl;
        // cout << pc + 1 << endl;
        delay_cycles++;
         taken = 1;
  }
  if((EXMEM.MemWrite) && (Shadow_EXMEM.RegWrite || Shadow_EXMEM.MemRead) && ((IDEX.Rt == Shadow_IDEX.Rs) || (IDEX.Rt == Shadow_IDEX.Rt))\
    && (taken == 0))
  {
        // cout << "Entered Forwarding Stall ?: " << endl;
        // cout << pc + 1 << endl;
        delay_cycles++;
         taken = 1;
  }

    Shadow_MEMWB.RegWrite = Shadow_EXMEM.RegWrite;
    Shadow_MEMWB.MemtoReg = Shadow_EXMEM.MemtoReg;
    Shadow_MEMWB.DstReg = Shadow_EXMEM.DstReg;
    Shadow_MEMWB.ALUResult = Shadow_EXMEM.ALUResult;
    Shadow_MEMWB.pcplus1 = Shadow_EXMEM.pcplus1;

    if((MEMWB.RegWrite) && (MEMWB.DstReg != 0) && (MEMWB.DstReg == Shadow_IDEX.Rs))
    {
        delay_cycles++;
    }
    if((MEMWB.RegWrite) && (MEMWB.DstReg != 0) && (MEMWB.DstReg == Shadow_IDEX.Rt))
    {
        delay_cycles++;
    }

    unsigned int data = 0;
    if(Shadow_EXMEM.MemRead)
    {
        if(Shadow_EXMEM.half == true)
        {
            switch(Shadow_EXMEM.mem)
            {
                case 0:
                {
                    Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF0000) >> 16;
                    if((Shadow_IDEX.opcode == lh_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00008000) != 0))
                    {
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFF0000;
                    }
                    break;
                }
                case 1:
                {
                    Shadow_MEMWB.DstRegValue = memory[Shadow_EXMEM.ALUResult] & 0x0000FFFF;
                    if((Shadow_IDEX.opcode == lh_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00008000) != 0))
                    {
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFF0000;
                    }
                    break;
                }
            }
        }
        if(Shadow_EXMEM.half == false)
        {
            switch(Shadow_EXMEM.mem)
            {
                case 0:
                {
                  data = (memory[Shadow_EXMEM.ALUResult] & 0xFF000000)>> 24;

                  Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0xFF000000)>> 24;

                  if((Shadow_IDEX.opcode == lb_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00000080) != 0))
                  {
                      Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFFFF00;
                  }
                    break;
                }
                case 1:
                {
                    Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0x00FF0000) >> 16;
                    if((Shadow_IDEX.opcode == lb_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00000080) != 0))
                    {
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFFFF00;
                    }
                    break;
                }
                case 2:
                {
                    Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0x0000FF00) >> 8;
                    if((Shadow_IDEX.opcode == lb_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00000080) != 0))
                    {
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFFFF00;
                    }
                    break;
                }
                case 3:
                {
                    Shadow_MEMWB.DstRegValue = memory[Shadow_EXMEM.ALUResult] & 0x000000FF;
                    if((Shadow_IDEX.opcode == lb_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00000080) != 0))
                    {
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFFFF00;
                    }
                    break;
                }
                case 4:
                {
                  // std::cout << "Attempting a load of " << memory[Shadow_EXMEM.ALUResult] << " to register " << Shadow_MEMWB.DstReg << '\n';
                  // std::cout << "The old value was " << Shadow_MEMWB.DstRegValue << '\n';
                  // std::cout << "The ALUResult is " << Shadow_EXMEM.ALUResult << '\n';
                  if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                  {
                    // This somehow sets a2 to a3 and fucks it up
                    Shadow_MEMWB.DstRegValue = dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset];
                    // std::cout << "It is now " << dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] << '\n';
                  }
                  else
                  {
                      Shadow_MEMWB.DstRegValue = dcache.mem_cache(Shadow_EXMEM.ALUResult);
                      // std::cout << "It is now " << dcache.mem_cache(Shadow_EXMEM.ALUResult) << '\n';

                  }
                  // std::cout << "The new value is " << Shadow_MEMWB.DstRegValue << '\n';
                  // Shadow_MEMWB.DstRegValue = memory[Shadow_EXMEM.ALUResult] & 0xFFFFFFFF;
                    break;
                }
            }
        }
    }
    else if (Shadow_EXMEM.MemWrite)
    {
        if(Shadow_EXMEM.half == true)
        {
            switch(Shadow_EXMEM.mem)
            {
                case 0:
                {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0x0000FFFF) | ((0x0000FFFF & Shadow_EXMEM.RtValue) << 16);
                    break;
                }
                case 1:
                {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF0000) | ((0x0000FFFF & Shadow_EXMEM.RtValue));
                    break;
                }
            }
        }
        if(Shadow_EXMEM.half == false)
        {
            switch(Shadow_EXMEM.mem)
            {
                case 0:
                {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0x00FFFFFF) | ((Shadow_EXMEM.RtValue) << 24);
                    break;
                }
                case 1:
                {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFF00FFFF) | ((Shadow_EXMEM.RtValue) << 16);
                    break;
                }
                case 2:
                {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF00FF) | ((Shadow_EXMEM.RtValue) << 8);
                    break;
                }
                case 3:
                {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFFFFFF00) | ((Shadow_EXMEM.RtValue));
                    break;
                }
                case 4:
                {
                    // std::cout << "Attempting a store word of " << Shadow_EXMEM.RtValue << " to " << memory[Shadow_EXMEM.ALUResult] << '\n';

                    std::cout << "The memory location " << Shadow_EXMEM.ALUResult << " is being written " << '\n';
                    std::cout << "The old memory data is " << memory[Shadow_EXMEM.ALUResult] << " is being written " << '\n';
                    std::cout << "The new memory data should be " << Shadow_EXMEM.RtValue << " is being written " << '\n';

                    dcache.write_dcache(Shadow_EXMEM.ALUResult, Shadow_EXMEM.RtValue);
                    // memory[Shadow_EXMEM.ALUResult] = 0xFFFFFFFF & Shadow_EXMEM.RtValue;
                    std::cout << '\n';
                    break;
                }
            }
        }
    }
    else
    {
    }
}
