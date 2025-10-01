#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fill a matrix with random numbers (0–9)
void fillMatrixRandom(int rows, int cols, int M[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            M[i][j] = rand() % 10;
        }
    }
}

// Multiply two matrices: A(r1 x c1) * B(r2 x c2) = C(r1 x c2)
void multiplyMatrices(int r1, int c1, int r2, int c2,
                      int A[r1][c1], int B[r2][c2], int C[r1][c2]) {
    // Initialize result to 0
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            C[i][j] = 0;
        }
    }

    // Multiply
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            for (int k = 0; k < c1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Print a matrix
void printMatrix(int rows, int cols, int M[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", M[i][j]);
        }
        printf("\n");
    }
}

// Test matrix multiplication correctness with a known case
void testMultiplication() {
    int A[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };

    int B[3][2] = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    int expected[2][2] = {
        {58, 64},
        {139, 154}
    };

    int C[2][2];
    multiplyMatrices(2, 3, 3, 2, A, B, C);

    // Check result
    int correct = 1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (C[i][j] != expected[i][j]) {
                correct = 0;
                break;
            }
        }
    }

    printf("Test case: ");
    if (correct) {
        printf("PASSED ✅\n");
    } else {
        printf("FAILED ❌\n");
    }
}

int main() {
    srand((unsigned int)time(NULL));

    // Run correctness test first
    testMultiplication();

    int r1, c1, r2, c2;

    // Input dimensions with type checking
    printf("Enter rows and columns of first matrix (r1 c1): ");
    if (scanf("%d %d", &r1, &c1) != 2 || r1 <= 0 || c1 <= 0) {
        printf("Error: Invalid input for first matrix dimensions.\n");
        return 1;
    }

    printf("Enter rows and columns of second matrix (r2 c2): ");
    if (scanf("%d %d", &r2, &c2) != 2 || r2 <= 0 || c2 <= 0) {
        printf("Error: Invalid input for second matrix dimensions.\n");
        return 1;
    }

    if (c1 != r2) {
        printf("Error: Cannot multiply matrices, c1 must equal r2.\n");
        return 1;
    }

    // Allocate matrices as VLAs (could use malloc for huge matrices)
    int A[r1][c1], B[r2][c2], C[r1][c2];

    // Fill with random values
    fillMatrixRandom(r1, c1, A);
    fillMatrixRandom(r2, c2, B);

    // Time the multiplication
    clock_t start = clock();
    multiplyMatrices(r1, c1, r2, c2, A, B, C);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print result only if small
    if (r1 <= 10 && c2 <= 10) {
        printf("Resultant Matrix (%dx%d):\n", r1, c2);
        printMatrix(r1, c2, C);
    } else {
        printf("Matrix multiplication done. (Result too large to print)\n");
    }

    printf("Execution time: %f seconds\n", time_taken);

    return 0;
}
