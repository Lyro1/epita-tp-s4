# include <stdio.h>
# include <stdlib.h>
# include <string.h>
 
void foo(char *str) {
  char *buf = NULL;
  size_t len = 1 + strlen(str);
  buf = calloc(len, 1);
  strncpy(buf, str, len);
  printf("buf = %s\n", buf);
}
 
int main() {
  char *str = "A simple string ...";
  foo(str);
  return 0;
}
