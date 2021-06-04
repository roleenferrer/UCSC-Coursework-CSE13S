#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

int moves_quick;
int comparisons_quick;

//
// Partition Function
// Sorts the array into 2 different sub-arrays, to which certain
// integers are placed in each sub-array.
//
// *array : An array containing integers to be stored
// left : The left most index of the array (0)
// right : The right most index of the array (n - 1)
//
int partition(uint32_t *array, uint32_t left, uint32_t right) {
  uint32_t pivot = array[left];
  uint32_t lo = left + 1;
  uint32_t hi = right;
  int temp;
  while (true) {
    if (lo <= hi) { // Check if second condition is passed (from lecture)
      comparisons_quick += 1;
      if (array[hi] >= pivot) {
        while ((lo <= hi) && (array[hi] >= pivot)) {
          hi -= 1;
          if (lo <= hi) {
            comparisons_quick += 1;
          }
        }
      }
    }
    if (lo <= hi) { // Check if second condition is passed (from lecture)
      comparisons_quick += 1;
      if (array[lo] <= pivot) {
        while ((lo <= hi) && (array[lo] <= pivot)) {
          lo += 1;
          if (lo <= hi) {
            comparisons_quick += 1;
          }
        }
      }
    }
    if (lo <= hi) {
      temp = array[lo]; // sets temp to current array[lo]
      array[lo] = array[hi]; // sets array[lo] to current array[hi]
      array[hi] = temp; // sets array[hi] to temp
      moves_quick += 3;
    } else {
      break;
    }
  }
  temp = array[left]; // sets temp to current array[left]
  array[left] = array[hi]; // sets array[left] to current array[hi]
  array[hi] = temp; // sets array[hi] to temp
  moves_quick += 3;
  return hi;
}

//
// Quick Sort
// Sorts the array using Quick Sort algorithm
//
// *array : An array containing integers to be sorted
// left : The leftmost index of the array
// right : The rightmost index of the array
//
void quickSort(uint32_t *array, int left, int right) {
  int index;
  if (left < right) { // run recursively until sorted
    index = partition(array, left, right);
    quickSort(array, left, index - 1);
    quickSort(array, index + 1, right);
  }
  return;
}
