#include "src/corruptor.h"

void	dinit(t_d *d)
{
	d->i = 0;
}



int	main(void)
{
	t_d	d;
	int	index;
	int index1;

	printf("How many random bytes: ");
	scanf("%i", &index);
	printf("\nHow many shuffles: ");
	scanf("%i", &index1);
	dinit(&d);
	file_to_buffer(&d);
	srand(time(0));
	while (index)
	{
		random_bit(&d);
		index--;
	}
	while (index1)
	{
		buffer_shuffle(&d);
//		printf("s1: %lu\ns2: %lu\n\n", d.s1, d.s2);
		index1--;
	}
	index1 = 0;
	while (index1)
	{
		random_minus(&d);
		index1--;
	}

	buffer_to_file(&d);
	buffer1_to_file(&d);
	free_buffers(&d);
	return (0);
}