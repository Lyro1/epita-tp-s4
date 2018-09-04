# include "queue.h"

struct list* List()
{
  struct list* res = malloc(sizeof(struct list));
  res->next = res;
  return res;
}

void freeList(struct list* list, size_t size)
{
  while (size > 0)
  {
    struct list* nxt = list->next;
    list->next = NULL;
    free(list);
    list = nxt;
    size -= 1;
  }
  free(list);
}

struct queue* Queue() {
  struct queue* res = malloc(sizeof(struct queue));
  res->size = 0;
  res->list = NULL;
  return res;
}

void freeQueue(struct queue* queue) {
  freeList(queue->list, queue->size);
  free(queue);
}

void push(struct queue* queue, int x)
{
  struct list* q = malloc(sizeof(struct list));
  q->value = x;
  if (queue->size == 0)
  {
    q->next = q;
  }
  else
  {
    q->next = queue->list->next;
    queue->list->next = q;
  }
  queue->size += 1;
  queue->list = q;
}

int pop(struct queue* queue)
{
  if (queue->size == 0)
  {
    errx(EXIT_FAILURE, "Error in pop() : queue (%p) is empty", (void*)&queue);
  }
  struct list* q = queue->list->next;
  int x = q->value;
  if (q->next == q)
  {
    queue->list = NULL;
  }
  else
  {
    queue->list->next = q->next;
  }
  free(q);
  queue->size -= 1;
  return x;
}
