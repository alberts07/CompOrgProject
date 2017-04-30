
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
                    // std::cout << "We are attempting an upper half load of " << memory[Shadow_EXMEM.ALUResult] << " to memory location " << Shadow_EXMEM.ALUResult << '\n';
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      // This somehow sets a2 to a3 and fucks it up
                      Shadow_MEMWB.DstRegValue = (dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] & 0xFFFF0000) >> 16;
                      // std::cout << "It is now " << dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] << '\n';
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = (dcache.mem_cache(Shadow_EXMEM.ALUResult) & 0xFFFF0000) >> 16;
                        // std::cout << "It is now " << dcache.mem_cache(Shadow_EXMEM.ALUResult) << '\n';

                    }
                  }

                  else{
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

                  if(dCACHEON){
                    // std::cout << "We are attempting a lower half load of " << memory[Shadow_EXMEM.ALUResult] << " to memory location " << Shadow_EXMEM.ALUResult << '\n';
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      // This somehow sets a2 to a3 and fucks it up
                      Shadow_MEMWB.DstRegValue = dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] & 0x0000FFFF;
                      // std::cout << "It is now " << dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] << '\n';
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = dcache.mem_cache(Shadow_EXMEM.ALUResult) & 0x0000FFFF;
                        // std::cout << "It is now " << dcache.mem_cache(Shadow_EXMEM.ALUResult) << '\n';

                    }
                  }

                  else{
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
                  if(dCACHEON){
                    // std::cout << "We are attempting a byte 0 load of " << memory[Shadow_EXMEM.ALUResult] << " to memory location " << Shadow_EXMEM.ALUResult << '\n';
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      // This somehow sets a2 to a3 and fucks it up
                      Shadow_MEMWB.DstRegValue = (dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] & 0xFF000000) >> 24;
                      // std::cout << "It is now " << dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] << '\n';
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = (dcache.mem_cache(Shadow_EXMEM.ALUResult) & 0xFF000000) >> 24;
                        // std::cout << "It is now " << dcache.mem_cache(Shadow_EXMEM.ALUResult) << '\n';

                    }
                  }

                  else{
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
                  if(dCACHEON){
                    // std::cout << "We are attempting a byte 1 load of " << memory[Shadow_EXMEM.ALUResult] << " to memory location " << Shadow_EXMEM.ALUResult << '\n';
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      // This somehow sets a2 to a3 and fucks it up
                      Shadow_MEMWB.DstRegValue = (dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] & 0x00FF0000) >> 16;
                      // std::cout << "It is now " << dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] << '\n';
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = (dcache.mem_cache(Shadow_EXMEM.ALUResult) & 0x00FF0000) >> 16;
                        // std::cout << "It is now " << dcache.mem_cache(Shadow_EXMEM.ALUResult) << '\n';

                    }
                  }
                  else{
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
                  if(dCACHEON){
                    // std::cout << "We are attempting a byte 2 load of " << memory[Shadow_EXMEM.ALUResult] << " to memory location " << Shadow_EXMEM.ALUResult << '\n';
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      // This somehow sets a2 to a3 and fucks it up
                      Shadow_MEMWB.DstRegValue = (dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] & 0x0000FF00) >> 8;
                      // std::cout << "It is now " << dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] << '\n';
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = (dcache.mem_cache(Shadow_EXMEM.ALUResult) & 0x0000FF00) >> 8;
                        // std::cout << "It is now " << dcache.mem_cache(Shadow_EXMEM.ALUResult) << '\n';

                    }
                  }
                  else{
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
                  if(dCACHEON){
                    // std::cout << "We are attempting a byte 3 load of " << memory[Shadow_EXMEM.ALUResult] << " to memory location " << Shadow_EXMEM.ALUResult << '\n';
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult))
                    {
                      // This somehow sets a2 to a3 and fucks it up
                      Shadow_MEMWB.DstRegValue = dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] & 0x000000FF;
                      // std::cout << "It is now " << dcache.data[dcache.block_address * dcache.block_size + dcache.block_offset] << '\n';
                    }
                    else
                    {
                        Shadow_MEMWB.DstRegValue = dcache.mem_cache(Shadow_EXMEM.ALUResult) & 0x000000FF;
                        // std::cout << "It is now " << dcache.mem_cache(Shadow_EXMEM.ALUResult) << '\n';

                    }
                  }
                  else{
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
                  if(dCACHEON){
                    // std::cout << "Attempting a load of " << memory[Shadow_EXMEM.ALUResult] << " to register " << Shadow_MEMWB.DstReg << '\n';
                    // std::cout << "The old value was " << Shadow_MEMWB.DstRegValue << '\n';
                    // std::cout << "The ALUResult is " << Shadow_EXMEM.ALUResult << '\n';
                    // std::cout << "We are attempting a load of " << memory[Shadow_EXMEM.ALUResult] << " to memory location " << Shadow_EXMEM.ALUResult << '\n';
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
                  }
                  else{
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
                  if(dCACHEON){
                    // std::cout << "We are attempting to write an upper half" << '\n';
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult)){
                      data = (dcache.data[dcache.block_address*dcache.block_size+dcache.block_offset] & 0x0000FFFF) | ((0xFFFF0000 & Shadow_EXMEM.RtValue) << 16);
                    }
                    else{
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
                  if(dCACHEON){
                    // std::cout << "We are attempting to write lower half" << '\n';
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult)){
                        data = (dcache.data[dcache.block_address*dcache.block_size+dcache.block_offset] & 0xFFFF0000) | ((0x0000FFFF & Shadow_EXMEM.RtValue));
                      }
                      else{
                        data = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF0000) | ((0x0000FFFF & Shadow_EXMEM.RtValue));
                      }
                        dcache.write_dcache(Shadow_EXMEM.ALUResult, data);
                    }
                    else{
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
                  if(dCACHEON){
                    // std::cout << "We are attempting to write byte 0" << '\n';
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult)){
                      data = (dcache.data[dcache.block_address*dcache.block_size+dcache.block_offset] & 0x00FFFFFF) | ((Shadow_EXMEM.RtValue) << 24);
                    }
                    else{
                      data = (memory[Shadow_EXMEM.ALUResult] & 0x00FFFFFF) | ((Shadow_EXMEM.RtValue) << 24);
                    }
                      dcache.write_dcache(Shadow_EXMEM.ALUResult, data);
                  }
                  else{
                  memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0x00FFFFFF) | ((Shadow_EXMEM.RtValue) << 24);
                  }
                  break;
                }
                case 1:
                {
                  if(dCACHEON){
                    // std::cout << "We are attempting to write byte 1" << '\n';
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult)){
                      data = (dcache.data[dcache.block_address*dcache.block_size+dcache.block_offset] & 0xFF00FFFF) | ((Shadow_EXMEM.RtValue) << 16);
                    }
                    else{
                      data = (memory[Shadow_EXMEM.ALUResult] & 0xFF00FFFF) | ((Shadow_EXMEM.RtValue) << 16);
                    }
                      dcache.write_dcache(Shadow_EXMEM.ALUResult, data);
                  }
                  else{
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFF00FFFF) | ((Shadow_EXMEM.RtValue) << 16);
                  }

                    break;
                }
                case 2:
                {
                  if(dCACHEON){
                    // std::cout << "We are attempting to write byte 2" << '\n';
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult)){
                      data = (dcache.data[dcache.block_address*dcache.block_size+dcache.block_offset] & 0xFFFF00FF) | ((Shadow_EXMEM.RtValue) << 8);
                    }
                    else{
                      data = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF00FF) | ((Shadow_EXMEM.RtValue) << 8);
                    }
                      dcache.write_dcache(Shadow_EXMEM.ALUResult, data);
                  }
                  else{
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF00FF) | ((Shadow_EXMEM.RtValue) << 8);
                  }

                  break;
                }
                case 3:
                {
                  if(dCACHEON){
                    // std::cout << "We are attempting to write byte 3" << '\n';
                    if(dcache.read_dcache(Shadow_EXMEM.ALUResult)){
                      data = (dcache.data[dcache.block_address*dcache.block_size+dcache.block_offset] & 0xFFFFFF00) | ((Shadow_EXMEM.RtValue));
                    }
                    else{
                      data = (memory[Shadow_EXMEM.ALUResult] & 0xFFFFFF00) | ((Shadow_EXMEM.RtValue));
                      dcache.write_dcache(Shadow_EXMEM.ALUResult, data);
                    }
                  }
                  else{
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFFFFFF00) | ((Shadow_EXMEM.RtValue));
                  }

                  break;
                }
                case 4:
                {
                  if(dCACHEON){
                    // std::cout << "Attempting a store word of " << Shadow_EXMEM.RtValue << " to " << memory[Shadow_EXMEM.ALUResult] << '\n';

                    // std::cout << "The memory location " << Shadow_EXMEM.ALUResult << " is being written " << '\n';
                    // std::cout << "The old memory data is " << memory[Shadow_EXMEM.ALUResult] << " is being written " << '\n';
                    // std::cout << "The new memory data should be " << Shadow_EXMEM.RtValue << " is being written " << '\n';

                    dcache.write_dcache(Shadow_EXMEM.ALUResult, Shadow_EXMEM.RtValue);
                  }
                  else{
                    memory[Shadow_EXMEM.ALUResult] = 0xFFFFFFFF & Shadow_EXMEM.RtValue;
                  }
                  break;
                }
            }
        }
    }
    else
    {
    }
}
