//
//  Instr_MEM.cpp
//  
//
//  Created by Austin Alberts on 3/11/17.
//
//
void Instr_Mem()
{
    if(Shadow_EXMEM.MemRead)
    {
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
            
                
        }
        else
        {
        
        }
}
    
    
