#ifndef NIL
#define NIL (void *)0
#endif

#ifndef __BF_H__
#define __BF_H__

#include "bv.h"
#include <inttypes.h>
#include <stdbool.h>

//
// Struct definition for a BloomFilter.
//
// primary:     Primary hash function salt.
// secondary:   Secondary hash function salt.
// tertiary:    Tertiary hash function salt.
// filter:      BitVector that determines membership of a key.
//
typedef struct BloomFilter {
  uint64_t primary[2];
  uint64_t secondary[2];
  uint64_t tertiary[2];
  BitVector *filter;
} BloomFilter;

//
// Constructor for a BloomFilter.
//
// size: The number of entries in the BloomFilter.
//
BloomFilter *bf_create(uint32_t size);

//
// Destructor for a BloomFilter.
//
// bf: The BloomFilter.
//
void bf_delete(BloomFilter *bf);

//
// Inserts a new key into the BloomFilter.
// Indices to set bits are given by the hash functions.
//
// bf: The BloomFilter.
// key: The key to insert into the BloomFilter.
//
void bf_insert(BloomFilter *bf, char *key);

//
// Probes a BloomFilter to check if a key has been inserted.
//
// bf: The BloomFilter.
// key: The key in which to check membership.
//
bool bf_probe(BloomFilter *bf, char *key);

#endif
