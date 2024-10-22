/**
 * @file    my_octave.c
 * @brief   This file contains the implementation of matrix operations.
 * 
 * @author  Zaharia Nicusor-Alexandru
 * @date    08-12-2022
 */

#include <stdio.h>
#include <stdlib.h>


/*structura care contine un dublu pointer, numarul de linii si
numarul de coloane*/
/**
 * @brief   Structure used for the matrix
 * 
 * This constant is used to prevent overflow in arithmetic operations.
 */
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


/**
 * @brief   Reads the number of lines and number of columns.
 * 
 * This function reads the number of lines and
 * the number of columns of a matrix.
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   Number of current matrixes stored by v.
 * 
 * @note    The number of lines and the number of columns must be signed int.
 */
void read_rows_cols(struct matrix *v, int count)
{
	scanf("%d%d", &v[count].m, &v[count].n);
}


/**
 * @brief   Allocates memory for a (m x n) matrix.
 * 
 * This function dynamically allocates memory for a matrix with m lines
 * and n columns.
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   ID of the current matrix.
 * @param	m	Number of lines for the matrix.
 * @param	n	Number of columns for the matrix
 * 
 * @note    The function checks if the resources were allocated.
 */
void alloc_matrix(struct matrix *v, int count, int m, int n)
{
	v[count].mat = (int **)malloc(m * sizeof(int *));
	if (!v[count].mat) {
		printf("Malloc failed!\n");
		exit(0);
	} else {
		for (int i = 0; i < m; i++) {
			v[count].mat[i] = (int *)malloc(n * sizeof(int));
			if (!v[count].mat[i]) {
				printf("Malloc failed!\n");
				exit(0);
			}
		}
	}
}


/**
 * @brief   Reads from STDIN the elements of the matrix.
 * 
 * This function reads from Standard Input the values that will
 * be stored in the matrix
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   ID of the current matrix.
 * 
 * @note    The read values will be signed ints.
 */
void load_matrix(struct matrix *v, int count)
{
	for (int i = 0; i < v[count].m; i++)
		for (int j = 0; j < v[count].n; j++)
			scanf("%d", &v[count].mat[i][j]);
}

/*functie care elibereaza memoria alocata unei matrici*/
void free_matrix(struct matrix *v, int count, int m)
{
	for (int i = 0; i < m; i++)
		free(v[count].mat[i]);
	free(v[count].mat);
}

/*functie care citeste indexul unei matrici si afiseaza matricea
sau, in caz contrar, mesaj daca indexul dat nu corespunde
unei matrici din memorie */
void print_matrix(struct matrix *v, int count)
{
	int index;
	scanf("%d", &index);
		if (index <= count && index >= 0) {
			for (int i = 0; i < v[index].m; i++) {
				for (int j = 0; j < v[index].n; j++)
					printf("%d ", v[index].mat[i][j]);
				printf("\n");
			}
		} else {
			printf("No matrix with the given index\n");
		}
}


/*functie care citeste indexul unei matrici si afiseaza numarul
ei de linii si de coloane sau mesaj daca indexul dat nu corespunde
unei matrici din memorie */
/**
 * @brief   Prints the number of lines and the number of columns of a matrix.
 * 
 * This function reads the ID of a matrix and prints
 * the number of the lines and the number of the columns of the matrix.
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   Number of current matrixes stored by v.
 * 
 * @note    If the index (ID) is invalid, a message will be printed.
 */
void print_rows_cols(struct matrix *v, int count)
{
	int index;
	scanf("%d", &index);
	if (index > count || index < 0)
		printf("No matrix with the given index\n");
	else
		printf("%d %d\n", v[index].m, v[index].n);
}

/*functie care redimensioneaza numarul de linii si numarul de
coloane al unei matrici*/
void crop_matrix(struct matrix *v, int count)
{
	int index, m, n, *index_rows, *index_cols, **copy, i, j;
	scanf("%d", &index);
	if (index <= count && index >= 0) {
		scanf("%d", &m);
		//pointer care memoreaza liniile dupa care fac redimensionarea
		index_rows = (int *)malloc(m * sizeof(int));
		if (!index_rows) {
			printf("Malloc failed!\n");
			exit(0);
		}
		for (int i = 0; i < m; i++)
			scanf("%d", &index_rows[i]);
		scanf("%d", &n);
		//pointer care memoreaza coloanele dupa care fac redimensionarea
		index_cols = (int *)malloc(n * sizeof(int));
		if (!index_cols) {
			printf("Malloc failed!\n");
			exit(0);
		}
		for (int i = 0; i < n; i++)
			scanf("%d", &index_cols[i]);
		//aloc dinamic un dublu pointer care memoreaza matricea redimensionata
		copy = (int **)malloc(m * sizeof(int *));
		if (!copy) {
			printf("Malloc failed!\n");
			exit(0);
		}
		for (i = 0; i < m; i++) {
			copy[i] = (int *)malloc(n * sizeof(int));
			if (!copy[i]) {
				printf("Malloc failed!\n");
				exit(0);
			}
		}
		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				copy[i][j] = v[index].mat[index_rows[i]][index_cols[j]];
		//eliberez vechea matrice si o aloc dinamic cu noile dimensiuni
		free_matrix(v, index, v[index].m);
		alloc_matrix(v, index, m, n);
		v[index].m = m;
		v[index].n = n;
		//copiez valorile din dublu pointerul ajutator in matrice
		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				v[index].mat[i][j] = copy[i][j];
		/*eliberez toti pointerii de care m-am folosit pentru a
		prelucra dimensiunile si valorile matricii*/
		for (int i = 0; i < m; i++)
			free(copy[i]);
		free(copy);
		free(index_rows);
		free(index_cols);
	} else {
		printf("No matrix with the given index\n");
	}
}

/* functie care inmulteste doua matrice*/
void matrix_multiplication(struct matrix *v, int *count)
{
	int index1, index2, i, j, k, x;
	scanf("%d%d", &index1, &index2);
	/*daca indecsii sunt negativi sau mai mari decat numarul de matrice
	memorate afisez mesajul*/
	if (index1 > *count - 1 || index2 > *count - 1) {
		printf("No matrix with the given index\n");
		(*count)--;
	} else if (v[index1].n != v[index2].m) {
		/*daca numarul de coloane de la prima matrice este diferit de numarul
		de linii de la a doua matrice afisez mesajul*/
		printf("Cannot perform matrix multiplication\n");
		(*count)--;
	} else {
		//aloc dinamic o matrice noua pe care o initializez cu 0
		v[*count].mat = (int **)calloc(v[index1].m, sizeof(int *));
		if (!v[*count].mat) {
			printf("Malloc failed!\n");
			exit(0);
		}
		for (i = 0; i < v[index1].m; i++) {
			v[*count].mat[i] = (int *)calloc(v[index2].n, sizeof(int));
			if (!v[*count].mat[i]) {
				printf("Malloc failed!\n");
				exit(0);
			}
		}
		//algoritm de inmultirea a doua matrice
		for (i = 0; i < v[index1].m; i++)
			for (j = 0; j < v[index2].n; j++)
				for (k = 0; k < v[index1].n; k++) {
					x = v[index1].mat[i][k] * v[index2].mat[k][j];
					v[*count].mat[i][j] += x;
					v[*count].mat[i][j] %= 10007;
					if (v[*count].mat[i][j] < 0)
						v[*count].mat[i][j] += 10007;
				}
		v[*count].m = v[index1].m;
		v[*count].n = v[index2].n;
	}
}

//agloritm de sortare al matricelor in functie de suma elementelor
void sort_matrix(struct matrix *v, int count, struct matrix aux)
{
	int *sum, i, j, k, sum_aux;
	//pointer alocat dinamic care memoreaza suma elementelor fiecarei matrice
	sum = (int *)calloc(count + 1, sizeof(int));
	if (!sum) {
		printf("Calloc failed!\n");
		exit(0);
	}
	for (i = 0; i <= count; i++) {
		for (j = 0; j < v[i].m; j++)
			for (k = 0; k < v[i].n; k++) {
				sum[i] = (sum[i] + v[i].mat[j][k]) % 10007;
				if (sum[i] < 0)
					sum[i] += 10007;
			}
	}
	//sortarea prin selectie
	for (i = 0; i < count; i++)
		for (j = i + 1; j <= count; j++)
			if (sum[i] > sum[j]) {
				aux = v[i];
				v[i] = v[j];
				v[j] = aux;
				sum_aux = sum[i];
				sum[i] = sum[j];
				sum[j] = sum_aux;
			}
	//eliberez din memorie pointerul
	free(sum);
}

//functie ce inlocuieste o matrice cu transpusa sa
void transpose_matrix(struct matrix *v, int count)
{
	int **transpose, i, j, m, n, index;
	scanf("%d", &index);
	if (index > count || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		m = v[index].n;
		n = v[index].m;
		//aloc dinamic un dublu pointer ce retine transpusa matricii date
		transpose = (int **)malloc(m * sizeof(int *));
		if (!transpose) {
			printf("Malloc failed!\n");
			exit(0);
		}
		for (i = 0; i < m; i++) {
			transpose[i] = (int *)malloc(n * sizeof(int));
			if (!transpose[i]) {
				printf("Malloc failed!\n");
				exit(0);
			}
		}
		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				transpose[i][j] = v[index].mat[j][i];
		//eliberez si aloc matricea data
		free_matrix(v, index, v[index].m);
		alloc_matrix(v, index, m, n);
		//copiez valorile din dublu pointerul ajutator in matricea nou alocata
		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				v[index].mat[i][j] = transpose[i][j];
		v[index].m = m;
		v[index].n = n;
		//eliberez din memorie dublu pointerul
		for (int i = 0; i < m; i++)
			free(transpose[i]);
		free(transpose);
	}
}

/* functie auxiliara pentru functia power_matrix.
Aceasta inmulteste doua matrice date si memoreaza rezultatul in
matricea ajutatoare p_aux_matrix*/
void matrix_multi_2(struct matrix *v, int **p_matrix, int index)
{
	int **p_aux_matrix, i, j, k, x, n;
	n = v[index].n;
	p_aux_matrix = (int **)calloc(n, sizeof(int *));
	if (!p_aux_matrix) {
		printf("Calloc failed!\n");
		exit(0);
	}
	for (i = 0; i < n; i++) {
		p_aux_matrix[i] = (int *)calloc(n, sizeof(int));
		if (!p_aux_matrix[i]) {
			printf("Calloc failed!\n");
			exit(0);
		}
	}
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++) {
				x = p_matrix[i][k] * v[index].mat[k][j];
				p_aux_matrix[i][j] += x;
				p_aux_matrix[i][j] %= 10007;
				if (p_aux_matrix[i][j] < 0)
					p_aux_matrix[i][j] += 10007;
			}
	//copiez rezultatele din matricea ajutatoare in matricea rezultat
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			p_matrix[i][j] = p_aux_matrix[i][j];
	for (i = 0; i < n; i++)
		free(p_aux_matrix[i]);
	free(p_aux_matrix);
}

//functie ce ridica la o putere data, o matrice in timp logaritmic
void power_matrix(struct matrix *v, int count)
{
	int index, power;
	scanf("%d%d", &index, &power);
	/*daca puterea sau indexul nu corespund cerintelor,
	afisez mesajele de eroare */
	if (index > count || index < 0) {
		printf("No matrix with the given index\n");
	} else if (power < 0) {
		printf("Power should be positive\n");
	} else if (v[index].n != v[index].m) {
		printf("Cannot perform matrix multiplication\n");
	} else {
		int **copy, **p_matrix, n, i, j, k, x;
		n = v[index].n;
		/*aloc dinamic doi pointeri care ma ajuta la inmultiri,
		unde p_matrix este matricea finala*/
		p_matrix = (int **)calloc(n, sizeof(int *));
		if (!p_matrix) {
			printf("Calloc failed!\n");
			exit(0);
		}
		for (i = 0; i < n; i++) {
			p_matrix[i] = (int *)calloc(n, sizeof(int));
			if (!p_matrix) {
				printf("Calloc failed!\n");
				exit(0);
			}
		}
		//initializare cu In
		for (i = 0; i < n; i++)
			p_matrix[i][i] = 1;
		//algoritm de ridicare la putere in timp alogritmic
		while (power) {
			if (power % 2) {
			/*daca puterea este impara inmultesc matricea baza (v[index].mat)
			cu matricea rezultat (p_matrix)*/
				power--;
				matrix_multi_2(v, p_matrix, index);
			}
			power /= 2;
			copy = (int **)calloc(n, sizeof(int *));
			if (!copy) {
				printf("Calloc failed!\n");
				exit(0);
			}
			for (i = 0; i < n; i++) {
				copy[i] = (int *)calloc(n, sizeof(int));
				if (!copy[i]) {
					printf("Calloc failed!\n");
					exit(0);
				}
			}
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					copy[i][j] = v[index].mat[i][j];
			/*la fiecare pas inmultesc matricea baza cu ea insasi si mut
			rezultatul din matricea auxiliara in matricea baza*/
			matrix_multi_2(v, copy, index);
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					v[index].mat[i][j] = copy[i][j];
			//eliberez din memorie primul pointer pe care l-am folosit
			for (i = 0; i < n; i++)
				free(copy[i]);
			free(copy);
		}
		//copiez rezultatele din matricea rezultat in matricea baza (initiala)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				v[index].mat[i][j] = p_matrix[i][j];
		//eliberez din memorie al doilea pointer de care m-am folosit
		for (i = 0; i < n; i++)
			free(p_matrix[i]);
		free(p_matrix);
	}
}

/*functie care sterge din memorie o matrice si care muta restul
matricelor cu o pozitie la stanga
functia returneaza 1 daca operatia s-a efectuat sau 0, in caz contrar*/
int free_and_move_matrix(struct matrix *v, int *count)
{
	int index, i, j, k, ok;
	scanf("%d", &index);
	if (index > *count || index < 0) {
		printf("No matrix with the given index\n");
		ok = 0;
	} else {
		/*sterg matricea i, o aloc dinamic si copiez elementele din
		matricea i+1 in matricea i*/
		for (i = index; i < *count; i++) {
			free_matrix(v, i, v[i].m);
		alloc_matrix(v, i, v[i + 1].m, v[i + 1].n);
		v[i].m = v[i + 1].m;
		v[i].n = v[i + 1].n;
		for (j = 0; j < v[i].m; j++)
			for (k = 0; k < v[i].n; k++)
				v[i].mat[j][k] = v[i + 1].mat[j][k];
		}
		//eliberez din memorie ultima matrice si scad numarul de matrice
		free_matrix(v, *count, v[*count].m);
		(*count)--;
		ok = 1;
	}
	return ok;
}

//functie care imi elimina din memorie toate matricele
void dealloc(struct matrix *v, int count)
{
	for (int i = 0; i <= count; i++)
		free_matrix(v, i, v[i].m);
}

int main(void)
{
	int count = -1, alloc = 0, ok;
	char c;
	struct matrix *v, aux;
	scanf("%c", &c);
	while (c != 'Q') {
		switch (c) {
			case 'L': // Load a matrix
				count++;
				if (alloc == 0) {
					/*
					If there is no matrix in memory, I alloc the v structure,
					Else, I realloc the structure
					*/
					v = (struct matrix *)malloc(sizeof(struct matrix));
					if (!v) {
						printf("Malloc failed!\n");
						exit(0);
					}
					alloc = 1;
				} else {
					v = realloc(v, sizeof(struct matrix) * (count + 1));
				}
				read_rows_cols(v, count);
				alloc_matrix(v, count, v[count].m, v[count].n);
				load_matrix(v, count);
				break;

			case 'D': // Print matrix dimensions
				print_rows_cols(v, count);
				break;

			case 'P': // Print the matrix
				print_matrix(v, count);
				break;

			case 'C': // Crop the matrix
				crop_matrix(v, count);
				break;

			case 'M': // Multiply matrices
				count++;
				if (alloc == 0) {
					v = (struct matrix *)malloc(sizeof(struct matrix));
					if (!v) {
						printf("Malloc failed!\n");
						exit(0);
					}
					alloc = 1;
				} else {
					v = realloc(v, sizeof(struct matrix) * (count + 1));
				}
				matrix_multiplication(v, &count);
				break;

			case 'O': // Sort matrices
				sort_matrix(v, count, aux);
				break;

			case 'T': // Transpose the matrix
				transpose_matrix(v, count);
				break;

			case 'R': // Raise matrix to a power
				power_matrix(v, count);
				break;

			case 'F': // Free memory and move matrix
				ok = free_and_move_matrix(v, &count);
				/*
				If the matrix is realy deallocated from the memory, then
				v will be reallocated to the new size (count is modified)
				in the function above
				*/
				if (ok)
					v = realloc(v, sizeof(struct matrix) * (count + 1));
				break;

			default:
				if (c >= 'A' && c <= 'Z') {
					printf("Unrecognized command\n");
				}
				break;
		}
		scanf("%c", &c);
	}

	// Free from the memory the matrixes accesed using v pointer
	dealloc(v, count);

	// Free from the memory v pointer to matrix struct
	free(v);
	return 0;
}
