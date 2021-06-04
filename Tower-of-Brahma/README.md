## DESCRIPTION

In this lab assignment, the user will be able to input commands in the command line in order to output different ways to solve the Tower of Hanoi puzzle. The Tower of Hanoi puzzle consists of three columns (pegs), in which the object of the game is to have all of the pegs onto another peg, in this case, column B. The game is very simple, but there are some rules:

- You may only move one disk at a time
- You are not able to place a larger disk on top of a smaller disk

**Recursion (-r)**

This command will run the recursive algorithm in order to solve the game. The function will call itself recursively in order to complete this process.

**Stack (-s)**

This command will run the stack algorithm in order to solve the game. The command calls the a function which solves the game iteratively using stacks.

**Number of Disks (-n)**

This command will tell the program how many disks will the game run with.

## FILES

***tower.c***

This file contains the source code in order to play the game. It contains the algorithms and functions for the Recursive and Stack iterations of the game, as well as the code to take in commands from the user.

***stack.c***

This file contains the source code for the stack implementation. It contains functions such as stack_create and stack_push.

***stack.h***

This file is the header file for stack.c, which contains the function declarations to be shared with tower.c.

***Makefile***

This file includes the instructions when building, compiling, and running the source code using make.

***DESIGN.pdf***

This file includes the description of the Tower of Hanoi game, as well as the design behind the functions in tower.c and stack.c.

***WRITEUP.pdf***

This file contains the post-lab discussion from the results of running the game using a recursive function and an iterative function using stacks. It discusses debugging complexity and the reason behind the design process

## Instructions

**Compiling**

This program is intended to be compiled using the makefile associated with the assignment folder. Running make on the command prompt will create file executable tower. Typing ./tower followed by any command (see Description) will print out the specified function for the stack implementation or the recursive implementation. If no "n" value is selected, it will default to five disks.

**Execution**

In order for the program to work correctly, when the user calls ./tower, they must input at least the "-r" or "-s" commands. The user can optionally specify the amount of disks using the "-n" command, if they choose.

**Known Issues**

- ~~There appears to be a "False-Positive" when running *make infer* , which shows a memory leak. Using valgrind, however, does not show this memory leak. The reason why make infer may be generating this error is because the error is directed towards the stack_create implementation, which does cannot leak since the stack is in use and freed correctly after the stack algorithm is finished.~~

