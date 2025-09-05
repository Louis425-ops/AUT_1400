# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview
This is a C++ homework project (AP1400-2-HW3) implementing a Binary Search Tree (BST). The project consists of:
- `Node` class: represents individual nodes in the BST (defined inside BST class)
- `BST` class: manages the binary search tree structure and operations

## Build System
Uses CMake with C++20 standard and Google Test for unit testing.

### Build Commands
```bash
# Build the project
mkdir build && cd build
cmake ..
make

# Run the program (debug mode by default)
./main

# Run unit tests (change main.cpp line 7 from true to false)
./main
```

## Code Structure
- `include/bst.h` - Header file for BST implementation (currently empty, needs implementation)
- `src/bst.cpp` - Implementation file (currently minimal, needs implementation)  
- `src/main.cpp` - Main program with debug section and unit test runner
- `src/unit_test.cpp` - Google Test unit tests

## Development Constraints
- **ONLY modify**: `bst.h`, `bst.cpp`, and debug section of `main.cpp`
- Cannot alter function signatures or add new member functions unless specified
- May add necessary keywords (const, virtual, etc.) to existing functions

## Key Implementation Requirements
### Node Class (defined inside BST):
- Constructor variants: default, parameterized, copy
- Operators: `<<` for printing, comparison operators with integers (`>`, `>=`, `<`, `<=`, `==`)
- Members: `int value`, `Node* left`, `Node* right`

### BST Class:
- Core operations: `add_node`, `delete_node`, `find_node`, `find_parrent`, `find_successor`
- Tree traversal: `bfs` with `std::function` parameter for lambda operations
- Utilities: `get_root`, `length`
- Operators: `<<` for tree printing, `++` (pre/post increment)
- Rule of 5: destructor, copy/move constructors, copy/move assignment
- Challenge: variadic constructor for multiple node initialization

## Testing
Toggle between debug mode and unit tests by changing the boolean condition in `main.cpp:7`:
- `true` - debug mode (default)
- `false` - run Google Test suite

The project uses Google Test framework for comprehensive BST functionality testing.