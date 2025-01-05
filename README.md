# Library Management System

A lightweight and efficient library management system implemented in C. This project provides features to add, search, and delete books using a combination of an array and a binary search tree for optimized performance.

---

## Table of Contents

- [Features](#features)
- [Technologies Used](#technologies-used)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

---

## Features

- **Add Books**: Insert books into the library using a binary search tree for indexing.
- **Search Books**: Search books by ISBN.
- **Delete Books**: Remove books from the library while maintaining tree and array consistency.
- **Efficient Storage**: Manage up to 1 million books with dynamic memory allocation and optimized slot reuse.

---

## Technologies Used

- **Programming Language**: C
- **Data Structures**: Binary Search Tree, Arrays
- **Testing Framework**: Unity Test Framework

---

## Installation

### Prerequisites

- GCC or any C compiler
- Git
- Unity Test Framework (included as a submodule in the repository)

### Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/library-management-system.git
   cd library-management-system
   ```

2. Ensure Unity is initialized (if using as a submodule):
   ```bash
   git submodule update --init --recursive
   ```

3. Compile the program using the provided scripts:

   #### Windows Batch Script: `build.bat`
   1. Open Command Prompt.
   2. Navigate to the project directory.
   3. Execute:
      ```cmd
      build.bat
      ```
   4. The executable will be created in the `build/` directory.

   #### Windows PowerShell Script: `build.ps1`
   1. Open PowerShell.
   2. Navigate to the project directory.
   3. Execute:
      ```powershell
      .\build.ps1
      ```
   4. The executable will be created in the `build/` directory.

---

## Usage

Run the compiled program:

```bash
./library
```



## Testing

### Unit tests are written using the Unity Test Framework.

#### Running Unit Tests with `run_test.bat`

1. Open Command Prompt.
2. Navigate to the `src/tests` directory.
3. Run the script:
   ```cmd
   run_test.bat
   ```
4. This script:
   - Compiles the test files.
   - Links the Unity Test Framework.
   - Executes the test suite.
   - Displays the test results in the console.

---

## Contributing

Contributions are welcome! Follow these steps to contribute:

1. Fork the repository.
2. Create a new branch for your feature:
   ```bash
   git checkout -b feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add new feature"
   ```
4. Push your branch:
   ```bash
   git push origin feature-name
   ```
5. Open a Pull Request.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Acknowledgments

- Unity Test Framework for lightweight unit testing.
