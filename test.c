#include "planner_lib/data_preparer.h"
#include "planner_lib/pure_hungarian.h"
#include "planner_lib/planner.c"

int main() {

	// test data preparer

	// test pure hungarian

	// test planner


	//

	//
	printf("TEST\n");

	int rows = 3;
	int columns = 3;
	int n = 3;

	double **m = (double**) malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++) {
		m[i] = (double*) malloc(columns * sizeof(double));
	}

	int ** optimal_pair;
	int n_optimal_pairs = find_optimal_pairs(m, rows, columns, optimal_pair);

//	m[0][0] = 3.46981e+08;
//	m[0][1] = 3.38214e+08;
//	m[0][2] = 5.56931e+08;
//
//	m[1][0] = 7.71379e+08;
//	m[1][1] = 1.26641e+09;
//	m[1][2] = 9.07187e+08;
//
//	m[2][0] = 7.46208e+08;
//	m[2][1] = 3.5137e+08;
//	m[2][2] = 1.20154e+09;

	m[0][0] = 9.08601e+08;
	m[0][1] = 1.56176e+08;
	m[0][2] = 1.17581e+09;

	m[1][0] = 1.98532e+09;
	m[1][1] = 1.15267e+09;
	m[1][2] = 3.25848e+08;

	m[2][0] = 4.14359e+08;
	m[2][1] = 9.36231e+08;
	m[2][2] = 1.27635e+09;

//	double m[3][3] = {
//		{3.46981e+08, 3.38214e+08, 5.56931e+08,},
//		{7.71379e+08, 1.26641e+09, 9.07187e+08,},
//		{7.46208e+08, 3.5137e+08, 1.20154e+09},
//	};
	int n_pairs_needed = (rows > columns) ? columns : rows;

	int **res = hungarian_assignment(m, n, n_pairs_needed);
	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			printf("%d ", res[r][c]);
		}
		printf("\n");
	}

}