#include <stdio.h>


int main(void)
{
	int i=0,j=0;

	start:
		switch(i){
			case 0: ++i;
			defualt: ++j;
		}
	one:
		switch(j){
			case 1:	--i;
			default: goto end;
		}
	two:
		switch(i){
			case 0: goto start;
			default: printf("hahahahah");
		}
	end: return 0;
}
	
