#include "data_preparer.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BAD_EDGE INFINITY

void set_all(int *arr, int arr_size, int value) {
	for (int i = 0; i < arr_size; i++) {
		arr[i] = value;
	}
}

void multiply_by_scalar(double **m, int rows, int columns, double scalar) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			m[r][c] *= scalar;
		}
	}
}

void make_positive(double **m, int rows, int columns) {
	double max = 0;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			if (fabs(m[r][c]) > max)
				max = fabs(m[r][c]);
		}
	}

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			m[r][c] += max;
			assert(m[r][c] >= 0);
		}
	}
}

void add_columns(double **m, int rows, int columns) {
	for (int r = 0; r < rows; r++) {
		m[r] = (double*) realloc(m[r], rows * sizeof(double));
		for (int c = columns; c < columns; c++) {
			m[r][c] = BAD_EDGE;
		}
	}
}

void add_rows(double **m, int rows, int columns) {
	m = (double**) realloc(m, columns * sizeof(double *));
	for (int r = rows; r < columns; r++) {
		m[r] = (double*) malloc(columns * sizeof(double));
		for (int c = 0; c < columns; c++) {
			m[r][c] = BAD_EDGE;
		}
	}
}

int prepare_matrix(double **orig_m, int rows, int columns, double **new_m) {
	double **m = (double**) malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++) {
		m[i] = (double*) malloc(columns * sizeof(double));
	}

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			m[r][c] = orig_m[r][c];
		}
	}

	multiply_by_scalar(m, rows, columns, -1.0);
	make_positive(m, rows, columns);

	if (rows > columns) {
		add_columns(m, rows, columns);
	}

	if (columns > rows) {
		add_rows(m, rows, columns);
	}

	new_m = m;

	int n = (rows > columns) ? rows : columns;
	return n;
}
