## **DESCRIPTION**

In this lab assignment, the user will input a random seed for random number generation and an amount of players (k) from 1 < k <= 10. These inputs from the user will determine how the game; Left, Right, and Center will play out.

Each player will receive a certain amount of rolls according to their amount of money. With each roll:

- if the player rolled LEFT, they must give the player to their left $1
- if the player rolled RIGHT, they must give the player to their right $1
- if the player rolled CENTER, they must give $1 to the pot
- if the player rolled PASS, they do nothing for that roll

The game will end until there is only one person left with money, thus ending the game and winning the pot.

## **FILES**

*DESIGN.pdf*

This file includes the basic description of the game and design of algorithms

in the source code in order to make the game work.

*lrc.c*

This file includes the code for the lab in C.

*Makefile*

This file includes the instructions when building, compiling, and running the

source code using make.

## **INSTRUCTIONS**

### Compiling

This program is intended to be compiled using the makefile associated with the assignment folder. Running make on the command prompt will create files executable titled lrc. Typing ./lrc will run the program and prompt the user for inputs.

### Execution

When the executable titled "lrc" is launched, the program will ask the user to input a random seed. This seed can be any value from 0 up to the maximum value for 32-bit signed integers (2,147,483,647).

The program will then prompt the user to input an integer for the number of players who are going to play the game. This integer (k) can be only from 1<k<=10. 

The game will play out as normal if these conditions are met.

### Known Issues

- The program will exit with no output if the user inputs a number (k) that is not from 1<k<=10. I created added this error check in order to stop the user from inputting numbers that break the functionality of the program.