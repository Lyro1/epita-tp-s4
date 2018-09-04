# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <err.h>
# include <pthread.h>
# include <unistd.h>


struct worker_data
{
    int id;
    double *begin;
    double *end;
    double result;
};

double* min(double *a, double *b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

void* lin_array_sum(void* datavoid)
{
    struct worker_data* data = datavoid;
    printf("\n-----------------------\nThread %d started to compute lin_array_sum :\n", data->id);
    while (data->begin <= data->end)
    {
        printf(" | %f\n", *(data->begin));
        data->result += *(data->begin);
        (data->begin)++;
    }
    printf(" | Result = %.0f\n", data->result);
    pthread_exit(NULL);
}

void printarray(double* array, int size)
{
    //printf("| ");
    for (int i = 0; i < size; i++)
    {
        printf("%f+", array[i]);
    }
    printf("\n");
}

double basic_split_sum(double *begin, double *end, int nbthr)
{
    pthread_t* workers = malloc(sizeof(pthread_t) * nbthr);
    struct worker_data data[nbthr];
    int len = (end - begin) / nbthr;
    printf("begin = %p | end = %p | (end-begin = %d)| len = %d", begin, end, (end-begin), len);
    printf("\nlen for a thread is %d\n\n", len);
    double *cur = begin;
    for (int i = 0; i < nbthr; i++)
    {
        data[i].id = i;
        data[i].begin = cur;
        data[i].end = min(end, cur + len);
        pthread_create(workers + i, NULL, lin_array_sum, &(data[i]));
        cur = cur + len;
    }
    double result = 0;
    for (int i = 0; i < nbthr; i++)
    {
        pthread_join(workers[i], NULL);
        result += data[i].result;
    }
    free(workers);
    return result;
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        errx(EXIT_FAILURE, "Invalid arguments\n");
    }
    int arraySize = atoi(argv[1]);
    int nbthr = atoi(argv[2]);
    if (arraySize < nbthr)
    {
        errx(EXIT_FAILURE, "Too much threads.\n");
    }
    double *array = malloc(sizeof(double) * arraySize);
    srand(time(NULL));
    for (int i = 0; i < arraySize; i++)
    {
        array[i] = (double)rand();
    }
    printarray(array, arraySize);
    printf("Sum = %f", basic_split_sum(array, array + arraySize - 1, nbthr));
    free(array);
}
