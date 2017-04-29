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
extern bool WRITE_BACK;

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
      data[i] = -1;
      tag[i] = -1;
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
  // std::cout << "address tag is " << addrtag <<  '\n';
  return addrtag;
}

void cache::get_block(unsigned int addr){
  block_address = (addr % cache_size) / block_size; //What block # it belongs to
  // std::cout << "block address is " << block_address <<  '\n';
}

void cache::get_block_offset(unsigned int addr){
  block_offset = addr  % block_size; // Where in the block it is located
  // std::cout << "Block offset is " << block_offset << '\n';
}

bool cache::is_valid(){
  return valid[block_address]; // checks if the block is valid
}

bool cache::is_dirty(){
  return dirty[block_address]; // checks if the block is dirty
}

unsigned int cache::read_icache(unsigned int addr){
  // std::cout << "pc is " << addr << '\n';
  addrtag = get_tag(addr);
  get_block(addr);
  get_block_offset(addr);
  int validblock = is_valid();
  // std::cout << "The block is " << block_address << '\t';
  // std::cout << "The block offset is " << block_offset << '\t';
  // std::cout << "The tag is " << addrtag << '\t';

  // std::cout << "is it valid?" << validblock << '\n';
  // std::cout << "Tag value " << tag[block_offset+block_address] << '\n';
  // std::cout << "Address tag " << addrtag << '\n';
  if(validblock && tag[block_offset + block_address*block_size] == addrtag)
    // Data is already in the cache
  {
    // std::cout << "The value is already in the cache :) " << '\t';
    cache_hit++;
    // std::cout << "Number of hits is " << cache_hit << '\t';
  }
  else // Need to get it from memory
  {

    for(int i = 0; i < block_size; i++){
      // Takes in the whole block from beginning to end
      // std::cout << "i is" << i << '\n';
      // std::cout << "The location is " << i + (block_address*block_size) << '\n';
      // std::cout << "The pc loaded is " << memory[addr - block_offset + i] << '\n';
      data[i + (block_address*block_size)] = memory[addr - block_offset + i];
      tag[i + block_address*block_size] = addrtag;

      if(i == 0){
        // std::cout << "I am increasing the cycle count from " << cycle << '\n';
        cycle = cycle + MISS_PENALTY;
        // std::cout << "I am increasing the cycle count to " << cycle << '\n';
      }

      else{
        // std::cout << "I am increasing the cycle count from " << cycle << '\n';
        cycle = cycle + MISS_PENALTY2;
        // std::cout << "I am increasing the cycle count to " << cycle << '\n';
      }
      if( i == block_offset){
            MISS_PENALTY2 = 1;
      }
      // std::cout << "Setting " << block_address << "to be valid" << '\n';
    }
    MISS_PENALTY2 = 2;
    // cache_access = cache_access+ block_size - block_offset
    valid[block_address] = true;
    dirty[block_address] = false;
  }
  cache_access++;
  // std::cout << "Number of accesses is " << cache_access << '\t';
  return data[block_offset + block_address*block_size];
}


unsigned int cache::read_dcache(unsigned int addr){
  // std::cout << "pc is " << addr << '\n';
  addrtag = get_tag(addr);
  get_block(addr);
  get_block_offset(addr);
  int validblock = is_valid();
  // std::cout << "Block number is " << block_address << '\n';
  // std::cout << "Block offset is " << block_offset << '\n';

  if(validblock && tag[block_offset + block_address*block_size] == addrtag)
    // Data is already in the cache
  {
    // std::cout << "The value is already in the cache :) " << '\t';
    cache_hit++;
    cache_access++;
    return true;
  }
  else // Need to get it from memory
  {
      cache_access++;
      return false;
  }
}

unsigned int cache::mem_cache(unsigned int addr){

  addrtag = get_tag(addr);
  get_block(addr);
  get_block_offset(addr);

  // std::cout << "The value in the cache is " << data[(block_address*block_size)+block_offset] << '\n';
  // std::cout << "The tag should be " << addrtag << '\n';
  // std::cout << "The tag in the cache is " << tag[block_address] << '\n';

  for(int i=0; i < block_size; i++){
      // Takes in the whole block from beginning to end

      data[i + (block_address*block_size)] = memory[addr - block_offset + i];
      tag[i + block_address*block_size] = addrtag;

      if(i == 0){
        // std::cout << "I am increasing the cycle count from " << cycle << '\n';
        cycle = cycle + MISS_PENALTY;
        // std::cout << "I am increasing the cycle count to " << cycle << '\n';
      }

      else{
        // std::cout << "I am increasing the cycle count from " << cycle << '\n';
        cycle = cycle + MISS_PENALTY2;
        // std::cout << "I am increasing the cycle count to " << cycle << '\n';
      }
      if( i == block_offset){
            MISS_PENALTY2 = 1;
      }
      // std::cout << "Setting " << block_address << "to be valid" << '\n';
    }
    MISS_PENALTY2 = 2;


    // std::cout << "The updated values are " << data[block_address*block_size] << "\n";// << data[block_address*block_size+1] << " " << data[block_address*block_size+2] << " " << data[block_address*block_size + 3] << '\n';

    valid[block_address] = true;
    dirty[block_address] = false;
    cache_access++;
    // std::cout << "Number of accesses is " << cache_access << '\t';
    return data[block_offset + block_address*block_size];
}

void cache::write_dcache(unsigned int addr, unsigned int rt){
  //store word instructions
  addrtag = get_tag(addr);
  get_block(addr);
  get_block_offset(addr);
  int validblock = is_valid();
  if(WRITE_BACK){
    // Need to check if the cache has updated data from memory
    if(validblock && dirty[block_address]){
      // Cache is diff from memory, so need to write value back before replacing
      for(int i = 0; i < block_size; i++){
        memory[addr - block_offset + i] = data[i + (block_address*block_size)];
        if(i == 0){
          // std::cout << "I am increasing the cycle count from " << cycle << '\n';
          cycle = cycle + MISS_PENALTY;
          // std::cout << "I am increasing the cycle count to " << cycle << '\n';
        }

        else{
          // std::cout << "I am increasing the cycle count from " << cycle << '\n';
          cycle = cycle + MISS_PENALTY2;
          // std::cout << "I am increasing the cycle count to " << cycle << '\n';
        }
        if( i == block_offset){
              MISS_PENALTY2 = 1;
        }
      }
      dirty[block_address] = false;
      MISS_PENALTY2 = 2;
    }
  }

  data[(block_address*block_size) +block_offset] = rt;
  tag[block_address * block_size +block_offset] = addrtag;
  
  if(!WRITE_BACK)
  {
    for(int i = 0; i < block_size; i++){
    // Write the data given to the cache
    memory[addr+i - block_offset] = data[i + (block_address*block_size)];
    tag[i + block_address*block_size] = addrtag;
    }
  }


  valid[block_address] = true;
  dirty[block_address] = true;

  //
  // else{ //WRITE_BACK is false, using write through
  //   for(int i = 0; i < block_size; i++){
  //     // Write the data given to the write buffer
  //     data[i + (block_address*block_size)] = input[i];
  //     tag[i + block_address*block_size] = addrtag;
  //     // Also update memory at the same time
  //     memory[addr - block_offset + i] = data[i + (block_address*block_size)];
  //   }
  //   valid[block_address] = true;
  //   dirty[block_address] = false;
  // }
}
