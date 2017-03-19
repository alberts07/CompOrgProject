
#include "Instr_IF.h"
#include "Update_State.h"
/*
extern struct ifid Shadow_IFID, IFID;
extern struct idex Shadow_IDEX, IDEX;
extern struct exmem Shadow_EXMEM, EXMEM;
extern struct memwb Shadow_MEMWB, MEMWB;
*/
void Update_State()
{
    IFID = Shadow_IFID;
    IDEX = Shadow_IDEX;
    EXMEM = Shadow_EXMEM;
    MEMWB = Shadow_MEMWB;
}
