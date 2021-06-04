#include "sieve.h"
#include <math.h>

// The Sieve of Eratosthenes.
// Set bits in a BitVector represent prime numbers.
// Composite numbers are sieved out by clearing bits.
//
// v : The BitVector to sieve.
// This code was from the Lab 4 Document
void sieve(BitVector *v) {
  bv_set_all_bits(v);
  bv_clr_bit(v, 0);
  bv_clr_bit(v, 1);
  bv_set_bit(v, 2);
  for (uint32_t i = 2; i < sqrtl(bv_get_len(v)); i += 1) {
    if (bv_get_bit(v, i)) {
      for (uint32_t k = 0; (k + i) * i <= bv_get_len(v); k += 1) {
        bv_clr_bit(v, (k + i) * i);
      }
    }
  }
  return;
}
