#ifndef CACHE_H
#define CACHE_H

#include "Set.h"
#include <string>
#include <vector>

class Cache {
    private: //should cache parameters be private instead? Would need a lot of getter methods
        int num_sets;
        int num_blocks;
        int num_bytes;
        std::string alloc;
        std::string through_back;
        std::string lru_fifo;

        //stats
        int total_loads;
        int total_stores;
        int load_hits;
        int load_misses;
        int store_hits;
        int store_misses;
        int total_cycles;
        uint32_t timestamp;

        //cache is a vector containing sets
        std::vector<Set> sets;;

    public:
    //public methods and constructor declarations
        //constructor for Cache
        Cache(int num_sets, int num_blocks, int num_bytes, std::string alloc, std::string through_back, std::string lru_fifo);


        //method to print stats
        void printStats();

        //add more methods
        void load(uint32_t set_index, uint32_t tag);

        void store(uint32_t set_index, uint32_t tag);

        //TODO: add lookup method 
        std::string lookup(uint32_t set_index, uint32_t tag);
        //TODO: add lru logic (method?)

        int get_block_index(uint32_t set_index, uint32_t tag);

};
#endif