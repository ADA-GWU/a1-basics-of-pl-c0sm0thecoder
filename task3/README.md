## Introduction

The files in the code/ folder contain implementations of matrix multiplication using C and Python (with NumPy). Both programs have been tested on matrices of sizes 100x100, 500x500, and 1000x1000. All tests were conducted on an Apple M1 Pro chip.

## Execution time

The results for the NumPy code are like this:

```
Time taken for multiplication or 100x100 matrix by NumPy: 0.000409 seconds
Time taken for multiplication or 500x500 matrix by NumPy: 0.000736 seconds
Time taken for multiplication or 1000x1000 matrix by NumPy: 0.004730 seconds
```

Execution times for the same sized data in C are like this:
```
Time taken for multiplication of 100x100 matrix by C: 0.009334 seconds
Time taken for multiplication of 500x500 matrix by C: 0.454038 seconds
Time taken for multiplication of 1000x1000 matrix by C: 4.637421 seconds
```

## Difference in code size

Accomplishing matrix multiplication was much easier and required significantly fewer lines of code in Python with NumPy compared to C. The basic code for matrix multiplication in NumPy took only 4 lines, while the same functionality was achieved in C in 20 lines, which is 5 times more than as much. Additionally, C code required a lot of pre-processing, such as allocating space in memory for operands and the resulting matrix. The manual handling of multiplication through nested loops is the main  reason why the C code runs very slow compared to NumPy.
