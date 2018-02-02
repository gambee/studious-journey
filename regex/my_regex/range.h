/* range.h
 *
 * Max Gambee
 * Copyright 2018
 */

#ifndef RANGE_H
#	define RANGE_H
#	include <string.h>
#	include <stdlib.h>
#	include "char_stack.h"


typedef struct {char member[32];} rng_ind;

int atob(char);

int charbit(unsigned char, int);
int charset(char*, int);
int charflip(char*, int);

int rngbit(rng_ind*, int);
int rngset(rng_ind*, int);
int rngflip(rng_ind*, int);
char* rngstr(rng_ind*);
void rnginit(rng_ind*);



int atob(char c)
{
	int ret = 0, i,ten=1;
	for(i=0;i<8;i++,ten*=10)
		ret += ((!!(((c>>i)&0x01)))*(ten));
	return ret;
}

void rnginit(rng_ind* rng){memset(rng->member,0,32);}

int charbit(unsigned char byte, int i) {return (i<9) ? ((byte>>i)&1) : -1;}
	 
int rngbit(rng_ind* rng, int i)
{
	if(!rng)
		return -1;
	return charbit(rng->member[i/8], i%8);
}

int rngset(rng_ind* rng, int i)
{
	int ret = -1;
	if(rng)
	{
		ret = rngbit(rng, i);
	}

	
	return ret;
}

int charset(char* c, int i)
{
	int ret;
	if(c && (i<8))
	{
		ret = charbit(*c, i);
		*c = *c | (1<<i);
	}
	else ret = -1;
	return ret;
}

int charflip(char* c, int i)
{
	return 0;
}

int rngflip(rng_ind* rng, int i)
{
	return 0;
}

char* rngstr(rng_ind* rng)
{
	return NULL;
}


#ifdef RANGE_DEBUG
#	include <stdio.h>


void rng_print(rng_ind*);


void rng_print(rng_ind* rng)
{
	int i,j;
	if(rng)
		for(i=0;i<32;i+=8)
		{
			for(j=0;j<8;j++)
				printf("%08d ", atob(rng->member[j+i]));
			printf("\n");
		}
}

#endif
#endif
