#include "Set.h"

Set::Set(int num_blocks) : blocks(num_blocks) {}

Block& Set::get_block(int index) {
    return blocks[index];
}