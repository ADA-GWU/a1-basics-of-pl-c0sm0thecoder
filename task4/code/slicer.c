#include <stdio.h>
#include <stdlib.h>
#include <png.h>

void print_matrix(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%-5d", matrix[i][j]);
        }
        printf("\n");
    }
}

void save_matrix_as_png(const char *filename, int **matrix, int rows, int cols, int max_val) {
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        printf("Cannot open file %s for writing.\n", filename);
        return;
    }

    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fclose(fp);
        return;
    }

    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, NULL);
        fclose(fp);
        return;
    }

    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        return;
    }

    png_init_io(png_ptr, fp);

    png_set_IHDR(png_ptr, info_ptr, cols, rows, 8, PNG_COLOR_TYPE_GRAY,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_ptr, info_ptr);

    png_bytep row = (png_bytep)malloc(cols * sizeof(png_byte));
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            row[x] = (png_byte)((matrix[y][x] * 255) / (float)max_val);
        }
        png_write_row(png_ptr, row);
    }
    free(row);

    png_write_end(png_ptr, NULL);
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    printf("\nSaved %s. You can open it with an image viewer.", filename);
}


int main() {
    int matrix_dim;
    printf("Enter the dimension for the square matrix: ");
    scanf("%d", &matrix_dim);

    int row_start, row_end, col_start, col_end;
    printf("Enter the starting row for the slice: ");
    scanf("%d", &row_start);
    printf("Enter the ending row for the slice: ");
    scanf("%d", &row_end);
    printf("Enter the starting column for the slice: ");
    scanf("%d", &col_start);
    printf("Enter the ending column for the slice: ");
    scanf("%d", &col_end);

    if (row_start < 0 || row_end > matrix_dim || col_start < 0 || col_end > matrix_dim || row_start >= row_end || col_start >= col_end) {
        printf("Invalid slice dimensions.\n");
        return 1;
    }

    int **original_matrix = (int **)malloc(matrix_dim * sizeof(int *));
    for (int i = 0; i < matrix_dim; i++) {
        original_matrix[i] = (int *)malloc(matrix_dim * sizeof(int));
    }

    int count = 0;
    for (int i = 0; i < matrix_dim; i++) {
        for (int j = 0; j < matrix_dim; j++) {
            original_matrix[i][j] = count++;
        }
    }

    int sliced_rows = row_end - row_start;
    int sliced_cols = col_end - col_start;

    int **sliced_matrix = (int **)malloc(sliced_rows * sizeof(int *));
    for (int i = 0; i < sliced_rows; i++) {
        sliced_matrix[i] = (int *)malloc(sliced_cols * sizeof(int));
    }

    for (int i = 0; i < sliced_rows; i++) {
        for (int j = 0; j < sliced_cols; j++) {
            sliced_matrix[i][j] = original_matrix[row_start + i][col_start + j];
        }
    }

    printf("\nOriginal Matrix:\n");
    print_matrix(original_matrix, matrix_dim, matrix_dim);

    printf("\nSliced Matrix:\n");
    print_matrix(sliced_matrix, sliced_rows, sliced_cols);

    int max_val = matrix_dim * matrix_dim - 1;
    if (max_val == 0) max_val = 1; // Avoid division by zero
    save_matrix_as_png("original.png", original_matrix, matrix_dim, matrix_dim, max_val);
    save_matrix_as_png("sliced.png", sliced_matrix, sliced_rows, sliced_cols, max_val);
    printf("\n");

    for (int i = 0; i < matrix_dim; i++) {
        free(original_matrix[i]);
    }
    free(original_matrix);

    for (int i = 0; i < sliced_rows; i++) {
        free(sliced_matrix[i]);
    }
    free(sliced_matrix);

    return 0;
}
