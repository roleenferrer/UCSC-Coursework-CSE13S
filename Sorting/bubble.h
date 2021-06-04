// bubble.h - Header file for Bubble Sort function.

#ifndef __BUBBLE_H__
#define __BUBBLE_H__

#include <inttypes.h>

extern int moves_bubble;
extern int comparisons_bubble;

//
// Bubble Sort
// Sorts the array using Bubble Sort algorithm
//
// *array : An array containing integers to be sorted
// n : The number of integers in the array
//
uint32_t bubbleSort(uint32_t *array, int n);

#endif
