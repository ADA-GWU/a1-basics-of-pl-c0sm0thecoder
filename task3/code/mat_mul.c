#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double** allocate_matrix(int rows, int cols);
void free_matrix(double** matrix, int rows);
void multiply_matrices(double** a, double** b, double** c, int m, int n, int p);
void run_unit_tests();

int main() {
    run_unit_tests();

    int sizes[] = {100, 500, 1000};
    for (int i = 0; i < 3; i++) {
        int m = sizes[i], n = sizes[i], p = sizes[i];

        double** a = allocate_matrix(m, n);
        double** b = allocate_matrix(n, p);
        double** c = allocate_matrix(m, p);

        srand(time(NULL));

        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                a[i][j] = (double)rand() / RAND_MAX;
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < p; j++)
                b[i][j] = (double)rand() / RAND_MAX;
        
        clock_t start_time = clock();
        multiply_matrices(a, b, c, m, n, p);
        clock_t end_time = clock();

        double duration = (double)(end_time - start_time) / CLOCKS_PER_SEC;

        printf("Time taken for multiplication of %dx%d matrix by C: %f seconds\n", sizes[i], sizes[i], duration);

        free_matrix(a, m);
        free_matrix(b, n);
        free_matrix(c, m);
    }
    return 0;
}

double** allocate_matrix(int rows, int cols) {
    double** matrix = (double**)malloc(rows * sizeof(double));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
    }
    return matrix;
}

void free_matrix(double** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void multiply_matrices(double** a, double** b, double** c, int m, int n, int p) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            c[i][j] = 0.0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

int are_matrices_equal(double** a, double** b, int rows, int cols) {
    double epsilon = 1e-9;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (fabs(a[i][j] - b[i][j]) > epsilon) {
                return 0;
            }
        }
    }
    return 1;
}

void run_unit_tests() {
    printf("--- Running Unit Tests ---\n");

    int m1 = 2, n1 = 2, p1 = 2;
    double** a1 = allocate_matrix(m1, n1);
    double** b1 = allocate_matrix(n1, p1);
    double** result1 = allocate_matrix(m1, p1);
    double** expected1 = allocate_matrix(m1, p1);

    a1[0][0] = 1; a1[0][1] = 2;
    a1[1][0] = 3; a1[1][1] = 4;
    b1[0][0] = 2; b1[0][1] = 0;
    b1[1][0] = 1; b1[1][1] = 2;
    expected1[0][0] = 4;  expected1[0][1] = 4;
    expected1[1][0] = 10; expected1[1][1] = 8;
    
    multiply_matrices(a1, b1, result1, m1, n1, p1);
    
    if (are_matrices_equal(result1, expected1, m1, p1)) {
        printf("Test Case 1 (2x2 Known Values): PASS\n");
    } else {
        printf("Test Case 1 (2x2 Known Values): FAIL\n");
    }
    
    free_matrix(a1, m1);
    free_matrix(b1, n1);
    free_matrix(result1, m1);
    free_matrix(expected1, m1);

    int m2 = 4, n2 = 4, p2 = 4;
    double** a2 = allocate_matrix(m2, n2);
    double** b2 = allocate_matrix(n2, p2);
    double** result2 = allocate_matrix(m2, p2);
    double** expected2 = allocate_matrix(m2, p2);

    double a2_vals[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 1, 2, 3}, {4, 5, 6, 7}};
    for (int i = 0; i < m2; i++) for (int j = 0; j < n2; j++) a2[i][j] = a2_vals[i][j];

    double b2_vals[4][4] = {{2, 0, 0, 0}, {0, 2, 0, 0}, {0, 0, 2, 0}, {0, 0, 0, 2}};
    for (int i = 0; i < n2; i++) for (int j = 0; j < p2; j++) b2[i][j] = b2_vals[i][j];
    
    double expected2_vals[4][4] = {{2, 4, 6, 8}, {10, 12, 14, 16}, {18, 2, 4, 6}, {8, 10, 12, 14}};
    for (int i = 0; i < m2; i++) for (int j = 0; j < p2; j++) expected2[i][j] = expected2_vals[i][j];

    multiply_matrices(a2, b2, result2, m2, n2, p2);

    if (are_matrices_equal(result2, expected2, m2, p2)) {
        printf("Test Case 2 (4x4 Known Values): PASS\n");
    } else {
        printf("Test Case 2 (4x4 Known Values): FAIL\n");
    }
    
    free_matrix(a2, m2);
    free_matrix(b2, n2);
    free_matrix(result2, m2);
    free_matrix(expected2, m2);

    printf("--- Unit Tests Finished ---\n\n");
}
