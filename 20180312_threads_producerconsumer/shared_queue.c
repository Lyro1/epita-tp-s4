# include "shared_queue.h"

// Classical queue implementation

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


// Shared queue implementation

struct shared_queue* new_shared_queue(void)
{
    struct shared_queue* sq = malloc(sizeof(struct shared_queue));

    sem_t lock;
    if ( sem_init(&lock, 0, 1) == -1)
      errx(1, "Failed to initialize semaphore lock.\n");
    sq->lock = lock;

    sem_t size;
    if ( sem_init(&size, 0, 0) == -1)
      errx(1, "Failed to initialize semaphore size.\n");
    sq->size = size;

    return sq;
}

void shared_queue_push(struct shared_queue *queue, int val)
{
  sem_wait(&(queue->lock));
  push(queue->store, val);
  sem_post(&(queue->size));
  sem_post(&(queue->lock));
}

int shared_queue_pop(struct shared_queue *queue)
{
  sem_wait(&(queue->lock));
  sem_wait(&(queue->size));
  int res = pop(queue->store);
  sem_post(&(queue->lock));
  return res;
};

void shared_queue_destroy(struct shared_queue *queue)
{
  freeQueue(queue->store);
  free(queue);
}
