#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

double** allocate_matrix(int rows, int cols);
void free_matrix(double** matrix, int rows);
void multiply_matrices(double** a, double** b, double** c, int m, int n, int p);
int get_positive_integer(const char* prompt);
void run_tests();

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "test") == 0) {
        run_tests();
        return 0;
    }

    int m, n, p;

    printf("Enter dimensions for Matrix A (m x n):\n");
    m = get_positive_integer("Enter number of rows (m): ");
    n = get_positive_integer("Enter number of columns (n): ");

    printf("\nEnter dimensions for Matrix B (n x p):\n");
    p = get_positive_integer("Enter number of columns (p): ");

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

    printf("Time taken for multiplication by C: %f seconds\n", duration);
    printf("Resulting matrix has dimensions: %d x %d\n", m, p);

    free_matrix(a, m);
    free_matrix(b, n);
    free_matrix(c, m);
    
    return 0;
}

void run_tests() {
    printf("Running tests\n");
    int passed = 1;

    int m = 2, n = 3, p = 2;
    double** a = allocate_matrix(m, n);
    double** b = allocate_matrix(n, p);
    double** c = allocate_matrix(m, p);

    if (!a || !b || !c) {
        printf("Test failed\n");
        passed = 0;
    }

    if (passed) {
        a[0][0] = 1; a[0][1] = 2; a[0][2] = 3;
        a[1][0] = 4; a[1][1] = 5; a[1][2] = 6;

        b[0][0] = 7; b[0][1] = 8;
        b[1][0] = 9; b[1][1] = 10;
        b[2][0] = 11; b[2][1] = 12;

        double expected[2][2] = {
            {58, 64},
            {139, 154}
        };

        multiply_matrices(a, b, c, m, n, p);

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < p; j++) {
                if (fabs(c[i][j] - expected[i][j]) > 0.001) {
                    printf("Test failed\n");
                    passed = 0;
                }
            }
        }
    }

    if (passed) {
        printf("All tests PASSED.\n");
    }

    if (a) free_matrix(a, m);
    if (b) free_matrix(b, n);
    if (c) free_matrix(c, m);
}

int get_positive_integer(const char* prompt) {
    int value;
    char buffer;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value > 0) {
            while ((buffer = getchar()) != '\n' && buffer != EOF);
            return value;
        } else {
            printf("Invalid input\n");
            while ((buffer = getchar()) != '\n' && buffer != EOF);
        }
    }
}

double** allocate_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;
    double** matrix = (double**)malloc(rows * sizeof(double*));
    if (!matrix) return NULL;
    for (int i = 0; i < rows; i++) {
        matrix[i] = (double*)malloc(cols * sizeof(double));
        if (!matrix[i]) {
            for(int k = 0; k < i; k++) free(matrix[k]);
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

void free_matrix(double** matrix, int rows) {
    if (!matrix) return;
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
