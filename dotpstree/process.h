/* process.h: process structure */
 
# ifndef DOTPSTREE_PROCESS_H_
# define DOTPSTREE_PROCESS_H_
 
# include <stddef.h>
# include <unistd.h>
# include <proc/readproc.h>
 
# include "mempool.h"
# include "tree.h"
 
struct process
{
  pid_t pid;
  struct list list;
  struct tree tree;
};
 
struct process_set
{
  struct list *process_list;
  struct tree *process_tree;
  struct mempool *pool;
};
 
static inline
void process_set_init(struct process_set *set)
{
  // be large, allocate a million of struct process
  // lazy memory mapping is nice (and any way what is 100MB)
  set->pool = mempool_init(sizeof (struct process) * (1 << 20));
  set->process_list = mempool_alloc(set->pool, sizeof (struct list));
  list_init_sentinel(set->process_list);
  set->process_tree = NULL;
}
 
static inline
struct process* process_set_find(struct process_set *set, pid_t pid)
{
  struct list *cur;
  foreach_list(set->process_list, cur) {
    struct process *proc = CONTAINER_OF(struct process, list, cur->next);
    if (proc->pid == pid)
      return proc;
  }
  return NULL;
}
 
struct process* process_set_add(struct process_set *set, pid_t pid);
void process_set_attach_process(struct process_set *set, proc_t *procinfo);
struct process_set* make_process_set(void);
 
static inline
void process_set_delete(struct process_set *set)
{
  mempool_delete(set->pool);
  free(set);
}
 
# endif /* DOTPSTREE_PROCESS_H_ */
