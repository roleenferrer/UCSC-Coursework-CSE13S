#include "stack.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Most of the stack implemetation is from the lecture slideshow.
Stack *stack_create(int capacity, char name) {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  if (!s) {
    return 0;
  }
  if (capacity < 1) {
    capacity = 1;
  }
  s->name = name;
  s->capacity = capacity;
  s->top = 0;

  s->items = (int *)calloc(capacity, sizeof(int));
  if (!s->items) {
    free(s);
    return 0;
  }
  return s;
}

void stack_delete(Stack *s) {
  free(s->items);
  free(s);
  return;
}

int stack_pop(Stack *s) {
  if (!s) {
    return -1;
  }
  if (s->top > 0) {
    s->top -= 1;
    return s->items[s->top];
  } else {
    return -1;
  }
}

void stack_push(Stack *s, int item) {
  if (!s) {
    return;
  }
  if (s->top == s->capacity) {
    s->capacity *= 2;
    s->items = (int *)realloc(s->items, s->capacity * sizeof(int));
  }
  if (s->items) {
    s->items[s->top] = item;
    s->top += 1;
  }
  return;
}

bool stack_empty(Stack *s) {
  return s->top == 0;
}

int stack_peek(Stack *s) {
  if (s->top == 0) {
    return s->top;
  } else {
    return s->items[s->top - 1];
  }
}
