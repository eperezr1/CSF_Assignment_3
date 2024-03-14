#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>

class Block {
  private:
    uint32_t tag;
    bool valid;
    uint32_t load_ts; //fifo, increment when loaded into cache
    uint32_t access_ts; //lru, increment when block is accessed
    // add "dirty" field to class?
    bool dirty;

  public:
    Block(); //default constructor? not sure which is needed
    Block(uint32_t t, bool v, uint32_t lts, uint32_t ats, bool d);

    //need getter and setter methods?
    uint32_t get_tag();

    bool is_valid();

    void set_valid(bool t_f);

    void update_load_ts(uint32_t new_ts);

    void update_access_ts(uint32_t new_ts);

    bool is_dirty() const;

    void set_dirty(bool t_f);

};

#endif