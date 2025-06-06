## SYSTEM REQUIREMENTS

- Windows 10/11
- MinGW-w64 (MSYS2)
- OpenSSL library
- C++11 compiler support

## INSTALLATION & SETUP

1. Install MSYS2 from https://www.msys2.org/
2. Open MSYS2 terminal and install required packages:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-openssl
   ```

3. Add MinGW to your PATH:
   ```
   C:\msys64\mingw64\bin
   ```

## PROJECT STRUCTURE

```
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
└── README.md          # This file
```

## HOW TO BUILD & RUN

1. Open Command Prompt in project directory
   ```bash
   cd "your_folder_path"
   ```

2. Build the project:
   ```bash
   mingw32-make
   ```

3. Run the program:
   ```bash
   mingw32-make run
   ```

4. Clean build files:
   ```bash
   mingw32-make clean
   ```

## AVAILABLE COMMANDS

| Command | Description |
|---------|-------------|
| `add <data>` | Add a new block with custom data |
| `show <index>` | Display block at specific index (0 = genesis) |
| `latest` | Show the most recent block |
| `length` | Display current chain length |
| `print` | Display all blocks in the chain |
| `gethash <hash>` | Find block by its hash value |
| `verify` | Check blockchain integrity |
| `hashmap` | Show hash table statistics and content |
| `generate <n>` | Generate n blocks with random data |
| `export <file>` | Export blockchain to CSV format |
| `help` | Show command list |
| `exit` | Quit program |

---

# DEMO TEST CASES

## TEST CASE 1: BASIC BLOCKCHAIN OPERATIONS

**Purpose:** Demonstrate basic blockchain functionality

**Commands to run:**
```bash
1. length                    # Should show: 1 (genesis block)
2. show 0                    # Display genesis block
3. add Hello World          # Add first custom block
4. add Second Block         # Add second custom block
5. latest                   # Show most recent block
6. print                    # Display entire blockchain
7. length                   # Should show: 3
```

**Expected Results:**
- Genesis block at index 0 with data "First Block Ever"
- Custom blocks at indices 1 and 2
- Each block should have proper hash linking
- Chain length increases correctly

## TEST CASE 2: HASH-BASED LOOKUP

**Purpose:** Test hash table functionality

**Commands to run:**
```bash
1. add Test Block for Hash Lookup
2. latest                   # Note the hash value displayed
3. gethash <copy_the_hash>  # Use actual hash from step 2
4. hashmap                  # Show hash table statistics
```

**Expected Results:**
- Block found successfully using hash
- Hash table shows proper distribution
- Load factor displayed correctly

## TEST CASE 3: BLOCKCHAIN INTEGRITY

**Purpose:** Verify blockchain security features

**Commands to run:**
```bash
1. generate 5               # Generate 5 random blocks
2. verify                   # Check blockchain integrity
3. print                    # View all blocks
```

**Expected Results:**
- All 5 blocks generated successfully
- Integrity check passes
- All hash links verified
- Timestamps in chronological order

## TEST CASE 4: BULK OPERATIONS

**Purpose:** Test performance with multiple blocks

**Commands to run:**
```bash
1. generate 10              # Generate 10 blocks quickly
2. length                   # Should show 11 (10 + genesis)
3. hashmap                  # Check hash table performance
4. export demo_blockchain   # Export to CSV file
```

**Expected Results:**
- 10 blocks generated efficiently
- Hash table maintains good performance
- CSV file created with proper formatting
- Load factor remains reasonable

## TEST CASE 5: EDGE CASES & ERROR HANDLING

**Purpose:** Test error handling and edge cases

**Commands to run:**
```bash
1. show 999                 # Index out of bounds
2. show -1                  # Negative index
3. add                      # Missing data
4. gethash                  # Missing hash
5. gethash invalid_hash     # Invalid hash
6. export                   # Missing filename
```

**Expected Results:**
- Appropriate error messages for each case
- Program continues running without crashes
- Input validation works correctly

---
