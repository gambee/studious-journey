#include <stdio.h>
#include <stdlib.h>

int is_int(char* str)
{
	char* cur;
	for(cur = str;*cur;cur++)
		if(*cur < '0' || *cur >'9')
			return -1;
	return 0;
}

int div_alg(int a, int b)
{
	int x, y, d, r, ret;
	x = a > b ? a : b;
	y = x == b ? a : b;
	d = x/y;
	r = x%y;
	printf("%d = %d(%d) + %d\n", x, d, y, r);
	return r ? ((ret = div_alg(y,r)) ? ret : r) : r;
}


int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("Error: Expected 2 arguments, but %d were provided\n\n", argc-1);
		return -1;
	}
		
	if(is_int(argv[1]))
	{
		printf("Error: '%s' is not a positive integer!\n\n", argv[1]);
		return -2;
	}

	if(is_int(argv[2]))
	{
		printf("Error: '%s' is not a positive integer!\n\n", argv[2]);
		return -3;
	}

	div_alg(atoi(argv[1]),atoi(argv[2]));

	return 0;
}
