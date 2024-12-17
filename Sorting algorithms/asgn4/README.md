# Assignment 4: All Sorts of C Code

## Files Included and Explanations

- DESIGN.pdf - Design files that offers general idea of the purpose of the program and provides pseudocode to give readers a basic idea as to how they would go about coding the program if they wanted to recreate it.
- WRITEUP.pdf - Discusses purpose of each function and how it was implemented. Explained why certain lines of code were written and how they contribute to the overall functionality of the program. Discusses differences in time complexity for the different sorting methods and offers possible reasons as to why they exist.
- bubble.c - C file that implements bubble sort.
- bubble.h - Header file that defines function that is used to implement bubble sort.
- heap.c - C file that implements heap sort. Includes helper function to find index of parent and children, build heap, and fix heap.
- heap.h - Header file that defines function that is used to implement heap sort.
- shell.c - C file that implements shell sort. Includes helper function to calculate gaps.
- shell.h - Header file that defines function that is used to implement shell sort.
- quick.c - C file that implements quick sort.
- quick.h - Header file that defines function that is used to implement quick sort.
- set.c - Contains functions that are used to create an empty set and check membership in the set. Used to keep track of what sorts are called.
- set.h - Header file that defines functions used in set.c.
- stats.c - C file that includes the statistics module that keeps track of moves and comparisons.
- stats.h - Header file that defines the stats structure.
- mtrand.c - Implements the Mersenne Twister module that is used to generate random numbers based on a given seed.
- mtrand.h - Header file that defines functions in mtrand.c.
- sorting.c - C file that takes in user input and set contraints for the array of numbers that is sorted. Calls sort functions and prints sorted arrays. Test harness file.
- Makefile - Compiles program.
- README.md - This file. To compile the program, use the command make. Then input ./sorting [-Habhqs] [-n #] [-p #] [-r #]. Does not require use of -n, -p, -r, but is there to set constraints. Sample input: ./sorting -a -n 20 -p 10 -r 12345678 will run all tests with array length 20 and random seed 12345678. Will print 10 elements of resulting array.

## Cited Sources

- Stack Overflow thread for better understanding of bit masking: https://stackoverflow.com/questions/10493411/what-is-bit-masking
