#include "Block.h"

Block::Block() : tag(0) , valid(false), load_ts(0), access_ts(0) {}

Block::Block(uint32_t t, bool v, uint32_t lts, uint32_t ats) 
  : tag(t), valid(v), load_ts(lts), access_ts(ats) {}



