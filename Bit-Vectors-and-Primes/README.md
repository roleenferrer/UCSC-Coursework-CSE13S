## DESCRIPTION

In this lab assignment, the user will be able to set commands in the command line in order to output prime numbers and their special prime uniqueness (Mersenne, Lucas, or Fibonacci) and print out Palindromic primes in their respective bases 2, 9, 10, or 16 (F (the first letter of my last name) + 10). 

The user will input commands in the command prompt to achieve the following:

1. **-s**: which will print out all of the primes and determine if they are of Fibonacci, Lucas, or Mersenne type
2. **-p**: which will print out the palindromic primes in the bases 2, 9, 10 and the first letter of my last name + 10 (16).
3. **-n + value**: which will take a value from the user to consider in creating the prime sieve. If no “n” command is given, it will default to 1000.

In order to obtain the a list of primes up to the value of n, a **Bit Vector** will be used. Using a Bit Vector abstract data type will be more efficient, as each bit can represent a Boolean value, either 1 (true) or 0 (false). The Bit Vector will then be passed through The Sieve of Eratosthenes to generate a list of primes, where in the Bit Vector, a composite number will be cleared to 0 (false) and a prime number will be set to 1 (true).

## FILES

***sequence.c***

This file contains the source code in order to run the program with commands. It contains the algorithms of special prime numbers and the algorithms for printing prime palindromic bases.

***bv.c***

This file contains the source code containing the functions for Bit Vectors.  Other source files will depending on these functions in order to implement a Bit Vector containing prime numbers.

***sieve.c***

This file contains the source code containing the function for The Sieve of Eratosthenes. This source file will be used in order to generate a list of primes from a given n value through the use of a Bit Vector ADT.

***bv.h***

The header file for **bv.c**.

***sieve.h***

The header file for **sieve.c**

***Makefile***

This file includes the instructions when building, compiling, and running the source code using make.

***DESIGN.pdf***

This file includes the description of the Prime Numbers, Special Prime Numbers, Bit Vectors, and The Sieve of Eratosthenes. It also contains the design behind each function

## INSTRUCTIONS

**Compiling**

This program is intended to be compiled using the makefile associated with the assignment folder. Running make on the command prompt will create a file executable *sequence*. Typing ./sequence followed by any command (see Description) will print out the specified function of either a list of primes and their uniqueness or Palindrome primes with their respective bases. If no "n" value is selected, it will default to 1000.

**Execution**

In order for the program to work correctly, when the user calls ./sequence, they must input at least the "-s" or "-p" command. The user can optionally specify the limit of prime numbers using the "-n" command if they choose.

**Known Issues**

- ~~NULL Dereference when passing Bit Vector through sieve()~~
- If a user inputs an n value that is less than 0, there will be no output.

