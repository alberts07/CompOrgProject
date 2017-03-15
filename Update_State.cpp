
#include "Instr_IF.h"
#include "Update_State.h"

extern struct ifid Shadow_IFID;
extern struct ifid IFID;
extern struct idex Shadow_IDEX;
extern struct idex IDEX;
extern struct exmem Shadow_EXMEM;
extern struct exmem EXMEM;
extern struct memwb Shadow_MEMWB;
extern struct memwb MEMWB;

void Update_State()
{
    IFID = Shadow_IFID;
    IDEX = Shadow_IDEX;
    EXMEM = Shadow_EXMEM;
    MEMWB = Shadow_MEMWB;
}
