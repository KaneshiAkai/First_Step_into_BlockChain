#pragma once

#include <string>
#include "block.h" // Để biết kiểu Block

// Giả sử common.h đã có using namespace std;
// Nếu không, bạn cần dùng std::string

struct HashNode {
    string key;      // Hash của block
    Block* value;    // Con trỏ tới block
    HashNode* next;  // Con trỏ tới node tiếp theo trong cùng một bucket (xử lý xung đột)

    HashNode(string k, Block* v) : key(k), value(v), next(nullptr) {}
};