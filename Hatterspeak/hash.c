#include "hash.h"
#include "speck.h"
#include <stdio.h>
#include <stdlib.h>

//
// Constructor for a HashTable.
//
// length:  Length of the HashTable.
// salt:    Salt for the HashTable.
//
HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3;
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    return ht;
  }

  return (HashTable *)NIL;
}

//
// Destructor for a HashTable.
//
// ht:  The HashTable.
//
// Euguene's Lab Section 11/25
//
void ht_delete(HashTable *ht) {
  // Parse through all indexes of heads and free ListNode.
  for (uint32_t i = 0; i < ht->length; i++) {
    if (ht->heads[i] != NULL) {
      ll_delete(ht->heads[i]);
    }
  }
  free(ht->heads);
  free(ht);
}

//
// Returns number of entries in hash table
//
// h:   The HashTable.
//
uint32_t ht_count(HashTable *h) {
  uint32_t count = 0;
  // Parse through al indexes heads and check if not NULL
  for (uint32_t i = 0; i < h->length; i++) {
    if (h->heads[i] != NULL) {
      count += 1;
    }
  }
  return count;
}

//
// Searches a HashTable for a key.
// Returns the ListNode if found and returns NULL otherwise.
// This should call the ll_lookup() function.
//
// ht:  The HashTable.
// key: The key to search for.
//
ListNode *ht_lookup(HashTable *ht, char *key) {
  // Store index using HT salt % HT length
  uint32_t index = (hash(ht->salt, key)) % ht->length;
  // Check if there is a valid ListNode at index
  return ll_lookup(&ht->heads[index], key);
}

//
// First creates a new ListNode from HatterSpeak.
// The created ListNode is then inserted into a HashTable.
// This should call the ll_insert() funciton.
//
// ht:  The HashTable.
// gs:  The HatterSpeak to add the HashTable.
//
void ht_insert(HashTable *ht, HatterSpeak *gs) {
  // Store index using HT salt % HT length
  uint32_t index = hash(ht->salt, gs->oldspeak) % ht->length;
  // Insert ListNode into HT
  ht->heads[index] = ll_insert(&ht->heads[index], gs); // Insert
  return;
}
