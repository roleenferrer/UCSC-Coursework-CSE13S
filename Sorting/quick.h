// quick.h - Header file for Bubble Sort function.

#ifndef __QUICK_H__
#define __QUICK_H__

#include <inttypes.h>

extern int moves_quick;
extern int comparisons_quick;

//
// Quick Sort
// Sorts the array using Quick Sort algorithm
//
// *array : An array containing integers to be sorted
// left : The leftmost index of the array
// right : The rightmost index of the array
//
void quickSort(uint32_t *array, int left, int right);

void printQuickSort(uint32_t *array, int n, int p);

#endif
