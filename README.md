# Arbitrary-Precision-Calculator
Arbitrary Precision Calculator is a C project that performs addition, subtraction, multiplication, and division on extremely large integers beyond normal data type limits, using linked lists (or arrays) to store digits and handle calculations digit-by-digit.
# Arbitrary Precision Calculator (APC)

A C-based **Arbitrary Precision Calculator** that performs arithmetic operations on very large numbers which cannot be handled by standard data types.  
This project is implemented using **linked lists** to store and manipulate numbers digit by digit.



## 📌 Features

- Supports **large integers of arbitrary length**
- Operations implemented:
  - ➕ Addition
  - ➖ Subtraction
  - ✖️ Multiplication
  - ➗ Division
- Modular design with separate source files for each operation
- Command-line based execution
- Efficient memory management using dynamic allocation


## 🗂️ Project Structure

APC_Arbitrary_Precision_Calculator

├── main.c # Program entry point\
├── apc.c # Core logic and control flow\
├── addition.c # Arbitrary precision addition\
├── subtraction.c # Arbitrary precision subtraction\
├── multiplication.c # Arbitrary precision multiplication\
├── division.c # Arbitrary precision division\
└── header.h # Structure definitions and function prototypes


## ⚙️ Compilation

Use `gcc` to compile all source files:

```bash
gcc *.c

```
## 🧪 Usage

The program accepts operands and operator as **command-line arguments**.

### General Usage
```bash
./a.out <number1> <operator> <number2>
```

## 🧠 Concepts Used

- Linked Lists
- Dynamic Memory Allocation
- Pointers
- Modular Programming in C
- Data Structures and Algorithms (DSA)

## 📚 Learning Outcome

This project demonstrates how arithmetic operations can be implemented without relying on built-in data types, making it useful for understanding:

- Low-level number representation
- Memory-efficient computation
- Core DSA principles in real-world applications

## 👨‍💻 Author

**SANDEEP HOSMANI**
