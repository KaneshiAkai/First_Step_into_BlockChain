#pragma once

#include "common.h"       
#include <openssl/sha.h>  

string CalculateHash_SHA512(string text);
long long sum_hex_values(const string& hex_hash);
