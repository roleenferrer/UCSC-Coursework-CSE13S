## DESCRIPTION

In this lab assignment, the user will be able to set commands in the command line in order to out a sorted list of integers using different sorting algorithms. These sorting algorithms are:

- Bubble Sort
- Shell Sort
- Quick Sort
- Binary Insertion Sort

The user will input commands in the command prompt to achieve the following:

1. **-A** : which will employ all of the sorting algorithms
2. **-b** : which will enable Bubble Sort
3. **-s** : which will enable Shell Sort
4. **-q** : which will enable Quick Sort
5. **-i** : which will enable Binary Insertion Sort
6. **-p n** : which will print the first n elements of the array. This command has a default value of n = 100
7. **-r s** : which will set the random seed to s. The default value of s is 8222022
8. **-n c** : which will set the array to some size c. The default value of c is 100

## FILES

***sorting.c***

This file contains the source code for main() and the the code to run the program with commands. Will call other functions from other files depending on which sorting algorithm is called

***bubble.c***

This file contains the source code for the Bubble Sort algorithm

***bubble.h***

This file specifies the interface to bubble.c

***shell.c***

This file contains the source code for the Shell Sort algorithm

***shell.h***

This file specifies the interface to shell.c

***quick.c***

This file contains the source code for the Quick Sort algorithm

***quick.h***

This file specifies the interface to quick.c

***binary.c***

This file contains the source code for the Binary Insertion Sort algorithm

***binary.h***

This file specifies the interface to binary.c

***Makefile***

This file includes instructions when building, compiling, and running the source code using make

***DESIGN.pdf***

This file includes the description of the sorting algorithms: Bubble Sort, Shell Sort, Quick Sort, and Binary Insertion Sort. It also contains the design behind each function

***WRITEUP.pdf***

This file contains a writeup after post-lab analysis. It includes the time complexities of each algorithm and I have learned and experimented with each sorting algorithm

## INSTRUCTIONS

**Compiling**

This program is intended to be compiled using the makefile associated with the assignment folder. Running make on the command prompt will create a file executable *sorting*. Typing ./sorting followed by any command (see Description) will print out the specified sorting algorithm.

**Execution**

In order for the program to work as intended, it is recommended that the user inputs a command that specifies a certain sorting algorithm (-b, -s, -q ,-i) or a command that will execute all of the sorting algorithms (-A). The user can optionally specify the limit of the array size, the seed of the random number generator, or the amount of integers to be printed.

**Known Issues**

- If a user inputs no commands when calling ./sorting, the program will do nothing.
- If a user inputs a zero length array (n = 0), the sorting algorithm will print, but no values will be sorted and resulting in 0 elements, 0 comparisons, and 0 moves. This is intentional in the design.

