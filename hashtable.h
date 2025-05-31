#pragma once

#include "hashtable_node.h"
#include "common.h"
#include <functional> 

class CustomHashTable {
private:
    vector<HashNode*> table;
    int capacity; 
    int current_size;

    unsigned int hash_function(const string& key, int capacity) const {
        unsigned int hash_val = 0; 
        int para = getPrime(capacity);
        for (char ch : key) {
            hash_val = para * hash_val + ch;  
            // cout << "hash_val: " << para;
        } 
        return hash_val % capacity;
    }

    bool checkPrime(int cap) const{
        if (cap == 1 || cap == 0){
            return false;
        }
        for (int i=2; i<cap; i++){
            if (cap%i==0){
                return false;
            }
        }
        return true;
    }

    int getPrime(int cap) const{
        if (cap%2==0){
            cap++;
        }
        while (!checkPrime(cap)){
            cap+=2;
        }
        return cap;
    }

public:
    CustomHashTable(int cap = 171){
        capacity = cap;
        current_size = 0;
        table.resize(capacity, nullptr);
    }

    ~CustomHashTable() {
        for (int i = 0; i < capacity; ++i) {
            HashNode* entry = table[i];
            while (entry != nullptr) {
                HashNode* prev = entry;
                entry = entry->next;
                delete prev;
            }
            table[i] = nullptr;
        }
    }

    void insert(const string& key, Block* value) {
        unsigned int bucket_index = hash_function(key, capacity);
        HashNode* prev = nullptr;
        HashNode* entry = table[bucket_index];

        while (entry != nullptr && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }
        entry = new HashNode(key, value);
        if (prev == nullptr) { 
            table[bucket_index] = entry;
        } 
        else {
            prev->next = entry;
            } 
        current_size++;
    }

    Block*find(const string& key) const {
        cout << "key: " << key << endl; 
        unsigned int bucket_index = hash_function(key, capacity);
        HashNode* entry = table[bucket_index];
        while (entry != nullptr) {
            if (entry->key == key) {
                return entry->value;
            }
            entry = entry->next;
        }
        return nullptr;  
    }
    
    int size() const {
        return current_size;
    }
};