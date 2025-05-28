
#include "common.h"
#include "blockchain.h"
#include "hash.h"

int main()
{
	BlockChain blockChain = BlockChain();

	string firstBlockData = "First Block Data";
	string secondBlockData = "Second Block Data";
	string thirdBlockData = "Third Block Data";
	string fourthBlockData = "Fourth Block Data";

	Block block1 = Block(blockChain.get_latest_block().get_hash(), firstBlockData, CalculateHash_SHA512(firstBlockData));
	blockChain.add_block(block1);

	Block block2 = Block(blockChain.get_latest_block().get_hash(), secondBlockData, CalculateHash_SHA512(secondBlockData));
	blockChain.add_block(block2);

	Block block3 = Block(blockChain.get_latest_block().get_hash(), thirdBlockData, CalculateHash_SHA512(thirdBlockData));
	blockChain.add_block(block3);

	Block block4 = Block(blockChain.get_latest_block().get_hash(), fourthBlockData, CalculateHash_SHA512(fourthBlockData));
	blockChain.add_block(block4);

	return 0;
}