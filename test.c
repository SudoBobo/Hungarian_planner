#include "planner_lib/planner.c"
#include <stdio.h>
#include <time.h>

//srand (time ( NULL));

/* generate a random floating point number from min to max */
double randfrom(double min, double max)
{
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}


void print_matrix(double **m, int rows, int columns) {
	printf("\n");

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			printf("%f ", m[r][c]);
		}
		printf("\n");
	}
}

void print_pairs(int **p, int n_pairs) {
	for (int i = 0; i < n_pairs; i++) {
		printf("%d %d   ", p[i][0], p[i][1]);
	}
	printf("\n");
}

bool compare_pairs(int **p, int **exp_p, int n_pairs) {
	for (int i = 0; i < n_pairs; i++) {
		int f = exp_p[i][0];
		int s = exp_p[i][1];

		bool is_found = false;
		for (int j = 0; j < n_pairs; j++) {
			if (p[j][0] == f && p[j][1] == s) {
				is_found = true;
				p[j][0] = -2;
				p[j][1] = -2;
			}
		}
		if (!is_found)
			return false;
	}
	return true;
}

bool compare_matrices(double ** m1, double** m2, int rows, int columns) {
	for (int r = 0; r < rows; r++){
		for (int c = 0; c < columns; c++) {
			if (fabs(m1[r][c] - m2[r][c]) > 0.000000000000001)
				return false;
		}
	}
	return true;
}

bool hungarian_test_1() {
	int rows = 3;
	int columns = 3;
	int n = 3;

	double **m = (double**) malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++) {
		m[i] = (double*) malloc(columns * sizeof(double));
	}

	m[0][0] = 2.82387e+08;
	m[0][1] = 2.0413e+09;
	m[0][2] = 1.19032e+09;

	m[1][0] = 1.06191e+08;
	m[1][1] = 1.39772e+09;
	m[1][2] = 2.90993e+08;

	m[2][0] = 2.08267e+09;
	m[2][1] = 6.2514e+07;
	m[2][2] = 1.50174e+09;

	int n_pairs_needed = (rows > columns) ? columns : rows;

	int **pairs = (int**) malloc(n_pairs_needed * sizeof(int *));
	for (int i = 0; i < n_pairs_needed; i++) {
		pairs[i] = (int*) malloc(2 * sizeof(int));
	}

	hungarian_assignment(m, n, pairs, n_pairs_needed);

	int **expected_pairs = (int**) malloc(n_pairs_needed * sizeof(int *));
	for (int i = 0; i < n_pairs_needed; i++) {
		expected_pairs[i] = (int*) malloc(2 * sizeof(int));
	}

	expected_pairs[0][0] = 0;
	expected_pairs[0][1] = 0;

	expected_pairs[1][0] = 1;
	expected_pairs[1][1] = 2;

	expected_pairs[2][0] = 2;
	expected_pairs[2][1] = 1;

	return compare_pairs(pairs, expected_pairs, n_pairs_needed);
}

bool hungarian_test_2() {
	int rows = 4;
	int columns = 4;
	int n = 4;

	double **m = (double**) malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++) {
		m[i] = (double*) malloc(columns * sizeof(double));
	}

	m[0][0] = 2.77887e+08;
	m[0][1] = 9.93376e+08;
	m[0][2] = 1.06243e+09;
	m[0][3] = 1.13672e+09;

	m[1][0] = 4.9247e+08;
	m[1][1] = 2.40241e+08;
	m[1][2] = 2.05722e+09;
	m[1][3] = 8.29913e+07;

	m[2][0] = 3.02488e+08;
	m[2][1] = 1.03201e+09;
	m[2][2] = 1.43062e+09;
	m[2][3] = 1.51605e+09;

	m[3][0] = 2.81458e+08;
	m[3][1] = 6.37004e+08;
	m[3][2] = 5.02025e+08;
	m[3][3] = 4.84453e+08;

	int n_pairs_needed = (rows > columns) ? columns : rows;

	int **pairs = (int**) malloc(n_pairs_needed * sizeof(int *));
	for (int i = 0; i < n_pairs_needed; i++) {
		pairs[i] = (int*) malloc(2 * sizeof(int));
	}

	hungarian_assignment(m, n, pairs, n_pairs_needed);

	int **expected_pairs = (int**) malloc(n_pairs_needed * sizeof(int *));
	for (int i = 0; i < n_pairs_needed; i++) {
		expected_pairs[i] = (int*) malloc(2 * sizeof(int));
	}

	expected_pairs[0][0] = 0;
	expected_pairs[0][1] = 1;

	expected_pairs[1][0] = 1;
	expected_pairs[1][1] = 3;

	expected_pairs[2][0] = 2;
	expected_pairs[2][1] = 0;

	expected_pairs[3][0] = 3;
	expected_pairs[3][1] = 2;

	return compare_pairs(pairs, expected_pairs, n_pairs_needed);
}

bool hungarian_test_3() {
	int rows = 5;
	int columns = 5;
	int n = 5;

	double **m = (double**) malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++) {
		m[i] = (double*) malloc(columns * sizeof(double));
	}

	m[0][0] = 1.21529e+09;
	m[0][1] = 4.56232e+08;
	m[0][2] = 3.39278e+08;
	m[0][3] = 1.95842e+09;
	m[0][4] = 2.02938e+09;

	m[1][0] = 5.62615e+08;
	m[1][1] = 7.49625e+08;
	m[1][2] = 1.33068e+09;
	m[1][3] = 9.70141e+08;
	m[1][4] = 3.14421e+08;

	m[2][0] = 1.00338e+09;
	m[2][1] = 1.34138e+09;
	m[2][2] = 9.85096e+08;
	m[2][3] = 1.94567e+09;
	m[2][4] = 2.05843e+09;

	m[3][0] = 1.60296e+09;
	m[3][1] = 1.98063e+08;
	m[3][2] = 1.96066e+09;
	m[3][3] = 1.97983e+09;
	m[3][4] = 7.57307e+08;

	m[4][0] = 1.1971e+09;
	m[4][1] = 7.97411e+08;
	m[4][2] = 1.50366e+09;
	m[4][3] = 2.40838e+08;
	m[4][4] = 9.9681e+08;

	int n_pairs_needed = (rows > columns) ? columns : rows;
	int **pairs = (int**) malloc(n_pairs_needed * sizeof(int *));
	for (int i = 0; i < n_pairs_needed; i++) {
		pairs[i] = (int*) malloc(2 * sizeof(int));
	}

	hungarian_assignment(m, n, pairs, n_pairs_needed);

	int **expected_pairs = (int**) malloc(n_pairs_needed * sizeof(int *));
	for (int i = 0; i < n_pairs_needed; i++) {
		expected_pairs[i] = (int*) malloc(2 * sizeof(int));
	}

	expected_pairs[0][0] = 0;
	expected_pairs[0][1] = 2;

	expected_pairs[1][0] = 1;
	expected_pairs[1][1] = 4;

	expected_pairs[2][0] = 2;
	expected_pairs[2][1] = 0;

	expected_pairs[3][0] = 3;
	expected_pairs[3][1] = 1;

	expected_pairs[4][0] = 4;
	expected_pairs[4][1] = 3;

	return compare_pairs(pairs, expected_pairs, n_pairs_needed);
}

bool data_preparer_test_1() {
	int rows = 3;
	int columns = 4;

	double ** in_m = (double**) malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++) {
		in_m[i] = (double*) malloc(columns * sizeof(double));
	}

	in_m[0][0] = 1000.0;
	in_m[0][1] = 700.0;
	in_m[0][2] = -1.0;
	in_m[0][3] = -1.0;

	in_m[1][0] = 200.0;
	in_m[1][1] = -1.0;
	in_m[1][2] = 1200.0;
	in_m[1][3] = 600.0;

	in_m[2][0] = 1300.0;
	in_m[2][1] = 500.0;
	in_m[2][2] = 800.0;
	in_m[2][3] = -1.0;

	double **m;
	int n = prepare_matrix(in_m, rows, columns, &m);
	assert(n == 4);

	double ** exp_m = (double**) malloc(n * sizeof(double *));
	for (int i = 0; i < n; i++) {
		exp_m[i] = (double*) malloc(n * sizeof(double));
	}

	exp_m[0][0] = 300.0;
	exp_m[0][1] = 600.0;
	exp_m[0][2] = INFINITY;
	exp_m[0][3] = INFINITY;

	exp_m[1][0] = 1100.0;
	exp_m[1][1] = INFINITY;
	exp_m[1][2] = 100.0;
	exp_m[1][3] = 700.0;

	exp_m[2][0] = 0.0;
	exp_m[2][1] = 800.0;
	exp_m[2][2] = 500.0;
	exp_m[2][3] = INFINITY;

	exp_m[3][0] = INFINITY;
	exp_m[3][1] = INFINITY;
	exp_m[3][2] = INFINITY;
	exp_m[3][3] = INFINITY;

	return compare_matrices(m, exp_m, n, n);
}

bool full_test() {
	int rows = 3;
	int columns = 4;

	double ** m = (double**) malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++) {
		m[i] = (double*) malloc(columns * sizeof(double));
	}

	m[0][0] = 1000.0;
	m[0][1] = 700.0;
	m[0][2] = -1.0;
	m[0][3] = -1.0;

	m[1][0] = 200.0;
	m[1][1] = -1.0;
	m[1][2] = 1200.0;
	m[1][3] = 600.0;

	m[2][0] = 1300.0;
	m[2][1] = 500.0;
	m[2][2] = 800.0;
	m[2][3] = -1.0;

	int n = rows > columns ? columns : rows;
	int **pairs = (int **) malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		pairs[i] = (int*) malloc(2 * sizeof(int));

	int n_found_pairs = find_optimal_pairs(m, rows, columns, pairs);

	if (n_found_pairs != n)
		return false;

	int ** exp_pairs = (int **) malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		exp_pairs[i] = (int*) malloc(2 * sizeof(int));


	exp_pairs[0][0] = 0;
	exp_pairs[0][1] = 1;

	exp_pairs[1][0] = 1;
	exp_pairs[1][1] = 2;

	exp_pairs[2][0] = 2;
	exp_pairs[2][1] = 0;

	return compare_pairs(pairs, exp_pairs, n);
}

void rec_func(double **m, int rows, int columns, int **path,
	      int *path_idx, int n_pairs_needed, int *is_r_used,
	      int *is_c_used, double *curr_max, int **curr_best_path,
		int *curr_best_path_size) {
	// if no step may be done then calculate new possible max
	// cmp with current max and rewrite
	if (*path_idx == n_pairs_needed){
		double new_max = 0.0;
		for (int i = 0; i < *path_idx; i++){
			int r = path[i][0];
			int c = path[i][1];
			assert(isnormal(m[r][c]));
			new_max += m[r][c];
		}
		if (new_max > *curr_max){
			*curr_max = new_max;
			// update curr_best_path
			*curr_best_path_size = *path_idx;
			for (int i = 0; i < *path_idx; i++) {
				curr_best_path[i][0] = path[i][0];
				curr_best_path[i][1] = path[i][1];
			}
		}
		return;
	}

	// if some steps may be done then do recursive calls for all of them
	for (int r = 0; r < rows; r++) {
		if (is_r_used[r] == 0) {
			is_r_used[r] = 1;
			for (int c = 0; c < columns; c++) {

				if (is_c_used[c] == 0 && isnormal(m[r][c])) {
					is_c_used[c] = 1;
					path[*path_idx][0] = r;
					path[*path_idx][1] = c;
					*path_idx += 1;

					rec_func(m, rows, columns, path,
					         path_idx, n_pairs_needed,
						 is_r_used,
					         is_c_used, curr_max,
						 curr_best_path,
						 curr_best_path_size);

					*path_idx -= 1;
					path[*path_idx][0] = -1;
					path[*path_idx][1] = -1;
					is_c_used[c] = 0;
				}
			}
			is_r_used[r] = 0;
		}
	}
}

void brute_force(double **m , int rows, int columns, int **pairs) {
	int *is_r_used = (int*) calloc(rows, sizeof(int));
	int *is_c_used = (int*) calloc(columns, sizeof(int));

	int n_pairs_needed = rows > columns ? columns : rows;
	int **path = (int**) malloc(n_pairs_needed * sizeof(int*));
	for (int i = 0; i < n_pairs_needed; i++)
		path[i] = (int*) malloc(2 * sizeof(int));
	int path_idx = 0;

	double curr_max = 0;

	int **curr_best_path = (int**) malloc(n_pairs_needed * sizeof(int*));
	for (int i = 0; i < n_pairs_needed; i++)
		curr_best_path[i] = (int*) malloc(2 * sizeof(int));
	int curr_best_path_size = 0;

	// TODO mind that results (be pair combination) must be written
	// into 'pairs' output param
	rec_func(m, rows, columns, path, &path_idx, n_pairs_needed, is_r_used,
		 is_c_used, &curr_max, curr_best_path, &curr_best_path_size);

	// use recursive function which return sum and write into pairs on the last stage

	for (int i = 0; i < n_pairs_needed; i++) {
		pairs[i][0] = curr_best_path[i][0];
		pairs[i][1] = curr_best_path[i][1];
	}
}

bool full_test_with_brute_force_1() {
	int rows = 3;
	int columns = 4;

	double ** m = (double**) malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++) {
		m[i] = (double*) malloc(columns * sizeof(double));
	}

	m[0][0] = 1000.0;
	m[0][1] = 700.0;
	m[0][2] = -1.0;
	m[0][3] = -1.0;

	m[1][0] = 200.0;
	m[1][1] = -1.0;
	m[1][2] = 1200.0;
	m[1][3] = 600.0;

	m[2][0] = 1300.0;
	m[2][1] = 500.0;
	m[2][2] = 800.0;
	m[2][3] = -1.0;

	int n = rows > columns ? columns : rows;
	int **pairs = (int **) malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		pairs[i] = (int*) malloc(2 * sizeof(int));

	int n_found_pairs = find_optimal_pairs(m, rows, columns, pairs);

	if (n_found_pairs != n)
		return false;

	int ** brute_pairs = (int **) malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		brute_pairs[i] = (int*) malloc(2 * sizeof(int));

	brute_force(m, rows, columns, brute_pairs);

//	printf("\n hing result\n");
//	print_pairs(pairs, n);
//
//	printf("\n brute force result\n");
//	print_pairs(brute_pairs, rows > columns ? columns : rows);

	return compare_pairs(pairs, brute_pairs, n);
}

bool full_test_with_brute_force_2() {
	int rows = 100;
	int columns = 100;

	double ** m = (double**) malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++) {
		m[i] = (double*) malloc(columns * sizeof(double));
	}


	double min = 200.0;
	double max = 3000.0;

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			double random = randfrom(min, max);
			m[r][c] = random > 500.0 ? random : -1;

		}
	}

	int n = rows > columns ? columns : rows;
	int **pairs = (int **) malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		pairs[i] = (int*) malloc(2 * sizeof(int));

	int n_found_pairs = find_optimal_pairs(m, rows, columns, pairs);

	if (n_found_pairs != n)
		return false;

	int ** brute_pairs = (int **) malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		brute_pairs[i] = (int*) malloc(2 * sizeof(int));

	brute_force(m, rows, columns, brute_pairs);

	return compare_pairs(pairs, brute_pairs, n);
}


int main() {
//	printf("data_preparer_test 1: %s\n", data_preparer_test_1() ? "ok":"failed");
//	printf("hungarian_test 1 result: %s\n", hungarian_test_1() ? "ok":"failed");
//	printf("hungarian_test 2 result: %s\n", hungarian_test_2() ? "ok":"failed");
//	printf("hungarian_test 3 result: %s\n", hungarian_test_3() ? "ok":"failed");
//	printf("full_test 1 result: %s\n", full_test() ? "ok":"failed");
	printf("full test 2 (cmp with brute force) result: %s\n",
	       full_test_with_brute_force_1() ? "ok":"falied");
	printf("full test 3 (cmp with brute force) result: %s\n",
	       full_test_with_brute_force_1() ? "ok":"falied");
}