# include <stdio.h>
# include <stdlib.h>
# include <err.h>
# include <errno.h>
# include <pthread.h>
# include <unistd.h>

struct thd_info {
    size_t id;
};

void echo(size_t id) {
  int r;
  char buf[256];
  while ( (r = read(STDIN_FILENO, buf, 255)) ) {
    if (r == -1) {
      if (errno == EINTR) continue;
      err(2, "Issue reading from stdin in thread %zu", id);
    }
    buf[r] = 0;
    printf("<%02zu>: %s", id, buf);
  }
}

void* echoThread(void* arg)
{
    struct thd_info* info = arg;
    echo(info->id);
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        errx(EXIT_FAILURE, "Invalid arguments.\n");
    }

    size_t thdNumber = atoi(argv[1]);
    pthread_t thread_handles[thdNumber];
    struct thd_info data[thdNumber];    

    for (size_t i = 0; i < thdNumber; i++)
    {
        data[i].id = i;
        int e = pthread_create(thread_handles + i, NULL, echoThread, data + i);
        if (e != 0)
        {
            errx(EXIT_FAILURE, "Error while creating the thread n°%zu", i);
        }
        pthread_join(thread_handles[i], NULL);  
    }   
    return 0;
}
