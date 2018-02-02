#include <stdio.h>
#define BITSTR_DEBUG
#include "bitstr.h"

int main(void)
{
	int size, cl, diff, max = bstrlen(0xFF);
	double percent;

	int SIZE, CL, DIFF;
	double PERCENT = 0;

	for(size = 1; size < max; size++)
	{
		cl = bstrlen(closest(size));
		diff = cl - size;
		percent = (100*((double) diff))/((double)cl);
		printf("size:%8d\tcl:%8d\tdiff:%6d\ttolerance:% 06.4f%%\n", size,cl,diff,percent);
		if(percent > PERCENT)
		{
			SIZE = size;
			CL = cl;
			DIFF = diff;
			PERCENT = percent;
		}
	}


	printf("SIZE:%8d\tCL:%8d\tDIFF:%6d\ttolerance:% 06.4f%%\n", SIZE,CL,DIFF,PERCENT);
	return 0;
}
