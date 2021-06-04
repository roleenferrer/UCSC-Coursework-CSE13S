// shell.h - Header file for Shell Sort function

#ifndef __SHELL_H__
#define __SHELL_H__

#include <inttypes.h>

extern int moves_shell;
extern int comparisons_shell;

//
// Shell Sort
// Sorts the array using Shell Sort algorithm
//
// *array : An array containing integers to be sorted
// n : The number of integers in the array
//
void shellSort(uint32_t *array, int n);

#endif
