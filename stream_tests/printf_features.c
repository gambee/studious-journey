#include <stdio.h>

int main(int argc, char** argv)
{
	char bytes [] = {'a', 'b', 'c', 'd' };
	printf("%c\t%c\t%c\t%c\n", bytes[0], bytes[1], bytes[2], bytes[3]);
	printf("%d\t%d\t%d\t%d\n", bytes[0], bytes[1], bytes[2], bytes[3]);
	printf("%e\t%e\t%e\t%e\n", bytes[0], bytes[1], bytes[2], bytes[3]);
	printf("%o\t%o\t%o\t%o\n", bytes[0], bytes[1], bytes[2], bytes[3]);
	printf("%u\t%u\t%u\t%u\n", bytes[0], bytes[1], bytes[2], bytes[3]);
	printf("%x\t%x\t%x\t%x\n", bytes[0], bytes[1], bytes[2], bytes[3]);
	printf("%X\t%X\t%X\t%X\n", bytes[0], bytes[1], bytes[2], bytes[3]);
	printf("%c\t%c\t%c\t%c\n", bytes[0], bytes[1], bytes[2], bytes[3]);
	return 0;
}
