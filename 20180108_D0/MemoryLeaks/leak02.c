# include <stdlib.h>
# include <stdio.h>
# include <string.h>
 
struct list {
  int          data;
  struct list *next;
};
 
static
struct list* add_front(struct list *list, int val) {
  struct list *tmp = malloc(sizeof (struct list));
  tmp->data = val;
  tmp->next = list;
  return tmp;
}
 
static
void print_list(struct list *list) {
  int line = 2;
  printf("list = [\n  ");
  for (; list; list = list->next) {
    if (line > 72) {
      printf("\n  ");
      line = 2;
    }
    line += printf("%4d;", list->data);
  }
  printf("\n]\n");
}
 
static
struct list* fill_list(size_t len) {
  struct list *list = NULL;
  for (size_t i = 0; i < len; i++)
    list = add_front(list, i);
  return list;
}
 
static
void delete_list(struct list *list) {
  struct list *tmp = list;
  while (tmp) {
    memset(tmp, 0, sizeof (struct list));
    list = tmp->next;
    free(tmp);
    tmp = list;
  }
}
 
int main(int argc, char *argv[]) {
  size_t len = 8;
  if (argc > 1)
    len = strtoul(argv[1], NULL, 10);
  struct list *list = fill_list(len);
  print_list(list);
  delete_list(list);
  return 0;
}
