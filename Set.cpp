#include "Set.h"

Set::Set(int num_blocks) : blocks(num_blocks) {}

Block& Set::get_block(int index) {
    return blocks[index];
}

int Set::lru_evict() { 
    uint32_t min_access_time = blocks[0].get_access_time();
    int lru_index = 0;
    int index = 0;
    for (Block& block: blocks) { // iterate through block vector
        if (block.get_access_time() < min_access_time) {    
            min_access_time = block.get_access_time(); // update min_access_time when we find new min
            lru_index = index;
        }
        index++;
    }
    return lru_index; // index of least recently used block (to be evicted)
}

int Set::fifo_evict() { // find block with min insertion time (load ts)
    uint32_t min_load_time = blocks[0].get_load_time();
    int fifo_index = 0;
    int index = 0;
    for (Block& block: blocks) { // iterate through block vector
        if (block.get_load_time() < min_load_time) {    
            min_load_time = block.get_load_time(); // update min_access_time when we find new min
            fifo_index = index;
        }
        index++;
    }
    return fifo_index; // index of least recently used block (to be evicted)
}
