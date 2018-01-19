#include <stdio.h>

int main(void)
{
    int i;
    for(i = 0; i < 50; i++)
    {
        switch(i)
        {
            case 0:
            case 1:
            case 2:
            case 10:
                printf("i=%d is in 0-10\n", i);
                break;
            case 11:
            case 20:
                printf("i=%d is in 11-20\n", i);
                break;
            case 21:
            case 30:
                printf("i=%d is in 21-30\n", i);
                break;
        }
    }
        return 0;
}

