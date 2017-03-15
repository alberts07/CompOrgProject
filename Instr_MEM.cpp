
#include "Instr_ID.hpp"
#include "Instr_IF.hpp"

extern struct idex Shadow_IDEX;
extern struct memwb Shadow_MEMWB;
extern struct exmem Shadow_EXMEM;

void Instr_MEM()
{
    if(Shadow_EXMEM.MemRead)
    {
        Shadow_MEMWB.Rt = Shadow_IDEX.Rt;
        Shadow_MEMWB.RsValue = Shadow_IDEX.RsValue;
        if(Shadow_EXMEM.half == true)
        {
            switch(Shadow_EXMEM.mem)
            {
                case 0:
                {
                    Shadow_MEMWB.RtValue = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF0000) >> 16;
                    break;
                }
                case 1:
                {
                    Shadow_MEMWB.RtValue = memory[Shadow_EXMEM.ALUResult] & 0x0000FFFF;
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
                    Shadow_MEMWB.RtValue = (memory[Shadow_EXMEM.ALUResult] & 0xFF000000)>> 24;
                    break;
                }
                case 1:
                {
                    Shadow_MEMWB.RtValue = (memory[Shadow_EXMEM.ALUResult] & 0x00FF0000) >> 16;
                    break;
                }
                case 2:
                {
                    Shadow_MEMWB.RtValue = (memory[Shadow_EXMEM.ALUResult] & 0x0000FF00) >> 8;
                    break;
                }
                case 3:
                {
                    Shadow_MEMWB.RtValue = memory[Shadow_EXMEM.ALUResult] & 0x000000FF;
                    break;
                }
                case 4:
                {
                    Shadow_MEMWB.RtValue = memory[Shadow_EXMEM.ALUResult] & 0xFFFFFFFF;
                    break;
                }
            }
        }
    }

        }
        else if (Shadow_EXMEM.MemWrite)
        {
            Shadow_MEMWB.Rt = Shadow_IDEX.Rt;
            Shadow_MEMWB.RsValue = Shadow_IDEX.RsValue;
            (Shadow_EXMEM.half == true)
            {
                switch(Shadow_EXMEM.mem)
                {
                    case 0:
                    {
                        memory[Shadow_EXMEM.ALUResult] = 0xFFFF0000 & (Shadow_MEMWB.RsValue << 16);
                        break;
                    }
                    case 1:
                    {
                        memory[Shadow_EXMEM.ALUResult] = (0x0000FFFF & Shadow_MEMWB.RsValue);
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
                        memory[Shadow_EXMEM.ALUResult] = 0xFF000000 & (Shadow_MEMWB.RsValue << 24);
                        break;
                    }
                    case 1:
                    {
                        memory[Shadow_EXMEM.ALUResult] = 0x00FF0000 & (Shadow_MEMWB.RsValue << 16);
                        break;
                    }
                    case 2:
                    {
                        memory[Shadow_EXMEM.ALUResult] = 0x0000FF00 & (Shadow_MEMWB.RsValue << 8);
                        break;
                    }
                    case 3:
                    {
                        memory[Shadow_EXMEM.ALUResult] = 0x0000FFFF & Shadow_MEMWB.RsValue;
                        break;
                    }
                    case 4:
                    {
                        memory[Shadow_EXMEM.ALUResult] = 0xFFFFFFFF & Shadow_MEMWB.RsValue;
                        break;
                    }
                }
            }
        }
        else
        {

        }
}
