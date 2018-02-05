/* comp.h
 *
 * Max Gambee
 * Copyright 2018
 *
 * sketches for range string compilation routines
 */

#include <stdio.h>
#include <stdlib.h>
#include "range.h"

char* expand(char* format)
{
	int state = 0;
	rng_ind rng;

	if(!format)
		return NULL;

	initrng(&rng);

	
