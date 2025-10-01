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

## Generating with ChatGPT

### Generating the C program
It took me 5 prompts to write the code with step by step advancements.

1.  **Initial Prompt:** I started by asking for a basic C program to multiply two hardcoded matrices. ChatGPT provided a simple, correct implementation using static arrays.

2.  **Adding User Input:** My next prompt was "change the code to ask the user to input the dimensions". ChatGPT used `scanf` but used variable-length arrays, which is a non-standard C feature and can be risky.

3.  **Adding Random Data and Timing:** I then asked it to "fill the matrix with random numbers, and measure how much the execution takes and print it". GPT correctly added `srand(time(NULL))` for seeding and used `clock()` to measure the execution time of the multiplication loop.

4.  **Improving Input Handling:** The program crashed when non-integer input was provided. I asked ChatGPT to "add type checking too" and it added a check on the return value of `scanf`.

5.  **Modularization and Testing:** All the code was inside the main method, so I asked it to "divide code into methods, and add a test method". It successfully refactored the code into functions and added a `testMultiplication` function with a hardcoded test case to verify correctness.

### Generating Python code with NumPy

After finalizing the C code, I just asked ChatGPT to "now do the same for python with numpy, but don't include any tests". In a single prompt it converted the C code into a fully functional Python code.

