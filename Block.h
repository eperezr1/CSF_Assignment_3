#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>

class Block {
  private:
    uint32_t tag;
    bool valid;
    uint32_t load_ts;
    uint32_t access_ts;

  public:
    Block(); //default constructor? not sure which is needed
    Block(uint32_t t, bool v, uint32_t lts, uint32_t ats);

    //need getter and setter methods?
};

#endif