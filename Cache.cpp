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