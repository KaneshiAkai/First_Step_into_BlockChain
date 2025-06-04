#pragma once

#include "common.h"    
#include <ctime>

class Block{
public:
    Block* _next_block; 

    Block();
    Block(string prevHash, string data, string hash);
    Block(const Block& other);

    void set_hash(string hash_val);
    void set_prev_hash(string prevHash_val);
    void set_data(string data_val);
    void set_nonce(long long nonce_val);
    void set_index(int index_val);

    string get_hash() const;
    string get_prev_hash() const;
    string get_data() const;
    string get_data_for_hashing() const;
    int get_index() const;
    time_t get_timestamp() const;
    long long get_nonce() const;
    bool is_valid() const;

private:
    string _prevBlockHash;
    string _hash;
    string _data;
    int _index;
    time_t _timestamp;
    long long _nonce;   
};
