# include <stdio.h>
# include <stdlib.h>
# include <string.h>
 
void foo(char *str) {
  char buf[8];
  strcpy(buf, str);
  printf("buf: %s\n", buf);
}
 
int main() {
  char str[32];
  for (size_t i = 0; i < 31; i++)
    str[i] = 'a';
  str[31] = 0;
  foo(str);
  return 0;
}
