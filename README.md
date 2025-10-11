# Chess Legal Moves Calculator

This project is a **C++ chess legal moves calculator**. Its goal is to generate all legal moves from a given chess position using a custom C++ data structure for the board and game state.

---

## Project Overview

- **C++**: Implements the chess game logic, including the board representation, player turn, castling rights, en passant, and move generation.
- **Python**: Used to generate and verify board positions from FEN strings. The Python scripts create a `ChessGame`-like data structure and calculate legal moves to validate the C++ implementation.

---

## Getting Started

### Prerequisites

- A C++ compiler (C++17 or newer recommended)
- Python 3.12+
- [Poetry](https://python-poetry.org/) (for Python dependency management)
- Make (for the Makefile commands)

---

### Running the C++ Project

To build and run the C++ legal moves calculator:

```bash
make
```

This will compile and execute your C++ project.

---

### Running the Python Verification Scripts

1. **Set up the Python environment**:

```bash
make env
```

This installs dependencies and sets up a virtual environment.

2. **Run the Python script**:

```bash
make python
```

This executes the Python program which:

- Reads a FEN string
- Initializes a Python representation of the board
- Calculates legal moves
- Prints a `ChessGame` initializer that mirrors the C++ data structure

---

## Notes

- The Python project helps verify the correctness of the C++ legal move generator.
- The `ChessGame` struct in C++ can be initialized directly from the Python output for testing and validation.
- Make sure to use `make env` before `make python` to ensure the Python environment is properly configured.

---
