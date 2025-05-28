#pragma once
#include "common.h"

class Block
{
public:
	Block() {};
	Block(string prevHash, string data, string hash);
	void set_hash(string hash);
	void set_prev_hash(string prevHash);
	void set_data(string data);
	string get_hash();
	string get_prev_hash();
	string get_data();
	string to_string();
	int get_index();
private:
	 string _prevBlockHash;
	 string _hash;
	 string _data;
	 int _index;
};