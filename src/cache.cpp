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
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
extern unsigned int memory[1200];
extern unsigned int instr[1200];
extern unsigned int clock_cycles;
extern int MISS_PENALTY;
extern int MISS_PENALTY2;

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


  // enum STATE = {IDLE , SEARCH, WRITE, SET};

cache::cache (int size, int block) {
  cache_size = size / 4;
  block_size = block;
  valid.resize(cache_size);
  dirty.resize(cache_size);
  data.resize(cache_size);
  tag.resize(cache_size);
  for(int i = 0; i < cache_size; i++)
  {
      valid[i] = false;
      dirty[i] = false;
      data[i] = 0;
      tag[i] = 0;
  }
  DONE = false;
  cache_hit = 0;
  cache_access = 0;
  addrtag = 0;
  block_address = 0;
  block_offset = 0;
  block_bits = log(cache_size / block_size) / log(2);    //log2 (x) = logy (x) / logy (2)
  byte_bits = 2;
}

unsigned int cache::get_tag(unsigned int addr){
  unsigned int tag_mask = (0xFFFFFFFF << block_bits);
  addrtag = addr & tag_mask;
  std::cout << "address tag is " << addrtag <<  '\n';
  return addrtag;
}

void cache::get_block(unsigned int addr){
  block_address = addr %  cache_size;
  std::cout << "block address is " << block_address <<  '\n';
}

void cache::get_block_offset(){
  block_offset = block_address % block_size;
}

bool cache::is_valid(){
  return valid[block_address];
}

bool cache::is_dirty(){
  return dirty[block_address];
}

unsigned int cache::read_cache(unsigned int addr){
  std::cout << "pc is " << addr << '\n';
  addrtag = get_tag(addr);
  get_block(addr);
  get_block_offset();
  int validblock = is_valid();
  int WRITE_BACK = 0;
  if(validblock && tag[block_offset + block_address] == addrtag)
  {
    std::cout << "The value is already in the cache :) " << '\n';
    DONE = true;
    cache_hit++;
    std::cout << "Number of hits is " << cache_hit << '\n';
  }
      //else if((WRITE_BACK && dirty[block_address+block_offset]) || !WRITE_BACK){
  else //if(!WRITE_BACK)
  {

    for(int i= 0; i < block_size; i++){
      data[block_offset+block_address] = memory[addr];
      tag[block_offset + block_address] = addrtag;

      if( i == block_size - 1){
        valid[block_address] = true;
      }

      if(i == 0){
        std::cout << "I am increasing the cycle count from " << clock_cycles << '\n';
        clock_cycles = clock_cycles + MISS_PENALTY;
        std::cout << "I am increasing the cycle count to " << clock_cycles << '\n';
      }

      else{
        std::cout << "I am increasing the cycle count from " << clock_cycles << '\n';
        clock_cycles = clock_cycles + MISS_PENALTY2;
        std::cout << "I am increasing the cycle count to " << clock_cycles << '\n';
      }

    //write_cache(addr, ); //need to write from memory
    }
  }
  // else
  // {
  //     //else if((WRITE_BACK && dirty[block_address+block_offset]) || !WRITE_BACK){
  //     if((dirty[block_address+block_offset])){
  //       //write to main memory
  //       //write_cache(addr, ); //need to write from memory
  //     }
  // }
  // std::cout << "Address Tag is: " << addrtag << '\n';
  // std::cout << "The block offset is: "<< block_offset << '\n';
  cache_access++;
  std::cout << "Number of accesses is " << cache_access << '\n';
  return data[block_offset + block_address];
}

void cache::write_cache(unsigned int *blockmemdata){
  for(int i = 0; i < block_size; i++){
    data[block_address+i] = blockmemdata[i];
  //write a whole block size to the cache data
  }
}
