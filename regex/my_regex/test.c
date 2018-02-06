#include <stdio.h>
#include "range.h"

	
int main(int argc, char **argv)
{
	char *str;
	int i;
	rng_ind rng;

	rnginit(&rng);

	for(i='a';i<='z';++i)
		rngset(&rng, i);

	for(i='A';i<='Z';++i)
		rngset(&rng, i);

	rngset(&rng, '\n');
	rngset(&rng, '\t');
	rngset(&rng, ' ');
	rngset(&rng, 3);
	rngset(&rng, 245);


	rngprintbits(&rng);
	str = rngexpr(&rng);

	if(str)
		printf("%s\n", str);

	return 0;
}
