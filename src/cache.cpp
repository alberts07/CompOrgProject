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
#include <string.h>

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
  memset(valid,false,cache_size);
  memset(dirty,false,cache_size);
  memset(data,false,cache_size);
  memset(tag,false,cache_size);
  DONE = false;
  cache_hit = 0;
  cache_access = 0;
  addrtag = 0;
  block_address = 0;
  block_offset = 0;
  //block_bits = (int) log2(cache_size / block_size);
  byte_bits = 2;
}

void cache::get_tag(unsigned int addr){
  unsigned int tag_mask= 0xFFFFFFFF<<(block_bits + byte_bits);
  addrtag = addr & tag_mask;
}

void cache::get_block(unsigned int addr){
  block_address = addr /  block_size;
}

void cache::get_block_offset(){
  block_offset = block_address % block_size;
}

bool cache::is_valid(){
  return valid[addrtag];
}

bool cache::is_dirty(){
  return dirty[addrtag];
}

void cache::write_cache(unsigned int addr, unsigned int *blockmemdata){
  for(int i = 0; i < block_size; i++){
    data[block_address+i] = blockmemdata[i];
  //write a whole block size to the cache data
  }
}

void cache::read_cache(cache, unsigned int addr, unsigned int *data){
  if(valid[addr] && tag[block_address+block_offset] == addrtag){
    *data = data[addrtag];
    DONE = true;
    cache_hit++;
  }
  //else if((WRITE_BACK && dirty[block_address+block_offset]) || !WRITE_BACK){
  else if((dirty[block_address+block_offset])){
    //write to main memory
    //write_cache(addr, ); //need to write from memory
  }
  cache_access++;
}
