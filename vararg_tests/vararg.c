#include <stdio.h>
#include <stdarg.h>

int var_func(int x, int y, ...)
{
	int z;
	char args = y;
	if(y == 3)
	{
		va_list v;
		va_start(v, y);

		z = va_arg(v, int);
	}
	if(args == 3)
		printf("Arguments: 3: x=%d, y=%d, z=%d\n", x, y, z);
	else if (args == 2)
		printf("Arguments: 2: x=%d, y=%d\n", x, y);
	else
	{
		fprintf(stderr, "ERROR: var_func expected either 2 or 3 arguments\n");
		fprintf(stderr, "recieved %d arguments", args);
	}
	return args;
}


		
int main(int argc, char** argv)
{
	var_func(1,3,2);
	var_func(1,2);
	return 0;
}
