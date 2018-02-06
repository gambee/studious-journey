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
#	define BUF_DEBUG
#	include "buffer.h"

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
void rngprintbits(rng_ind*);
int bufputch(struct BUF_buffer*, int);
char* rngexpr(rng_ind*);

int bufputch(struct BUF_buffer *buf, int c)
{
	char fmt[100];
	if(!buf)
		return -1;

	switch(c)
	{
		case '\n':
			BUF_puts(buf, "\\n");
			return 0;
		case '\t':
			BUF_puts(buf, "\\t");
			return 0;
		case '\f':
			BUF_puts(buf, "\\f");
			return 0;
		case '\v':
			BUF_puts(buf, "\\v");
			return 0;
		case '\r':
			BUF_puts(buf, "\\r");
			return 0;
		case ' ':
			BUF_puts(buf, "\\s");
			return 0;
		case '\\':
			BUF_puts(buf, "\\\\");
			return 0;
		case '-':
			BUF_puts(buf, "\\-");
			return 0;
		case '<':
			BUF_puts(buf, "\\<");
			return 0;
		case '{':
			BUF_puts(buf, "\\{");
			return 0;
		case ']':
			BUF_puts(buf, "\\]");
			return 0;
	}

	if(isgraph(c))
		BUF_putc(buf, c);
	else
	{
		sprintf(fmt, "<%u>", c);
		BUF_puts(buf, fmt);
	}

	return 0;
}

char* rngexpr(rng_ind* rng)
{
	struct BUF_buffer buffer;
	int i, flag, blen;
	char *ret, *cur;

	if(!rng)
		return NULL;

	BUF_init(&buffer);

	BUF_putc(&buffer, '[');

	for(i=1,flag=0;i<256;i++)
	{
		if(flag)
		{
			if(!rngbit(rng,i))
			{
				bufputch(&buffer, i-1);
				flag = 0;
			}
		}
		else
		{
			if(rngbit(rng,i))
			{
				bufputch(&buffer, i);
				if(rngbit(rng,i+1))
				{
					BUF_putc(&buffer, '-');
					flag = 1;
				}
			}
		}
	}
	BUF_putc(&buffer, ']');

	
	blen = BUF_line_len(&buffer);
	blen = (blen < 0) ? -blen : blen; 
	ret = (char*) malloc(blen+1);

	if(ret)
		for(cur = ret; *cur = BUF_getc(&buffer); ++cur);
	else while(BUF_getc(&buffer));

	return ret;
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
