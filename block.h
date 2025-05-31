#pragma once

#include "common.h"    
#include <ctime>


class Block{
public:
    Block* _next_block; // Con trỏ tới block tiếp theo

	Block() {
        _timestamp = 0;
        _index = 0;
        _nonce = 0;
        _prevBlockHash = "";
        _data = "";
        _hash = "";
        _next_block = nullptr;
    }
	Block(string prevHash, string data, string hash) {
        _prevBlockHash = prevHash;
        _data = data;
        _hash = hash;
        _index = 0;
        _nonce = 0;     
        _timestamp = time(nullptr); 
    }

    // Copy constructor (quan trọng khi BlockChain tạo node mới từ block được truyền vào)
    // ????
    Block(const Block& other) {
        _prevBlockHash = other._prevBlockHash;
        _data = other._data;
        _hash = other._hash;
        _index = other._index;
        _timestamp = other._timestamp;
        _nonce = other._nonce;
        _next_block = nullptr; // _next_block không nên được copy trực tiếp, nó sẽ được thiết lập bởi BlockChain
    }


	void set_hash(string hash_val) { // Đổi tên tham số để tránh trùng tên với thành viên
        _hash = hash_val;
    }
	void set_prev_hash(string prevHash_val) {
        _prevBlockHash = prevHash_val;
    }
	void set_data(string data_val) {
        _data = data_val;
    }
    void set_nonce(long long nonce_val) { 
        _nonce = nonce_val;
    }
    void set_index(int index_val) { 
        _index = index_val;
    }

	string get_hash() const {
        return _hash;
    }
	string get_prev_hash() const {
        return _prevBlockHash;
    }
	string get_data() const {
        return _data;
    }
    // Chỗ này được dùng để tạo chuỗi đầu vào cho việc tính hash
	string get_data_for_hashing() const {
        return _prevBlockHash + to_string(_timestamp) + _data + to_string(_nonce); 
    }
	int get_index() const { 
        return _index; 
    }
    time_t get_timestamp() const { 
        return _timestamp;
    }
    long long get_nonce() const { 
        return _nonce;
    }

    bool is_valid() const {
        if (_hash.empty()) {
            return false;
        }
        return true; ;
    }

private:
	 string _prevBlockHash;
	 string _hash;
	 string _data;
	 int _index; // Index của block trong chuỗi
     time_t _timestamp;
     long long _nonce;   
};
