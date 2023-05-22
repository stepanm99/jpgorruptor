#include "corruptor.h"

void	buffer_shuffle(t_d *d)
{
	printf("buffer shuffle\n");
	long	rn;
	long	s1;
	long	s2;

	d->buffer1 = d->buffer1_start;
	d->buffer = d->buffer_start;
	printf("set buffers to the start\n");
	rn = (rand() % (d->flen / 4));
	s1 = (rand() % (d->flen / 5));
	s2 = (rand() % (d->flen / 5));
	printf("generated random values\n");
	printf("s1: %lu\ns2: %lu\nrn: %lu\nflen: %lu\n\n", s1, s2, rn, d->flen);
	printf("flen - s1: %lu\nflen - s2: %lu\n\n", d->flen - s1 - rn, d->flen - s2 - rn);
	if ((d->flen - s1 - rn) > 1 || ((d->flen - s2 + rn) - d->flen) > 1)
	{
		printf("Buffer would overflow!\nTrying again!\n");
		buffer_shuffle(d);
	}
	printf("after safety if\n");
	d->buffer += s1;
	d->buffer1 += d->flen - s2;
	printf("shifted buffer pointers\n");
	while (rn != 0)
	{
		*d->buffer = *d->buffer1;
		d->buffer++;
		d->buffer1++;
		rn--;
	}
	printf("first while done\n");
	d->buffer = d->buffer_start;
	d->buffer1 = d->buffer1_start;
	rn = d->flen;
	while (rn != 0)
	{
		*d->buffer1 = *d->buffer;
		d->buffer++;
		d->buffer1++;
		rn--;
	}
	printf("second while done\n");
	d->buffer = d->buffer_start;
	d->buffer1 = d->buffer1_start;
	printf("set buffers to the start\n");
}