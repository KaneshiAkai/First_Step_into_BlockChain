#pragma once

#include "block.h" 
#include "common.h"    
#include "hashtable.h" 
#include <iostream>      

class BlockChain{
public:
	BlockChain() {
        Block genesis_data_block("**********", "First Block Ever", "**********");
        Block* genesis_node = new Block(genesis_data_block); 
        genesis_node->set_index(0); 
        _head = genesis_node;
        _tail = genesis_node;
        _length = 1;
        
        _block_hash_map = CustomHashTable(); 
        _block_hash_map.insert(genesis_node->get_hash(), genesis_node); 

    }

    ~BlockChain() {
        Block* current = _head;
        Block* next_node = nullptr;
        while (current != nullptr) {
            next_node = current->_next_block;
            delete current;
            current = next_node;
        }
        _head = nullptr;
        _tail = nullptr;
    }

	void add_block(Block newBlockData) { 
        Block* new_node = new Block(newBlockData); 
        new_node->set_index(_length); 

        if (_head == nullptr) { 
            _head = new_node;
            _tail = new_node;
        } else {
            _tail->_next_block = new_node; 
            _tail = new_node;              
        }
        _length++;
        _block_hash_map.insert(new_node->get_hash(), new_node); 
    }

	Block get_block(int index) const { 
        if (index < 0 || index >= _length) {
            cout << "Error: Requested block index " << index << " is out of bounds. Chain length is " << _length << "." << endl;
            return Block(); 
        }
        Block* current = _head;
        for (int i = 0; i < index; ++i) {
            if (current == nullptr) { 
                 cout << "Error: Chain structure error." << endl;
                 return Block(); 
            }
            current = current->_next_block;
        }
        return *current; 
    }

	Block get_latest_block() const {
        return *_tail; 
    }

    Block get_block_by_hash(const string& hash_val) const {
        Block* found_block = _block_hash_map.find(hash_val); 
        if (found_block != nullptr) { 
            return *found_block; 
        }
        cout << "Error: Block with hash " << hash_val << " not found." << endl;
        return Block(); 
    }

	int chain_length() const {
        return _length;
    }

// kiểm tra tính toàn venmj của chuỗi
    bool integrity_check() const {
        if (_head == nullptr) {
            cout << "Blockchain is empty. \n";
            return true;
        }

        Block* current =_head;
        Block* prev = nullptr;

        int index = 0;
        while (current != nullptr) {
            if (index >0){
            // check hash của block hiện tại
            string expected_hash = CalculateHash_SHA512(current->get_data_for_hashing());
            if (current->get_hash() != expected_hash) {
                cout << "Conflict detected at blokc "<< index << "\n";
                cout << "Stored Hash: "<< current->get_hash() << "\n";
                cout << "Calculated hash: " << expected_hash << "\n";
                return false;

        }
        //check previous hash
            if (prev != nullptr){
                if (current->get_prev_hash() != prev->get_hash()) {
                    cout << "Conflict detected at block "<< index << "\n";
                    cout << "Stored previous hash: "<< current->get_prev_hash() << "\n";
                    cout << "Actual previous hash: "<< prev->get_hash() << "\n";
                    return false;

                }
                
            }
        }
            prev = current;
            current = current->_next_block;
            index++;
        }

        
    cout << "No conflict detected.\n";
    return true;
    }
private:
	Block* _head;    
    Block* _tail;    
    int _length;     
    CustomHashTable _block_hash_map; // Sử dụng hash table tự tạo
};
