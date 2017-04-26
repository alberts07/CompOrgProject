
#include "Instr_ID.hpp"
#include "Instr_IF.hpp"
#include <iostream>

extern struct idex Shadow_IDEX;
extern struct memwb Shadow_MEMWB;
extern struct exmem Shadow_EXMEM;
using namespace std;

extern int memory[1200];

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
                    if((Shadow_IDEX.opcode == lh_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00008000) != 0))
                    {
                        cout << "attempting a load upper half word";
                        cout << "Mem value is " << Shadow_MEMWB.DstRegValue;
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFF0000;
                        cout << "Updated value is " << Shadow_MEMWB.DstRegValue;
                    }
                    break;
                }
                case 1:
                {
                    Shadow_MEMWB.DstRegValue = memory[Shadow_EXMEM.ALUResult] & 0x0000FFFF;
                    if((Shadow_IDEX.opcode == lh_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00008000) != 0))
                    {
                        cout << "attempting a load lower half word";
                        cout << "Mem value is " << Shadow_MEMWB.DstRegValue;
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFF0000;
                        cout << "Updated value is " << Shadow_MEMWB.DstRegValue;
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
                    Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0xFF000000)>> 24;
                    if((Shadow_IDEX.opcode == lb_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00000080) != 0))
                    {
                        cout << "attempting a load byte 0";
                        cout << "mem value is " << Shadow_MEMWB.DstRegValue;
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFFFF00;
                        cout << "Updated value is " << Shadow_MEMWB.DstRegValue;
                    }
                    break;
                }
                case 1:
                {
                    Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0x00FF0000) >> 16;
                    if((Shadow_IDEX.opcode == lb_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00000080) != 0))
                    {
                        cout << "attempting a load byte 1";
                        cout << "Byte value is " << Shadow_MEMWB.DstRegValue;
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFFFF00;
                        cout << "Updated value is " << Shadow_MEMWB.DstRegValue;
                    }
                    break;
                }
                case 2:
                {
                    Shadow_MEMWB.DstRegValue = (memory[Shadow_EXMEM.ALUResult] & 0x0000FF00) >> 8;
                    if((Shadow_IDEX.opcode == lb_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00000080) != 0))
                    {
                        cout << "attempting a load byte 2";
                        cout << "Original value is " << Shadow_MEMWB.DstRegValue;
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFFFF00;
                        cout << "Updated value is " << Shadow_MEMWB.DstRegValue;
                    }
                    break;
                }
                case 3:
                {
                    Shadow_MEMWB.DstRegValue = memory[Shadow_EXMEM.ALUResult] & 0x000000FF;
                    if((Shadow_IDEX.opcode == lb_opcode) && ((Shadow_MEMWB.DstRegValue & 0x00000080) != 0))
                    {
                        cout << "attempting a load byte 3";
                        cout << "Original value is " << Shadow_MEMWB.DstRegValue;
                        Shadow_MEMWB.DstRegValue = Shadow_MEMWB.DstRegValue | 0xFFFFFF00;
                        cout << "Updated value is " << Shadow_MEMWB.DstRegValue;
                    }
                    break;
                }
                case 4:
                {
                    cout << "attempting a load byte 4";
                    cout << "Original value is " << Shadow_MEMWB.DstRegValue;
                    Shadow_MEMWB.DstRegValue = memory[Shadow_EXMEM.ALUResult] & 0xFFFFFFFF;
                    cout << "Updated value is " << Shadow_MEMWB.DstRegValue;
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
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0x00FFFFFF) | ((0x000000FF & Shadow_EXMEM.RtValue) << 24);
                    break;
                }
                case 1:
                {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFF00FFFF) | ((0x000000FF & Shadow_EXMEM.RtValue) << 16);
                    break;
                }
                case 2:
                {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFFFF00FF) | ((0x000000FF & Shadow_EXMEM.RtValue) << 8);
                    break;
                }
                case 3:
                {
                    memory[Shadow_EXMEM.ALUResult] = (memory[Shadow_EXMEM.ALUResult] & 0xFFFFFF00) | ((0x000000FF & Shadow_EXMEM.RtValue));
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
