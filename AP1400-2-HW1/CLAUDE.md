# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 要求

1. 引导我完成, 不要帮助我完成, 你需要做的是提示我, 如果我需要答案, 我会直接说的
2. 我写错的地方, 你需要整理在一个文档里面, 做详细的记录(发现错误, 直接更新文档)

## Project Overview

This is a C++ linear algebra homework assignment (AP1400-2-HW1) implementing matrix operations library. The project implements various matrix functions including basic operations, determinants, inverse matrices, and elementary row operations.

## Build System

- **Language**: C++ (C++14 standard)
- **Build Tool**: CMake (minimum version 3.13)
- **Testing Framework**: Google Test (GTest)

### Common Commands

```bash
# Build the project
mkdir -p build && cd build
cmake ..
make

# Run the program (with debug section active by default)
./main

# Run unit tests (modify main.cpp to set flag to false)
# Edit src/main.cpp line 8: change `if (true)` to `if (false)`
./main
```

### Docker Support

```bash
# Build and run with Docker
docker build -t ap-hw1 .
docker run ap-hw1
```

## Code Architecture

### Core Structure

- **`include/hw1.h`**: Header file for all function declarations (currently minimal)
- **`src/hw1.cpp`**: Implementation file for all matrix operations (currently empty)
- **`src/main.cpp`**: Entry point with debug section and test runner toggle
- **`src/unit_test.cpp`**: Comprehensive Google Test suite (currently commented out)

### Key Design Patterns

1. **Namespace Organization**: All functions must be implemented in `algebra` namespace
2. **Matrix Type**: Uses `using Matrix = std::vector<std::vector<double>>;` type alias
3. **Error Handling**: Functions should throw `std::logic_error` for invalid operations
4. **Test-Driven Development**: Extensive unit tests define expected behavior

### Required Functions to Implement

The library requires implementing these functions in the `algebra` namespace:

- Matrix creation: `zeros()`, `ones()`, `random()`
- Display: `show()` (with 3 decimal places using `<iomanip>`)
- Operations: `multiply()`, `sum()`, `transpose()`
- Advanced: `minor()`, `determinant()`, `inverse()`, `concatenate()`
- Elementary Row Operations: `ero_swap()`, `ero_multiply()`, `ero_sum()`
- Upper triangular: `upper_triangular()` (bonus: handle zero pivots)

### Special Requirements

- Use `<random>` library (not `rand()`/`srand()`) for random number generation
- Use `<iomanip>` for formatted matrix display (3 decimal places)
- Handle edge cases (empty matrices, dimension mismatches, singular matrices)
- Determinant calculation must use minor expansion method only
- Elementary row operations are used to implement upper triangular form

### Test Toggle

The main function has a toggle mechanism:
- Set `if (true)` on line 8 of `src/main.cpp` for debug mode
- Set `if (false)` to run the comprehensive unit test suite

### Development Notes

- All implementations go in `src/hw1.cpp` and `src/hw1.h`
- Do not modify other files except for debugging in main.cpp debug section
- The project includes comprehensive unit tests that define exact expected behavior
- Bonus question involves handling zero pivots in upper triangular transformation