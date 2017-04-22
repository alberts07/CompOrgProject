//
//  Instr_cache.cpp
//
//
//  Created by Austin Alberts on 4/16/17.
//
//
#include "cache.hpp"
#include <iostream>
#include <math.h>

// switch(STATE){
//   case IDLE:
//     //Need to check if there is a request
//     if(REQUEST){
//       STATE = SEARCH;
//     }
//   case SEARCH:
//     get_tag();
//     get_index();
//     get_block();
//     read_cache();
//     if(DONE){
//       STATE = IDLE;
//     }
//     if(WRITE_BACK){
//       STATE = WRITE;
//     }
//   case WRITE:
//     //More details
//
//   case SET:
//
// }



  // bool valid[];
  // bool dirty[];
  // int data[];
  // unsigned int tag[];
  // enum STATE = {IDLE , SEARCH, WRITE, SET};
  // bool DONE = false;
  // int cache_hit = 0;
  // int cache_access = 0;
  // int cache_size = 0;
  // int block_size = 0;
  //
  // unsigned int tag = 0;
  // int block_address = 0;
  // int block_offset = 0;
  // int byte_offset = 2;

cache::cache (int size, int block) {
  cache_size = size;
  block_size = block;
  valid[cache_size] = {false};
  dirty[cache_size] = {false};
  data[cache_size] = {0};
  tag[cache_size] = {0};
  DONE = false;
  cache_hit = 0;
  cache_access = 0;
  addrtag = 0;
  block_address = 0;
  block_offset = cache_size / block_size;
  byte_offset = 2;
}

unsigned int cache::get_tag(unsigned int addr){
  unsigned int tag_mask= 0xFFFFFFFF<<(block_offset + byte_offset);
  addrtag = addr & tag_mask;
}

unsigned int cache::get_block(unsigned int addr){
  block_address = addr /  block_size;
}

unsigned int cache::get_block_offset(unsigned int addr){
  return get_block(addr) % block_size;
}

bool cache::is_valid(unsigned int addr){
  return valid[get_tag(addr)];
}

bool cache::is_dirty(unsigned int addr){
  return dirty[get_tag(addr)];
}

void cache::write_cache(unsigned int addr, unsigned int *blockmemdata){
  for(int i = 0; i < block_size; i++){
    data[block_address+i] = blockmemdata[i];
  //write a whole block size to the cache data
  }
}

void cache::read_cache(cache, unsigned int addr, unsigned int *data){
  if(valid[addr] && tag[block_address+block_offset] == get_tag(addr)){
    *data = data[get_tag(addr)];
    DONE = true;
    cache_hit++;
  }
  else if((WRITE_BACK && dirty[block_address+block_offset]) || !WRITE_BACK){
    //write to main memory
    //write_cache(addr, ); //need to write from memory
  }
  cache_access++;
}
