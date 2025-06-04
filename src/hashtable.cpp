#include "../include/hashtable.h"

HashTable::HashTable(){
    capacity = 700;
    current_size = 0;
    table.resize(capacity, nullptr);
}

HashTable::~HashTable() {
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

unsigned int HashTable::hash_function(const string& key, int capacity) const {
    unsigned int hash_val = 0; 
    int para = getPrime(capacity);
    for (char ch : key) {           
        hash_val = capacity * hash_val + ch;  
    } 
    return hash_val % para;
}

bool HashTable::checkPrime(int cap) const{
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

int HashTable::getPrime(int cap) const{
    if (cap%2==0){
        cap++;
    }
    while (!checkPrime(cap)){
        cap+=2;
    }
    return cap;
}

void HashTable::insert(const string& key, Block* value) {
    cout << "\nInserting block into HashTable." << endl;
    unsigned int bucket_index = hash_function(key, capacity);
    HashNode* prev = nullptr;
    int node_index = 0;
    HashNode* entry = table[bucket_index];

    if (entry != nullptr && entry->key != key){
        cout << "Conflict detected! At bucket index: " << bucket_index << endl; 
    }
    while (entry != nullptr && entry->key != key) {
        prev = entry;
        entry = entry->next;
        node_index++;
        cout << "Considering node index " << node_index << "..." << endl;
    }
    cout << "Key at bucket index: " << bucket_index << " - node " << node_index << endl;
    entry = new HashNode(key, value);
    if (prev == nullptr) {
        table[bucket_index] = entry;
    } 
    else {
        prev->next = entry;
    } 
    current_size++;
}

Block* HashTable::find(const string& key) const {
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

int HashTable::size() const {
    return current_size;
}

void HashTable::print_hashtable() const {
    cout << "\n HASHTABLE CONTENT " << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Current size: " << current_size << endl;
    cout << "Load factor: " << (double)current_size / capacity << endl;
    cout << "-------------------------" << endl;
    
    for (int i = 0; i < capacity; i++) {
        cout << "Bucket[" << i << "]: ";
        HashNode* entry = table[i];
        
        if (entry == nullptr) {
            cout << "EMPTY" << endl;
        } 
        else {
            int node_count = 0;
            while (entry != nullptr) {
                if (node_count > 0) {
                    cout << " -> ";
                }
                cout << "Node" << node_count << "(Hash: " << entry->key.substr(0, 4) << "...)";
                entry = entry->next;
                node_count++;
            }
            cout << " [Chain length: " << node_count << "]" << endl;
        }
    }
    cout << "=========================" << endl;
}
