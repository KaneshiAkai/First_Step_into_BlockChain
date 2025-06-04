#include "../include/block.h"

Block::Block() {
    _timestamp = 0;
    _index = 0;
    _nonce = 0;
    _prevBlockHash = "";
    _data = "";
    _hash = "";
    _next_block = nullptr;
}

Block::Block(string prevHash, string data, string hash) {
    _prevBlockHash = prevHash;
    _data = data;
    _hash = hash;
    _index = 0;
    _nonce = 0;     
    _timestamp = time(nullptr); 
}

Block::Block(const Block& other) {
    _prevBlockHash = other._prevBlockHash;
    _data = other._data;
    _hash = other._hash;
    _index = other._index;
    _timestamp = other._timestamp;
    _nonce = other._nonce;
    _next_block = nullptr;
}

void Block::set_hash(string hash_val) { 
    _hash = hash_val;
}

void Block::set_prev_hash(string prevHash_val) {
    _prevBlockHash = prevHash_val;
}

void Block::set_data(string data_val) {
    _data = data_val;
}

void Block::set_nonce(long long nonce_val) { 
    _nonce = nonce_val;
}

void Block::set_index(int index_val) { 
    _index = index_val;
}

string Block::get_hash() const {
    return _hash;
}

string Block::get_prev_hash() const {
    return _prevBlockHash;
}

string Block::get_data() const {
    return _data;
}

string Block::get_data_for_hashing() const {
    return _prevBlockHash + to_string(_timestamp) + _data + to_string(_nonce); 
}

int Block::get_index() const { 
    return _index; 
}

time_t Block::get_timestamp() const { 
    return _timestamp;
}

long long Block::get_nonce() const { 
    return _nonce;
}

bool Block::is_valid() const {
    if (_hash.empty()) {
        return false;
    }
    return true;
}
