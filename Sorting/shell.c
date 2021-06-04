#include <inttypes.h>
#include <stdio.h>

int moves_shell;
int comparisons_shell;

//
// Gap Function
// Generates the intervals (gaps) to be used for Shell sorting.
//
// n : The amount of integers (changes when shellSort() is called)
//
int gap(int n) {
  if (n <= 2) {
    n = 1;
  } else {
    n = 5 * n / 11;
  }
  return n;
}

//
// Shell Sort
// Sorts the array using Shell Sort algorithm
//
// *array : An array containing integers to be sorted
// n : The number of integers in the array
//
void shellSort(uint32_t *array, int n) {
  int step = n;
  int temp;

  while (step > 1) {
    step = gap(step);
    for (int i = step; i < n; i++) {
      for (int j = i; j > step - 1; j -= step) {
        comparisons_shell += 1;
        if (array[j] < array[j - step]) {
          temp = array[j]; // sets temp to array[j]
          array[j] = array[j - step]; // sets array[j] to array[j - step]
          array[j - step] = temp; // sets [j - step] to temp
          moves_shell += 3;
        }
      }
    }
  }
  return;
}
