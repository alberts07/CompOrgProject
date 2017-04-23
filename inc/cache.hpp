//
//  cache.hpp
//
//
//  Created by Austin Alberts on 4/16/17.
//
//
#ifndef cache_h
#define cache_h
bool WRITE_BACK = 0;
class cache{
  public:
    bool valid[];
    bool dirty[];
    int data[];
    unsigned int tag[];
    bool DONE;
    int cache_hit;
    int cache_access;
    int cache_size;
    int block_size;

    unsigned int addrtag;
    int block_address;
    int block_offset;
    int byte_offset;

    cache (int size, int block);
    unsigned int get_tag(unsigned int addr);
    unsigned int get_block(unsigned int addr);
    unsigned int get_block_offset(unsigned int addr);
    bool is_valid(unsigned int addr);
    bool is_dirty(unsigned int addr);
    void read_cache(cache, unsigned int addr, unsigned int *data);
    void write_cache(unsigned int addr, unsigned int *blockmemdata);
};

#endif
