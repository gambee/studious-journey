#include <stdio.h>

#define RANGE_DEBUG
#include "range.h"

	
int main(int argc, char **argv)
{
	char *cur,str[257], input[201];
	int i;
	rng_ind rng;


	while(1)
	{
		memset(input,0,257);
		rnginit(&rng);
		printf("enter an input curing:\n\t");
		scanf("%s", input);

		for(cur=input;*cur;cur++)
			rngset(&rng,*cur);
		
		i = rngstr(str, &rng, 257);

		if(i>0)
			printf("%s\n", str);
		else
		{
			printf("\n");
			break;
		}
	}

	return 0;
}
