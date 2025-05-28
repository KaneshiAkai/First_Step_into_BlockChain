#pragma once

#include "common.h"
#include <openssl/sha.h>
#include <openssl/pem.h>

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