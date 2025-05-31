#pragma once

#include "common.h"       
#include <openssl/sha.h>  

string CalculateHash_SHA512(string text)
{
	unsigned char hash[SHA512_DIGEST_LENGTH];
	char hashDigest[SHA512_DIGEST_LENGTH * 2 + 1];
	SHA512_CTX sha512;
	SHA512_Init(&sha512);
	SHA512_Update(&sha512, text.c_str(), text.size());
	SHA512_Final(hash, &sha512);

	for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
	{
		sprintf(&hashDigest[i * 2], "%02x", hash[i]);
	}

	return string(hashDigest);
}

// Hàm mới để tính tổng giá trị các ký tự hex trong chuỗi hash
inline long long sum_hex_values(const string& hex_hash) { 
    long long sum = 0;
    for (size_t i = 0; i < hex_hash.length(); ++i) {
        char c = hex_hash[i];
        if (c >= '0' && c <= '9') {
            sum += (c - '0');
        } 
		else if (c >= 'a' && c <= 'f') {
            sum += (c - 'a' + 10);
        }
    }
    return sum;
}