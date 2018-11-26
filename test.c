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
			if (p[j][0] == f && p[j][1] == s)
				is_found = true;
		}

		assert(is_found);
	}
}
int main() {
	printf("TEST\n");

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

	printf("exp\n");
	print_pairs(expected_pairs, n_pairs_needed);

	printf("got\n");
	print_pairs(pairs, n_pairs_needed);

	compare(pairs, expected_pairs, n_pairs_needed);
}