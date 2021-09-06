#include <sys/time.h>
double Timer(void)
{
  struct timeval tv;
  struct timezone tz;

  gettimeofday(&tv, &tz);

  return (double)tv.tv_sec + (double)tv.tv_usec/1e6 ;
}
