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

Pentru citirea literei 'P' se afiseaza valorile matricei al carei index este
dat.

Litera 'C' apeleaza functia pentru redimensionare, functie care citeste liniile
si coloanele dupa care se face redimensionarea, aloca dinamic o matrice in care
se memoreaza valorile aferente liniilor si coloanelor. Elibereaza matricea din
memorie, o aloca din nou cu un nou numar de linii si cu un nou numar de
coloane, apoi preia valorile din matricea ajutatoare. Se dealoca toate
resursele auxiliare.

La citirea literei 'M' se adauga o noua matrice la finalul multimii de matrice
cu numarul de linii si numarul de coloane conforme inmultirii a doua matrice.
Se efectueaza algoritmul de inmultire a doua matrice, iar valorile sunt
memorate in matricea produs.

Daca se citeste litera 'O' se sorteaza matricele in functie de suma elementelor
fiecarei matrice. Algoritmul de sortare este cel prin selectie.

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

