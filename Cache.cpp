#include <string>
#include <iostream>
#include "Cache.h"
using namespace std; 

Cache::Cache(int num_sets,  int num_blocks, int num_bytes, string alloc, string through_back, string lru_fifo)
    : num_sets(num_sets),
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
        total_cycles(0)
{}


void Cache::printStats() {
    cout << "Total loads: " << total_loads << "\n";
    cout << "Total stores: " << total_stores << "\n";
    cout << "Load hits: " << load_hits << "\n";
    cout << "Load misses: " << load_misses << "\n";
    cout << "Store hits: " << store_hits << "\n";
    cout << "Store misses: " << store_misses << "\n";
    cout << "Total cycles: " << total_cycles << "\n";

   
}