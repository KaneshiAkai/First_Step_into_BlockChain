#include "common.h"
#include "blockchain.h"
#include "hash.h"

using namespace std;

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

	cout << "Blockchain created successfully!" << endl;
    cout << "Current chain length: " << blockChain.chain_length() << endl;
    if (blockChain.chain_length() > 0) {
        Block latestBlock = blockChain.get_latest_block();
        cout << "Latest block data: " << latestBlock.get_data() << endl;
        cout << "Latest block hash: " << latestBlock.get_hash() << endl;
        cout << "Latest block previous hash: " << latestBlock.get_prev_hash() << endl;
    }
	return 0;
}