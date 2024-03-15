#ifndef SET_H
#define SET_H

#include "Block.h"
#include <vector>

class Set {
  private:
    std::vector<Block> blocks;
    int num_blocks; //new, added for add_block

  public:
    //Set constructor
    Set(int num_blocks);
    
    //get block method?
    Block& get_block(int index);

    void add_block(uint32_t tag); // add new block to current set and lru evict logic?

    int lru_evict();

  

};

#endif