#include <stdio.h>
#include <stdlib.h>
#include <termcap.h>

int main(int argc, char** argv)
{
	switch(tgetent(NULL, getenv("TERM"))){
		case -1:	printf("Incomplete Access to Terminal Database for %s\n"
							,getenv("TERM"));
					break;
		case 0:		printf("%s is not defined in Terminal Database\n"
							,getenv("TERM"));
					break;
		default:	printf("Termcap successfully retrieved Terminal"
							" Capabilities\n");
	}

	tputs("

	return 0;
}
