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

typedef struct
{
	char lwrbnd;
	char uprbnd;
}cinterval;

int atob(char);
int tob(int*, void*, int);
int cbit(int);
int cbitcnt(unsigned char);

int charbit(unsigned char, int);
int charset(unsigned char*, int);
int charflip(unsigned char*, int);

int rngbitcnt(rng_ind*);
void rnginit(rng_ind*);
int rngbit(rng_ind*, int);
int rngset(rng_ind*, int);
int rngflip(rng_ind*, int);
int rngstr(char*,rng_ind*,int);

int cbit(int i)
{
	if((i>=0)&&(i<8))
		return (1<<i);
	else
		return -1;
}

int tob(int* dest, void* data, int size)
{
	int i;
	char* tmp;

	if(!dest || !data || size<=0)
		return -1;
	
	for(tmp = (char*) data, i=1; i<=size; i++)
		dest[size-i] = atob(tmp[i-1]);

	return 0;
}

int atob(char c)
{
	int ret = 0, i,ten=1;
	for(i=0;i<8;i++,ten*=10)
		ret += ((!!((cbit(i)&c)))*(ten));
	return ret;
}

int cbitcnt(unsigned char c)
{
	int i,j;
	for(i=0, j=0; i<8; i++)
		j+=!!(c&cbit(i));
	return j;
}

int charbit(unsigned char byte, int i) {return (i<9) ? ((byte>>i)&1) : -1;}

void rnginit(rng_ind* rng){memset(rng->member,0,32);}
	 
int rngbit(rng_ind* rng, int i)
{
	if(!rng)
		return -1;
	return charbit(rng->member[i/8], i%8);
}

int rngset(rng_ind* rng, int i)
{
	if(rng&&(i<256))
		return charset(rng->member + i/8, i%8);
	else
		return -1;
}

int charset(unsigned char* c, int i)
{
	if(c && (i<8))
		return (*c = *c | cbit(i));
	else 
		return -1;
}

int charflip(unsigned char* c, int i)
{
	if(!c||(i<0)||(i>8))
		return -1;
	else
		return (*c = ( *c & ~cbit(i)) | ((*c & cbit(i)) ? 0 : cbit(i)));
}

int rngflip(rng_ind* rng, int i)
{
	if(rng&&(i<256))
	{
		return charflip(rng->member + i/8, i%8);
	}
	else return -1;
}

int rngbitcnt(rng_ind* rng)
{
	int i, cnt;
	
	if(!rng)
		return -1;
	
	for(i=0,cnt=0;i<32;i++)
		cnt += (rng->member[i] ? cbitcnt(rng->member[i]) : 0);
	
	return cnt;
}

int rngstr(char* dest, rng_ind* rng, int size)
{
	int i, j, index;

	if(!rng || !dest)
		return -1;
	if(size < rngbitcnt(rng) + 2)
	{
		*dest = 0;
		return -2;
	}
	memset(dest, 0, size); 
	
	for(i=0,index=0;i<32;i++)
		if(rng->member[i])
			for(j=0;j<8;j++)
				if(charbit(rng->member[i], j)>0)
				{
					dest[index] = i*8 + j;
					++index;
				}

	return index;
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
