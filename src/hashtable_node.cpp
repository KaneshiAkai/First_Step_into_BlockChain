#include "../include/hashtable_node.h"

HashNode::HashNode(string k, Block* v){
    key = k;
    value = v;
    next = nullptr;
}
