#include "bf.h"
#include "bv.h"
#include "hash.h"
#include "ll.h"
#include "parser.h"
#include "speck.h"
#include <getopt.h>
#include <inttypes.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t seeks = 0; // Declare varible for number of seeks
// Declare variables for statistical analysis
double number_of_ones = 0, traversed = 0, sum = 0;
// Declare variables for boolean check
bool traversed_bool = false, move_to_front = false;

// hs_create
// This function will take in an OldSpeak word and HatterSpeak
// in order to create a HatterSpeak struct.
//
// *old = OldSpeak word (key)
// *hatter = HatterSpeak word (translation or NULL)
//
HatterSpeak *hs_create(char *old, char *hatter) {
  HatterSpeak *hs = (HatterSpeak *)malloc(sizeof(HatterSpeak));
  if (hs == NULL) { // return nothing if struct is NULL
    return 0;
  }
  hs->oldspeak // Allocate memory for oldspeak word
      = (char *)malloc(strlen(old) + 1 * sizeof(char)); // Oly Lab Section 11/23
  if (hs->oldspeak != NULL) { // Assert that hs->oldspeak is not NULL
    strcpy(hs->oldspeak, old);
  }
  if (hatter != NULL) {
    // Allocate memory for hatterspeak word
    hs->hatterspeak = (char *)malloc(strlen(hatter) + 1 * sizeof(char));
    if (hs->hatterspeak != NULL) { // Assert that hs->hatterspeak is not NULL
      strcpy(hs->hatterspeak, hatter);
    }
  } else { // Set hs->hatterspeak to NULL if hatter is NULL
    hs->hatterspeak = NULL;
  }

  return hs; // Return HatterSpeak struct
}

int main(int argc, char **argv) {
  int opt = 0;
  uint32_t hash_length = 10000; // Default value
  uint32_t bloom_length = 1048576; // 2^20, default value

  bool statistics = false;

  while ((opt = getopt(argc, argv, "sh:f:mb")) != -1) {
    switch (opt) {
    case 's': // Print statistics
      statistics = true;
      break;
    case 'h': // Set hash length
      hash_length = atoi(optarg);
      break;
    case 'f': // Set bloom length
      bloom_length = atoi(optarg);
      break;
    case 'm': // Use move to front rule
      move_to_front = true;
      break;
    case 'b': // Do not use move to front rule
      move_to_front = false;
      break;
    }
  }
  if (hash_length == 0 || bloom_length == 0) {
    exit(0); // Exit program if either length is 0
  }
  // Create BloomFilter and Hash Table structs
  struct BloomFilter *words_bloom = bf_create(bloom_length);
  struct HashTable *words_hash = ht_create(hash_length);

  // Create buffers for words from each file
  char word[4096] = { 0 };
  char word2[4096] = { 0 };

  // Check oldspeak.txt and parse through bf and ht
  FILE *oldspeak_file = fopen("oldspeak.txt", "r");

  while (fscanf(oldspeak_file, "%s\n", word) != EOF) {
    bf_insert(words_bloom, word);
    ht_insert(words_hash, hs_create(word, NULL));
  }

  fclose(oldspeak_file); // Close oldspeak.txt

  // Check hatterspeak.txt and parse through bf and ht
  FILE *hatterspeak_file = fopen("hatterspeak.txt", "r");

  while (fscanf(hatterspeak_file, "%s %s\n", word, word2) != EOF) {
    bf_insert(words_bloom, word);
    ht_insert(words_hash, hs_create(word, word2));
  }

  fclose(hatterspeak_file); // Close hatterspeak.txt

  // Declare a regular expression to use
  // Help from Oly Lab Section 11/25
  regex_t word_regex;
  if (regcomp(
          &word_regex, "[a-zA-Z0-9_]+(('|-)[a-zA-Z0-9_]*)*", REG_EXTENDED)) {
    printf("Error with expression\n");
    return 0;
  }

  // Declare ListNode's to store words when parsing through i/o
  ListNode *translation = NULL;
  ListNode *forbidden = NULL;
  char *myword = NULL;

  bool translation_bool = false, forbidden_bool = false;

  // Run loop to parse through words until user exits (ctrl + d)
  while ((myword = next_word(stdin, &word_regex))) {
    if (ht_lookup(words_hash, myword) == NULL) {
      continue;
    }
    if (bf_probe(words_bloom, myword)) { // Check if word is in BloomFilter
      ListNode *node = ht_lookup(
          words_hash, myword); // Check if there exists a node of word
      if (node) { // If node exists in HashTable
        // Create a HatterSpeak struct to store into one of the ListNodes
        HatterSpeak *hs = hs_create(node->gs->oldspeak, node->gs->hatterspeak);
        if (node->gs->hatterspeak
            != NULL) { // If there is a hatterspeak translation, store into translation
          ll_insert(&translation, hs);
          translation_bool = true;
        } else { // If there is not a hatterspeak translation, store into forbidden
          ll_insert(&forbidden, hs);
          forbidden_bool = true;
        }
      }
    }
  }

  if (statistics == true) { // Print statistics if true
    printf("Seeks: %d\n", seeks); // Number of seeks
    printf("Average seek length: %f\n",
        traversed / seeks); // Traversed nodes / seeks
    // Number of LL insersts / HT length
    printf("Average Linked List Length: %f\n", sum / hash_length);
    double hash_length_double = hash_length;
    // Number of entries in HT / HT length
    printf("Hash table load: %f%%\n",
        (ht_count(words_hash) / hash_length_double) * 100);
    // Number of Set Bits / BF length
    printf("Bloom filter load: %f%%\n", (number_of_ones / bloom_length) * 100);
    // Free memory from LL from head of Linked Lists
    ListNode *head = forbidden;
    ListNode *head2 = translation;
    ll_delete(head);
    ll_delete(head2);
  } else {
    if (translation_bool
        && forbidden_bool) { // Print nontalk/hatterspeak message
      printf("Dear Comrade,\n\n");
      printf(
          "You have chose to use words that the queen has decreed oldspeak.\n");
      printf("Due to your infraction you will be sent to the dungeon where you "
             "will\n");
      printf("    be taught hatterspeak.\n\n");
      printf("Your errors:\n\n");

      ListNode *head = forbidden;
      while (forbidden != NULL) {
        printf("%s\n", forbidden->gs->oldspeak);
        forbidden = forbidden->next;
      }

      printf("\n");
      printf("Appropriate hatterspeak translations.\n\n");

      ListNode *head2 = translation;
      while (translation != NULL) {
        printf("%s -> %s\n", translation->gs->oldspeak,
            translation->gs->hatterspeak);
        translation = translation->next;
      }

      ll_delete(head);
      ll_delete(head2);

    } else if (translation_bool
               && !forbidden_bool) { // Print hatterspeak message
      printf("Dear Wonderlander,\n\n");
      printf("The decree for hatterspeak finds your message lacking. Some of "
             "the\n");
      printf("    words that you used are not hatterspeak.\n");
      printf("The list shows how to turn the oldspeak words into "
             "hatterspeak.\n\n");

      ListNode *head = translation;
      while (translation != NULL) {
        printf("%s -> %s\n", translation->gs->oldspeak,
            translation->gs->hatterspeak);
        translation = translation->next;
      }

      ll_delete(head);

    } else if (!translation_bool && forbidden_bool) { // Print nontalk message
      printf("Dear Comrade,\n\n");
      printf(
          "You have chose to use words that the queen has decreed oldspeak.\n");
      printf("Due to your infraction you will be sent to the dungeon where you "
             "will\n");
      printf("    be taught hatterspeak.\n\n");
      printf("Your errors:\n\n");

      ListNode *head = forbidden;
      while (forbidden != NULL) {
        printf("%s\n", forbidden->gs->oldspeak);
        forbidden = forbidden->next;
      }

      ll_delete(head);
    } else {
      printf("\n");
    }
  }
  // Free memory from ADT's
  clear_words();
  regfree(&word_regex);
  ht_delete(words_hash);
  bf_delete(words_bloom);

  return 0;
}
