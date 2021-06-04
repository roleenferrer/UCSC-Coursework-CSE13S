// binary.h - Header file for Bubble Sort function.

#ifndef __BINARY_H__
#define __BINARY_H__

#include <inttypes.h>

extern int moves_binary;
extern int comparisons_binary;

//
// Binary Sort
// Sorts the array using Binary Sort algorithm
//
// *array : An array containing integers to be sorted
// n : The number of integers in the array
//
void binarySort(uint32_t *array, int n);

#endif
