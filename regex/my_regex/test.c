#include <stdio.h>

#define RANGE_DEBUG
#include "range.h"

	
int main(int argc, char **argv)
{
	int i;
	rng_ind rng;
	
	rnginit(&rng);

	for(i=0;i<256;i++)
	{
		printf("%3d : %3d\n", i, rngbitcnt(&rng));
		rngset(&rng, i);
	}

	for(i=0;i<256;i++)
	{
		printf("%3d : %3d\n", i, rngbitcnt(&rng));
		rngflip(&rng, i);
	}

	return 0;
}
