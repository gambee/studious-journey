#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	FILE* file = fopen("file.txt", "w");
	fprintf(file, "Testing, Testing...");
	return 0;
}
