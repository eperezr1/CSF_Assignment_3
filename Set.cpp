#include "Set.h"

Set::Set(int num_blocks) : blocks(num_blocks) {}

std::vector<Block> Set::get_blocks() {
    return blocks;
}