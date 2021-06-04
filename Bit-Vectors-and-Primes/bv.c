#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>

// Struct definition for a BitVector.
//
// vector : The vector of bytes to hold bits.
// length : The length in bits of the BitVector.
typedef struct BitVector {
  uint8_t *vector;
  uint32_t length;
} BitVector;

// *bv_create Function
// Creates a new BitVector of specified length.
//
// Parameters:
// bit_len : The length in bits of the BitVector.
// With the help of Oly from lab section
BitVector *bv_create(uint32_t bit_len) {
  BitVector *v = (BitVector *)malloc(sizeof(BitVector));
  if (!v) { // Check if creation of BitVector is successful
    return 0;
  }

  if (bit_len < 1) { // If array size is less than 1, set to 1 to malloc
    bit_len = 1;
  }

  v->length = bit_len;
  v->vector = (uint8_t *)malloc(((bit_len / 8) + 1) * sizeof(uint8_t));

  if (!v->vector) { // Free BitVector if unsuccessful allocation
    free(v);
    return 0;
  }
  return v;
}

// bv_delete Function
// Frees memory allocated for a BitVector.
//
// Parameters:
// v : The BitVector.
void bv_delete(BitVector *v) {
  free(v->vector); // Free elements from v->vector first
  free(v); // Free BitVector itself
  return;
}

// bv_get_len Function
// Returns the length in bits of the BitVector.
//
// Parameters:
// v : The BitVector.
uint32_t bv_get_len(BitVector *v) {
  return v->length;
}

// bv_set_bit Function
// Sets the bit at index in the BitVector.
//
// Parameters:
// v : The BitVector.
// i : Index of the bit to set.
void bv_set_bit(BitVector *v, uint32_t i) {
  v->vector[i / 8] = v->vector[i / 8] | (1 << (i % 8));
  // Bits are indexed per 8 bits (e.g 0-7).
  // OR the current bit with 0x1 shifted left at index
  return;
}

// bv_clr_bit Funciton
// Clears the bit at index in the BitVector.
//
// Parameters:
// v : The BitVector.
// i : Index of the bit to get.
void bv_clr_bit(BitVector *v, uint32_t i) {
  v->vector[i / 8] = v->vector[i / 8] & ~(1 << (i % 8));
  // Bits are indexed per 8 bits (e.g 0-7)
  // AND the current bit with NOT of 0x1 shifted left at index
  return;
}

// bv_get_bit Function
// Gets a bit from a BitVector.
//
// Parameters:
// v : The BitVector.
// i : Index of the bit to get.
uint8_t bv_get_bit(BitVector *v, uint32_t i) {
  return v->vector[i / 8] & (1 << (i % 8));
  // Bits are indexed per 8 bits (e.g 0-7)
  // AND the current bit with 0x1 shifted left at index
}

// bv_set_all_bits Function
// Sets all bits in a BitVector.
//
// Parameters:
// v : The BitVector.
void bv_set_all_bits(BitVector *v) {
  for (uint32_t i = 0; i < bv_get_len(v) + 1; i++) {
    // For each index until v->length
    bv_set_bit(v, i); // Set bit at index
  }
  return;
}
