# Matrix calculator

## Copyright 2022 Zaharia Nicusor-Alexandru

### Project Idea

The program simulates MatLab/Octave.
It processes matrixes (it memorates them, their number of lines and their number of columns).
The supported operations are:
- matrix printing
- matrix cropping
- matrix multiplication and exponentiation
- dynamically allocating and deallocating matrixes from memory


### Tasks description and Workflow

The first thing in the project is the **matrix structure**.

```C
struct matrix {
	 /**
	 * @brief   double int pointer for the matrix.
	 */
	int **mat;
	 /**
	 * @brief   n for number of lines and m for number of columns.
	 */
	int n;
	int m;
};
```

In `main()`, a pointer is declared so the array of matrixes can be dynamically reallocated.

The program reads a char from `STDIN` until 'Q' is read, when it stops. 

If the letter **'L'** is read, the matrix counter in incremented, then the number of lines and the number of columns is read, the matrix is allocated its elements are read.

When letter **'D'** is read, the number of lines and the number of columns are printed for a given matrix index.

Reading the letter **'P'**, will print the values of the matrix whose index is given.

Letter **'C'** stands for cropping, a function that reads the number of the lines and the number of the columns.
It allocates dynamically a matrix in which the new matrix in which the new values (according to the lines and the columns given in the command).
It frees the old matrix from the memory, it allocates a new matrix with the new number of lines and the new number of columns and copies the values from the auxiliary matrix.
All auxiliary resources are deallocated.

When reading the letter **'M'** a new matrix is added at the final of the array of matrixes.
A matrix multiplying will be performed with the indexes of the matrixes from the instruction and the multiplied values are memorated in the new matrix.

If the letter **'O'** is read, matrixes will be sort by the sum of their values.
The algorithm used for sorting is selection sort.

By reading the letter **'T'** a function to dynamically allocate the transpose of
the matrix is called. The initial matrix is deallocated and is replaced **in-place**
with its transpose.

For the letter **'R'** a matrix is raised at a given power. The algorithm works in
`logarithmic time` and it uses a helper function and two dyanimically alocated
matrixes to compute the matrix to the given power. The base matrix is replaced by
the new matrix, where the new matrix is `the exponentiation of the given matrix`.
Before leaving the functions, all helper resources are deallocated.

**'F'** letter is used to delete a matrix from the memory, and the matrixes
that follows it will be shifted one position to left. But a problem raises with
this, the last matrix will appear twice. In order to keep only one copy, the
counter for the matrixes is decremented and the new double pointer is reallocated
according to the new change.

> Note: If another letter beside those is read, an error message will be printed.

When the program ends, all the matrixes from the memory are deallocated and
**all memory is freed, thus having 0 memory leaks**.

