# include <time.h>
# include <unistd.h>

# define TIMING_CODE(BLK__, RES__)	    \
    do {				    \
      struct timespec t0, t1;		    \
      clock_gettime(CLOCK_MONOTONIC, &t0);  \
      BLK__;				    \
      clock_gettime(CLOCK_MONOTONIC, &t1);  \
      RES__ = double_difftime(&t0, &t1);    \
    } while (0)

double double_difftime(struct timespec *t0, struct timespec *t1)
{
    return (double)(t1->tv_sec - t0->tv_sec);
}
