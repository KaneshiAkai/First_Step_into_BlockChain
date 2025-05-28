#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Block{
public:
	Block() {};
	Block(string prevHash, string data, string hash) {
        _prevBlockHash = prevHash;
        _data = data;
        _hash = hash;
    }
	void set_hash(string hash) {
        _hash = hash;
    }
	void set_prev_hash(string prevHash) {
        _prevBlockHash = prevHash;
    }
	void set_data(string data) {
        _data = data;
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
	string to_string() const {
        return _prevBlockHash + _data + _hash;
    }
	int get_index() const { 
        return _index; 
    }
private:
	 string _prevBlockHash;
	 string _hash;
	 string _data;
	 int _index;
};
