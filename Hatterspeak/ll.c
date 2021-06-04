#include "ll.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Constructor for a ListNode.
//
// gs:  HatterSpeak struct containing oldspeak and its hatterspeak
// translation.
//
// Help From Oly Lab Section 11/23
//
ListNode *ll_node_create(HatterSpeak *gs) {
  if (!gs) {
    return 0;
  }
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  if (node == NULL) { // Return if allocation fails
    return 0;
  }
  node->gs = gs; // Set node to GS struct
  node->next = NULL; // Set next to NULL
  return node; // Return ListNode
}

//
// Destructor for a ListNode.
//
// n:   The ListNode to free.
//
void ll_node_delete(ListNode *n) {
  // Free memory in ListNode
  free(n->gs->oldspeak);
  free(n->gs->hatterspeak);
  free(n->gs);
  free(n);
}

//
// Destructor for a linked list of ListNodes
//
// head:    The head of the linked list.
//
// From Eugene's Lab Section 11/25
//
void ll_delete(ListNode *head) {
  ListNode *next = NULL;
  // Iterate through all nodes and free them
  while (head != NULL) {
    next = head->next;
    ll_node_delete(head);
    head = next;
  }
}

//
// Creates and inserts a ListNode into a linked list.
//
// head:    The head of the linked list to insert in.
// gs:      HatterSpeak struct.
//
// Oly Lab Section 11/23
// Eugene's Lab Section 11/25
//
ListNode *ll_insert(ListNode **head, HatterSpeak *gs) {
  if (ll_lookup(head, gs->oldspeak)) { // Free memory if ll_lookup
    free(gs->oldspeak);
    free(gs->hatterspeak);
    free(gs);
    return *head;
  }
  sum += 1;
  // Create a new ListNode
  ListNode *new = ll_node_create(gs);
  if (new == NULL) { // Assert ListNode is created successfully
    return 0;
  }
  new->next = *head; // Set to next to head
  *head = new; // Set head to ListNode (data)
  return *head; // Return the head
}

//
// Searches for a specific key in a linked list.
// Returns the ListNode if found and NULL otherwise.
//
// head:    The head of the linked list to search in.
// key:     The key to search for.
//
// Euguene Lab Section 11/25
//
ListNode *ll_lookup(ListNode **head, char *key) {
  seeks += 1;
  ListNode *previous = NULL; // Create new ListNode for tracking
  ListNode *current = *head; // Create ListNode set to head
  while (current != NULL) { // Run while current (ListNode) isn't NULL
    if (traversed_bool
        == false) { // If traversed_bool is true, stop adding to statistics
      traversed += 1;
    }
    if (strcmp(current->gs->oldspeak, key)
        == 0) { // Check if current key is equal to given key
      if (move_to_front && previous != NULL) { // Check for move_to_front
        previous->next = current->next; // Set previous next to current next
        current->next = *head; // Set current next to head
        *head = current; // Set head to current (data)
        return current;
      }
      return current;
    }
    previous = current; // Set previous to current to hold ListNode
    current = current->next; // Set current to current next (next node)
  }
  return NULL;
}
