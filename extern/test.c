
#include <stdio.h>

extern int function1(void);
extern int function2(void);

int main(void)
{
	printf("function1: %d\nfunction2: %d\n", function1(), function2());
	return 0;
}
