Team members:
Amy Lin
Emily Perez-Rodriguez

Contributions: 
Given the less structured nature of this assignment, we took a collaborative approach to completing it.
Emily did the Makefile and we both updated it as needed. Amy did the Block and Set classes. Emily started the Cache
class load and store methods as well as the logic for evicting a block, and Amy helped implement helper methods, add 
in the lru timestamp logic, and fixed bugs in the load and store methods. Emily wrote code to test that the parameters were
valid in main.cpp, Amy implemented the logic to get the tag and set_index , and we both worked on the file parsing.

For milestone 3, Emily implemented the lru eviction logic, and Amy ran the cache experiments.

Cache experiments:
I started testing with the smallest cache possible, a direct mapped cache of 1 set with 1 block with 4 bytes. This was done
to establish a baseline performance. I varied the write policies and replacement policies for a total of 6 tests. These
experiments were ran on the gcc.trace since it has more total loads and stores and thus more data to derive information from.
I found that the results were identical for test cases 1, 2, 4, and 5. This suggests that changing the write policy from
write-back to write-through and from LRU to FIFO did not affect the cache performance at all. Tests 3 and 6 had identical results
which were more load misses and less store misses from the other tests. This can be explained by the no-write-allocate policy 
which does not load data into the cache when a store miss occurs. Therefore, subsequent load operations that attempt to access
this data will result in load misses since the data is not present in the cache. 

./csim  1 1 4  write-allocate write-back  lru
./csim  1 1 4  write-allocate write-through  lru
./csim  1 1 4  no-write-allocate write-through  lru
./csim  1 1 4  write-allocate write-back  fifo
./csim  1 1 4  write-allocate write-through  fifo
./csim  1 1 4  no-write-allocate write-through  fifo

Next I ran the below tests with a fully associative cache of 1 set of 16 blocks with 32 bytes. The results 
similarly showed that write-allocate produced better hit rates compared to no-write allocate while
write-back and write-through showed identical results. Here, we see that LRU replacement yields better results 
than FIFO replacement, suggesting that maybe gcc.trace frequently loaded and stored the same memory traces which
would lead to least recently used blocks being evicted.  

./csim  1 16 32  write-allocate write-back  lru
./csim  1 16 32  write-allocate write-through  lru
./csim  1 16 32  no-write-allocate write-through  lru
./csim  1 16 32  write-allocate write-back  fifo
./csim  1 16 32  write-allocate write-through  fifo
./csim  1 16 32  no-write-allocate write-through  fifo

Next I ran tests with a 16-way set-associative cache. I kept the byte size small while keeping the set and block
sizes relatively large. Again, I found the same trends as I discussed above, LRU having better results than FIFO and
the no-write-back policy having the worst hit rate among the configurations. 
./csim  16 64 4  write-allocate write-back  lru
./csim  16 64 4  write-allocate write-through  lru
./csim  16 64 4  no-write-allocate write-through  lru
./csim  16 64 4  write-allocate write-back  fifo
./csim  16 64 4  write-allocate write-through  fifo
./csim  16 64 4  no-write-allocate write-through  fifo

Next I ran tests with a direct mapped cache, keeping the number of blocks low and the other parameters large. 
The same patterns were produced on these tests as above. 
./csim  16 1 32  write-allocate write-back  lru
./csim  16 1 32  write-allocate write-through  lru
./csim  16 1 32  no-write-allocate write-through  lru
./csim  16 1 32  write-allocate write-back  fifo
./csim  16 1 32  write-allocate write-through  fifo
./csim  16 1 32  no-write-allocate write-through  fifo

I found that the best cache configuration was a 64 set of 64 blocks with 128 bytes each. This cache has a large total cache size,
which reduces the likelihood of cache misses. This is confirmed by the output in which there is a 0.21% load miss rate and a
0.65% store miss rate. The best cache policies for this cache was write-allocate and write-through/write-back which had identical
results. Generally, LRU yielded lower misses than FIFO which is logical due to the evicting the least recently used block when the set is full.
The low number of load and store misses indicates that the cache is effectively capturing and retaining frequently accessed data,
resulting in the highest hit rates and the most effective performance. Output for the best experiment shown below. 

./csim  64 64 128  write-allocate write-through/write-back  lru < gcc.trace
Total loads: 318197
Total stores: 197486
Load hits: 317534
Load misses: 663
Store hits: 196200
Store misses: 1286
Total cycles: 6751820

