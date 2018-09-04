# include <pthread.h>
# include <err.h>
# include <stdlib.h>
# include <stdio.h>

struct th_arg {
  const char *msg;
  size_t id;
};


// Basic function printinf the message and exiting the thread
void* helloFromThread(void* data)
{   
    struct th_arg* thddata = data;
    printf("<%zu> : ", thddata->id);
    printf(thddata->msg);
    pthread_exit(NULL);
}

// Main function. Requires one argument: the number of threads to create
int main(int argc, char* argv[])
{
    // Managing arguments error
    if (argc != 2)
    {
        errx(EXIT_FAILURE, "Invalid arguments\n");
    }

    // Creating usefull variables for the program
    size_t thdNumber = atoi(argv[1]);
    pthread_t thread_handles[thdNumber];
    struct th_arg data[thdNumber];
    
    for (size_t i = 0; i < thdNumber; i++)
    {
        (data + i)->msg = "Hello from thread !\n";
        (data + i)->id = i;
        int error = pthread_create(thread_handles + i, NULL, 
                                   helloFromThread, data + i);
        if (error != 0)
        {
            errx(EXIT_FAILURE, "Error while creating the thread.\n");
        }

        // Waiting for the thread to finish before creating the next one
        pthread_join(thread_handles[i], NULL);
    }
    
    return 0;
}
