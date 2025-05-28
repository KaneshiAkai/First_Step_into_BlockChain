#include "block.h"

Block::Block(string prevHash, string data, string hash)
{
	_prevBlockHash = prevHash;
	_data = data;
	_hash = hash;
}

void Block::set_hash(string hash)
{
	_hash = hash;
}

void Block::set_prev_hash(string prevHash)
{
	_prevBlockHash = prevHash;
}

void Block::set_data(string data)
{
	_data = data;
}

string Block::get_hash()
{
	return _hash;
}

string Block::get_prev_hash()
{
	return _prevBlockHash;
}

string Block::get_data()
{
	return _data;
}

string Block::to_string()
{
	return _prevBlockHash + _data + _hash;
}

int Block::get_index()
{
	return _index;
}