#include "stack.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// recursiveTower Function
//
// Parameters:
// int disks - The number of disks in the given game
// char column_A - The character for column A
// char column_B - The character for column B
// char column_C - The character for column C
//
// This function will call itself recursivly in order to play the game
// using a recursive function. This function will run if the user inputs
// the -r command.
void recursiveTower(int disks, char column_A, char column_B, char column_C) {
  if (disks == 1) { // if disks is equal to 1, print and exit program
    printf("\nMove disk %d from peg %c to peg %c", disks, column_A, column_B);
    return;
  } else if (disks == 0) { // if disks is equal to 0, return an error statement
    printf("\nThere are no disks!");
    return;
  }

  recursiveTower(
      disks - 1, column_A, column_C, column_B); // disks - 1 for recursion
  printf("\nMove disk %d from peg %c to peg %c", disks, column_A, column_B);
  recursiveTower(
      disks - 1, column_C, column_B, column_A); // disks - 1 for recursion
}

// legalMovementOdd Helper Function
//
// Parameters:
// int disk - takes in the current disk
// struct Stack *column_A - stack iterator for column_A
// struct Stack *column_B - stack iterator for column_B
// struct Stack *column_C - stack iterator for column_C
//
// This helper function will be called if the current disk iteration
// is odd. The function will parse through each column and check for a
// legal movement.
void legalMovementOdd(int disk, struct Stack *column_A, struct Stack *column_B,
    struct Stack *column_C) {
  int x = 0;
  int column_a_peek
      = stack_peek(column_A); // Block will get the top most item in
  int column_b_peek = stack_peek(column_B); // the stack
  int column_c_peek = stack_peek(column_C);

  if (column_a_peek == disk) { // if stack_peek(column_A) is the disk
    if (stack_empty(column_B) == 1 || column_a_peek < column_b_peek) {
      // Enter statement if either column_B is empty or a < b
      x = stack_pop(column_A);
      stack_push(column_B, x);
      printf("\nMove disk %d from peg %c to peg %c", disk, column_A->name,
          column_B->name);
    }
  } else if (column_b_peek == disk) { // if stack_peek(column_B) is the disk
    if (stack_empty(column_C) == 1 || column_b_peek < column_c_peek) {
      // Enter statement if either column_C is empty or b < c
      x = stack_pop(column_B);
      stack_push(column_C, x);
      printf("\nMove disk %d from peg %c to peg %c", disk, column_B->name,
          column_C->name);
    }
  } else if (column_c_peek == disk) { // if stack_peek(column_C) is the disk
    if (stack_empty(column_A) == 1 || column_c_peek < column_a_peek) {
      // Enter statement if either column_A is empty or c < a
      x = stack_pop(column_C);
      stack_push(column_A, x);
      printf("\nMove disk %d from peg %c to peg %c", disk, column_C->name,
          column_A->name);
    }
  }
}

// legalMovementEven Helper Function
//
// Parameters:
// int disk - takes in the current disk
// struct Stack *column_A - stack iterator for column_A
// struct Stack *column_B - stack iterator for column_B
// struct Stack *column_C - stack iterator for column_C
//
// This helper function will be called if the current disk iteration
// is even. The function will parse through each column and check for a
// legal movement.
void legalMovementEven(int disk, struct Stack *column_A, struct Stack *column_B,
    struct Stack *column_C) {
  int x = 0;
  int column_a_peek
      = stack_peek(column_A); // Block will get the top most item in
  int column_b_peek = stack_peek(column_B); // the stack
  int column_c_peek = stack_peek(column_C);

  if (column_a_peek == disk) { // if stack_peek(column_A) is the disk
    if (stack_empty(column_C) == 1 || column_a_peek < column_c_peek) {
      // Enter statement if either column_C is empty or a < c
      x = stack_pop(column_A);
      stack_push(column_C, x);
      printf("\nMove disk %d from peg %c to peg %c", disk, column_A->name,
          column_C->name);
    }
  } else if (column_b_peek == disk) { // if stack_peek(column_B) is the disk
    if (stack_empty(column_A) == 1 || column_b_peek < column_a_peek) {
      // Enter statement if either column_A is empty or b < a
      x = stack_pop(column_B);
      stack_push(column_A, x);
      printf("\nMove disk %d from peg %c to peg %c", disk, column_B->name,
          column_A->name);
    }
  } else if (column_c_peek == disk) { // if stack_peek(column_C) is the disk
    if (stack_empty(column_B) == 1 || column_c_peek < column_b_peek) {
      // Enter statement if either column_B is empty or c < b
      x = stack_pop(column_C);
      stack_push(column_B, x);
      printf("\nMove disk %d from peg %c to peg %c", disk, column_C->name,
          column_B->name);
    }
  }
}

// stackTower Function
//
// Parameters:
// int disks - takes in the number of disks
//
// This function will be called if the user uses the command -s.
// Creates the stacks that will be used, pushes the amount of disks
// to column_A (start), and runs a loop to the helper functions which
// runs until the condition is met.
void stackTower(int disks) {
  struct Stack *column_A = stack_create(disks, 'A');
  struct Stack *column_B = stack_create(disks, 'B');
  struct Stack *column_C = stack_create(disks, 'C');

  // Pushes the amount of disks into the stack
  for (int x = disks; x >= 1; x = x - 1) {
    stack_push(column_A, x);
  }
  // Gets total moves
  int moves = 1;
  for (int i = 1; i <= disks; i++) {
    moves *= 2;
  }

  int i = 0;

  // This loop will continue to run until column_B-top == disks
  while (column_B->top != disks) {
    if (i == disks) { // Check the disk number is equal to amount
      i = 1; // reset current disk
    } else {
      i += 1;
    }
    if (i % 2 == 1) { // if the disk (i) is odd
      if (disks % 2 == 1) { // checks if total disks is odd
        legalMovementOdd(i, column_A, column_B, column_C);
      } else {
        legalMovementEven(i, column_A, column_B, column_C);
      }
    } else if (i % 2 == 0) { // if the disk (i) is even
      if (disks % 2 == 1) { // checks if total disks is odd
        legalMovementEven(i, column_A, column_B, column_C);
      } else {
        legalMovementOdd(i, column_A, column_B, column_C);
      }
    }
  }
  stack_delete(column_A); // When finished, delete the stacks to
  stack_delete(column_B); // restore allocated memory
  stack_delete(column_C);
}

// Main Function
//
// This function will primarily be used to call getopt(), which
// is a function that will obtain commands from the user.
int main(int argc, char **argv) {
  int opt = 0;
  int disks = 5;

  bool stack = false;
  bool recursion = false;

  while ((opt = getopt(argc, argv, "n:sr")) != -1) {
    switch (opt) {
    case 'n':
      disks = atoi(optarg);
      break;
    case 's':
      stack = true;
      break;
    case 'r':
      recursion = true;
      break;
    }
  }
  if (stack == true) { // if command is -s
    printf("================================\n---------   STACKS    "
           "----------\n================================");
    stackTower(disks);

    int moves = 1;
    for (int i = 1; i <= disks; i++) {
      moves *= 2;
    }

    printf("\n\nNumber of moves: %d\n\n", moves - 1);
  }
  if (recursion == true) { // if command is -r
    printf("================================\n--------   RECURSION    "
           "--------\n================================");
    char column_A = 'A';
    char column_B = 'B';
    char column_C = 'C';
    recursiveTower(disks, column_A, column_B, column_C);

    int moves = 1;
    for (int i = 1; i <= disks; i++) {
      moves *= 2;
    }

    printf("\n\nNumber of moves: %d\n\n", moves - 1);
  }
  return 0;
}
