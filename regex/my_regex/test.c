#include <stdio.h>
#include "range.h"

	
int main(int argc, char **argv)
{
	char *str;
	int i;
	rng_ind rng;
	rnginit(&rng);

	compexpr(&rng, "[abcdefg]");
	rngprintbits(&rng);
	str = rngexpr(&rng);
	if(str)
		printf("%s\n", str);

compexpr(&rng, "[^abcdefg]");
	rngprintbits(&rng);
	str = rngexpr(&rng);
	if(str)
		printf("%s\n", str);


	return 0;
}
