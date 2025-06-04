#pragma once

#include <string>
#include "block.h"

using namespace std;

struct HashNode {
    string key;      
    Block* value;    
    HashNode* next;  

    HashNode(string k, Block* v);
};
