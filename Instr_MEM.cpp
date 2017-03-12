//
//  Instr_MEM.cpp
//  
//
//  Created by Austin Alberts on 3/11/17.
//
//

case 0: 
{   
    Shadow_EXMEM.ALUResult = 0xFF000000 & byte;
    break;
}
case 1: 
{
    Shadow_EXMEM.ALUResult = 0x00FF0000 & byte;           
    break;
}
case 2: 
{
    Shadow_EXMEM.ALUResult = 0x0000FF00 & byte;
    break;
}
case 3:
{
    Shadow_EXMEM.ALUResult = 0x000000FF & byte;
    break;
}


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
                    memory[Shadow_EXMEM.ALUResult] & 0xFFFF0000;
                    break;
                }
                case 1:
                {
                    memory[Shadow_EXMEM.ALUResult] & 0x0000FFFF;
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
                    memory[Shadow_EXMEM.ALUResult] & 0xFF000000;
                    break;
                }
                case 1:
                {
                    memory[Shadow_EXMEM.ALUResult] & 0x00FF0000;
                    break;
                }
                case 2: 
                {
                    memory[Shadow_EXMEM.ALUResult] & 0x0000FF00;
                    break;
                }
                case 3:
                {
                    memory[Shadow_EXMEM.ALUResult] & 0x000000FF;
                    break;
                }
                case 4: 
                {
                    memory[Shadow_EXMEM.ALUResult] & 0xFFFFFFFF;
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
    
    
