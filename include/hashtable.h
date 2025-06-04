#pragma once

#include "hashtable_node.h"
#include "common.h"
#include <functional> 

class HashTable {
private:
    vector<HashNode*> table;
    int capacity; 
    int current_size;

    unsigned int hash_function(const string& key, int capacity) const;
    bool checkPrime(int cap) const;
    int getPrime(int cap) const;

public:
    HashTable();
    ~HashTable();

    void insert(const string& key, Block* value);
    Block* find(const string& key) const;
    int size() const;
    void print_hashtable() const;
};
