#include <stdio.h>
//#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

char prgm [] = \
	"#include <stdio.h>\nint main(int argc, char **argv)\n"
	"{\n"
	"printf(\"hello world!\\n\");\n"
	"return 0;\n"
	"}";

char prgm_name [] = "output.c";
char compile [] = "gcc %s -o jit.out";
	

int main(int argc, char **argv)
{
	char tmp[101];
	*tmp = 0;

	char output[101];
	strcpy(output, "Failed to compile and run jit.out\n");

	char* exe = NULL;
	FILE *file = NULL;
	FILE *run = NULL;

	file = fopen(prgm_name, "w");
	if(!file)
	{
		fprintf(stderr, "Unable to open file 'output.c'\n");
		return 1;
	}//else
		fprintf(file, "%s", prgm);
		fclose(file);
	exe = (char*) malloc(strlen(prgm_name) + strlen(compile));
	sprintf(exe, compile, prgm_name);
	pclose(popen(exe, "w"));
	run = popen("./jit.out", "r");
	if(run)
	{
		fscanf(run, "%[^\n]", tmp);
		pclose(run);
	}
	sprintf(output, "%s\n", tmp);
	printf(output);
	
	return 0;
}
