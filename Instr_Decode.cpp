//
//  Single_Cycle.cpp
//  
//
//  Created by Drew Lockwood on 3/1/17.
//
//
#include "Instr_Decode.hpp"
#include "IF.hpp"

std::vector<int> Instr_Decode(unsigned int instr)
{
    std::vector<int> format = find_format(instr);
    if(format[0] == rtype)
    {
        Shadow_IDEX.Rs = find_rs(Shadow_IFID.instr);
        Shadow_IDEX.Rt = find_rt(Shadow_IFID.instr);
        Shadow_IDEX.Rd = find_rd(Shadow_IFID.instr);
        Shadow_IDEX.shamt = find_shamt(Shadow_IFID.instr);
    } 
         
    if(format[0] == itype)
    {
        Shadow_IDEX.immed16 = find_immed16(Shadow_IFID.instr);
        Shaodw_IDEX.Rs = find_rs(Shadow_IFID.instr);
        Shadow_IDEX.Rt = find_rt(Shadow_IFID.instr);
    }  
    if(format[0] == jtype)
    {
        Shadow_IDEX.immed26 = find_immed26(Shadow_IFID.instr);
           
    }
    /*
    if(format[0] == special_opcode1l)
    {
        Shadow_IDEX.Rs = find_rs(Shadow_IFID.instr);
        Shadow_IDEX.RsValue = Reg[Shadow_IDEX.Rs];
        Shadow_IDEX.Rt = find_rt(Shadow_IFID.instr);
        Shadow_IDEX.RtValue = Reg[Shadow_IDEX.Rt];
        Shadow_IDEX.Rd = find_rd(Shadow_IFID.instr);
        Shadow_IDEX.RdValue = Reg[Shadow_IDEX.Rd];             
        Shadow_IDEX.shamt = find_shamt();       
        switch(format[2])
        {
            case: clo_func
            {
                clo();      
                break;
            }
            case: clz_func
            {
                clz();      
                break;
            }
            case: mul_func
            {
                mul();
                break;
            }
            case: madd_func
            {
                madd();
                break;
            }
            case: maddu_func
            {
                maddu();      
                break;
            }
            case: msub_func
            {
                msub();
                break;
            }
            case: msubu_func
            {
                msubu();
                break;
            }
        }
    } 
    if(format[0] == special_opcode2l)
    {
        Shadow_IFID.immed16 = find_immed16(Shadow_IFID.instr);
        Shadow_IDEX.immed16 = Shadow_IFID.immed16;
        Shadow_IDEX.Rs = find_rs(Shadow_IFID.instr);
        Shadow_IDEX.RsValue = Reg[Shadow_IDEX.Rs];  
        switch(format[2])
        {
            case: bclt_func
            {
                bclt();
                break;
            }
            case: bclf_func
            {
                bclf();
                break;
            }
        }
    }
    if(format[0] == special_opcode3l)
    {
        Shadow_IFID.immed16 = find_immed16(Shadow_IFID.instr);
        Shadow_IDEX.immed16 = Shadow_IFID.immed16;
        Shadow_IDEX.Rs = find_rs(Shadow_IFID.instr);
        Shadow_IDEX.RsValue = Reg[Shadow_IDEX.Rs];   
        switch(format[2])
        {
            case: bgez_func
            {
                bgez();
                break;
            }
            case: bgezal_func
            {
                bgezal();
                break;
            }
            case: bltz_func
            {
                bltz();
                break;
            }
            case: bltzal_func
            {
                bltzal();
                break;
            }
            case: teqi_func
            {
                teqi();
                break;
            }
            case: tnei_func
            {
                tnei();
                break;
            }  
            case: tgei_func
            {
                tgei();
                break;
            }
            case: tgeiu_func
            {
                tgeiu();
                break;
            }    
            case: tlti_func
            {
                tlti();
                break;
            }
            case: tltiu_func
            {
                tltiu();
                break;
            }    
        }
    }*/
    }
}
        
        
    
        

                
 
 
