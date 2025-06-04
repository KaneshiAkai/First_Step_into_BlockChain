#pragma once

#include "block.h" 
#include "common.h"    
#include "hashtable.h" 
#include "hash.h"
#include <iostream>      

class BlockChain{
public:
    BlockChain();
    ~BlockChain();

    void add_block(Block newBlockData);
    Block get_block(int index) const;
    Block get_latest_block() const;
    Block get_block_by_hash(const string& hash_val) const;
    int chain_length() const;
    void print_hash_stats() const;
    bool integrity_check() const;

private:
    Block* _head;    
    Block* _tail;    
    int _length;     
    HashTable _block_hash_map; 
};
