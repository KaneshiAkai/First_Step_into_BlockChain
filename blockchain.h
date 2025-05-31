#pragma once

#include "block.h" 
#include "common.h"    
#include "hashtable.h" 
#include <iostream>      

class BlockChain{
public:
	BlockChain() { // Bỏ khởi tạo _block_hash_map khỏi member initializer list
        _head = nullptr;
        _tail = nullptr;
        _length = 0;

        // Khởi tạo _block_hash_map trong thân constructor
        // Điều này sẽ gọi constructor mặc định của CustomHashTable trước (nếu capacity mặc định là 100)
        // Sau đó gán một đối tượng mới.
        // Cách tốt hơn là CustomHashTable có một phương thức reinitialize hoặc dùng member initializer list.
        // Tuy nhiên, để theo yêu cầu, chúng ta sẽ gán:
        _block_hash_map = CustomHashTable(); // Gán một đối tượng CustomHashTable mới với capacity 1000

        Block genesis_data_block("**********", "First Block Ever", "**********");
        
        Block* genesis_node = new Block(genesis_data_block); 
        genesis_node->set_index(0); 

        _head = genesis_node;
        _tail = genesis_node;
        _length = 1;
        _block_hash_map.insert(genesis_node->get_hash(), genesis_node); 
    }

    ~BlockChain() {
        Block* current = _head;
        Block* next_node = nullptr;
        while (current != nullptr) {
            next_node = current->_next_block;
            // _block_hash_map.remove(current->get_hash()); // Không cần thiết vì CustomHashTable sẽ tự dọn HashNode
            delete current; // BlockChain chịu trách nhiệm delete Block objects
            current = next_node;
        }
        _head = nullptr;
        _tail = nullptr;
        // CustomHashTable sẽ tự dọn dẹp các HashNode trong destructor của nó.
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

private:
	Block* _head;    
    Block* _tail;    
    int _length;     
    CustomHashTable _block_hash_map; // Sử dụng hash table tự tạo
};
