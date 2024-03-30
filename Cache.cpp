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
  // check if block in cache has matching tag and is valid
  if (lookup(set_index, tag) == "hit") {
    store_hits++;
    int block_index = get_block_index(set_index, tag);
    sets[set_index].get_block(block_index).update_access_ts(timeclock); // update timestamp of block
  } else { // miss
    store_misses++;
    if (alloc == "write-allocate") {
      // bring block into cache before store proceeds (same functionality as load, so just call load)
      load(set_index, tag);
      load_misses--;
      total_loads--; // avoid double total_loads
    } 
  }
  // check if its write-through: write to both cache and memory
  if (through_back == "write-back") {
    // write to cache only and mark block as dirty
    int block_index = get_block_index(set_index, tag);
    sets[set_index].get_block(block_index).set_dirty(true); 
    total_cycles++; // cache only
  } else if (through_back == "write-through") {
    // write to memory
    total_cycles += 100; // bc we're not moving entire block
  }
  timeclock++;
  total_stores++;
}

void Cache::load(uint32_t set_index, uint32_t tag) {
  // check if block in cache has matching tag and is valid (hit), else miss
  if (lookup(set_index, tag) == "hit") {
    // get block index and update load and access timestamps
    int block_index = get_block_index(set_index, tag);
    //sets[set_index].get_block(block_index).update_load_ts(timeclock); // commented out bc causing error with fifo
    sets[set_index].get_block(block_index).update_access_ts(timeclock);
    load_hits++;
    total_cycles++; // loads from cache take 1 cycle
  } else {
    if (find_empty_block_index(set_index) == -1) { // set full
      // update tag and valid, load, and access
      int evict_index;
      if (lru_fifo == "lru") { // check type
        evict_index = sets[set_index].lru_evict(); // find block with lowest access ts
      } else if (lru_fifo == "fifo") {
        evict_index = sets[set_index].fifo_evict();
      }
      // if block to evict "dirty" and write-back, update main memory before "evicting"
      if (sets[set_index].get_block(evict_index).is_dirty() && through_back == "write-back") {
        total_cycles += 100 * (num_bytes / 4);
      }
      //update block at evict_index to be new block
      Block &new_block = sets[set_index].get_block(evict_index);
      new_block.set_tag(tag);
      new_block.set_dirty(false);
      new_block.update_access_ts(timeclock);
      new_block.update_load_ts(timeclock);
    } else { // set not full, just add block at empty index
      int block_index = find_empty_block_index(set_index);
      //update block at the empty to be new block
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
  timeclock++;
  total_loads++; // increment total loads
}

std::string Cache::lookup(uint32_t set_index, uint32_t tag) {
  Set &cache_set = sets[set_index];
  for (int i = 0; i < num_blocks; ++i) { // iterate through blocks in matching set to search for match
    Block &block = cache_set.get_block(i);
    // if block in matching set in Cache has matching tag and is valid
    if (block.get_tag() == tag && block.is_valid()) {
      return "hit";
    }
  }
  return "miss"; // no matching block found
}

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

int Cache::find_empty_block_index(uint32_t set_index) {
  Set &cache_set = sets[set_index];
  for (int i = 0; i < num_blocks; ++i) {
    Block &block = cache_set.get_block(i);
    if (!block.is_valid()) { // only check that block is not valid
      return i;
    }
  }
  return -1; // cache is full
}