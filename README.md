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

Se ocupa cu prelucrarea matricelor (memorare, afisarea numarului de linii si a
numarului de coloane, afisarea valorilor, redimensionare, inmultire, sortare in
functie de suma elementelor, calcularea transpusei, ridicarea la putere si
eliminarea din memorie)

-----------------------------------------------------------------------------

### Functionare


Am declarat o variabila de tip pointer la o structura care ma ajuta sa accesez:
un dublu pointer (o matrice), numarul de linii si numarul de coloane.

Programul citeste un caracter de la STDIN pana cand intalneste caracterul 'Q'.

Daca este citita litera 'L', creste contorul pentru matrici, se citeste numarul
de linii si numarul de coloane, se aloca o matrice si se citesc elementele
acesteia.

Daca este citita litera 'D' se afiseaza numarul de linii si numarul de coloane
pentru o matrice al carei index este stiut.

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

