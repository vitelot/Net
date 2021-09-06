#include <stdio.h>

void Dots(const char c, int i, int step)
{
  if( i%step == 0 ) {putchar(c); fflush(stdout);}
}
