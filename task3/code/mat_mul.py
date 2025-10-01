import numpy as np
import time

sizes = [100, 500, 1000]

for size in sizes:
    m = size # rows for matrix A
    p = size # rows for matrix B
    n = size # common dimension

    mat_a = np.random.rand(m, n)
    mat_b = np.random.rand(n, p)

    start_time = time.time()

    res = np.matmul(mat_a, mat_b)

    end_time = time.time()

    duration = end_time - start_time

    print(f"Time taken for multiplication or {size}x{size} matrix by NumPy: {duration:.6f} seconds")
