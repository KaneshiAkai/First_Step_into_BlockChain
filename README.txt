================================================================================
                        BLOCKCHAIN IMPLEMENTATION PROJECT
================================================================================

OVERVIEW:
---------
This is a educational blockchain implementation written in C++. It features:
- Custom hash table implementation for fast block lookup
- Proof of Work mining algorithm
- SHA-512 cryptographic hashing
- Blockchain integrity verification
- CSV export functionality
- Interactive command-line interface

SYSTEM REQUIREMENTS:
-------------------
- Windows 10/11
- MinGW-w64 (MSYS2)
- OpenSSL library
- C++11 compiler support

INSTALLATION & SETUP:
--------------------
1. Install MSYS2 from https://www.msys2.org/
2. Open MSYS2 terminal and install required packages:
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-openssl

3. Add MinGW to your PATH:
   C:\msys64\mingw64\bin

PROJECT STRUCTURE:
-----------------
BlockChain/Demo/
├── include/           # Header files
│   ├── blockchain.h   # Main blockchain class
│   ├── block.h        # Block data structure
│   ├── hashtable.h    # Custom hash table implementation
│   ├── hash.h         # SHA-512 hashing functions
│   ├── miner.h        # Proof of work mining
│   └── common.h       # Common includes
├── src/               # Implementation files
│   ├── blockchain.cpp
│   ├── block.cpp
│   ├── hashtable.cpp
│   ├── hash.cpp
│   └── miner.cpp
├── test/              # Test files
│   └── test.cpp       # Main program
├── obj/               # Object files (auto-generated)
├── makefile           # Build configuration
└── README.txt         # This file

HOW TO BUILD & RUN:
------------------
1. Open Command Prompt in project directory
    use the below code to direct to your folder in terminal
    cd "your_folder" 

2. Build the project:
   mingw32-make

3. Run the program:
   mingw32-make run

4. Clean build files:
   mingw32-make clean

AVAILABLE COMMANDS:
------------------
add <data>       - Add a new block with custom data
show <index>     - Display block at specific index (0 = genesis)
latest           - Show the most recent block
length           - Display current chain length
print            - Display all blocks in the chain
gethash <hash>   - Find block by its hash value
verify           - Check blockchain integrity
hashmap          - Show hash table statistics and content
generate <n>     - Generate n blocks with random data
export <file>    - Export blockchain to CSV format
help             - Show command list
exit             - Quit program

================================================================================
                               DEMO TEST CASES
================================================================================

TEST CASE 1: BASIC BLOCKCHAIN OPERATIONS
----------------------------------------
Purpose: Demonstrate basic blockchain functionality

Commands to run:
1. length                    # Should show: 1 (genesis block)
2. show 0                    # Display genesis block
3. add Hello World          # Add first custom block
4. add Second Block         # Add second custom block
5. latest                   # Show most recent block
6. print                    # Display entire blockchain
7. length                   # Should show: 3

Expected Results:
- Genesis block at index 0 with data "First Block Ever"
- Custom blocks at indices 1 and 2
- Each block should have proper hash linking
- Chain length increases correctly

TEST CASE 2: HASH-BASED LOOKUP
------------------------------
Purpose: Test hash table functionality

Commands to run:
1. add Test Block for Hash Lookup
2. latest                   # Note the hash value displayed
3. gethash <copy_the_hash>  # Use actual hash from step 2
4. hashmap                  # Show hash table statistics

Expected Results:
- Block found successfully using hash
- Hash table shows proper distribution
- Load factor displayed correctly

TEST CASE 3: BLOCKCHAIN INTEGRITY
---------------------------------
Purpose: Verify blockchain security features

Commands to run:
1. generate 5               # Generate 5 random blocks
2. verify                   # Check blockchain integrity
3. print                    # View all blocks

Expected Results:
- All 5 blocks generated successfully
- Integrity check passes
- All hash links verified
- Timestamps in chronological order

TEST CASE 4: BULK OPERATIONS
----------------------------
Purpose: Test performance with multiple blocks

Commands to run:
1. generate 10              # Generate 10 blocks quickly
2. length                   # Should show 11 (10 + genesis)
3. hashmap                  # Check hash table performance
4. export demo_blockchain   # Export to CSV file

Expected Results:
- 10 blocks generated efficiently
- Hash table maintains good performance
- CSV file created with proper formatting
- Load factor remains reasonable

TEST CASE 5: EDGE CASES & ERROR HANDLING
----------------------------------------
Purpose: Test error handling and edge cases

Commands to run:
1. show 999                 # Index out of bounds
2. show -1                  # Negative index
3. add                      # Missing data
4. gethash                  # Missing hash
5. gethash invalid_hash     # Invalid hash
6. export                   # Missing filename

Expected Results:
- Appropriate error messages for each case
- Program continues running without crashes
- Input validation works correctly

DEMO PRESENTATION SCRIPT:
------------------------
For a 5-minute demonstration to lecturer:

1. INTRODUCTION (30 seconds)
   "This is a blockchain implementation with custom hash table and proof-of-work mining."
   Command: help

2. BASIC FUNCTIONALITY (1 minute)
   "Let's see the genesis block and add some data."
   Commands: show 0
            add "Student Project Demo"
            latest

3. MINING DEMONSTRATION (1.5 minutes)
   "Each block requires proof-of-work mining with difficulty target."
   Commands: add "Blockchain Technology"
            # Show mining progress with attempts/nonce

4. HASH TABLE LOOKUP (1 minute)
   "Fast block lookup using custom hash table implementation."
   Commands: latest          # Copy the hash
            gethash <hash>   # Demonstrate O(1) lookup
            hashmap          # Show hash table statistics

5. INTEGRITY & BULK TESTING (1.5 minutes)
   "Generate multiple blocks and verify chain integrity."
   Commands: generate 5
            verify           # Show integrity checking
            export demo      # Export to CSV

6. CONCLUSION (30 seconds)
   "The blockchain maintains cryptographic integrity with efficient hash-based storage."
   Commands: print           # Show final blockchain state

TROUBLESHOOTING:
---------------
Q: Compilation fails with "undefined reference to SSL functions"
A: Ensure OpenSSL is properly installed: pacman -S mingw-w64-x86_64-openssl

Q: "WinMain not found" error
A: Run: mingw32-make clean && mingw32-make

Q: Mining takes too long
A: The difficulty is set to 149. Blocks typically mine in 5-15 seconds.

Q: Hash table shows many collisions
A: This is normal with small capacity (700). Real implementations use larger tables.

TECHNICAL DETAILS:
-----------------
- Hash Function: SHA-512
- Mining Algorithm: Sum of hex digits divisible by difficulty
- Hash Table: Chaining with prime number capacity
- Memory Management: Manual allocation/deallocation
- Time Complexity: O(1) average for hash operations, O(n) for chain traversal

AUTHOR & CREDITS:
----------------
Implementation: Student Blockchain Project
Hash Algorithm: OpenSSL SHA-512
Build System: MinGW Make
Development Environment: VS Code

For questions or issues, refer to source code comments or contact the development team.

================================================================================
                                END OF README
================================================================================
