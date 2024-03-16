#ifndef SET_H
#define SET_H

#include "Block.h"
#include <vector>

class Set {
  private:
    std::vector<Block> blocks;
    int num_blocks; 

  public:
    //Set constructor, initializes blocks vector with num_blocks elements
    Set(int num_blocks);
    
    // Returns block at index 'index' of blocks vector
    // Returns:
    // Block at index index of the set
    Block& get_block(int index);

  // Iterates through blocks in set, finds the block with the lowest
  //   access timestamp, and returns the index of that block
  // Returns:
  //   index of block to evict
    int lru_evict();

  

};

#endif