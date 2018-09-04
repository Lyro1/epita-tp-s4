# include "dot_out.h"
# include <stdlib.h>

void dot_output(FILE *out, struct process_set *set)
{
    struct tree *proctree = set->tree;
    fprintf("Process Tree {");
    _print_link(NULL, proctree);
    fprintf("}");
}

void _print_link(struct tree* parent, struct tree *child) {
    fprintf("  %d -> %d", parent->pid, child->pid);
    _print_link(child, child->child);
    _print_link(parent, child->sibling);
}
