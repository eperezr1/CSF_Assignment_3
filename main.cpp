#include <iostream>
#include <cmath>
#include <cstring>
#include <sstream>
#include "Cache.h"
using namespace std; 


int main(int argc, char **argv) {
    //get command line arguments, store, verify validity
    //argc = # of args
    if (argc != 7) {
        cout << "Invalid number of command line arguments provided";
        return 1;
    }
    
    //arg1: # sets in cache
    int num_sets = atoi(argv[1]);
    //arg2: # blocks in cache
    int num_blocks = atoi(argv[2]);
    //arg3: # bytes in each block
    int num_bytes = atoi(argv[3]);
    //arg4: write-allocate or no-write-allocate (bool instead?)
    string alloc = argv[4]; 
    //arg5: write-through or write-back
    string through_back = argv[5]; 
    //arg6: lru or fifo
    string lru_fifo = argv[6];

    //check for valid parameters

    //check that num_sets is power of 2
    if (num_sets == 0 || ceil(log2(num_sets)) != floor(log2(num_sets))) {
        cerr << "Invalid number of sets. Must be a power of 2";
        return 1;
    }
    //check that num_blocks is power of 2
    if (num_blocks == 0 || ceil(log2(num_blocks)) != floor(log2(num_blocks))) {
        cerr << "Invalid number of blocks. Must be a power of 2\n";
        return 1;
    }
    //check that num_bytes is at least 4
    if (num_bytes < 4) {
        cerr << "Invalid block size, must be at least 4\n";
        return 1;
    }   
    //cannot have write_back AND no-write-allocate
    if (alloc == "no-write-allocate" && through_back == "write-back") { 
        cerr << "Invalid combination of no-write-allocate and write-back specified\n";
        return 1;
    }

    //create a Cache object with the provided parameters
    Cache cache(num_sets, num_blocks, num_bytes, alloc, through_back, lru_fifo);

    //read trace file line by line (file given as input to program)  --- make this a cache method instead? 
    string cur_line;
    while(getline(cin, cur_line)) {
        //extract first and second fields (ignore third field)
        istringstream iss(cur_line);
        string command, address;
        iss >> command >> address; //fix address to ignore 0x?
        //cout << "command: " << command << "\n";
        //cout << "address: " << address << "\n";
        //if first field is store, call function
        /*
        if (command == "s") {

        } else if (command == "l") {

        }
        */
        //if first field is load, call function
        
        
    }
    
    //once done reading file, print summary of stats
    cache.printStats();

    return  0;
}