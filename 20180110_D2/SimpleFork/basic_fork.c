// basic_fork.c: simple example of fork
 
/*
 * MESSAGE is a simple wrapper around printf so that printf call display the
 * PID in front of the message
 * Must have at least 2 arguments, NULL can be used for the empty case
 */
# define MESSAGE(fmt_, args...) printf("(%u): " fmt_, getpid(), args);
 
int main() {
  int           fork_ret, x = 0;
  fork_ret = fork();
  if (fork_ret == -1)
    err(1, "Fork failed");
  if (fork_ret) {
    MESSAGE("Inside parent\n", NULL);
    MESSAGE("Initial x: %d\n", x);
    x = -42;
  } else {
    MESSAGE("Inside child\n", NULL);
    MESSAGE("Initial x: %d\n", x);
    x = 42;
  }
  MESSAGE("parent id: %u\n", getppid());
  MESSAGE("new x:%d\n", x);
  return 0;
}
