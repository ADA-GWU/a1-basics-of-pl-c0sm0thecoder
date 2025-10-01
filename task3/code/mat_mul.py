import numpy as np
import time

def get_positive_integer(prompt):
    while True:
        try:
            value = int(input(prompt))
            if value > 0:
                return value
            else:
                print("Enter a positive integer:")
        except ValueError:
            print("Invalid input")

try:
    print("Enter dimensions for Matrix A (m x n):")
    m = get_positive_integer("Enter number of rows (m): ")
    n = get_positive_integer("Enter number of columns (n): ")

    print("\nEnter dimensions for Matrix B (n x p):")
    p = get_positive_integer("Enter number of columns (p): ")

    mat_a = np.random.rand(m, n)
    mat_b = np.random.rand(n, p)

    start_time = time.time()

    res = np.matmul(mat_a, mat_b)

    end_time = time.time()

    duration = end_time - start_time

    print(f"Time taken for multiplication by NumPy: {duration:.6f} seconds")
    print(f"Resulting matrix has dimensions: {res.shape}")

except KeyboardInterrupt:
    print("\nOperation cancelled by user.")
