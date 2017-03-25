
#include "Instr_ID.h"
#include "Instr_IF.h"

extern struct idex Shadow_IDEX;
extern struct memwb Shadow_MEMWB;
extern struct exmem Shadow_EXMEM;

extern int memory[0x50000000];

void Instr_MEM()
{
    Shadow_MEMWB.RegWrite = Shadow_EXMEM.RegWrite;
    Shadow_MEMWB.MemtoReg = Shadow_EXMEM.MemtoReg;
    Shadow_MEMWB.DstReg = Shadow_EXMEM.DstReg;
    Shadow_MEMWB.ALUResult = Shadow_EXMEM.ALUResult;
    Shadow_MEMWB.pcplus1 = Shadow_EXMEM.pcplus1;

    if(Shadow_EXMEM.MemRead)
    {
        if(Shadow_EXMEM.half == true)
        {
            switch(Shadow_EXMEM.mem)
            {
                case 0:
                {
                    Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF0000) >> 16;
                    break;
                }
                case 1:
                {
                    Shadow_MEMWB.DstRegValue = memory[Shadow_EXMEM.ALUResult] & 0x0000FFFF;
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
                    Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0xFF000000)>> 24;
                    break;
                }
                case 1:
                {
                    Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0x00FF0000) >> 16;
                    break;
                }
                case 2:
                {
                    Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0x0000FF00) >> 8;
                    break;
                }
                case 3:
                {
                    Shadow_MEMWB.DstRegValue = memory[Shadow_EXMEM.ALUResult] & 0x000000FF;
                    break;
                }
                case 4:
                {
                    Shadow_MEMWB.DstRegValue = memory[Shadow_EXMEM.ALUResult] & 0xFFFFFFFF;
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
                    memory[Shadow_EXMEM.ALUResult] = 0xFFFF0000 & (Shadow_EXMEM.RtValue << 16);
                    break;
                }
                case 1:
                {
                    memory[Shadow_EXMEM.ALUResult] = (0x0000FFFF & Shadow_EXMEM.RtValue);
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
                    memory[Shadow_EXMEM.ALUResult] = 0xFF000000 & (Shadow_EXMEM.RtValue << 24);
                    break;
                }
                case 1:
                {
                    memory[Shadow_EXMEM.ALUResult] = 0x00FF0000 & (Shadow_EXMEM.RtValue << 16);
                    break;
                }
                case 2:
                {
                    memory[Shadow_EXMEM.ALUResult] = 0x0000FF00 & (Shadow_EXMEM.RtValue << 8);
                    break;
                }
                case 3:
                {
                    memory[Shadow_EXMEM.ALUResult] = 0x000000FF & Shadow_EXMEM.RtValue;
                    break;
                }
                case 4:
                {
                    memory[Shadow_EXMEM.ALUResult] = 0xFFFFFFFF & Shadow_EXMEM.RtValue;
                    break;
                }
            }
        }
    }
    else
    {

    }
}
