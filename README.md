# Determinant of Matrices

A C command-line program for working with matrices, focused on transforming a matrix into triangular form and calculating its determinant.

The project was created as a learning exercise in C programming, dynamic memory allocation, matrix operations, and basic linear algebra algorithms.

## Features

* User input for matrix dimensions
* Dynamic memory allocation for matrix data
* Input validation for rows, columns, and matrix elements
* Matrix printing function
* Transformation of a matrix into triangular form
* Determinant calculation for square matrices
* Basic matrix rank calculation logic
* Matrix addition/subtraction function structure

## How It Works

The program reads a matrix from the user and stores it dynamically in memory.

For determinant calculation, the matrix is transformed into an upper triangular form using row operations. The determinant is then calculated as the product of the diagonal elements.

If row swaps are performed during the transformation, the determinant sign is adjusted.

The main algorithm is based on Gaussian elimination.

## Example

Input:

```txt
Please insert dimensions of matrix:
Insert rows: 3
Insert columns: 3

Enter elements of row 1 one by one:
Enter element 11: 1
Enter element 12: 2
Enter element 13: 3

Enter elements of row 2 one by one:
Enter element 21: 4
Enter element 22: 5
Enter element 23: 6

Enter elements of row 3 one by one:
Enter element 31: 7
Enter element 32: 8
Enter element 33: 9
```

Expected output:

```txt
The determinant of the matrix is: 0.00
```

## Tech Stack

* C
* Standard C library
* Dynamic memory allocation
* Basic linear algebra
* Gaussian elimination

## Main Functions

### `TransformMatrixTriangle`

Transforms the matrix into triangular form using row operations.

### `Det`

Calculates the determinant of a square matrix.

### `Rang`

Calculates the rank of a matrix by transforming it into triangular form and counting non-zero rows.

### `printMatrix`

Prints the matrix in a readable format.

### `SumSbs`

Performs matrix addition or subtraction depending on the selected operation.

## How to Compile

Using GCC:

```bash
gcc main.c -o determinant -lm
```

## How to Run

```bash
./determinant
```

On Windows:

```bash
determinant.exe
```

## Project Purpose

This project was built to practice:

* working with pointers in C
* allocating and freeing dynamic memory
* representing matrices with structs
* implementing matrix algorithms manually
* understanding determinant calculation through row operations

## Limitations

* The current version is a learning project and does not yet include a full menu system.
* Determinant calculation should only be used for square matrices.
* Some functions are still under development.
* The code can be improved with better memory safety and cleaner structure.

## Future Improvements

* Add a menu for choosing determinant, rank, addition, subtraction, and transpose operations
* Add support for matrix multiplication
* Improve memory management
* Add better error handling
* Separate the code into multiple files
* Add comments and documentation for each function
* Add tests with known matrices

## Status

Educational project under development.
