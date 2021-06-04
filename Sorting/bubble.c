#include <inttypes.h>
#include <stdio.h>

int moves_bubble;
int comparisons_bubble;

//
// Bubble Sort
// Sorts the array using Bubble Sort algorithm
//
// *array : An array containing integers to be sorted
// n : The number of integers in the array
//
void bubbleSort(uint32_t *array, int n) {
  int temp, j;

  for (int i = 0; i < n - 1; i++) {
    j = n - 1;
    while (j > i) {
      comparisons_bubble += 1; // adds 1 to comparisons
      if (array[j] < array[j - 1]) {
        temp = array[j]; // set temp to number to be swapped
        array[j] = array[j - 1]; // sets array at j to previous number
        array[j - 1] = temp; // sets previous j at array to temp
        moves_bubble += 3; // adds 3 to moves in array
      }
      j = j - 1;
    }
  }
  return;
}
