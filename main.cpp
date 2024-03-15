#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include "Cache.h"


int main(int argc, char **argv) {
    //get command line arguments, store, verify validity
    //argc = # of args
    if (argc != 7) {
        std::cout << "Invalid number of command line arguments provided";
        return 1;
    }
    
    //arg1: # sets in cache
    int num_sets = atoi(argv[1]);
    //arg2: # blocks in cache
    int num_blocks = atoi(argv[2]);
    //arg3: # bytes in each block
    int num_bytes = atoi(argv[3]);
    //arg4: write-allocate or no-write-allocate (bool instead?)
    std::string alloc = argv[4]; 
    //arg5: write-through or write-back
    std::string through_back = argv[5]; 
    //arg6: lru or fifo
    std::string lru_fifo = argv[6];

    //check for valid parameters

    //check that num_sets is power of 2
    if (num_sets == 0 || ceil(log2(num_sets)) != floor(log2(num_sets))) {
        std::cerr << "Invalid number of sets. Must be a power of 2\n";
        return 1;
    }
    //check that num_blocks is power of 2
    if (num_blocks == 0 || ceil(log2(num_blocks)) != floor(log2(num_blocks))) {
        std::cerr << "Invalid number of blocks. Must be a power of 2\n";
        return 1;
    }
    //check that num_bytes is at least 4 and power of 2
    if (num_bytes < 4 || ceil(log2(num_bytes)) != floor(log2(num_bytes))) {
        std::cerr << "Invalid block size, must be at least 4 and a power of 2\n";
        return 1;
    }   
    //cannot have write_back AND no-write-allocate
    if (alloc == "no-write-allocate" && through_back == "write-back") { 
        std::cerr << "Invalid combination of no-write-allocate and write-back specified\n";
        return 1;
    }

    //create a Cache object with the provided parameters
    Cache cache(num_sets, num_blocks, num_bytes, alloc, through_back, lru_fifo);

    //read trace file line by line (file given as input to program)  --- make this a cache method instead? 
    std::string cur_line;
    while(std::getline(std::cin, cur_line)) {
        //extract first and second fields (ignore third field)
        std::istringstream iss(cur_line);
        std::string command, hex_string;
        iss >> command >> hex_string;
        uint32_t address;
        //convert hexadecimal string to integer address
        std::istringstream(hex_string) >> std::hex >> address;
        // std::cout << "command: " << command << " address: " << address << "\n";
        //get the set index and tag based on the address
        uint32_t set_index = address % num_sets;
        uint32_t tag = address / num_sets; // fix tag
        //take log 2 of num_bytes, shift right by that number
        //int shift = log2(num_bytes); // why? to get correct address
        //use set_index and tag to see if there is cache hit or miss?
        //implement lookup method? 

        
        if (command == "s") {
            cache.store(set_index,tag);
        
        } else if (command == "l") {
            cache.load(set_index, tag);
        }
        
        
        
    }
    
    //once done reading file, print summary of stats
    cache.printStats();

    return  0;
}