#include <stdarg.h>

struct a_range{
	char low, high, neg;
};

struct rng_elmnt{
	struct a_range range;
	char is_last;
};

struct a_range mk_range(char low, char high, char neg)
{
	struct a_range range;
	range.low = low;
	range.high = high;
	range.neg = neg;
	return range;
}

int in_range(struct a_range range, char c)
{
	int ret;
	
	if(range.low < range.high)
		ret = (c >= range.low && c <= range.high) ? 0 : 1;
	else if(range.low > range.high)
		ret = (c < range.low && c > range.high) ? 0 : 1;
	else //range.low == range.high
		ret = (c == range.low) ? 0 : 1;
	
	return range.neg ? !ret : ret;
}


