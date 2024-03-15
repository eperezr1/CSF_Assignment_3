#include "Cache.h"
#include <iostream>
#include <string>

Cache::Cache(int num_sets, int num_blocks, int num_bytes, std::string alloc,
             std::string through_back, std::string lru_fifo)
    : num_sets(num_sets), num_blocks(num_blocks), num_bytes(num_bytes),
      alloc(alloc), through_back(through_back), lru_fifo(lru_fifo),
      total_loads(0), total_stores(0), load_hits(0), load_misses(0),
      store_hits(0), store_misses(0), total_cycles(0), timeclock(0),
      sets(num_sets, Set(num_blocks)) // initialize sets with blocks
{}

void Cache::printStats() {
  std::cout << "Total loads: " << total_loads << "\n";
  std::cout << "Total stores: " << total_stores << "\n";
  std::cout << "Load hits: " << load_hits << "\n";
  std::cout << "Load misses: " << load_misses << "\n";
  std::cout << "Store hits: " << store_hits << "\n";
  std::cout << "Store misses: " << store_misses << "\n";
  std::cout << "Total cycles: " << total_cycles << "\n";
}

void Cache::store(uint32_t set_index, uint32_t tag) {
  // cache store method (store to memory)
  // check if block in cache has matching tag and is valid
  if (lookup(set_index, tag) == "hit") { // either write through or write back
    store_hits++;
    int block_index = get_block_index(set_index, tag);
    sets[set_index]
        .get_block(block_index)
        .update_access_ts(timeclock); // update timestamp of block

  } else { // miss
    store_misses++;
    if (alloc == "write-allocate") {
      // bring block into cache before store proceeds (same functionality as
      // load, so just call load)
      load(set_index, tag);
      total_loads--; // avoid double total_loads
    }
  }
  // check if its write-through: write to both cache and memory
  if (through_back == "write-back") {
    // write to cache only and mark block as dirty
    int block_index = get_block_index(set_index, tag);
    sets[set_index].get_block(block_index).set_dirty(true);
    total_cycles++;
  } else if (through_back == "write-through") {
    // write to both cache and memory
    total_cycles += 100; // bc we're not moving entire block
  }
  // add functionality to update lru "timestamps"
  // update cycles: stores to cache take 1 cycle, stores to memory take 100
  // cycles for every 4 bytes
  //  add in functionality to set block to valid if added to the Cache
  timeclock++;
  total_stores++;
}

// cache load method (load data from memory)
void Cache::load(uint32_t set_index, uint32_t tag) {
  // check if block in cache has matching tag and is valid (hit), else miss
  //   std::string str = lookup(set_index, tag);
  // std::cout << str;
  if (lookup(set_index, tag) == "hit") {
    // get block index and update load timestamp
    int block_index = get_block_index(set_index, tag);
    sets[set_index].get_block(block_index).update_load_ts(timeclock);
    load_hits++;
    total_cycles++; // loads from cache take 1 cycle
  } else {
    // find an empty block in the set, make into method?
    // if an empty block is found, update the block with tag and set valid to
    // true if write-back, mark block as dirty if no empty blocks, evict a
    // block, then add new block
    // get_blocks vector
    // get size of blocks_vector

    if (find_empty_block_index(set_index) == -1) { // set full
      // update tag and valid, load, and access
      int evict_index = sets[set_index].lru_evict(); // find block with lowest ts
      //if block to evict "dirty" and write-back, update main memory before "evicting"
      if (sets[set_index].get_block(evict_index).is_dirty() && through_back == "write-back") {
        total_cycles += 100 * (num_bytes / 4);
      }
      Block &new_block = sets[set_index].get_block(evict_index);
      new_block.set_tag(tag);
      new_block.set_dirty(false);
      new_block.update_access_ts(timeclock);
      new_block.update_load_ts(timeclock);
    } else { // set not full, just add block
             //   std::cout << "debugging\n";
      int block_index = find_empty_block_index(set_index);
      Block &new_block = sets[set_index].get_block(block_index);
      new_block.set_tag(tag);
      new_block.set_valid(true);
      new_block.set_dirty(false);
      new_block.update_access_ts(timeclock);
      new_block.update_load_ts(timeclock);

    }
     load_misses++;
      total_cycles += 100 * (num_bytes / 4); // loads from memory take 100 cycles per 4 bytes
  }

  total_loads++; // increment total loads
}

// TODO: implement lookup method to refactor code out of store and load
std::string Cache::lookup(uint32_t set_index, uint32_t tag) {
  Set &cache_set = sets[set_index];
  for (int i = 0; i < num_blocks;
       ++i) { // iterate through blocks in matching set to search for match
    Block &block = cache_set.get_block(i);
    // if block in matching set in Cache has matching tag and is valid
    // std::cout << "block tag = " << block.get_tag() << "\n";
    // std::cout << "tag = " << tag << "\n";
    if (block.get_tag() == tag && block.is_valid()) {
      return "hit";
    }
  }
  return "miss"; // no matching block found
}

// helper method to get block index provided index and tag
int Cache::get_block_index(uint32_t set_index, uint32_t tag) {
  Set &cache_set = sets[set_index];
  for (int i = 0; i < num_blocks; ++i) {
    Block &block = cache_set.get_block(i);
    if (block.get_tag() == tag && block.is_valid()) {
      return i;
    }
  }
  return -1; // error: block not found
}

// method to find empty block index in cache
int Cache::find_empty_block_index(uint32_t set_index) {
  Set &cache_set = sets[set_index];
  for (int i = 0; i < num_blocks; ++i) {
    Block &block = cache_set.get_block(i);
    if (!block.is_valid()) {
      return i;
    }
  }
  return -1; // cache is full
}