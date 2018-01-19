#include <stdio.h>
#include "express.h"

int main(int argc, char **argv)
{
	struct a_range range;
	char c;
	int i;

	range.low = 'a';
	range.high = 'z';
	range.neg = 1;

	for(i = 0, c = ('a' - 4); i < 10; i++, c++)
		printf("%c is in range a-z: %s\n", c, in_range(range, c) ? "False" : "True");
	

	printf("\nsizeof(a_range): %d\nsizeof(rng_elmnt): %d\n", 
		sizeof(struct a_range), sizeof(struct rng_elmnt));
	
	return 0;
}
