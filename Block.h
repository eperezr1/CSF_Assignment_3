#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>

class Block {
  private:
    uint32_t tag;
    bool valid;
    uint32_t load_ts; // increment when block is loaded 
    uint32_t access_ts; // increment when block is accessed
    bool dirty;

  public:

    //default contructor to create new block, initializes attributes to 0 or false
    // depending on type
    Block();

    // Constructor, creates new block using provided arguments
    // Parameters:
    //  t - tag
    //  v - valid (true or false)
    // lts - load timestamp
    // ats - access timestamp
    // d - dirty
    Block(uint32_t t, bool v, uint32_t lts, uint32_t ats, bool d, uint32_t its);

    // gets tag of block
    //Returns:
    //  tag - tag of block
    uint32_t get_tag();

    // checks whether block is valid or not
    // Returns:
    //  - true or false value of valid attribute
    bool is_valid();

    // Updates the value of the valid attribute of a block
    // Parameters:
    // t_f - true or false value to set for valid
    void set_valid(bool t_f);

    // Updates the value of the load timestamp of a block with given value
    // Parameters:
    //  new_ts- new load timestamp value
    void update_load_ts(uint32_t new_ts);

    // Updates the value of the access timestamp of a block with given value
    // Parameters:
    //  new_ts- new access timestamp value
    void update_access_ts(uint32_t new_ts);

    // checks whether a block is dirty
    // Returns:
    // true if block is dirty, otherwise false
    bool is_dirty() const;

    // sets a block's dirty attribute to true or false
    // Parameters:
    //  t_f - true or false valie to set for dirty
    void set_dirty(bool t_f);

    // gets the access time of a block
    // Returns:
    // access_ts - value of the access timestamp of the block
    uint32_t get_access_time();

    uint32_t get_load_time();

    // Sets the value of a block's tag
    // Parameters:
    //  new_tag - value to set block's tag to
    void set_tag(uint32_t new_tag);

   
};

#endif