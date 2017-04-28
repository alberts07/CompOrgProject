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
    vector<unsigned int> data;
    vector<unsigned int> tag;
    vector<unsigned int> write_buffer;
    bool DONE;
    int cache_hit;
    int tot_block_offset;
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

    unsigned int get_tag(unsigned int);
    void get_block(unsigned int);
    void get_block_offset(unsigned int);
    bool is_valid(void);
    bool is_dirty(void);
    unsigned int read_icache(unsigned int);
    unsigned int read_dcache(unsigned int);
    void write_cache(unsigned int, unsigned int *);
};

#endif
