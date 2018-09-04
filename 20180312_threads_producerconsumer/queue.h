# include <stdlib.h>
# include <stdio.h>
# include <err.h>

struct list {
    int value;
    size_t size;
    struct list* next;
};

struct queue {
    size_t size;
    struct list* list;
};

// Init a linked list without sentinel.
struct list* List();

// Free a linked list;
void freeList(struct list* list, size_t size);

// Init a new queue
struct queue* Queue();

// Free a Queue
void freeQueue(struct queue* queue);

// Push an element in the Queue
void push(struct queue* queue, int x);

// Pop an element from the Queue
int pop(struct queue* queue);
