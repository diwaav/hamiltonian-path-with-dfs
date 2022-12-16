// CITE: Stack constructor, destructor, stack print,
// struct provided by professor, as well as *x = s->items[s->top]

#include "stack.h"

#include "graph.h"
#include "path.h"
#include "vertices.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// The struct Stack defines the components of the stack
// top: keeps track of the next empty slot
// capacity: the number of items that can be pushed
// items: an array with the items

struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

// The stack_create() function constructs the stack
// Inputs: the capacity of the stack
// Outputs: pointer to the stack s

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

// The stack_delete() function destructs the stack
// Inputs: a pointer to the pointer for the stack
// Outputs: none

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

// The function stack_size() finds out how many items are in the stack
// Inputs: a pointer to the stack
// Outputs: the number of items in the stack

uint32_t stack_size(Stack *s) {
    return s->top;
}

// The stack_empty() function checks if the stack is empty
// Inputs: a pointer to the stack
// Outputs: true or false depending on if the stack is empty

bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    } else {
        return false;
    }
}

// The stack_full() function checks if the stack is full
// Inputs: a pointer to the stack
// Outputs: true or false depending on if stack is full

bool stack_full(Stack *s) {
    if (stack_size(s) == s->capacity) {
        return true;
    } else {
        return false;
    }
}

// The stack_push() function pushes an item into the top of the stack
// Inputs: a pointer to the stack, the item to be pushed
// Outputs: true or false depending on if the push was successful

bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        return false;
    } else {
        s->items[s->top] = x;
        s->top += 1;
        return true;
    }
}

// The stack_pop() function pops an item from the stack
// Inputs: a pointer to the stack, a pointer to the item to be popped
// Outputs: true or false depending on if pop was successful

bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    } else {
        s->top -= 1;
        *x = s->items[s->top];
        return true;
    }
}

// The stack_peek() function peeks into the top of the stack without
// popping anything off
// Inputs: a pointer to the stack, a pointer to the item to
// be looked at
// Outputs: true or false depending on if the top value was stored successfully

bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    } else {
        *x = s->items[s->top - 1];
        return true;
    }
}

// The stack_copy() function copies the src stack into dst so
// they are the same
// Inputs: pointers to stacks dst and src
// Outputs: none

void stack_copy(Stack *dst, Stack *src) {
    if (dst->capacity == src->capacity) {
        for (uint32_t i = 0; i < src->capacity; i += 1) {
            dst->items[i] = src->items[i];
        }
        dst->top = src->top;
    }
    return;
}

// The stack_print() function prints out the contents of the stack to
// the given file using fprintf().
// Inputs: a pointer to the stack, outfile, and cities
// Outputs: none

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
    return;
}
