#include "binary.h"
#include "bubble.h"
#include "quick.h"
#include "shell.h"
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int moves, comparisons; // Declare variable for global usage

//
// Print Array
// Prints an array
//
// *array : An array containing integers
// n : The nubmer of integers in the array
// p : The number of integers to print
// moves : The amount of moves from the sorting algorithm
// comparisons : The amountof comparisons from the sorting algorithm
//
void printArray(uint32_t *array, int n, int p, int moves, int comparisons) {
  printf("%d elements, %d moves, %d compares\n", n, moves, comparisons);
  int columns = 0;
  if (n < p) {
    p = n;
  }
  for (int i = 0; i < p; i++) {
    printf("%13d", array[i]);
    columns += 1;
    if (columns == 7) {
      printf("\n");
      columns = 0;
    }
  }
  printf("\n");
}

//
// Main Function
// This function will take in a command from the user using getopt().
// Will also call functions depending on the command to print output.
//
int main(int argc, char **argv) {
  int opt = 0;
  int n = 100, p = 100;
  int seed = 8222022;

  bool print_all = false;
  bool print_bubble_sort = false;
  bool print_shell_sort = false;
  bool print_quick_sort = false;
  bool print_binary_sort = false;

  while ((opt = getopt(argc, argv, " Absqip:r:n:")) != -1) {
    switch (opt) {
    case 'A': // Print all sorting
      print_all = true;
      break;
    case 'b': // Print bubble sort
      print_bubble_sort = true;
      break;
    case 's': // Print shell sort
      print_shell_sort = true;
      break;
    case 'q': // Print quick sort
      print_quick_sort = true;
      break;
    case 'i': // Print binary sort
      print_binary_sort = true;
      break;
    case 'p': // Print out number of elements
      p = atoi(optarg);
      break;
    case 'r': // Set seed to some value
      seed = atoi(optarg);
      break;
    case 'n': // Set array size to some value
      n = atoi(optarg);
      break;
    }
  }

  if (print_all == true) { // set all algorithms to true if user uses -A
    print_bubble_sort = true;
    print_shell_sort = true;
    print_quick_sort = true;
    print_binary_sort = true;
  }

  if (print_binary_sort == true) { // print Binary Insertion sort if true
    uint32_t *array = calloc(n, sizeof(uint32_t));
    srand(seed); // set srand to seed
    for (int i = 0; i < n; i++) {
      array[i] = rand() & ~(0xC0000000);
    }
    binarySort(array, n);
    printf("Binary Insertion Sort\n"); // print results
    printArray(array, n, p, moves_binary, comparisons_binary);
    free(array);
  }

  if (print_quick_sort == true) { // print Quick sort if true
    uint32_t *array = calloc(n, sizeof(uint32_t));
    srand(seed); // set srand to seed
    for (int i = 0; i < n; i++) {
      array[i] = rand() & ~(0xC0000000);
    }
    quickSort(array, 0, n - 1);
    printf("Quick Sort\n"); // print results
    printArray(array, n, p, moves_quick, comparisons_quick);
    free(array);
  }

  if (print_shell_sort == true) { // print Shell sort if true
    uint32_t *array = calloc(n, sizeof(uint32_t));
    srand(seed); // set srand to seed
    for (int i = 0; i < n; i++) {
      array[i] = rand() & ~(0xC0000000);
    }
    shellSort(array, n);
    printf("Shell Sort\n"); // print name of algorithm
    printArray(array, n, p, moves_shell, comparisons_shell);
    moves = 0;
    comparisons = 0;
    free(array);
  }

  if (print_bubble_sort == true) { // print Bubble sort if true
    uint32_t *array = calloc(n, sizeof(uint32_t));
    srand(seed); // set srand to seed
    for (int i = 0; i < n; i++) {
      array[i] = rand() & ~(0xC0000000);
    }
    bubbleSort(array, n);
    printf("Bubble Sort\n"); // print name of algorithm
    printArray(array, n, p, moves_bubble, comparisons_bubble);
    moves = 0;
    comparisons = 0;
    free(array);
  }
  return 0;
}
