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

// int icache128[32] = {0};
// int icache64[16] = {0};
// bool valid_icache128[32] = {false};
// bool valid_icache64[16] = {false};
// bool dirty_icache128[32] = {false};
// bool dirty_icache64[16] = {false};
//
// #define WRITETHROUGH 0
// int dcache1024[256] = {0};
// int dcache256[64] = {0};
// bool valid_dcache1024[256] = {false};
// bool valid_dcache256[64] = {false};
// bool dirty_dcache1024[256] = {false};
// bool dirty_dcache256[64] = {false};
//
// extern unsigned int clock_cycles;
// extern struct ifid  Shadow_IFID;
//
// void icache(unsigned int instruction, int cache_size, int block_size){
//
//   int block_offset = log2(block_size) + 2;
//   std::cout << "The block_offset is " << block_offset << '\n';
//   int block_number = (instruction >> 2)/ block_offset;
//   std::cout << "The block_number is " << block_number << '\n';
//   int offset = block_number % block_size;
//   std::cout << "The offset is " << offset << '\n';
//   int tag = instruction >> ((int)log2(block_size) - (int) log2(cache_size/4 / block_size));
//
//   std::cout << "The tag is " << tag << '\n';
//   if (cache_size == 128){
//     if(icache128[offset] != tag){
//       //////////////////////
//       //Shadow_IFID.pcplus1 = Shadow_IFID.pcplus1 - 1; //Is this the right register?
//       //////////////////////
//       if(!WRITETHROUGH){
//         if(dirty_icache128[offset]){
//           //todo place in the code to write to memory
//           // do we set the value we are updating to in memory since we are already there?
//           //dirty_icache128[offset] = false;
//         }
//         std::cout << icache128[50] << '\n';
//         std::cout << icache128[66] << '\n';
//         std::cout << valid_icache128[74] << '\n';
//
//         std::cout << "The problem is coming" << '\n';
//
//         dirty_icache128[offset] = true;
//
//         std::cout << icache128[50] << '\n';
//         std::cout << icache128[66] << '\n';
//         std::cout << valid_icache128[74] << '\n';
//         std::cout << "dirty_icache128 of " << offset << " has been updated" << '\n';
//       }
//
//       else{
//         std::cout << "Shouldnt be here" << '\n';
//         icache128[offset] = tag;
//         //todo place in the code to write to memory
//       }
//
//       std::cout << "icache128 of " << offset << " has been updated" << '\n';
//       icache128[offset] = tag;
//       std::cout << "valid_icache128 of " << offset << " has been updated" << '\n';
//       valid_icache128[offset] = true;
//     }
//   }
//
//   else if (cache_size == 64){
//     std::cout << "Shouldnt be here" << '\n';
//
//     if(icache64[offset] != tag){
//       //////////////////////
//       //Shadow_IFID.pcplus1 = Shadow_IFID.pcplus1 - 1; //Is this the right register?
//       //////////////////////
//       if(!WRITETHROUGH){
//         if(dirty_icache64[offset]){
//           //todo place in the code to write to memory
//           // do we set the value we are updating to in memory since we are already there?
//           //dirty_icache128[offset] = false;
//         }
//
//         dirty_icache64[offset] = true;
//       }
//       else{
//         icache64[offset] = tag;
//         //todo place in the code to write to memory
//       }
//       icache64[offset] = tag;
//       valid_icache64[offset] = true;
//     }
//   }
//   else std::cout << "The cache size is not valid enter 64 or 128";
//   for(int i=0;i<cache_size;i++){
//     if(icache128[i])
//       std::cout << "The icache of " << i << " is " << icache128[i] <<'\n';
//     if(valid_icache128[i])
//       std::cout << "The valid bits of " << i << " is " << valid_icache128[i] <<'\n';
//     if(dirty_icache128[i])
//       std::cout << "The dirty bits of " << i << " is " << dirty_icache128[i] <<'\n';
//   }
// }
//
//
// void dcache(unsigned int memory, int cache_size, int block_size){
//   int block_offset = log(block_size) + 2;
//   int block_number = memory / block_offset;
//   int offset = block_number % block_size;
//   int tag = memory >> ((int) log2(block_size) - (int) log2(cache_size/4 / block_size));
//   if (cache_size == 256){
//     if(dcache256[offset] != tag){
//       //////////////////////
//       //Shadow_IFID.pcplus1 = Shadow_IFID.pcplus1 - 1; //Is this the right register?
//       //////////////////////
//       if(!WRITETHROUGH){
//         if(dirty_dcache256[offset]){
//           //todo place in the code to write to memory
//           // do we set the value we are updating to in memory since we are already there?
//           //dirty_dcache128[offset] = false;
//         }
//         dirty_dcache256[offset] = true;
//       }
//
//       else{
//         dcache256[offset] = tag;
//         //todo place in the code to write to memory
//       }
//       dcache256[offset] = tag;
//       valid_dcache256[offset] = true;
//     }
//   }
//   else if (cache_size == 1024){
//     if(dcache1024[offset] != tag){
//       //////////////////////
//       //Shadow_IFID.pcplus1 = Shadow_IFID.pcplus1 - 1; //Is this the right register?
//       //////////////////////
//       if(!WRITETHROUGH){
//         if(dirty_dcache1024[offset]){
//           //todo place in the code to write to memory
//           // do we set the value we are updating to in memory since we are already there?
//           //dirty_dcache128[offset] = false;
//         }
//         dirty_dcache1024[offset] = true;
//       }
//
//       else{
//         dcache1024[offset] = tag;
//         //todo place in the code to write to memory
//       }
//       dcache1024[offset] = tag;
//       valid_dcache1024[offset] = true;
//     }
//   }
//   else std::cout << "The cache size is not valid enter 1024 or 256";
// }
//
// switch (CACHE_STATE){
//     case IDLE:
//         if(REQUEST){
//            CACHE_STATE = SEARCH;
//         }
//         break;
//     case SEARCH:
//         //todo update dummy variables
//         if(valid && cachetag == tag){
//             //update data with correct location
//             cache_hit = true;
//         }
//         if(dirty){
//           //need to write to memory
//           CACHE_STATE = WRITE;
//         }
//     case WRITE:
//         //need to stall for penalty time
// }




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

cache::get_tag(unsigned int addr){
  tag_mask= 0xFFFFFFFF<<(block_offset + byte_offset);
  addrtag = addr & tag_mask;
}

cache::get_block(unsigned int addr){
  block_address = addr /  block_size;
}

cache::get_block_offset(unsigned int addr){
  return get_block(addr) % block_size;
}

cache::is_valid(unsigned int addr){
  return valid[get_tag(addr)];
}

cache::is_dirty(unsigned int addr){
  return dirty[get_tag(addr)];
}

cache::write_cache(unsigned int addr, unsigned int *blockmemdata){
  for(int i = 0; i < block_size; i++){
    data[block_address+i] = blockmemdata[i];
  //write a whole block size to the cache data
  }
}

cache::read_cache(cache, unsigned int addr, unsigned int *data){
  if(cache.is_valid[addr] && cache.tag[block_address+block_offset] == get_tag(addr)){
    *data = cache.data[get_tag(addr)];
    DONE = true;
    cache_hit++;
  }
  else if((WRITE_BACK && dirty[]) || !WRITE_BACK){
    //write to main memory
    write_cache(addr); //need to write from memory
  }
  cache_access++;
}
