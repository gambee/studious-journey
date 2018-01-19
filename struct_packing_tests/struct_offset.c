#include <stdio.h>
#include <stddef.h>

struct test
{
	char a;
	char b;
	char c;
	int x;
	struct test *next;
};

int main(void)
{
	printf("Offset to a: %d\n", offsetof(struct test, a));
	printf("Offset to b: %d\n", offsetof(struct test, b));
	printf("Offset to c: %d\n", offsetof(struct test, c));
	printf("Offset to x: %d\n", offsetof(struct test, x));
	printf("Offset to next: %d\n", offsetof(struct test, next));
	return 0;
}
