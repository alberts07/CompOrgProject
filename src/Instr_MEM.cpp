
#include "Instr_ID.hpp"
#include "Instr_IF.hpp"
#include "cache.hpp"
#include <iostream>

extern struct idex Shadow_IDEX, IDEX, IDEX_1;
extern struct memwb Shadow_MEMWB, MEMWB_1, MEMWB;
extern struct exmem Shadow_EXMEM, EXMEM, EXMEM_1;
extern unsigned int pc;
extern cache dcache;
using namespace std;
extern unsigned int delay_cycles;
extern int dCACHEON;

extern int memory[1200];

void Instr_MEM()
{

  int taken = 0;

  if(((IDEX_1.opcode == lw_opcode) || (IDEX_1.opcode == lb_opcode)) && ((Shadow_IDEX.opcode == blez_opcode)\
   || (Shadow_IDEX.opcode == bltz_opcode) || (Shadow_IDEX.opcode == bgtz_opcode) \
    || (Shadow_IDEX.opcode == beq_opcode) || (Shadow_IDEX.opcode == bne_opcode)) \
    && ((EXMEM_1.DstReg == Shadow_IDEX.Rs) || (EXMEM_1.DstReg == Shadow_IDEX.Rt)))
    {
        // Load 2 cycles before dependent branch
        delay_cycles++;
    }
  if(EXMEM.MemRead && (EXMEM.DstReg != 0)  && ((EXMEM.DstReg == Shadow_IDEX.Rs) || (EXMEM.DstReg == Shadow_IDEX.Rt))\
   && ((Shadow_IDEX.opcode == blez_opcode) || (Shadow_IDEX.opcode == bltz_opcode)\
    || (Shadow_IDEX.opcode == bgtz_opcode) || (Shadow_IDEX.opcode == beq_opcode) || (Shadow_IDEX.opcode == bne_opcode))\
    && (taken == 0))
  {

        // Load 1 cycle before a dependent Branch
        delay_cycles++;
        taken = 1;
  }

  if(EXMEM.RegWrite && (EXMEM.DstReg != 0)  && ((EXMEM.DstReg == Shadow_IDEX.Rs) || (EXMEM.DstReg == Shadow_IDEX.Rt))\
    && ((Shadow_IDEX.opcode == blez_opcode) || (Shadow_IDEX.opcode == bltz_opcode)\
    || (Shadow_IDEX.opcode == bgtz_opcode) || (Shadow_IDEX.opcode == beq_opcode) || (Shadow_IDEX.opcode == bne_opcode))\
    && (taken == 0))
  {
        // Instr 1 cycle before Branch
        delay_cycles++;
        taken = 1;
  }
  if(EXMEM.MemRead && (EXMEM.DstReg != 0)  && ((EXMEM.DstReg == Shadow_IDEX.Rt) || (EXMEM.DstReg == Shadow_IDEX.Rs))\
    && ((Shadow_IDEX.opcode != blez_opcode) || (Shadow_IDEX.opcode != bltz_opcode)\
    || (Shadow_IDEX.opcode != bgtz_opcode) || (Shadow_IDEX.opcode != beq_opcode) || (Shadow_IDEX.opcode != bne_opcode))\
    && (taken == 0))
  {
        //Load 1 cycle before Instr
        delay_cycles++;
        taken = 1;
  }

    Shadow_MEMWB.RegWrite = Shadow_EXMEM.RegWrite;
    Shadow_MEMWB.MemtoReg = Shadow_EXMEM.MemtoReg;
    Shadow_MEMWB.DstReg = Shadow_EXMEM.DstReg;
    Shadow_MEMWB.ALUResult = Shadow_EXMEM.ALUResult;
    Shadow_MEMWB.pcplus1 = Shadow_EXMEM.pcplus1;

    unsigned int data = 0;
    if(Shadow_EXMEM.MemRead)
    {
        if(Shadow_EXMEM.half == true)
        {
            switch(Shadow_EXMEM.mem)
            {
                case 0:
                {
                  if(dCACHEON){
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      Shadow_MEMWB.DstRegValue = (dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] & 0xFFFF0000) >> 16;
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = (dcache.mem_cache(Shadow_EXMEM.ALUResult) & 0xFFFF0000) >> 16;
                    }
                  }

                  else
                  {
                      Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF0000) >> 16;
                  }

                    if((Shadow_IDEX.opcode == lh_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00008000) != 0))
                    {
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFF0000;
                    }
                    break;
                }
                case 1:
                {

                  if(dCACHEON)
                  {
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      Shadow_MEMWB.DstRegValue = dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] & 0x0000FFFF;
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = dcache.mem_cache(Shadow_EXMEM.ALUResult) & 0x0000FFFF;
                    }
                  }

                  else
                  {
                    Shadow_MEMWB.DstRegValue = memory[Shadow_EXMEM.ALUResult] & 0x0000FFFF;
                  }

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
                  if(dCACHEON)
                  {
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      Shadow_MEMWB.DstRegValue = (dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] & 0xFF000000) >> 24;
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = (dcache.mem_cache(Shadow_EXMEM.ALUResult) & 0xFF000000) >> 24;
                    }
                  }

                  else
                  {
                    Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0xFF000000)>> 24;
                  }

                  if((Shadow_IDEX.opcode == lb_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00000080) != 0))
                  {
                      Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFFFF00;
                  }
                    break;
                }
                case 1:
                {
                  if(dCACHEON)
                  {
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                        Shadow_MEMWB.DstRegValue = (dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] & 0x00FF0000) >> 16;
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = (dcache.mem_cache(Shadow_EXMEM.ALUResult) & 0x00FF0000) >> 16;
                    }
                  }
                  else
                  {
                      Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0x00FF0000) >> 16;
                  }

                  if((Shadow_IDEX.opcode == lb_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00000080) != 0))
                  {
                      Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFFFF00;
                  }
                  break;
                }
                case 2:
                {
                  if(dCACHEON)
                  {
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      Shadow_MEMWB.DstRegValue = (dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] & 0x0000FF00) >> 8;
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = (dcache.mem_cache(Shadow_EXMEM.ALUResult) & 0x0000FF00) >> 8;
                    }
                  }
                  else
                  {
                    Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0x0000FF00) >> 8;
                  }

                  if((Shadow_IDEX.opcode == lb_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00000080) != 0))
                    {
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFFFF00;
                    }
                  break;
                }
                case 3:
                {
                  if(dCACHEON)
                  {
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      Shadow_MEMWB.DstRegValue = dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] & 0x000000FF;
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = dcache.mem_cache(Shadow_EXMEM.ALUResult) & 0x000000FF;
                    }
                  }
                else
                {
                  Shadow_MEMWB.DstRegValue = memory[Shadow_EXMEM.ALUResult] & 0x000000FF;
                }

                if((Shadow_IDEX.opcode == lb_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00000080) != 0))
                  {
                      Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFFFF00;
                  }
                  break;
                }
                case 4:
                {
                  if(dCACHEON)
                  {
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      Shadow_MEMWB.DstRegValue = dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset];
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = dcache.mem_cache(Shadow_EXMEM.ALUResult);
                    }
                  }
                else
                {
                  Shadow_MEMWB.DstRegValue = memory[Shadow_EXMEM.ALUResult] & 0xFFFFFFFF;
                }
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
                  if(dCACHEON)
                  {
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      data = (dcache.data[dcache.block_address*dcache.block_size+dcache.block_offset] & 0x0000FFFF) | ((0xFFFF0000 & Shadow_EXMEM.RtValue) << 16);
                    }
                    else
                    {
                      data = (memory[Shadow_EXMEM.ALUResult] & 0x0000FFFF) | ((0xFFFF0000 & Shadow_EXMEM.RtValue) << 16);
                    }
                      dcache.write_dcache(Shadow_EXMEM.ALUResult, data);
                  }
                  else{
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0x0000FFFF) | ((0x0000FFFF & Shadow_EXMEM.RtValue) << 16);
                  }
                  break;
                }
                case 1:
                {
                  if(dCACHEON)
                  {
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult)){
                        data = (dcache.data[dcache.block_address*dcache.block_size+dcache.block_offset] & 0xFFFF0000) | ((0x0000FFFF & Shadow_EXMEM.RtValue));
                    }
                    else
                    {
                      data = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF0000) | ((0x0000FFFF & Shadow_EXMEM.RtValue));
                    }
                      dcache.write_dcache(Shadow_EXMEM.ALUResult, data);
                    }
                    else
                    {
                      memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF0000) | ((0x0000FFFF & Shadow_EXMEM.RtValue));
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
                  if(dCACHEON)
                  {
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      data = (dcache.data[dcache.block_address*dcache.block_size+dcache.block_offset] & 0x00FFFFFF) | ((Shadow_EXMEM.RtValue) << 24);
                    }
                    else
                    {
                      data = (memory[Shadow_EXMEM.ALUResult] & 0x00FFFFFF) | ((Shadow_EXMEM.RtValue) << 24);
                    }
                      dcache.write_dcache(Shadow_EXMEM.ALUResult, data);
                  }
                  else
                  {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0x00FFFFFF) | ((Shadow_EXMEM.RtValue) << 24);
                  }
                  break;
                }
                case 1:
                {
                  if(dCACHEON)
                  {
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      data = (dcache.data[dcache.block_address*dcache.block_size+dcache.block_offset] & 0xFF00FFFF) | ((Shadow_EXMEM.RtValue) << 16);
                    }
                    else
                    {
                      data = (memory[Shadow_EXMEM.ALUResult] & 0xFF00FFFF) | ((Shadow_EXMEM.RtValue) << 16);
                    }
                    dcache.write_dcache(Shadow_EXMEM.ALUResult, data);
                  }
                  else
                  {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFF00FFFF) | ((Shadow_EXMEM.RtValue) << 16);
                  }
                    break;
                }
                case 2:
                {
                  if(dCACHEON)
                  {
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      data = (dcache.data[dcache.block_address*dcache.block_size+dcache.block_offset] & 0xFFFF00FF) | ((Shadow_EXMEM.RtValue) << 8);
                    }
                    else
                    {
                      data = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF00FF) | ((Shadow_EXMEM.RtValue) << 8);
                    }
                    dcache.write_dcache(Shadow_EXMEM.ALUResult, data);
                  }
                  else
                  {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF00FF) | ((Shadow_EXMEM.RtValue) << 8);
                  }
                  break;
                }
                case 3:
                {
                  if(dCACHEON)
                  {
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      data = (dcache.data[dcache.block_address*dcache.block_size+dcache.block_offset] & 0xFFFFFF00) | ((Shadow_EXMEM.RtValue));
                    }
                    else
                    {
                      data = (memory[Shadow_EXMEM.ALUResult] & 0xFFFFFF00) | ((Shadow_EXMEM.RtValue));
                      dcache.write_dcache(Shadow_EXMEM.ALUResult, data);
                    }
                  }
                  else
                  {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFFFFFF00) | ((Shadow_EXMEM.RtValue));
                  }
                  break;
                }
                case 4:
                {
                  if(dCACHEON)
                  {
                    dcache.write_dcache(Shadow_EXMEM.ALUResult, Shadow_EXMEM.RtValue);
                  }
                  else
                  {
                    memory[Shadow_EXMEM.ALUResult] = 0xFFFFFFFF & Shadow_EXMEM.RtValue;
                  }
                  break;
                }
            }
        }
    }
    else
    {}
}
