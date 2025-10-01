import numpy as np
import time

def main():
    try:
        r1, c1 = map(int, input("Enter rows and columns of first matrix (r1 c1): ").split())
        r2, c2 = map(int, input("Enter rows and columns of second matrix (r2 c2): ").split())
    except ValueError:
        print("Error: Please enter valid integers.")
        return

    if r1 <= 0 or c1 <= 0 or r2 <= 0 or c2 <= 0:
        print("Error: Dimensions must be positive integers.")
        return

    if c1 != r2:
        print("Error: Cannot multiply matrices, c1 must equal r2.")
        return

    # Fill with random integers (0–9)
    A = np.random.randint(0, 10, size=(r1, c1))
    B = np.random.randint(0, 10, size=(r2, c2))

    # Time the multiplication
    start = time.time()
    C = np.dot(A, B)
    end = time.time()

    if r1 <= 10 and c2 <= 10:
        print("Resultant Matrix ({}x{}):".format(r1, c2))
        print(C)
    else:
        print("Matrix multiplication done. (Result too large to print)")

    print(f"Execution time: {end - start:.6f} seconds")

if __name__ == "__main__":
    main()
