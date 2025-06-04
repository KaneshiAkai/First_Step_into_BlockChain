#include "../include/blockchain.h"
#include "../include/hash.h"

BlockChain::BlockChain() {
    cout << "Creating genesis block..." << endl;
    
    try {
        Block genesis_data_block("**********", "First Block Ever", "**********");
        Block* genesis_node = new Block(genesis_data_block); 
        genesis_node->set_index(0); 
        _head = genesis_node;
        _tail = genesis_node;
        _length = 1;
        
        cout << "Initializing hash table..." << endl;
        _block_hash_map = HashTable(); 
        
        cout << "Inserting genesis block into hash table..." << endl;
        _block_hash_map.insert(genesis_node->get_hash(), genesis_node); 
        
        cout << "Blockchain constructor completed." << endl;
    } catch (const exception& e) {
        cout << "Error in BlockChain constructor: " << e.what() << endl;
        throw;
    }
}

BlockChain::~BlockChain() {
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

void BlockChain::add_block(Block newBlockData) { 
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

Block BlockChain::get_block(int index) const { 
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

Block BlockChain::get_latest_block() const {
    if (_tail == nullptr) {
        cout << "Warning: Chain is empty, returning default block." << endl;
        return Block();
    }
    return *_tail; 
}

Block BlockChain::get_block_by_hash(const string& hash_val) const {
    Block* found_block = _block_hash_map.find(hash_val); 
    if (found_block != nullptr) { 
        return *found_block; 
    }
    cout << "Error: Block with hash " << hash_val << " not found." << endl;
    return Block(); 
}

int BlockChain::chain_length() const {
    return _length;
}

void BlockChain::print_hash_stats() const {
    _block_hash_map.print_hashtable();
}

bool BlockChain::integrity_check() const {
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
