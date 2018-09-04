/* dot_out.h: produce dot file from process tree */

# ifndef DOTPSTREE_DOT_OUT_H_
# define DOTPSTREE_DOT_OUT_H_

# include <stdio.h>

# include "process.h"

void dot_output(FILE *out, struct process_set *set);

# endif /* DOTPSTREE_DOT_OUT_H_ */
