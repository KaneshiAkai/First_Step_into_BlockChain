#pragma once

#include "block.h" 
#include <vector>
#include <string>
#include <stdexcept> // Required for std::runtime_error

// using namespace std; // This is often in common.h or block.h

class BlockChain{
public:
	BlockChain() {
        Block firstBlock("**********", "First Block Ever", "**********");
        _chain.push_back(firstBlock);
        // _current_block and _previou_block are default-constructed.
        // _current_block will be the genesis block after constructor.
        // _previou_block remains default-constructed until a second block is added.
        if (!_chain.empty()) {
            _current_block = _chain.back();
        }
    }

	void add_block(Block newBlock) {
        if (!_chain.empty()) {
            _previou_block = _chain.back(); // The current latest block becomes the previous one
        }
        // If the chain was empty before this (shouldn't happen with current constructor), 
        // _previou_block would remain in its default state or its state from the constructor.

        _chain.push_back(newBlock);
        _current_block = _chain.back(); // The newly added block is now the current one
    }

	Block get_block(int index) const { 
        if (index >= 0 && index < (int)_chain.size()) {
            return _chain.at(index);
        } else {
            // Index is out of bounds.
            if (!_chain.empty()) { // This should always be true due to constructor
                return _chain.at(0); // Return genesis block as a fallback
            }
            // This state (empty chain) should be impossible if constructor works.
            throw std::runtime_error("Blockchain is unexpectedly empty in get_block.");
        }
    } 

	Block get_latest_block() const { 
        if (!_chain.empty()) { // This should always be true due to constructor
            return _chain.back();
        }
        // This state (empty chain) should be impossible if constructor works.
        throw std::runtime_error("Blockchain is unexpectedly empty in get_latest_block.");
    }

	int chain_length() const {
        return (int)_chain.size();
    }

private:
	vector<Block> _chain;
	Block _current_block;  
	Block _previou_block; // Typo from user's original code is preserved
};
