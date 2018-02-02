#include <stdio.h>

#define RANGE_DEBUG
#include "range.h"

	
int main(int argc, char **argv)
{
	cinterval test[10];
	char* lwr = (char*) test;
	char* upper = (char*) &test[8];
	printf("expect 16: %d\n", (int) (upper - lwr));

	return 0;
}
