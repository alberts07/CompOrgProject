//
//  cache.hpp
//
//
//  Created by Austin Alberts on 4/16/17.
//
//

#include <vector>
#ifndef cache_h
#define cache_h
using namespace std;
class cache{
  public:

    vector<bool> valid;
    vector<bool> dirty;
    vector<int> data;
    vector<unsigned int> tag;
    bool DONE;
    int cache_hit;
    int cache_access;
    int cache_size;
    int block_size;
    unsigned int addr;
    unsigned int addrtag;
    int block_address;
    int block_offset;
    int byte_offset;
    int block_bits;
    int byte_bits;

    cache (int size, int block);
    unsigned int get_tag(void);
    unsigned int get_block(void);
    unsigned int get_block_offset(void);
    bool is_valid(void);
    bool is_dirty(void);
    unsigned int read_cache(void);
    void write_cache(unsigned int *blockmemdata);
};

#endif
