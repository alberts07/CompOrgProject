int holder[4] = {0x8fc20018, 0x00021080, 0x27c30018, 0x00621021};
int memory[0x50000000];
int $pc = 0x00000000;
int Reg[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


int main()
{
    for(;;)
    {
        Instr_IF();
        Instr_WB();
        Instr_ID();
        Instr_Exe();
        Instr_Mem();
    }
}
