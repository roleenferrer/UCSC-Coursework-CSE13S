#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

int moves_binary;
int comparisons_binary;

//
// Binary Sort
// Sorts the array using Binary Sort algorithm
//
// *array : An array containing integers to be sorted
// n : The number of integers in the array
//
void binarySort(uint32_t *array, int n) {
  uint32_t value, left, right, mid, temp;
  for (int i = 1; i < n; i++) { // from range [1, n)
    value = array[i];
    left = 0;
    right = i;
    while (left < right) {
      mid = left + ((right - left) / 2);
      if (value >= array[mid]) {
        comparisons_binary += 1;
        left = mid + 1;
      } else {
        comparisons_binary += 1;
        right = mid;
      }
    }
    for (uint32_t j = i; j > left; j--) { // from range [i, left), backwards
      temp = array[j - 1]; // sets temp to array[j - 1]
      array[j - 1] = array[j]; // sets array[j - 1] to current array[j]
      array[j] = temp; // sets array[j] to current temp
      moves_binary += 3;
    }
  }
  return;
}
