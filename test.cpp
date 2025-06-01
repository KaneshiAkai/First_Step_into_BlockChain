#include <iostream>
#include "blockchain.h"
#include "hash.h"
#include "miner.h" 
#include <string>
#include <sstream> 
#include <ctime>   
#include <iomanip> 

using namespace std;

void print_help() {
    cout << "\nAdmin Commands !!! Mark my words\n";
    cout << "  add <data>       - Add a new block with the given data\n";
    cout << "  show <index>     - Show block at the given index (0 for genesis)\n";
    cout << "  latest           - Show the latest block\n";
    cout << "  length           - Show the current chain length\n";
    cout << "  print            - Print all blocks in the chain\n";
    cout << "  gethash <hash>   - Get block by its hash\n"; 
    cout << "  verify           - Check blockchain integrity\n";
    cout << "  hashmap          - Show hash table content\n"; // Thêm lệnh mới
    cout << "  help             - Show this help message\n";
    cout << "  exit             - Exit the program\n";
    cout << "--------------------------------------------------\n";
}

void print_block_details(const Block& block, int index) {
    cout << "\n--- Block " << index << " ---\n";
    cout << "Data: " << block.get_data() << endl;
    cout << "Hash: " << block.get_hash() << endl;
    cout << "Previous Hash: " << block.get_prev_hash() << endl;
    cout << "Nonce: " << block.get_nonce() << endl; 

    // Timestamp // CÓ THAM KHẢO TỪ NGUỒN STACKOVERFLOW ĐỂ PRINT RA THỜI GIAN THỰC
    time_t raw_time = block.get_timestamp();
    struct tm timeinfo;
    char buffer[80];
    localtime_s(&timeinfo, &raw_time); 
    // Định dạng "YYYY-MM-DD HH:MM:SS"
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);
    cout << "Time created: " << buffer << endl;
    cout << "-------------------\n";
}

int main() {
    BlockChain blockChain = BlockChain();
    cout << "Blockchain Initialized\n";
    const int MINING_DIFFICULTY_DIVISOR = 149; 
    print_help();

    string line;
    string command;
    string argument;

    while (true) {
        cout << "\nEnter command: ";
        getline(cin, line);
        stringstream ss(line);
        ss >> command; 
        argument = ""; 
        string temp_arg;
        if (ss >> temp_arg) {
            argument = temp_arg; 
            while(ss >> temp_arg) {
                argument += " " + temp_arg;
            }
        }

        if (command == "add") {
            if (argument.empty()) {
                cout << "Error: 'add' command requires data. Usage: add <your data here>\n";
                continue;
            }
            Block newBlockData(
                blockChain.get_latest_block().get_hash(), 
                argument,                                
                ""
            );
            mine_block_divisible_sum(newBlockData, MINING_DIFFICULTY_DIVISOR); 
            
            blockChain.add_block(newBlockData); // BlockChain sẽ tạo node mới trên heap từ newBlockData
            Block latestBlockToPrint = blockChain.get_latest_block();
            print_block_details(latestBlockToPrint, latestBlockToPrint.get_index());
        } 
        else if (command == "show") {
            if (argument.empty()) {
                cout << "Error: 'show' command requires an index. Usage: show <index>\n";
                continue;
            }
            int index_val = stoi(argument);
            Block b = blockChain.get_block(index_val); 
            print_block_details(b, index_val); 
        } 
        else if (command == "latest") { 
            if (blockChain.chain_length() > 0) {
                Block b = blockChain.get_latest_block();
                print_block_details(blockChain.get_latest_block(), blockChain.chain_length() - 1);
            } else {
                cout << "Blockchain is empty.\n"; 
            }
        } 
        else if (command == "length") {
            cout << "Current chain length: " << blockChain.chain_length() << endl;
        } 
        else if (command == "print") {
            if (blockChain.chain_length() == 0) {
                cout << "Blockchain is empty.\n";
            } 
            else {
                cout << "\n--- Blockchain ---" << endl;
                for (int i = 0; i < blockChain.chain_length(); ++i) {
                    Block b = blockChain.get_block(i);
                    print_block_details(b, b.get_index());
                }
            }
        } 
        else if (command == "gethash") { 
            if (argument.empty()) {
                cout << "Error: 'gethash' command requires a hash string.\n";
                continue;
            }
            Block b = blockChain.get_block_by_hash(argument);
            
            if (b.is_valid()){
                print_block_details(b, b.get_index());
            }
        }
        else if (command == "verify") { // Thêm xử lý lệnh verify
            cout << "Starting blockchain integrity verification..." << endl;
            bool is_valid = blockChain.integrity_check();
            if (is_valid) {
                cout << "\nBlockchain verification completed successfully!" << endl;
            } 
            else {
                cout << "\nBlockchain verification failed! Chain may be compromised." << endl;
            }
        }
        else if (command == "hashmap") { // Thêm xử lý lệnh hashmap
            blockChain.print_hash_stats();
        }
        else if (command == "help") {
            print_help();
        } 
        
        else if (command == "exit") {
            cout << "Exiting program.\n";
            break;
        } else {
            cout << "Error: Unknown command. Type 'help' for a list of commands.\n";
        }
    }
    return 0;
}
