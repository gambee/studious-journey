/* bitstr.h
 *
 * Max Gambee
 * Copyright 2018
 */


char mkbstrlen(int i, int j)
{
	char I, J, ret;
	I = (char) i;
	J = (char) j;
	return (((0x0F & i) << 4) | (0x0F & j));
}

int bstrlen(char c)
{
	int i = (0xF0 & c) >> 4;
	int j = (0x0F & c);
	return (!j)*16*(1<<i)+(!(!j))*(!(!i))*8*(1<<i)+(!(!j))*j*(1<<(i?(i-1):0));
}

char closest(int size)
{
	int i, j;
	for(i = 0; (i < 0x10)&&(bstrlen(i<<4) < size); i++);
	if(bstrlen(i = (i<<4)) == size)
		return i;
	else for(j=1; (j<0x0F)&&(bstrlen(i|j)<size); j++);

	return (bstrlen(i|j) < size)? i : i|j;
}
