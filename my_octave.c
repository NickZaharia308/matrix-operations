/**
 * @file    my_octave.c
 * @brief   This file contains the implementation of matrix operations.
 * 
 * @author  Zaharia Nicusor-Alexandru
 * @date    08-12-2022
 */

#include <stdio.h>
#include <stdlib.h>


/**
 * @brief   Structure used for the matrix
 * 
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


/**
 * @brief   Frees from memory an allocated matrix
 * 
 * This function frees from the memory a dynamically allocates matrix.
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   ID of the current matrix.
 * @param	m	Number of lines.
 * 
 */
void free_matrix(struct matrix *v, int count, int m)
{
	for (int i = 0; i < m; i++)
		free(v[count].mat[i]);
	free(v[count].mat);
}


/**
 * @brief   Prints the matrix.
 * 
 * This function reads the ID of a matrix and prints all the values
 * of a matrix (first by line, then by column).
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   Number of current matrixes stored by v.
 * 
 * @note    If the index (ID) is invalid, a message will be printed.
 */
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


/**
 * @brief   Crops a given matrix.
 * 
 * This function reads the ID of a matrix and crops the number of lines
 * and the number of the columns
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   Number of current matrixes stored by v.
 * 
 * @note    If the index (ID) is invalid, a message will be printed.
 */
void crop_matrix(struct matrix *v, int count)
{
	int index, m, n, *index_rows, *index_cols, **copy, i, j;
	scanf("%d", &index);

	if (index <= count && index >= 0) {

		// Pointer that memorates the lines by which the crop is made
		index_rows = (int *)malloc(m * sizeof(int));

		scanf("%d", &m);
		if (!index_rows) {
			printf("Malloc failed!\n");
			exit(0);
		}
		for (int i = 0; i < m; i++)
			scanf("%d", &index_rows[i]);

		// Pointer that memorates the columns by which the crop is made
		index_cols = (int *)malloc(n * sizeof(int));

		scanf("%d", &n);
		if (!index_cols) {
			printf("Malloc failed!\n");
			exit(0);
		}
		for (int i = 0; i < n; i++)
			scanf("%d", &index_cols[i]);

		// Dynamically allocated double pointer that memorates the new matrix
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

		// Free the old matrix and realloc it with the new dimensions
		free_matrix(v, index, v[index].m);
		alloc_matrix(v, index, m, n);
		v[index].m = m;
		v[index].n = n;

		// Copy the values from the copy matrix
		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				v[index].mat[i][j] = copy[i][j];

		// Free all the pointers
		for (int i = 0; i < m; i++)
			free(copy[i]);
		free(copy);
		free(index_rows);
		free(index_cols);
	} else {
		printf("No matrix with the given index\n");
	}
}


/**
 * @brief   Multiplies two matrixes.
 * 
 * This function reads the ID of two matrixes and multiplies them
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   Number of current matrixes stored by v.
 * 
 * @note    If the indexes (IDs) are invalids, a message will be printed.
 */
void matrix_multiplication(struct matrix *v, int *count)
{
	int index1, index2, i, j, k, x;
	scanf("%d%d", &index1, &index2);

	// If the idexes are invalid print some error messages
	if (index1 > *count - 1 || index2 > *count - 1) {
		printf("No matrix with the given index\n");
		(*count)--;
	} else if (v[index1].n != v[index2].m) {
		
		// If the sizes don't match for multiplication
		printf("Cannot perform matrix multiplication\n");
		(*count)--;
	} else {

		// Dynamically allocating a new matrix and initialising with 0
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

		// Algorithm for matrix multiplication
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


/**
 * @brief   Sorts matrixes.
 * 
 * This function sorts matrixes by the sum of their elements
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   Number of current matrixes stored by v.
 * @param	aux		Auxiliary matrix.
 */
void sort_matrix(struct matrix *v, int count, struct matrix aux)
{
	int *sum, i, j, k, sum_aux;

	// Dynamically allocated pointer that stores the sum of each matrix
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
	
	// Selection sort
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
	
	// Free the pointer from the memory
	free(sum);
}


/**
 * @brief   Replaces a matrix with its transpose.
 * 
 * This function replaces a matrix with its transpose.
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   Number of current matrixes stored by v.
 */
void transpose_matrix(struct matrix *v, int count)
{
	int **transpose, i, j, m, n, index;
	scanf("%d", &index);
	if (index > count || index < 0) {
		printf("No matrix with the given index\n");
	} else {
		m = v[index].n;
		n = v[index].m;

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

		free_matrix(v, index, v[index].m);
		alloc_matrix(v, index, m, n);

		// Copy the values from the auxiliary double pointer in the newly
		// allocated matrix
		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				v[index].mat[i][j] = transpose[i][j];
		v[index].m = m;
		v[index].n = n;

		// Free the transpose matrix
		for (int i = 0; i < m; i++)
			free(transpose[i]);
		free(transpose);
	}
}


/**
 * @brief   Helper function for matrix to a power.
 * 
 * Helper function for "power_matrix".
 * Memorates the result in @param	p_matrix.
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param	p_matrix	The result matrix
 * @param   index   Index of the matrix that will be raised to a power.
 */
void matrix_multi_2(struct matrix *v, int **p_matrix, int index)
{
	int **p_aux_matrix, i, j, k, x, n;

	// No of lines / columns
	n = v[index].n;

	// Helper matrix
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

	// Multiplying operation
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++) {
				x = p_matrix[i][k] * v[index].mat[k][j];
				p_aux_matrix[i][j] += x;
				p_aux_matrix[i][j] %= 10007;
				if (p_aux_matrix[i][j] < 0)
					p_aux_matrix[i][j] += 10007;
			}

	
	// Copy the results in helper matrix and free the memory
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			p_matrix[i][j] = p_aux_matrix[i][j];
	for (i = 0; i < n; i++)
		free(p_aux_matrix[i]);
	free(p_aux_matrix);
}


/**
 * @brief   Raises to a given power a matrix
 * 
 * Function that raises to a given power a matrix in logarithmic time.
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   Number of current matrixes stored by v.
 */
void power_matrix(struct matrix *v, int count)
{
	int index, power;
	scanf("%d%d", &index, &power);

	// If the index or power is invalid, print a message
	if (index > count || index < 0) {
		printf("No matrix with the given index\n");
	} else if (power < 0) {
		printf("Power should be positive\n");
	} else if (v[index].n != v[index].m) {
		printf("Cannot perform matrix multiplication\n");
	} else {
		int **copy, **p_matrix, n, i, j, k, x;
		n = v[index].n;

		/**
		 * Create dynamically two matrixes that help for the multiplying.
		 * p_matrix is the final matrix
		 */
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

		// Initialize with I(n)
		for (i = 0; i < n; i++)
			p_matrix[i][i] = 1;

		// Algorithm for logarithmic matrix exponentation
		while (power) {
			if (power % 2) {

			// If the power is odd, multiply base matrix (v[indnex].mat) with
			// result matrix (p_matrix)
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

			// At each step multiply the base matrix with itself and move
			// the result from auxiliary matrix in the base matrix
			matrix_multi_2(v, copy, index);
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					v[index].mat[i][j] = copy[i][j];
					
			// Free from the memory the first pointer
			for (i = 0; i < n; i++)
				free(copy[i]);
			free(copy);
		}

		// Copy the results from result matrix in the base matrix (initial one)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				v[index].mat[i][j] = p_matrix[i][j];

		// Free from the memory the second pointer
		for (i = 0; i < n; i++)
			free(p_matrix[i]);
		free(p_matrix);
	}
}


/**
 * @brief   Deletes a matrix and moves the following matrixes one place to left
 * 
 * Function that removes from memory a matrix and moves all following matrixes
 * one spot to the left so the indexes for the matrixes are continious.
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   Number of current matrixes stored by v.
 */
int free_and_move_matrix(struct matrix *v, int *count)
{
	int index, i, j, k, ok;
	scanf("%d", &index);
	if (index > *count || index < 0) {
		printf("No matrix with the given index\n");
		ok = 0;
	} else {

		// Free from the memory "i" matrix, allocate it with the new size
		// (size of the next matrix) and copy in it the elements from "i + 1"
		for (i = index; i < *count; i++) {
			free_matrix(v, i, v[i].m);
		alloc_matrix(v, i, v[i + 1].m, v[i + 1].n);
		v[i].m = v[i + 1].m;
		v[i].n = v[i + 1].n;
		for (j = 0; j < v[i].m; j++)
			for (k = 0; k < v[i].n; k++)
				v[i].mat[j][k] = v[i + 1].mat[j][k];
		}

		// Free from memory the last matrix and decrement
		// the number of matrixes
		free_matrix(v, *count, v[*count].m);
		(*count)--;
		ok = 1;
	}
	return ok;
}


/**
 * @brief   Frees from memory all matrixes
 * 
 * Function that deallocates from the memory all the matrixes.
 * 
 * @param   v   Pointer to the array of matrixes.
 * @param   count   Number of current matrixes stored by v.
 */
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
