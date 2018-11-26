#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#include "data_preparer.h"
#include "pure_hungarian.h"


int prepare_matrix_test(double **orig_m, int rows, int columns, double **new_m) {
	return prepare_matrix(orig_m, rows, columns, new_m);
}

int ** hungarian_assignment_test(double **m, int n, int n_pairs_needed) {
	return hungarian_assignment(m, n, n_pairs_needed);
}

// returns number of pairs of indexes
// [[i_1, j_1], [i_2, j_2], ...]
//
// uses 'pairs' as output param
int find_optimal_pairs(double **m, int rows, int columns, int **pairs) {

	// copy m
	double **new_m;
	int n = prepare_matrix(m, rows, columns, new_m);

	int n_pairs_needed = (rows > columns) ? columns : rows;
	pairs = hungarian_assignment(new_m, n, n_pairs_needed);

	return n;
}
