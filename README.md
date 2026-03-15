# ThreadedBinarySearchTree

A cleaned and refactored C++ implementation of a **threaded binary search tree**.

This project started as a university assignment and was later refactored into a more maintainable, testable repository with:

- a reproducible **VS Code devcontainer** setup
- a **CMake + Ninja** build
- a separate **test executable**
- cleaner encapsulation and copy/delete logic
- optional tooling for **Valgrind**, **clang-tidy**, **clang-format**, and **coverage**

The repo now contains a dedicated devcontainer config, `CMakeLists.txt`, a separate `tests.cpp`, and the original driver in `ass5.cpp`, which means the documented build flow should be based on CMake rather than the older ad hoc compile/script approach. 

## Features

- Threaded binary search tree storing positive `int` values
- Constructor builds a balanced BST from the range {1, 2, ..., n}
- Inorder traversal using threads (no recursion or stack required)
- Deep copy support
- Insert and remove operations (values must be positive; no duplicates)
- Separate test binary for regression coverage
- Containerized development workflow for reproducibility

## Project Layout

```text
.
├── .devcontainer/
│   ├── Dockerfile
│   └── devcontainer.json
├── .clang-format
├── .gitignore
├── CMakeLists.txt
├── README.md
├── ass5.cpp
├── tests.cpp
├── threadedBST.cpp
└── threadedBST.h
```

## Development Environment

This repo is set up to work cleanly inside a VS Code devcontainer.

### Host prerequisites

- Docker
- VS Code
- Dev Containers extension

### Open in container

From the repo root:

```sh
code .
```

Then in VS Code run:

> **Dev Containers: Reopen in Container**

The devcontainer includes the C++ toolchain and supporting tools used during the refactor, including clang, clangd, clang-tidy, clang-format, cmake, ninja, lldb, valgrind, and gcovr. The repo also includes the devcontainer configuration needed to rebuild that environment consistently.

## Build

Configure and build with CMake + Ninja:

```sh
cmake -S . -B build -G Ninja
cmake --build build
```

This produces:

- `build/tbst` — the assignment/demo driver
- `build/tbst_tests` — the regression test executable

The repo now contains a top-level `CMakeLists.txt` and test target rather than only the original flat assignment files, so CMake is the intended build entrypoint.

## Run

### Demo / assignment driver

```sh
./build/tbst
```

This is interactive — it will prompt you to enter a positive integer `n`, then build a threaded BST containing {1..n}, print it, copy it, remove even numbers from the copy, and print both.

### Tests

```sh
./build/tbst_tests
```

## Tooling

### Valgrind

Run the tests under Valgrind:

```sh
ulimit -n 1024
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./build/tbst_tests
```

### clang-tidy

Generate compile commands, then run static analysis:

```sh
cmake -S . -B build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
clang-tidy threadedBST.cpp -p build
clang-tidy ass5.cpp -p build
clang-tidy tests.cpp -p build
```

### clang-format

Check formatting:

```sh
clang-format --dry-run --Werror ass5.cpp threadedBST.cpp threadedBST.h tests.cpp
```

Format in place:

```sh
clang-format -i ass5.cpp threadedBST.cpp threadedBST.h tests.cpp
```

### Coverage

Build with coverage instrumentation:

```sh
cmake -S . -B build-coverage -G Ninja \
  -DCMAKE_CXX_FLAGS="--coverage -g -O0" \
  -DCMAKE_EXE_LINKER_FLAGS="--coverage"

cmake --build build-coverage
./build-coverage/tbst_tests
```

Generate a text report:

```sh
cd build-coverage
gcovr -r .. .
```

Generate an HTML report:

```sh
gcovr -r .. . --html-details coverage.html
```

## Notes on the Implementation

This is a threaded BST, not a self-balancing tree. A few things to keep in mind:

- The constructor always produces a balanced tree for the range {1..n}, but subsequent `add()` calls can unbalance it — there is no rebalancing.
- Inorder traversal is the main strength: threads allow traversal without a stack or recursion.
- Mutation logic is more complex than a plain BST because threads must be maintained on every insert and remove.
- Worst-case search/insert/delete is still O(n) if the tree becomes unbalanced through additions after construction.
- Only positive integers are supported; zero and negative values are not.

The refactor focused on making the implementation cleaner and safer while preserving its behavior as a threaded BST rather than turning it into a different tree type.

## Background

This repository began as a CSS 342 assignment implementation and was later cleaned up to improve:

- API boundaries
- iterator visibility
- deletion structure
- copy semantics
- regression testing
- development reproducibility

The current repository no longer matches the older script-driven README workflow; the cleaned version is now centered on CMake, the devcontainer, and the separate test target.