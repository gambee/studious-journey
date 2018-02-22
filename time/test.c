#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
	time_t start, current;
	double seconds;
	
	time(&start);

	while(1)
	{
		time(&current);
		printf("runtime:%f\n", difftime(current, start));
		usleep(300);

	}
	return 0;
}
