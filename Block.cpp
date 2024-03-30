#include "Block.h"


Block::Block() : tag(0) , valid(false), load_ts(0), access_ts(0), dirty(false) {}

Block::Block(uint32_t t, bool v, uint32_t lts, uint32_t ats, bool d, uint32_t its) 
  : tag(t), valid(v), load_ts(lts), access_ts(ats), dirty(d) {}


uint32_t Block::get_tag() {
  return tag;
}

bool Block::is_valid(){
  return valid;
}

void Block::set_valid(bool t_f) {
  valid = t_f;
}

void Block::update_load_ts(uint32_t new_ts) {
  load_ts = new_ts; //was access_ts before
}

void Block::update_access_ts(uint32_t new_ts) {
  access_ts = new_ts;
}

bool Block::is_dirty() const {
  return dirty;
}

void Block::set_dirty(bool t_f) {
  dirty = t_f;
}

uint32_t Block::get_access_time() {
  return access_ts;
}

uint32_t Block::get_load_time() {
  return load_ts;
}

void Block::set_tag(uint32_t new_tag) {
  tag = new_tag;
}

