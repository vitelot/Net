#include <time.h>
#include "extern.h"

void RandomInit( long *Seed)
{
  *Seed = -time(NULL);

  URand( Seed); /* Initialize uniform random generator */
}
