
int local_function(void)
{
	return 1;
}

int function1(void)
{
	return local_function();
}
