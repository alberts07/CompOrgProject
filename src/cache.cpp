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
  unsigned int tag_mask = (0xFFFFFFFF << (block_bits + byte_bits));
  std::cout << "Tag mask is " << tag_mask << '\n';
  addrtag = addr & tag_mask;
  return addrtag;
}

void cache::get_block(unsigned int addr){
  std::cout << "addr is " << addr << '\n';
  block_address = addr %  cache_size;
  std::cout << "block_address is " << block_address << '\n';
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

unsigned int cache::read_cache(unsigned int addr){
  addrtag = get_tag(addr);
  get_block(addr);
  get_block_offset();
  int WRITE_BACK = 0;
  if(is_valid() && tag[block_offset + block_address] == addrtag)
  {
    DONE = true;
    cache_hit++;
  }
      //else if((WRITE_BACK && dirty[block_address+block_offset]) || !WRITE_BACK){
  else //if(!WRITE_BACK)
  {
    data[block_offset+block_address] = memory[addr];
    clock_cycles = clock_cycles + MISS_PENALTY;
    //write_cache(addr, ); //need to write from memory
  }
  // else
  // {
  //     //else if((WRITE_BACK && dirty[block_address+block_offset]) || !WRITE_BACK){
  //     if((dirty[block_address+block_offset])){
  //       //write to main memory
  //       //write_cache(addr, ); //need to write from memory
  //     }
  // }
  std::cout << "Address Tag is: " << addrtag << '\n';
  std::cout << "The block offset is: "<< block_offset << '\n';
  std::cout << "Data is " << data[block_offset+block_address] << '\n';
  cache_access++;
  return data[addrtag];
}

void cache::write_cache(unsigned int *blockmemdata){
  for(int i = 0; i < block_size; i++){
    data[block_address+i] = blockmemdata[i];
  //write a whole block size to the cache data
  }
}
