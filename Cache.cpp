#include <string>
#include <iostream>
#include "Cache.h"

Cache::Cache(int num_sets,  int num_blocks, int num_bytes, std::string alloc, std::string through_back, std::string lru_fifo)
    :   num_sets(num_sets),
        num_blocks(num_blocks),
        num_bytes(num_bytes),
        alloc(alloc),
        through_back(through_back),
        lru_fifo(lru_fifo),
        total_loads(0),
        total_stores(0),
        load_hits(0),
        load_misses(0),
        store_hits(0),
        store_misses(0),
        total_cycles(0),
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
//cache store method (store to memory)
    //check if block in cache has matching tag and is valid (refactor into lookup method, which returns hit or miss)
    //if cache hit, increment total store hits, update lru "timestamps"
    //if its a miss
         //check if its write-allocate. If yes, bring block into the cache before store proceeds
        // increment total store misses

    //check if its write-through: write to both cache and memory
    //if write-back: write to cache only and mark block as dirty
    
    //update cycles: stores to cache take 1 cycle, stores to memory take 100 cycles for every 4 bytes
    //increment total_stores
    total_stores++;
}

void Cache::load(uint32_t set_index, uint32_t tag) {
   
//cache load method (load data from memory)
    //check if block in cache has matching tag and is valid (hit), else miss (refactor into lookup method, which returns hit or miss)
        //if hit
            //update lru "timestamps",  increment load hits

         //else increment load_misses 

    //update cycles: loads from cache take 1 cycle, loads from memory take 100 cycles for every 4 bytes
    //increment total loads
    total_loads++;
}


//TODO: implement lookup method to refactor code out of store and load

//TODO: add lru logic (method?)

