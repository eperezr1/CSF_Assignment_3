#ifndef SET_H
#define SET_H

#include "Block.h"
#include <vector>

class Set {
  private:
    std::vector<Block> blocks;

  public:
    //Set constructor
    Set(int num_blocks);
    
    //get block method?
    Block& get_block(int index);
};

#endif