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
    //check if block in cache has matching tag and is valid 
    if (lookup(set_index, tag) == "hit") {
        store_hits++;
        //if its a hit, can we return here?
        //update lru
    } else { //miss
        store_misses++;
        if (alloc == "write-allocate") {
            //bring block into cache before store proceeds
        }
    
    }
    //check if its write-through: write to both cache and memory
    if (through_back == "write-back") {
        //write to cache only and mark block as dirty
        total_cycles++;
    } else if (through_back == "write-through") {
        //write to both cache and memory
        total_cycles += 100;
    }
    //add functionality to update lru "timestamps"   
    //update cycles: stores to cache take 1 cycle, stores to memory take 100 cycles for every 4 bytes
    // add in functionality to set block to valid if added to the Cache
    total_stores++;
}


//cache load method (load data from memory)
void Cache::load(uint32_t set_index, uint32_t tag) { 
    //check if block in cache has matching tag and is valid (hit), else miss 
   if (lookup(set_index, tag) == "hit") {
        load_hits++;
        total_cycles++; //loads from cache take 1 cycle
        //update lru "timestamps"?
   } else { 
        load_misses++;
        total_cycles += 100; // loads from memory take 100 cycles per 4 bytes
        //functionality to "load" data from memory (find matching block, set tag, valid, load_ts??)
   }

    total_loads++;  //increment total loads
}


//TODO: implement lookup method to refactor code out of store and load
std::string Cache::lookup(uint32_t set_index, uint32_t tag) {
    for (Block block : sets[set_index].get_blocks()) { //iterate through blocks in matching set to search for match
        if (block.get_tag() == tag && block.is_valid()) {// if block in matching set in Cache has matching tag and is valid
            return "hit";
        } 
    }
    return "miss"; //no matching block found
}

//TODO: add lru logic (method?)

//note: currently, total cycles above the accurate amount because we haven't actually implemented functionality to "move" memory to cache