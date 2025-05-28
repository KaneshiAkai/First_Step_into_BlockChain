#include "blockchain.h"

BlockChain::BlockChain()
{
	Block firstBlock("**********", "First Block Ever", "**********");
	_chain.push_back(firstBlock);
}

void BlockChain::add_block(Block block)
{
	int nPrevIndex;
	if (_chain.size() > 0)
	{
		nPrevIndex = chain_length() - 1;
	}
	else
		nPrevIndex = 0;

	_previou_block = _chain.at(nPrevIndex);
	_chain.push_back(block);
	_current_block = _chain.at(chain_length() - 1);
}

Block BlockChain::get_block(int index)
{
	if (index >= 0 && index < chain_length())
	{
		return _chain.at(index);
	}
	else
	{
		// should never reach here
		return _chain.at(0);
	}
}

Block BlockChain::get_latest_block()
{
	return get_block(chain_length() - 1);
}

int BlockChain::chain_length()
{
	return (int)_chain.size();
}