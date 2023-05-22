#include "corruptor.h"

void	random_bit(t_d *d)
{
	printf("buffer to buffer\n");
	long	k;

	k = d->i;
	d->buffer1 = d->buffer1_start;
	d->buffer = d->buffer_start;
	d->rn = rand() % k;
	d->rv = rand() % 250;
	while (k != 0)
	{
		if (k == d->rn)
		{
			*d->buffer1 = (unsigned char)d->rv;
			k--;
			d->buffer++;
			d->buffer1++;
		}
		*d->buffer1 = *d->buffer;
		d->buffer++;
		d->buffer1++;
		k--;
	}
	d->buffer1 = d->buffer1_start;
	d->buffer = d->buffer_start;
	k = d->i;
	while (k != 0)
	{
		*d->buffer = *d->buffer1;
		d->buffer++;
		d->buffer1++;
		k--;
	}
	d->buffer1 = d->buffer1_start;
	d->buffer = d->buffer_start;
}