#include <stdio.h>

#define TAB_WIDTH 4

int main(void)
{
	char c;

	int len = 0;
	int line = 1;

	int max_len = -1;
	int max_line = -1;

	while((c = getchar()) != EOF)
	{
		switch(c)
		{
			case '\n':
				if(len > max_len)
				{
					max_line = line;
					max_len = len;
				}
				++line;
				len = 0;
				break;
			case '\t':
				len += TAB_WIDTH;
				break;
			default:
				++len;
				break;
		}
	}

	printf("The longest line length is %d, which first occurs on line %d.\n", max_len, max_line);

	return 0;
}
