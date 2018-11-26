#include "planner_lib/planner.c"
#include <stdio.h>

void print_pairs(int **p, int n_pairs) {
	for (int i = 0; i < n_pairs; i++) {
		printf("%d %d   ", p[i][0], p[i][1]);
	}
	printf("\n");
}

bool compare(int** p, int** exp_p, int n_pairs) {
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
	int **pairs = hungarian_assignment_test(m, n, n_pairs_needed);

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

//	printf("exp\n");
//	print_pairs(expected_pairs, n_pairs_needed);
//
//	printf("got\n");
//	print_pairs(pairs, n_pairs_needed);

	return compare(pairs, expected_pairs, n_pairs_needed);
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
	int **pairs = hungarian_assignment_test(m, n, n_pairs_needed);

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

//	printf("exp\n");
//	print_pairs(expected_pairs, n_pairs_needed);
//
//	printf("got\n");
//	print_pairs(pairs, n_pairs_needed);

	return compare(pairs, expected_pairs, n_pairs_needed);
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
	int **pairs = hungarian_assignment_test(m, n, n_pairs_needed);

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

//	printf("exp\n");
//	print_pairs(expected_pairs, n_pairs_needed);
//
//	printf("got\n");
//	print_pairs(pairs, n_pairs_needed);

	return compare(pairs, expected_pairs, n_pairs_needed);
}

int main() {

	printf("hungarian_test 1 result: %s\n", hungarian_test_1()?"true":"false");
	printf("hungarian_test 2 result: %s\n", hungarian_test_2()?"true":"false");
	printf("hungarian_test 3 result: %s\n", hungarian_test_3()?"true":"false");


}