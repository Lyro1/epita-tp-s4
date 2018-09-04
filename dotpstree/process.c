# include "process.h"
# include "mempool.h"

/* process_set_add(set, pid) tries to add the process pid to the list and   */
/* returns it if it's already in the list, returns the process node         */
/* if it's the first encounter of the process, it'll add it to the          */
/* process list. The process will be set as the root of process tree        */
/* if pid==1                                                                */
struct process* process_set_add(struct process_set *set, pid_t pid)
{
    struct process* current = process_set_find(set, pid);
    if (!current)
    {
        current = mempool_alloc(set->pool, sizeof(struct process));
        current->pid = pid;
        list_push_front(set->process_list, current->list);
        if (pid == 1)
        {
            set->process_tree = &(current->tree);
        }
    }
    return current;
}

/* process_set_attach_process(set, procinfo) attaches a new process to the set       */
/* this function is responsible to add the process and attach it to its parent       */
void process_set_attach_process(struct process_set *set, proc_t *procinfo)
{
    pid_t pid = procinfo->tgid;
    struct process *proc = process_set_add(set, pid);
    if (pid != 1)
    {
        pid_t ppid = procinfo->ppid;
        struct process *pproc = process_set_find(set, ppid);
        tree_attach_child(pproc->tree, proc->tree);
    }
}

/* make_process_set() creates and populates the set of processes                     */
struct process_set* make_process_set(void)
{
    struct process_set *set = malloc(sizeof(struct process_set));
    process_set_init(set);
    proc_t* proclist = readproctab(PROC_FILLSTAT);
    while (proclist)
    {
        process_set_attach_process(set, proclist);
        proclist++;
    }
    return set;
}
