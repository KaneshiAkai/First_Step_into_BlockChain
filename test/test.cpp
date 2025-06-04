#include <iostream>
#include "../include/blockchain.h"
#include "../include/hash.h"
#include "../include/miner.h" 
#include <string>
#include <sstream> 
#include <ctime>   
#include <iomanip> 
#include <random>  
#include <fstream>  

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
    cout << "  hashmap          - Show hash table content\n";
    cout << "  generate <n>     - Generate n blocks with random data\n";
    cout << "  export <file>    - Export blockchain data to CSV file\n";
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
    srand(static_cast<unsigned int>(time(nullptr))); 
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
            proof_of_work(newBlockData, MINING_DIFFICULTY_DIVISOR); 
            
            blockChain.add_block(newBlockData);
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
        else if (command == "hashmap") { 
            blockChain.print_hash_stats();
        }
        else if (command == "generate") {
            if (argument.empty()) {
                cout << "Error: 'generate' command requires number of blocks. Usage: generate <number>\n";
                continue;
            }
            int num_blocks = stoi(argument);
            if (num_blocks <= 0) {
                cout << "Error: Number of blocks must be positive.\n";
                continue;
            }
            
            cout << "Generating " << num_blocks << " blocks with random data...\n";
            
            for (int i = 0; i < num_blocks; i++) {
                int random_num = rand() % 10000;
                string random_data = "Random_Data_" + to_string(random_num);
                
                Block newBlockData(
                    blockChain.get_latest_block().get_hash(),
                    random_data,
                    ""
                );
                
                proof_of_work(newBlockData, MINING_DIFFICULTY_DIVISOR);
                blockChain.add_block(newBlockData);
                
                cout << "Generated block " << i + 1 << ": " << random_data << endl;
            }
            cout << "Block generation completed!\n";
        }
        else if (command == "export") {
            if (argument.empty()) {
                cout << "Error: 'export' command requires a filename. Usage: export <filename.csv>\n";
                continue;
            }
            string filename = argument;
            if (filename.find(".csv") == string::npos) {
                filename += ".csv";
            }
            ofstream csvFile(filename);
            if (!csvFile.is_open()) {
                cout << "Error: Could not open file " << filename << " for writing.\n";
                continue;
            }
            //header
            csvFile << "+-------+---------------------+------------------+------------------+------------------+-------+\n";
            csvFile << "| Index | Timestamp           | Data             | Hash             | Previous Hash    | Nonce |\n";
            csvFile << "+-------+---------------------+------------------+------------------+------------------+-------+\n";

            for (int i = 0; i < blockChain.chain_length(); ++i) {
                Block b = blockChain.get_block(i);
                //timne
                time_t raw_time = b.get_timestamp();
                struct tm timeinfo;
                char buffer[80];
                localtime_s(&timeinfo, &raw_time);
                strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &timeinfo);               
                //data
                string data = b.get_data();
                if (data.length() > 16) {
                    data = data.substr(0, 13) + "...";
                }
                //hash
                string hash = b.get_hash();
                if (hash.length() > 16) {
                    hash = hash.substr(0, 13) + "...";
                }
                //prev_hash
                string prev_hash = b.get_prev_hash();
                if (prev_hash.length() > 16) {
                    prev_hash = prev_hash.substr(0, 13) + "...";
                }
                //separator
                csvFile << "| " << setw(5) << b.get_index() << " | "
                       << setw(19) << buffer << " | "
                       << setw(16) << data << " | "
                       << setw(16) << hash << " | "
                       << setw(16) << prev_hash << " | "
                       << setw(5) << b.get_nonce() << " |\n";
                csvFile << "+-------+---------------------+------------------+------------------+------------------+-------+\n";
            }
            csvFile.close();
            cout << "Blockchain data exported to " << filename << " in table format" << endl;
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
