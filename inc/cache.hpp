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

    unsigned int addrtag;
    int block_address;
    int block_offset;
    int byte_offset;
    int block_bits;
    int byte_bits;

    cache (int size, int block);
    void get_tag(unsigned int addr);
    void get_block(unsigned int addr);
    void get_block_offset();
    bool is_valid();
    bool is_dirty();
    void read_cache(cache, unsigned int addr, unsigned int *data);
    void write_cache(unsigned int addr, unsigned int *blockmemdata);
};

#endif
