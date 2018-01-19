#include <stdio.h>

int main(void)
{
	FILE* file = NULL;
	if(file)
		puts("file is non-NULL\n");
	else
		puts("file is NULL\n");
	
	file = fopen("test.out", "w");

	if(file)
		puts("file is non-NULL\n");
	else
		puts("file is NULL\n");

	fputs("Haha you silly-face!\n", file);
	fclose(file);

	if(file)
		puts("file is non-NULL\n");
	else
		puts("file is NULL\n");

	return 0;
}
