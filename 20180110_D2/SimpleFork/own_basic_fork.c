# define MESSAGE(fmt_, args...) printf("(%u): " fmt_, getpid(), args);
 
void random_fill(int tab[], size_t len) {
  for (int *cur = tab; cur != tab + len; ++cur)
    *cur = random() % 1024;
}
 
void swap(int *a, int *b) {
  int           c = *a;
  *a = *b;
  *b = c;
}
 
void sort01(int tab[], size_t len) {
  for (size_t i = 0; i < len; ++i) {
    size_t      min = i;
    for (size_t j = i + 1; j < len; ++j)
      if (tab[j] < tab[min]) min = j;
    swap(tab + i, tab + min);
  }
}
 
void sort02(int tab[], size_t len) {
  int           move = 1;
  for (size_t i = 0; i < len && move; ++i) {
    move = 0;
    for (size_t j = 0; j < len - i - 1; ++j) {
      if (tab[j] > tab[j + 1]) {
        move = 1;
        swap(tab + j, tab + j + 1);
      }
    }
  }
}
 
int is_sorted(int tab[], size_t len) {
  size_t        j;
  for (j = 1; j < len && tab[j - 1] <= tab[j]; ++j) {}
  return j == len;
}
