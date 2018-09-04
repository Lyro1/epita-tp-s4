/* dotpstree.c: a dot version of pstree using procps-ng */

# include <err.h>
# include <stdlib.h>
# include <stdio.h>

# include "dot_out.h"
# include "process.h"

int main(int argc, char *argv[])
{

  struct process_set *set = make_process_set();

  int has_file_output = 0;
  FILE *out = stdout;
  if (argc > 1) {
    out = fopen(argv[1], "w");
    has_file_output = 1;
    if (!out)
      err(1, "can't open %s", argv[1]);
  }

  dot_output(out, set);

  if (has_file_output)
    fclose(out);

  process_set_delete(set);

  return 0;
}
