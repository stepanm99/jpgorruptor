#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int	main(void)
{
	long rn;

	srand(time(0));
	rn = rand() % 100000000;
	printf("random number: %ld", rn);
	return (0);
}