#include "corruptor.h"

void	random_bit_minus(t_d *d)
{
	printf("random minus\n");
	long	rn;
	long	rl;
	long	rv;
	long	k;

	rv = rand() % 10;
	rn = rand() % d->i;
	rl = rand() % (d->i / 20);
	k = d->i;
	d->buffer1 = d->buffer1_start;
	d->buffer = d->buffer_start;
	while (k != 0)
	{
		if (k == rn)
		{
			while (rl != 0 && k != 0)
			{
				if ((*d->buffer - rv) > 0)
					*d->buffer1 = (*d->buffer - rv);
				else
					*d->buffer1 = *d->buffer;
				d->buffer++;
				d->buffer1++;
				k--;
				rl--;
			}
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