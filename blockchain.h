#pragma once

#include "block.h" 
#include "common.h"    
#include "hashtable.h" 
#include "hash.h"
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
        cout << "\n=== BLOCKCHAIN INTEGRITY CHECK ===" << endl;
        
        if (_head == nullptr) {
            cout << "Blockchain is empty." << endl;
            cout << "Status: VALID (empty blockchain)" << endl;
            return true;
        }

        Block* current = _head;
        Block* prev = nullptr;
        int index = 0;
        int total_blocks_checked = 0;
        
        cout << "Checking " << _length << " blocks..." << endl;

        while (current != nullptr) {
            cout << "\nChecking Block " << index << ":" << endl;
            
            if (index > 0) {
                // Kiểm tra hash của block hiện tại
                string expected_hash = CalculateHash_SHA512(current->get_data_for_hashing());
                cout << "  - Hash verification: ";
                if (current->get_hash() != expected_hash) {
                    cout << "FAILED" << endl;
                    cout << "    Stored Hash: " << current->get_hash() << endl;
                    cout << "    Calculated Hash: " << expected_hash << endl;
                    cout << "\nINTEGRITY CHECK RESULT: FAILED" << endl;
                    cout << "Conflict detected at Block " << index << " - Invalid hash" << endl;
                    return false;
                } 
                else {
                    cout << "PASSED" << endl;
                }

                // Kiểm tra previous hash
                if (prev != nullptr) {
                    cout << "  - Previous hash verification: ";
                    if (current->get_prev_hash() != prev->get_hash()) {
                        cout << "FAILED" << endl;
                        cout << "    Stored Previous Hash: " << current->get_prev_hash() << endl;
                        cout << "    Actual Previous Hash: " << prev->get_hash() << endl;
                        cout << "\n=== INTEGRITY CHECK RESULT: FAILED ===" << endl;
                        cout << "Conflict detected at Block " << index << " - Previous hash mismatch" << endl;
                        return false;
                    } 
                    else {
                        cout << "PASSED" << endl;
                    }
                }
            } 
            else {
                cout << "  - Genesis block: SKIPPED" << endl;
            }
            total_blocks_checked++;
            prev = current;
            current = current->_next_block;
            index++;
        }

        cout << "\n=== INTEGRITY CHECK RESULT: PASSED ===" << endl;
        cout << "Successfully verified " << total_blocks_checked << " blocks" << endl;
        cout << "Blockchain integrity: INTACT" << endl;
        cout << "All blocks are properly linked and have valid hashes" << endl;
        return true;
    }
private:
	Block* _head;    
    Block* _tail;    
    int _length;     
    CustomHashTable _block_hash_map; 
};
