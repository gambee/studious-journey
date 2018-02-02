#include <stdio.h>

#define RANGE_DEBUG
#include "range.h"

	
int main(int argc, char **argv)
{
	int set, i;
	unsigned char c = 0;
	for(i=0;i<8;c=0,i++)
	{
		set = charset(&c,i);
		printf("c: %08d\tset:%d\n", atob(c), set);
	}
	printf("c: %08d\tset:%d\n", atob(c), set);

	return 0;
}
