#include "Set.h"

Set::Set(int num_blocks) : blocks(num_blocks) {}

Block& Set::get_block(int index) {
    return blocks[index];
}




//check if correct
int Set::lru_evict() { // return index of block to evict, so in cache we can add new block at index
    uint32_t min_access_time = blocks[0].get_access_time();
    int lru_index = 0;
    int index = 0;
    for (Block& block: blocks) {
        if (block.get_access_time() < min_access_time) {    
            min_access_time = block.get_access_time();
            lru_index = index;
        }
        index++;
    }
    return lru_index;
}