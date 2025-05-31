#pragma once

#include <string>
#include "block.h" 

struct HashNode {
    string key;      // Hash 
    Block* value;    // Con trỏ tới block
    HashNode* next;  // Con trỏ tới node tiếp theo trong cùng một bucket (xử lý xung đột)

    HashNode( const string& k, Block* v){
        key = k;
        value = v;
        next = nullptr;
    }
};