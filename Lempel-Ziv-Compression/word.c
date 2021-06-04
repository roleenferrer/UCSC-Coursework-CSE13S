#include "word.h"
#include "code.h"
#include <stdio.h>

//
// Constructor for a word.
//
// syms:    Array of symbols a Word represents.
// len:     Length of the array of symbols.
// returns: Pointer to a Word that has been allocated memory.
//
Word *word_create(uint8_t *syms, uint64_t len) {
  Word *w = (Word *)malloc(sizeof(Word));
  if (!w) { // Check if Word was created successfully
    return 0;
  }

  w->syms = (uint8_t *)malloc(sizeof(uint8_t) * len + 1);
  if (!w->syms) { // Check if w->syms was created successfuly
    free(w); // Free w if not created successfuly
    return 0;
  }

  w->len = len; // Set w->len to given len

  for (uint64_t i = 0; i < len; i++) { // Copy syms to w->syms at index i
    w->syms[i] = syms[i];
  }

  return w;
}

//
// Constructs a new Word from the specified Word appended with a symbol.
// The Word specified to append to may be empty.
// If the above is the case, the new Word should contain only the symbol.
//
// w:       Word to append to.
// sym:     Symbol to append.
// returns: New Word which represents the result of appending.
// Eugene Lab Section 12/9
//
Word *word_append_sym(Word *w, uint8_t sym) {
  // Allocate memory to store temp symbols
  uint8_t *temp = (uint8_t *)malloc(sizeof(uint8_t) * w->len + 1);
  if (!temp) { // Check if temp was created succesfully
    return 0;
  }

  for (uint64_t i = 0; i < w->len; i++) { // Set temp syms to w->syms
    temp[i + 1] = w->syms[i + 1];
  }

  Word *x = word_create(temp, w->len + 1);
  if (!x) { // Check if x was created successfully
    free(temp); // Free temp if not created successfully
    return 0;
  }

  x->syms[x->len] = sym; // Set last index to sym to append

  free(temp); // Free memory of temp

  return x;
}

//
// Destructor for a Word.
//
// w:       Word to free memory for.
// returns: Void.
//
void word_delete(Word *w) {
  free(w->syms);
  free(w);
  return;
}

//
// Creates a new WordTable, which is an array of Words.
// A WordTable has a pre-defined size of MAX_CODE (UINT16_MAX - 1).
// This is because codes are 16-bit integers.
// A WordTable is initialized with a single Word at index EMPTY_CODE.
// This Word represents the empty word, a string of length of zero.
//
// returns: Initialized WordTable.
// Eugene Lab Section 12/2
WordTable *wt_create(void) {
  // Use calloc to already initialize the WordTable
  WordTable *t = calloc(MAX_CODE, sizeof(Word *));
  if (!t) { // Check if t was created successfully
    return 0;
  }
  // Initiallize t at index EMPTY_CODE (1) to some Word
  t[EMPTY_CODE] = (Word *)calloc(1, sizeof(Word));

  return t;
}

//
// Resets a WordTable to having just the empty Word.
//
// wt:      WordTable to reset.
// returns: Void.
//
void wt_reset(WordTable *wt) {
  // Iterate through START_CODE (2) to MAX_CODE (uint_16)
  for (uint32_t i = START_CODE; i < MAX_CODE; i++) {
    word_delete(wt[i]);
  }
  return;
}

//
// Deletes an entire WordTable.
// All Words in the WordTable must be deleted as well.
//
// wt:      WordTable to free memory for.
// returns: Void.
//
void wt_delete(WordTable *wt) {
  if (!wt) { // Check if wt exists
    return;
  }
  // Iterate through 0 - MAX_CODE (uint_16)
  for (uint32_t i = 0; i < MAX_CODE; i++) {
    if (wt[i] != NULL) { // Check if current index is not NULL
      word_delete(wt[i]); // Delete Word
    }
  }
  free(wt); // Free memory from WordTable
  return;
}
