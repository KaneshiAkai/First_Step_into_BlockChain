#include "../include/miner.h"

void proof_of_work(Block& block, int difficulty_divisor) {
    if (difficulty_divisor == 0) {
        cout << "Error: Difficulty divisor cannot be zero. Setting to 1." << endl; 
        difficulty_divisor = 1; 
    }
    if (difficulty_divisor < 0) {
        difficulty_divisor = -difficulty_divisor; 
    }
    block.set_nonce(0); 
    string current_hash; 
    long long current_sum_hex;
    long long attempts = 0;
    cout << "\nMining with target: sum of hex values divisible by " << difficulty_divisor << "..." << endl; 

    do {
        block.set_nonce(block.get_nonce() + 1);
        attempts++;
        string data_to_hash = block.get_data_for_hashing(); 
        current_hash = CalculateHash_SHA512(data_to_hash);
        current_sum_hex = sum_hex_values(current_hash);

        if (attempts % 100 == 0) {
            cout << "Attempt: " << attempts << ", Hash: " << current_hash.substr(0,10) << "..., SumHex: " << current_sum_hex << ", Nonce: " << block.get_nonce() << endl; 
        }

    } while (current_sum_hex % difficulty_divisor != 0);
    block.set_hash(current_hash);
    cout << "Block Mined! Attempts: " << attempts << ", Hash: " << current_hash.substr(0,10) << "..., SumHex: " << current_sum_hex << ", Nonce: " << block.get_nonce() << endl; 
}
