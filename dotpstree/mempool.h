/* mempool.h: a simple memory pool */
 
# ifndef DOTPSTREE_MEMPOOL_H_
# define DOTPSTREE_MEMPOOL_H_
 
# include <assert.h>
# include <stddef.h>
# include <stdlib.h>
 
struct mempool
{
  size_t capacity, size;
  char *data;
};
 
static inline
struct mempool* mempool_init(size_t capacity)
{
  struct mempool *pool = malloc(sizeof (struct mempool));
  pool->size = 0;
  pool->capacity = capacity;
  pool->data = calloc(capacity, sizeof (char));
  return pool;
}
 
static inline
void *mempool_alloc(struct mempool *pool, size_t size)
{
  // you should take care of initial capacity
  assert(pool->size + size <= pool->capacity);
  void *ptr = pool->data + pool->size;
  pool->size += size;
  return ptr;
}
 
static inline
void mempool_reset(struct mempool *pool)
{
  pool->size = 0;
}
 
static inline
void mempool_delete(struct mempool *pool)
{
  free(pool->data);
  free(pool);
}
 
# endif /* DOTPSTREE_MEMPOOL_H_ */
