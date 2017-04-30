
#include "Instr_IF.hpp"
#include "Update_State.hpp"

extern struct ifid Shadow_IFID, IFID, IFID_1;
extern struct idex Shadow_IDEX, IDEX, IDEX_1;
extern struct exmem Shadow_EXMEM, EXMEM, EXMEM_1;
extern struct memwb Shadow_MEMWB, MEMWB, MEMWB_1;

void Update_State()
{
    IFID_1 = IFID;
    IDEX_1 = IDEX;
    EXMEM_1 = EXMEM;
    MEMWB_1 = MEMWB;
    IFID = Shadow_IFID;
    IDEX = Shadow_IDEX;
    EXMEM = Shadow_EXMEM;
    MEMWB = Shadow_MEMWB;
}
