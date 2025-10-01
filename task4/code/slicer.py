import numpy as np
import matplotlib.pyplot as plt

matrix_dim = int(input("Enter the dimension for the square matrix: "))

row_start = int(input("Enter the starting row for the slice: "))
row_end = int(input("Enter the ending row for the slice: "))
col_start = int(input("Enter the starting column for the slice: "))
col_end = int(input("Enter the ending column for the slice: "))

total_elements = matrix_dim**2
original_matrix = np.arange(total_elements).reshape(matrix_dim, matrix_dim)

sliced_matrix = original_matrix[row_start:row_end, col_start:col_end]

print("Original Matrix:")
print(original_matrix)

print("\nSliced Matrix:")
print(sliced_matrix)

plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.imshow(original_matrix, cmap='gray')
plt.title("Original Matrix")

plt.subplot(1, 2, 2)
plt.imshow(sliced_matrix, cmap='gray')
plt.title("Sliced Matrix")

plt.show()