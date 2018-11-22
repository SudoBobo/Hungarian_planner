#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <float.h>
#include <stdbool.h>

#define BAD_EDGE DBL_MAX

// TODO add matrix struct

// TODO move to helpers

void multiply_by_scalar(double **m, int rows, int columns, double scalar) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			m[r][c] *= scalar;
		}
	}
}

// TODO below may not be moved to helpers
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

void fill_with_test_values(double **m, int rows, int columns) {
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			m[r][c] = r * 100.0 + c * 100.0;
		}
	}
}


int double_eq(double d1, double d2) {
	return fabs(d1 - d2) < 0.000001;
}

// Tries to find non-saturated vertex from the second half.
// Returns zero if non-saturated vertex from second half was not found. In that
// case clean ups last element in curr_path and decreases it's curr_path_idx.

// Returns non-zero if non-saturated vertex from second half is found. In that
// case curr_path and curr_path_idx are not changed.
int DFS(int idx, char r_or_c, int *curr_path, int *curr_path_idx, int *is_r_in_pair, int *is_c_in_pair,
	int *is_r_visited, int *is_c_visited, int n) {
	// check if hit non saturated from second half
	// if it is then return success

	// 'idx' is in second half
	if (r_or_c == 'c') {
		int c = idx;
		// reached non-saturated vertex from the second half
		if (!is_c_in_pair[c]) {
			curr_path[*curr_path_idx] = c;
			*curr_path_idx += 1;
			return 1;
		}

		// reached saturated vertex from the second half
		// run DFS for all possible

		curr_path[*curr_path_idx] = c;
		*curr_path_idx += 1;
		is_c_visited[c] = 1;

		// DFSes
		for (int r = 0; r < n; r++) {
			if (is_r_visited[r])
				continue;

			// we can't go from 2 to 1 if r-c is not a pair
			if (is_r_in_pair[r] != c) {
				continue;
			}

			// if edge is solid
			if (double_eq(u[r] + v[c], m[r][c]) {
				int res = DFS(r, 'r');
				if (res) {
					return 1;
				}
			}
		}
		// after DFS run

		*curr_path_idx -= 1;
		curr_path[*curr_path_idx] = -1;
		is_c_visited[c] = 0;

		return 0;
	}

	if (r_or_c == 'r') {
		int r = idx;

		curr_path[*curr_path_idx] = r;
		*curr_path_idx += 1;
		is_r_visited[r] = 1;

		for (int c = 0; c < n; c++) {
			if (is_c_visited[c])
				continue;

			// we can't go from 1 to 2 if r-c is a pair
			if (is_c_in_pair[c] == r) {
				continue;
			}

			// if edge is solid
			if (double_eq(u[r] + v[c], m[r][c])) {
				int res = DFS(c, 'c');
				if (res) {
					return 1;
				}
			}
		}

		*curr_path_idx -= 1;
		curr_path[*curr_path_idx] = -1;
		is_r_visited[r] = 0;

		return 0;
		//
	}

	// if not run DFS through all hard edges
	// if all of them fails return fail
	// and remove last element from curr_path and descrease curr_path_idx
}

//Из всех ненасыщенных вершин первой доли запускается обход в глубину/в ширину.
//Если в результате обхода удалось достигнуть ненасыщенной вершины второй доли,
//	то это означает, что мы нашли увеличивающий путь из первой доли во вторую.
//Если прочередовать рёбра вдоль этого пути (т.е. первое ребро включить в
//паросочетание, второе исключить, третье включить, и т.д.), то тем самым мы
//увеличим мощность паросочетания на единицу.


// 1) x0 -> x1 включить
// 2) x1 -> x2 исключить
// 3) x2 -> x3 включить
void alternate_pairs_in_path(int *curr_path, int last_elem_idx) {
	assert(last_elem_idx / 2 == 1);

	bool include = true;

	for (int i = 0; i < last_elem_idx; i += 2) {
		if (include) {
			// do include for two elem
			int r = curr_path[i];
			int c = curr_path[i+1];

			is_r_in_pair[r] = c;
			is_c_in_pair[c] = r;
			include = false;
		} else {
			// do exclude for two elems
			// actuall excluding was on the previous stage
			include = true;
		}
	}
	// add pairs to pairs maps
	// edit 'is_in' dict
}

int main() {
	// we recieve a matrix of N x M
	int rows = 3;
	int columns = 3;
	double ** m = (double**) malloc(rows * sizeof(double *));
	for (int i = 0; i < rows; i++) {
		m[i] = (double*) malloc(columns * sizeof(double));
	}

	fill_with_test_values(m, rows, columns);

	multiply_by_scalar(m, rows, columns, -1.0);
	make_positive(m, rows, columns);

	if (rows > columns) {
		add_columns(m, rows, columns);
	}

	if (columns > rows) {
		add_rows(m, rows, columns);
	}

	int n = (rows > columns) ? rows : columns;

	// init potential
	double *u = (double*) malloc(n * sizeof(double));
	double *v = (double*) malloc(n * sizeof(double));
	for (int i = 0; i < n; i++) {
		u[i] = 0.0;
		v[i] = 0.0;
	}

	// init result
	int n_pairs_found = 0;
	int n_pairs_needed = (rows > columns) ? columns : rows;

	// dict (implemented as arrays)
	// edge_r_to_c[r] = -1 if there is no pair with 'r'
	// edge_r_to_c[r] = c if there is a pair [r, c]
	//
	// edge_c_to_r[c] = -1 if there is no pair with 'c'
	// edge_c_to_r[c] = r if there is a pair [r, c]
	// TODO add funct init arr and set defaults
	int *edge_r_to_c = (int*) calloc((size_t)n, sizeof(int));
	int *edge_c_to_r = (int*) calloc((size_t)n, sizeof(int));

	int *curr_path = (int*) calloc((size_t)n, sizeof(int));
	int *curr_path_idx;
	*curr_path_idx = 0;

	while (n_pairs_found < n_pairs_needed) {
		// try to find new pair
		for (int r = 0; r < n; r++) {
			if (!edge_r_to_c[r] == 0) {
				if (DFS(r, 'i', curr_path, curr_path_idx, edge_r_to_c, edge_c_to_r)) {
					alternate_pairs_in_path(curr_path, curr_path_idx, edge_r_to_c, edge_c_to_r);
					assert(false);
					// TODO clear curr_path
					// TODO set curr_path_idx to zero
					n_pairs_found++;
					if (n_pairs_found == n_pairs_needed)
						goto finish;
				}
				// start DFS for it
				// if DFS returned 1 then we found new pair and
				// have to change existing pairs
			}
		}

		// update potential
	}

	//
	// do algorith till we have min(N, M) optimal pairs
	//
	// free all resources ))

	finish:
	for (int i = 0; i < n; i++) {
		free(m[i]);
	}
	free(u);
	free(v);
	// return pairs

	return 0;
}