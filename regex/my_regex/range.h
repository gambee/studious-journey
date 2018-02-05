/* range.h
 *
 * Max Gambee
 * Copyright 2018
 */

#ifndef RANGE_H
#	define RANGE_H
#	include <string.h>
#	include <ctype.h>
#	include <stdlib.h>
#	include <stdio.h>
#	include "char_stack.h"

#define BAD_TYPE -1
#define CTL_TYPE 1
#define NUM_TYPE 2

typedef struct {char member[32];} rng_ind;

typedef struct
{
	char lwrbnd;
	char uprbnd;
}cinterval;

typedef struct
{
	cinterval* intervals;
	char* isopnts;
}crng;


int spclstrcpy(char**, char*, int);
int spclstrlen(char*);
int catspclchar(char*, char, int);
int chartype(char);
char ctlletter(char);
int showbits(char);
int tob(int*, void*, int);
int cbit(int);
int cbitcnt(unsigned char);

int charbit(unsigned char, int);
int charset(unsigned char*, int);
int charflip(unsigned char*, int);

void rnginit(rng_ind*);
int rngbitcnt(rng_ind*);
int rngbit(rng_ind*, int);
int rngset(rng_ind*, int);
int rngflip(rng_ind*, int);
int rngstr(char*,rng_ind*,int);
char* rnggetfstr(rng_ind*);
void rngprintbits(rng_ind*);

void crnginit(crng*);
int isincrng(crng*, char);
int crngpopul(crng*,rng_ind*);

int spclstrcpy(char** dest, char* src, int max)
{
	int len, i;
	char *cur;

	if(!src || !dest)
		return -1;
	
	len = spclstrlen(src);

	if(!*dest)
	{
		if(max)
			return -2;
		else if(!(*dest = (char*) malloc(len + 1)))
			return -4;
	}
	else
	{
		if(!max)
			return -2;
		else if(len + 1 > max)
			return -3;
	}

	for(cur=src, i=0; *cur; ++cur)
	{
		if(chartype(*cur))
			i += catspclchar(*dest, *cur, 7);
		else *dest[i++] = *cur;
	}

	(*dest)[i] = 0;

	return i;
}
	

int spclstrlen(char* str)
{
	int len;
	char *cur;
	if(!str)
		return -1;
	len = 0;
	cur = str;

	while(*cur)
	{
		switch(chartype(*cur))
		{
			case 0:
				++len;
			case CTL_TYPE:
			case BAD_TYPE:
				len +=2;
				break;
			case NUM_TYPE:
				if(*cur<10)
					len +=3;
				else if(*cur<100)
					len +=4;
				else len +=5;
				break;
		}
		++cur;
	}

	return len;
}


int catspclchar(char* dest, char c, int max)
{
	char spcl[7];
	int type = chartype(c);

	if(!dest || !c)
		return 0;
	
	if(type == BAD_TYPE)
		strcpy(spcl, "\E");
	else if(type == CTL_TYPE)
		sprintf(spcl, "\\%c", ctlletter(c));
/*	{
		spcl[0] = '\';
		spcl[1] = ctlletter(c);
		spcl[2] = 0;
	}*/
	else //type == NUM_TYPE
		sprintf(spcl, "<%u>", c);
	
	type = strlen(spcl);

	if(type <= max)
	{
		strcat(dest, spcl);
		return type;
	}
	else return -type;
}


int chartype(char c)
{
	if(!c || c =='\b')
		return BAD_TYPE;
	else if(iscntrl(c)||(c == ' ')||(c == '-')||(c == '<')||(c == '{'))
		return CTL_TYPE;
	else if(isgraph(c))
		return 0;
	else return NUM_TYPE;
}

char ctlletter(char c)
{
	switch(c)
	{
		case '\n':
			return 'n';
		case '\t':
			return 't';
		case '\v':
			return 'v';
		case '\f':
			return 'f';
		case '\r':
			return 'r';
		case ' ':
			return 's';
		case '-':
			return '-';
		case '{':
			return '{';
		case '<':
			return '<';
		default:
			return 'E';
	}
}

void crnginit(crng* to_init)
{
	if(to_init)
	{
		to_init->intervals = NULL;
		to_init->isopnts = NULL;
	}
}

int isincrng(crng* range, char c)
{
	cinterval* intval;
	char* isopnt;

	if(!range)
		return 0;
	
	intval = range->intervals;
	isopnt = range->isopnts;

	if(isopnt)
		while(*isopnt)
			if(*isopnt == c)
				return 1;
			else ++isopnt;
		
	if(intval)
		while(intval->lwrbnd != 0)
			if(intval->uprbnd < c)
				intval++;
			else return (intval->lwrbnd > c) ? 0 : 1;
	
	return 0;
}
			
char* rnggetfstr(rng_ind* rngi)
{
	char* ret;
	int len, i;
	crng range;

	cinterval* curival;
	char* curisop;

	crnginit(&range);
	crngpopul(&range, rngi);

	if(range.intervals)
		for(len = 0; range.intervals[len].lwrbnd; ++len);
	len += range.intervals ? spclstrlen((char*)range.intervals) : 0;
	len += range.isopnts ? spclstrlen(range.isopnts) : 0;
	++len;

	if((ret = (char*) malloc(len)))
	{
		i = 0;
		curisop = range.isopnts;
		curival = range.intervals;
		if(curisop && curival)
		{
			while(*curisop && curival->lwrbnd)
			{
				if(*curisop < curival->lwrbnd)
				{
					if(chartype(*curisop))
						i += catspclchar(ret, *curisop, 7);
					else ret[i++] = *(curisop++);
				}
				else
				{
					if(chartype(curival->lwrbnd))
						i += catspclchar(ret, curival->lwrbnd, 7);
					else ret[i++] = curival->lwrbnd;
					ret[i++] = '-';
					if(chartype(curival->uprbnd))
						i += catspclchar(ret, curival->uprbnd, 7);
					else ret[i++] = curival->uprbnd;
					++curival;
				}
			}
		}
		if(curisop)
		{
			while(*curisop)
			{
				if(chartype(*curisop))
					i += catspclchar(ret, *curisop, 7);
				else ret[i++] = *(curisop++);
			}
		}
		if(curival)
		{
			while(curival->lwrbnd)
			{
				if(chartype(curival->lwrbnd))
					i += catspclchar(ret, curival->lwrbnd, 7);
				else ret[i++] = curival->lwrbnd;
				ret[i++] = '-';
				if(chartype(curival->uprbnd))
					i += catspclchar(ret, curival->uprbnd, 7);
				else ret[i++] = curival->uprbnd;
				++curival;
			}
		}
	}

	if(range.intervals)
		free(range.intervals);
	if(range.isopnts)
		free(range.isopnts);

	return ret;
}

int crngpopul(crng* range, rng_ind* rngi)
{
	int ivals, isops, i,flag;

/*
	int pntrsz = sizeof(char*);
	int ivalsz = sizeof(cinterval);
	*/

	char* curpnt;
	cinterval* curival;

	if(!range || !rngi)
		return -1;

	for(ivals=0, isops=0, i=1,flag=0;i<256;i++)
	{
		if(flag)
		{
			if(!rngbit(rngi,i))
				flag = 0;
		}
		else
		{
			if(rngbit(rngi,i))
			{
				if(rngbit(rngi,++i))
				{
					flag = 1;
					++ivals;
				}
				else ++isops;
			}
		}
	}
	/*
	printf("ivals: %d\t isops: %d\n", ivals, isops);
	printf("2*%d + (%d+1)*%d + (%d+1) = %d\n"
		,pntrsz
		,ivals
		,ivalsz
		,isops
		, (2*pntrsz + (ivals+1)*ivalsz + (isops+1))); 
	*/

	range->intervals = (cinterval*) malloc(sizeof(cinterval)*(ivals+1));
	range->isopnts = (char*) malloc(isops+1);

	for(curival=range->intervals, curpnt=range->isopnts,i=1,flag=0;i<256;i++)
	{
		if(flag)
		{
			if(!rngbit(rngi,i))
			{
				curival->uprbnd = i - 1;
				flag = 0;
				curival++;
			}
		}
		else
		{
			if(rngbit(rngi,i))
			{
				++i;
				if(rngbit(rngi,i))
				{
					curival->lwrbnd = i - 1;
					flag = 1;
				}
				else *(curpnt++) = i - 1;
					
			}
		}
	}
	curival->lwrbnd = 0;
	*curpnt = 0;
		
	return 0;
}

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
		dest[size-i] = showbits(tmp[i-1]);

	return 0;
}

int showbits(char c)
{
	int ret = 0, i,ten=1;
	for(i=7;i>=0;i--,ten*=10)
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
	if(size < rngbitcnt(rng) + 1)
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


void rngprintbits(rng_ind* rng)
{
	int i,j;
	if(rng)
		for(i=0;i<32;i+=8)
		{
			for(j=0;j<8;j++)
				printf("%08d ", showbits(rng->member[j+i]));
			printf("\n");
		}
		printf("\n");
}

#endif
