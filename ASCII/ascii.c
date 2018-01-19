#include <stdio.h>

int main(void)
{
	char i,c;
	for(i=0,c='0';i<10;i++,c++)
		printf("Character:\t%c\tASCII:\t%d\n", c,c);
	return 0;
}
