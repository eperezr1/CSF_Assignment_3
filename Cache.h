
#include <string>
using namespace std; 

class Cache {
    private: //should cache parameters be private instead? Would need a lot of getter methods
        int num_sets;
        int num_blocks;
        int num_bytes;
        string alloc;
        string through_back;
        string lru_fifo;

        //stats
        int total_loads;
        int total_stores;
        int load_hits;
        int load_misses;
        int store_hits;
        int store_misses;
        int total_cycles;

    public:
    //public methods and constructor declarations
        //constructor for Cache
        Cache(int num_sets, int num_blocks, int num_bytes, string alloc, string through_back, string lru_fifo);


        //method to print stats
        void printStats();

        //add more methods

};