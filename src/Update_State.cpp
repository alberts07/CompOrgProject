
#include "Instr_IF.hpp"
#include "Update_State.hpp"

extern struct ifid Shadow_IFID, IFID, IFID_1;
extern struct idex Shadow_IDEX, IDEX, IDEX_1;
extern struct exmem Shadow_EXMEM, EXMEM, EXMEM_1;
extern struct memwb Shadow_MEMWB, MEMWB, MEMWB_1;

void Update_State()
{
    IFID_1 = IFID;          //Two states behind next state
    IDEX_1 = IDEX;          //Two states behind next state
    EXMEM_1 = EXMEM;        //Two states behind next state
    MEMWB_1 = MEMWB;        //Two states behind next state
    IFID = Shadow_IFID;     //One state behind next state
    IDEX = Shadow_IDEX;     //One state behind next state
    EXMEM = Shadow_EXMEM;   //One state behind next state
    MEMWB = Shadow_MEMWB;   //One state behind next state
}
