# include <stdio.h>
# include <stdlib.h>
 
int main() {
  int *p = NULL;
  *p = 42;
  printf("*p = %d\n", *p);
  return 0;
}
