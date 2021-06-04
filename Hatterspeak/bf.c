#include "bf.h"
#include "speck.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

extern double number_of_ones;

//
// Constructor for a BloomFilter.
//
// size: The number of entries in the BloomFilter.
//
BloomFilter *bf_create(uint32_t size) {
  BloomFilter *bf = (BloomFilter *)malloc(sizeof(BloomFilter));
  if (bf) {
    bf->primary[0] = 0xfc28ca6885711cf7;
    bf->primary[1] = 0x2841af568222f773;
    bf->secondary[0] = 0x85ae998311115ae3;
    bf->secondary[1] = 0xb6fac2ae33a40089;
    bf->tertiary[0] = 0xd37b01df0ae8f8d0;
    bf->tertiary[1] = 0x911d454886ca7cf7;
    bf->filter = bv_create(size);
    if (bf->filter == NULL) {
      return bf;
    }

    for (uint32_t bit = 0; bit < bf->filter->length; bit++) {
      bv_clr_bit(bf->filter, bit);
    }

    return bf;
  }
  return (BloomFilter *)NIL;
}

//
// Destructor for a BloomFilter.
//
// bf: The BloomFilter.
//
void bf_delete(BloomFilter *bf) {
  bv_delete(bf->filter); // Delete BitVector ADT
  free(bf);
}

//
// Inserts a new key into the BloomFilter.
// Indices to set bits are given by the hash functions.
//
// bf: The BloomFilter.
// key: The key to insert into the BloomFilter.
//
void bf_insert(BloomFilter *bf, char *key) {
  // Store hashes using hash function
  uint32_t hash1 = 0, hash2 = 0, hash3 = 0;
  hash1 = hash(bf->primary, key) % bf->filter->length;
  hash2 = hash(bf->secondary, key) % bf->filter->length;
  hash3 = hash(bf->tertiary, key) % bf->filter->length;

  // Get bit at BitVector
  uint8_t bit1 = bv_get_bit(bf->filter, hash1);
  uint8_t bit2 = bv_get_bit(bf->filter, hash2);
  uint8_t bit3 = bv_get_bit(bf->filter, hash3);

  // Check if bit is set
  if (bit1 == 0) {
    number_of_ones += 1;
  }
  if (bit2 == 0) {
    number_of_ones += 1;
  }
  if (bit3 == 0) {
    number_of_ones += 1;
  }

  // Set bits at hash
  bv_set_bit(bf->filter, hash1);
  bv_set_bit(bf->filter, hash2);
  bv_set_bit(bf->filter, hash3);
  return;
}

//
// Probes a BloomFilter to check if a key has been inserted.
//
// bf: The BloomFilter.
// key: The key in which to check membership.
//
bool bf_probe(BloomFilter *bf, char *key) {
  // Store hashes using hash function
  uint32_t hash1 = 0, hash2 = 0, hash3 = 0;
  hash1 = hash(bf->primary, key) % bf->filter->length;
  hash2 = hash(bf->secondary, key) % bf->filter->length;
  hash3 = hash(bf->tertiary, key) % bf->filter->length;

  // Set bits at hash
  uint8_t bit1 = bv_get_bit(bf->filter, hash1);
  uint8_t bit2 = bv_get_bit(bf->filter, hash2);
  uint8_t bit3 = bv_get_bit(bf->filter, hash3);

  // Check if bits are set and return TRUE if they all are
  if (bit1 != 0 && bit2 != 0 && bit3 != 0) {
    return true;
  }
  return false;
}
