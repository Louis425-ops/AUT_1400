# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a C++ cryptocurrency simulation homework project implementing a simple centralized cryptocurrency system with Server and Client classes. The project uses RSA digital signatures, SHA-256 hashing, and a mining mechanism with proof-of-work.

## Build System

The project uses CMake with C++20 standard and requires:
- OpenSSL library for cryptographic functions
- Google Test (GTest) for unit testing

### Build Commands
```bash
mkdir build && cd build
cmake ..
make
```

### Run Tests
```bash
./main
```
The main executable runs unit tests by default. To use debug mode, change the condition in `src/main.cpp:10` from `false` to `true`.

## Architecture

### Core Classes
- **Server**: Manages clients, wallets, transactions, and mining
  - `clients` map: `std::map<std::shared_ptr<Client>, double>` stores client wallets
  - Handles pending transactions via global `pending_trxs` vector
  - Mining requires 3 consecutive zeros in first 10 digits of SHA-256 hash
  - Successful mining awards 6.25 coins

- **Client**: Represents cryptocurrency users
  - Has RSA key pair for digital signatures
  - Can transfer money and generate nonces for mining
  - Each new client starts with 5 coins

### Transaction Format
Transactions use string format: `"sender-receiver-value"` (e.g., `"ali-hamed-1.5"`)

### Global Variables
- `std::vector<std::string> pending_trxs` - declared outside Server class
- Required for `show_pending_transactions()` and `show_wallets()` functions

### Cryptographic Functions
Located in `crypto.cpp/h`:
- `crypto::sha256(string)` - SHA-256 hashing
- `crypto::generate_key(public_key, private_key)` - RSA key generation  
- `crypto::signMessage(private_key, data)` - Digital signing
- `crypto::verifySignature(public_key, data, signature)` - Signature verification

## Development Restrictions

- Only modify: `server.cpp/h`, `client.cpp/h`, and debug section of `main.cpp`
- Client IDs must be unique (server auto-appends 4-digit random number if duplicate)
- Do not use `srand()` for random number generation
- Server class requires specific function signatures as defined in homework specification

## File Structure
- `include/` - Header files (server.h, client.h, crypto.h)
- `src/` - Implementation files and main.cpp with unit tests
- `CMakeLists.txt` - Build configuration
- Headers currently contain only guard includes - implementation needed
- 你要引导我完成这个作业, 而不是直接告诉我答案
- 维护一个文档, 每次发现我的错误, 你都要在这个文档中记录. 下一次更新文档的时候记得检查一下原来的错误有没有修正过来
- 重要的知识点, 我会告诉你让你"写入文档", 你就在记录错误的文档中记录一下注明"知识点", 然后做相应的记录和阐释
- 更新新的错误的时候, 不要覆盖原来的错误