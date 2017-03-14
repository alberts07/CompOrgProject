#ifndef decode_hpp
#define decode_hpp


#include <vector>

std::vector<int> find_format(unsigned int);
int find_func(unsigned int);
int find_immed26(unsigned int);
short find_immed16(unsigned int);
int find_opcode(unsigned int);
int find_rd(unsigned int);
int find_rt(unsigned int);
int find_rs(unsigned int);
int find_shamt(unsigned int);






#endif
