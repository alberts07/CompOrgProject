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
extern unsigned int cycle;
extern int MISS_PENALTY;
extern int MISS_PENALTY2;
int WRITE_BACK = 0;

cache::cache (int size, int block) {
  cache_size = size / 4; // Words we can store
  block_size = block;  // Number of words in a block
  valid.resize(cache_size / block_size); // true if data in that cache block
  dirty.resize(cache_size / block_size); // true cache block doesn't match memory
  data.resize(cache_size); // data in the cache
  tag.resize(cache_size); // tag in the location
  for(int i = 0; i < cache_size  / block_size; i++) // Initialization
  {
      valid[i] = false;
      dirty[i] = false;
      data[i] = 0;
      tag[i] = 0;
  }
  cache_hit = 0;
  cache_access = 0;
  addrtag = 0;
  block_address = 0;
  block_offset = 0;
  tot_block_offset = log(block_size) / log(2);
  block_bits = log(cache_size / block_size) / log(2); // # of bits to get block #
  byte_bits = 2;  //This will always be 2 because we are word aligned
}

unsigned int cache::get_tag(unsigned int addr){
  unsigned int tag_mask = (0xFFFFFFFF << (block_bits + tot_block_offset)); //Tag only upper bits above block and byte offset
  addrtag = addr & tag_mask; //Tag that gets placed in tag vector
  std::cout << "address tag is " << addrtag <<  '\n';
  return addrtag;
}

void cache::get_block(unsigned int addr){
  block_address = (addr % cache_size) / block_size; //What block # it belongs to
  std::cout << "block address is " << block_address <<  '\n';
}

void cache::get_block_offset(unsigned int addr){
  block_offset = addr  % block_size; // Where in the block it is located
  std::cout << "Block offset is " << block_offset << '\n';
}

bool cache::is_valid(){
  return valid[block_address]; // checks if the block is valid
}

bool cache::is_dirty(){
  return dirty[block_address]; // checks if the block is dirty
}

unsigned int cache::read_cache(unsigned int addr){
  std::cout << "pc is " << addr << '\n';
  addrtag = get_tag(addr);
  get_block(addr);
  get_block_offset(addr);
  int validblock = is_valid();
  std::cout << "is it valid?" << validblock << '\n';
  std::cout << "Tag value " << tag[block_offset+block_address] << '\n';
  std::cout << "Address tag " << addrtag << '\n';
  if(validblock && tag[block_offset + block_address] == addrtag)
    // Data is already in the cache
  {
    std::cout << "The value is already in the cache :) " << '\n';
    cache_hit++;
    std::cout << "Number of hits is " << cache_hit << '\n';
  }
  else // Need to get it from memory
  {

    for(int i = 0; i < block_size; i++){
      // Takes in the whole block from beginning to end
      std::cout << "i is" << i << '\n';
      std::cout << "The location is " << i + (block_address*block_size) << '\n';
      std::cout << "The pc loaded is " << memory[addr - block_offset + i] << '\n';
      data[i + (block_address*block_size)] = memory[addr - block_offset + i];
      tag[i + block_address] = addrtag;

      if(i == 0){
        std::cout << "I am increasing the cycle count from " << cycle << '\n';
        cycle = cycle + MISS_PENALTY;
        std::cout << "I am increasing the cycle count to " << cycle << '\n';
      }

      else{
        std::cout << "I am increasing the cycle count from " << cycle << '\n';
        cycle = cycle + MISS_PENALTY2;
        std::cout << "I am increasing the cycle count to " << cycle << '\n';
      }
      std::cout << "Setting " << block_address << "to be valid" << '\n';
      valid[block_address] = true;
    }
  }
  cache_access++;
  std::cout << "Number of accesses is " << cache_access << '\n';
  return data[block_offset + block_address];
}

void cache::write_cache(addr, unsigned int *data){
  addrtag = get_tag(addr);
  get_block(addr);
  get_block_offset(addr);
  int validblock = is_valid();
  unsigned int write_buffer[block_size] = {0};
  for(int i=0; i < block_size; i++){
    write_buffer[i] = data - block_offset + i;
  }
  if(WRITE_BACK){
    // Need to check if the cache has updated data from memory
    if(validblock && dirty[block_address]){
      // Cache is diff from memory, so need to write value back before replacing
      for(int i = 0; i < block_size; i++){
        memory[addr - block_offset + i] = data[i + (block_address*block_size)];
      }

      for(int i = 0; i < block_size; i++){
        // Write the data given to the write buffer
        data[i + (block_address*block_size)] = writebuffer[i];
        tag[i + block_address] = addrtag;
      }
      valid[block_address] = true;
      dirty[block_address] = false;
    }
    else{
      for(int i = 0; i < block_size; i++){
        // Write the data given to the write buffer
        data[i + (block_address*block_size)] = writebuffer[i];
        tag[i + block_address] = addrtag;
      }
      valid[block_address] = true;
      dirty[block_address] = true;
    }
    //SHOULD WRITE CHECK TO SEE IF WHAT IT IS WRITING IS ALREADY IN THE CACHE?
  }
  else{ //WRITE_BACK is false, using write through
    for(int i = 0; i < block_size; i++){
      // Write the data given to the write buffer
      data[i + (block_address*block_size)] = writebuffer[i];
      tag[i + block_address] = addrtag;
      // Also update memory at the same time
      memory[addr - block_offset + i] = data[i + (block_address*block_size)];
    }
    valid[block_address] = true;
    dirty[block_address] = false;
  }
}
