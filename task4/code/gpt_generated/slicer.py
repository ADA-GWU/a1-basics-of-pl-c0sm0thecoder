import numpy as np
import matplotlib.pyplot as plt

# Step 1: Ask the user for matrix dimensions
rows = int(input("Enter the number of rows for the matrix: "))
cols = int(input("Enter the number of columns for the matrix: "))

# Step 2: Create a random 2D matrix
matrix = np.random.rand(rows, cols)  # Values between 0 and 1 for grayscale

# Step 3: Ask the user for slice coordinates
row_start = int(input(f"Enter row start (0 to {rows-1}): "))
row_end = int(input(f"Enter row end (1 to {rows}): "))
col_start = int(input(f"Enter column start (0 to {cols-1}): "))
col_end = int(input(f"Enter column end (1 to {cols}): "))

# Validate coordinates
if not (0 <= row_start < row_end <= rows) or not (0 <= col_start < col_end <= cols):
    raise ValueError("Invalid slice coordinates!")

# Step 4: Extract the slice
matrix_slice = matrix[row_start:row_end, col_start:col_end]

# Step 5: Display both matrices
fig, axes = plt.subplots(1, 2, figsize=(10, 5))

axes[0].imshow(matrix, cmap='gray')
axes[0].set_title('Original Matrix')
axes[0].axis('off')

axes[1].imshow(matrix_slice, cmap='gray')
axes[1].set_title('Sliced Matrix')
axes[1].axis('off')

plt.tight_layout()
plt.show()
