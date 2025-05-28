#pragma once

#include "common.h"
#include "block.h"

class BlockChain
{
public:
	BlockChain();
	void add_block(Block block);
	Block get_block(int index);
	Block get_latest_block();
	int chain_length();
private:
	vector<Block> _chain;
	Block _current_block;
	Block _previou_block;
};