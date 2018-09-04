# define _XOPEN_SOURCE 700
 
# include <err.h>
# include <stdio.h>
# include <stdlib.h>
 
void mycat(FILE *in, FILE *out) {
  for (;;) {
    char *line = NULL;
    size_t n = 0;
    if (getline(&line, &n, in) == -1) break;
    fprintf(out, "%s", line);
  }
}
 
int main(int argc, char *argv[]) {
  FILE *in = stdin;
  if (argc > 1) {
    in = fopen(argv[1], "r");
    if (!in) err(1, "can't open %s", argv[1]);
  }
  mycat(in, stdout);
  if (argc > 1)
    fclose(in);
  return 0;
}
