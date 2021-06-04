#include "trie.h"
#include "code.h"

//
// Constructor for a TrieNode.
//
// code:    Code of the constructed TrieNode.
// returns: Pointer to a TrieNode that has been allocated memory.
//
// Eugene Lab Section 12/2
//
TrieNode *trie_node_create(uint16_t code) {
  TrieNode *n = (TrieNode *)malloc(sizeof(TrieNode));
  if (!n) { // Check if TrieNode was created successfully
    return 0;
  }
  for (int i = 0; i < 256; i++) { // Set all children to NULL (initialize)
    n->children[i] = NULL;
  }
  n->code = code; // Set TrieNode code to code
  return n;
}

//
// Destructor for a TrieNode.
//
// n:       TrieNode to free allocated memory for.
// returns: Void.
//
void trie_node_delete(TrieNode *n) {
  free(n); // Free TrieNode
}

//
// Initializes a Trie: a root TrieNode with the code EMPTY_CODE.
//
// returns: Pointer to the root of a Trie.
//
TrieNode *trie_create(void) {
  // Create TrieNode at EMPTY_CODE (1)
  return trie_node_create(EMPTY_CODE);
}

//
// Resets a Trie to just the root TrieNode.
//
// root:    Root of the Trie to reset.
// returns: Void.
//
void trie_reset(TrieNode *root) {
  for (int i = 0; i < 256; i++) { // Iterate through all children
    if (root->children[i] != NULL) { // Check if current index is not NULL
      trie_delete(root->children[i]);
    }
  }
  return;
}

//
// Deletes a sub-Trie starting from the sub-Trie's root.
//
// n:       Root of the sub-Trie to delete.
// returns: Void.
//
void trie_delete(TrieNode *n) {
  if (!n) { // Check if there exists a TrieNode
    return;
  }
  for (int i = 0; i < 256; i++) { // Iterate through all children
    trie_delete(n->children[i]);
  }
  trie_node_delete(n); // Delete TrieNode itself
  return;
}

//
// Returns a pointer to the child TrieNode representing the symbol sym.
// If the symbol doesn't exist, NULL is returned.
//
// n:       TrieNode to step from.
// sym:     Symbol to check for.
// returns: Pointer to the TrieNode representing the symbol.
//
TrieNode *trie_step(TrieNode *n, uint8_t sym) {
  return n->children[sym]; // Return symbol (if it exists)
}
