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

If the letter 'L' is read, the matrix counter in incremented, then the number of lines and the number of columns is read, the matrix is allocated its elements are read.

When letter 'D' is read, the number of lines and the number of columns are printed for a given matrix index.

Reading the letter 'P', will print the values of the matrix whose index is given.

Letter 'C' stands for cropping, a function that reads the number of the lines and the number of the columns.
It allocates dynamically a matrix in which the new matrix in which the new values (according to the lines and the columns given in the command).
It frees the old matrix from the memory, it allocates a new matrix with the new number of lines and the new number of columns and copies the values from the auxiliary matrix.
All auxiliary resources are deallocated.

When reading the letter 'M' a new matrix is added at the final of the array of matrixes.
A matrix multiplying will be performed with the indexes of the matrixes from the instruction and the multiplied values are memorated in the new matrix.

If the letter 'O' is read, matrixes will be sort by the sum of their values.
The algorithm used for sorting is selection sort.

Pentru citirea litere 'T' se apeleaza o functie ce aloca dinamic matricea
transpusa a unei matrice date. Matricea data se dealoca si este inlocuita cu
transpusa sa.

Cand se citeste litera 'R', se ridica la o putere data, o matrice. Algoritmul se
executa in timp logaritmic si se foloseste de doua subprograme si de doua
matrice alocate dinamic pentru a calcula matricea la puterea data. Matricea
baza este inlocuita de noua matrice, iar la final sunt dealocate toate
resursele ajutatoare.

Litera 'F' sterge din memorie o matrice, iar restul matricelor ce o succed sunt
mutate cu o pozitie la stanga. Ultima matrice se repeta de doua ori, deci
trebuie eliminata o data, iar contorul de matrici scade. pointerul de tip
struct este realocat in functie de noul contor.

Daca este citita o alta litera in afara de cele mentionate se afiseaza un mesaj
de eroare. 

La final se elimina toate matricele din memorie si se dealoca toate resursele
pentru a elibera memoria.

