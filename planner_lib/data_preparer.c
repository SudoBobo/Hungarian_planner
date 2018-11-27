#include "data_preparer.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BAD_EDGE INFINITY

void print_matrix_m(double **m, int rows, int columns) {
	printf("\n");
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			printf("%f ", m[r][c]);
		}
		printf("\n");
	}
}

void multiply_by_scalar(double **m, int rows, int columns, double scalar) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			if (isnormal(m[r][c]))
				m[r][c] *= scalar;
		}
	}
}

void make_positive(double **m, int rows, int columns) {
	double max = 0;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			if (fabs(m[r][c]) > max && !(isinf(m[r][c])))
				max = fabs(m[r][c]);
		}
	}

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			m[r][c] += max;
		}
	}
}

void add_columns(double ***m, int rows, int columns) {
	double **new_m = (double**) malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++) {
		new_m[i] = (double*) malloc(rows * sizeof(double));
	}

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < rows; c++) {
			if (c < columns)
				new_m[r][c] = *m[r][c];
			else
				new_m[r][c] = BAD_EDGE;
		}
	}

	*m = new_m;
}

void add_rows(double ***m, int rows, int columns) {
	double **new_m = (double**) malloc(columns * sizeof(double *));
	for (int i = 0; i < columns; i++) {
		new_m[i] = (double*) malloc(columns * sizeof(double));
	}

	for (int r = 0; r < columns; r++) {
		for (int c = 0; c < columns; c++) {
			if (r < rows)
				new_m[r][c] = (*m)[r][c];
			else
				new_m[r][c] = BAD_EDGE;
		}
	}

	*m = new_m;
}

void set_infs(double **m, int rows, int columns) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			if (fabs(m[r][c] + 1) < 0.00000000000001)
				m[r][c] = INFINITY;
		}
	}
}

int prepare_matrix(double **orig_m, int rows, int columns, double ***res) {
	double **new_m = (double**) malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++) {
		new_m[i] = (double*) malloc(columns * sizeof(double));
	}

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			new_m[r][c] = orig_m[r][c];
		}
	}

	set_infs(new_m, rows, columns);
	multiply_by_scalar(new_m, rows, columns, -1.0);
	make_positive(new_m, rows, columns);

	if (rows > columns) {
		add_columns(&new_m, rows, columns);
	}

	if (columns > rows) {
		add_rows(&new_m, rows, columns);
	}

	*res = new_m;

	int n = (rows > columns) ? rows : columns;
	return n;
}
