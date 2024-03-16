#ifndef CACHE_H
#define CACHE_H

#include "Set.h"
#include <string>
#include <vector>

class Cache {
private: 
  int num_sets;
  int num_blocks;
  int num_bytes;
  std::string alloc;
  std::string through_back;
  std::string lru_fifo;

  // stats
  int total_loads;
  int total_stores;
  int load_hits;
  int load_misses;
  int store_hits;
  int store_misses;
  int total_cycles;
  uint32_t timeclock;
  
  // cache is represented as a vector containing sets
  std::vector<Set> sets;
  

public:
  
  // constructor for Cache, sets cache attributes to provided values
  // Parameters:
  //  num_sets - number of sets in cache
  //  num_blocks - number of blocks in each set
  //  num_bytes - number of bytes in each block
  //  alloc - stores whether cache if wriye-allocate or no-write-allocate
  //  through_back - stores whether cache is write-through or write-back
  //  lru_fifo - stores whether cache is least recently used (lru) or first in first out (fifo)
  Cache(int num_sets, int num_blocks, int num_bytes, std::string alloc,
        std::string through_back, std::string lru_fifo);

  // prints all the stats variables in necessary format
  void printStats();

  // loads a block into cache
  // Parameters:
  //  set_index - index of set in cache's sets vector
  //  tag - identifier for a block
  void load(uint32_t set_index, uint32_t tag);
  
  // writes to cache and/or memory
  // Parameters:
  //  set_index - index of set in cache's sets vector
  //  tag - identifier for a block
  void store(uint32_t set_index, uint32_t tag);

  // searches for block in set with set_index with matching tag
  // Parameters:
  //  set_index - index of set in cache's sets vector
  //  tag - identifier for a block
  // Returns:
  //  "hit" - matching block was found
  //  "miss" - matching block not found
  std::string lookup(uint32_t set_index, uint32_t tag);

  // finds block with matching tag within a set
  // Parameters:
  //  set_index - index of set in cache's sets vector
  //  tag - identifier for a block
  // Returns:
  //  index of block or -1 if not found
  int get_block_index(uint32_t set_index, uint32_t tag);

  // finds the index of the first empty block in a set by searching for a block
  // marked as not valid
  // Parameters:
  //  set_index - index of set in cache's sets vector
  // Returns:
  //  index of empty block in the set
  int find_empty_block_index(uint32_t set_index);

};

#endif