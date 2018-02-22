
static int local_function(void)
{
	return 2;
}

int function2(void)
{
	return local_function();
}
