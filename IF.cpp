int holder[4] = {0x8fc20018, 0x00021080, 0x27c30018, 0x00621021};
int memory[0x50000000];
int $pc = 0x00000000;


#include "IF.hpp"

int main()
{
    int i = 0;
    for($pc = 0; $pc < 0x50000000; $pc = $pc+4)
    {
        memory[$pc] = holder[i];
        i++;
    }
    
    for($pc = 0; $pc < 0x50000000; $pc = $pc + 4)
    {
        ex(memory[$pc]);
    }
}
