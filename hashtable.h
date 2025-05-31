#pragma once

#include "hashtable_node.h" // Node đã định nghĩa ở trên
#include "common.h"
#include <functional> // Cho std::hash (nếu dùng hàm băm chuẩn cho string)

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
            cout << "hash_val: " << para;
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
                // Quan trọng: Destructor của CustomHashTable không nên delete Block* value
                // vì Block* được quản lý (delete) bởi BlockChain.
                // Nó chỉ delete các HashNode mà nó đã tạo.
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

        if (entry == nullptr) { // Không tìm thấy key, thêm mới
            entry = new HashNode(key, value);
            if (prev == nullptr) { // Node đầu tiên trong bucket
                table[bucket_index] = entry;
            } else {
                prev->next = entry;
             }
            current_size++;
            // TODO: Cân nhắc việc resize (rehashing) nếu bảng quá đầy (load factor cao)
        } else { // Tìm thấy key, cập nhật value (trong trường hợp này, không nên xảy ra với hash block duy nhất)
            entry->value = value;
        }
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
        return nullptr; // Không tìm thấy
    }

    void remove(const string& key) {
        unsigned int bucket_index = hash_function(key, capacity);
        HashNode* prev = nullptr;
        HashNode* entry = table[bucket_index];

        while (entry != nullptr && entry->key != key) {
            prev = entry;
            entry = entry->next;
        }

        if (entry == nullptr) { // Không tìm thấy key
            return;
        } else {
            if (prev == nullptr) { // Node cần xóa là node đầu tiên
                table[bucket_index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            // Quan trọng: Không delete entry->value ở đây
            delete entry;
            current_size--;
        }
    }
    
    int size() const {
        return current_size;
    }
};