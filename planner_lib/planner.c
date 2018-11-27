#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#include "data_preparer.h"
#include "pure_hungarian.h"

// returns number of pairs of indexes
// [[i_1, j_1], [i_2, j_2], ...]
//
// uses 'pairs' as output param
int find_optimal_pairs(double **m, int rows, int columns, int **pairs) {
	double **new_m;
	int n = prepare_matrix(m, rows, columns, &new_m);

	int n_pairs_needed = (rows > columns) ? columns : rows;
	hungarian_assignment(new_m, n, pairs, n_pairs_needed);

	return n;
}
