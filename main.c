#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct s_d {
	char	filename_i[50];
	char	filename_o[50];
	FILE	*fileptr;
	char	*buffer;
	char	*buffer1;
	char	*buffer_start;
	char	*buffer1_start;
	long	flen;
	long	i;
	long	rn;				//random number
	long	rv;				//random value
}	t_d;

void	dinit(t_d *d)
{
	d->i = 0;
}

void	file_to_buffer(t_d *d)
{
	d->fileptr = fopen("input.jpg", "rb");
	fseek(d->fileptr, 0, SEEK_END);
	d->flen = ftell(d->fileptr);
	rewind(d->fileptr);
	d->buffer = (char *)malloc((d->flen + 1) * sizeof(char));
	d->buffer1 = (char *)malloc((d->flen + 1) * sizeof(char));
	if (!d->buffer || !d->buffer1)
	{
		printf("Allocation failed :(\n");
		return ;
	}
	d->buffer_start = d->buffer;
	d->buffer1_start = d->buffer1;
	while (d->i < d->flen)
	{
		fread(d->buffer, 1, 1, d->fileptr);
		d->buffer++;
		d->i++;
	}
	fclose(d->fileptr);
	d->buffer = d->buffer_start;
}

void	buffer_to_file(t_d *d)
{
	d->fileptr = fopen("output.jpg", "wb");
	while (d->i != 0)
	{
		fprintf(d->fileptr, "%c", *d->buffer1);
		d->buffer1++;
		d->i--;
	}
	fclose(d->fileptr);
}

void	buffer_to_buffer(t_d *d)
{
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
			*d->buffer1 = (char)d->rv;
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

void	free_buffers(t_d *d)
{
	free(d->buffer_start);
	free(d->buffer1_start);
}

void	buffer_shuffle(t_d *d)
{
	long	n;

	n = (rand() % (d->i) / 5);
	d->buffer += (rand() % (d->i - n));
	d->buffer1 += d->i;
	d->buffer1 -= (rand() % (d->i - n));
	memmove(d->buffer1, d->buffer, n);
	d->buffer1 = d->buffer1_start;
	d->buffer = d->buffer_start;
}

int	main()
{
	t_d	d;
	int	index;
	int index1;

	index = 50;
	index1 = 5;
	dinit(&d);
	file_to_buffer(&d);
	srand(time(0));
	while (index)
	{
		buffer_to_buffer(&d);
		index--;
	}
	while (index1)
	{
	buffer_shuffle(&d);
	index1--;
	}
	buffer_to_file(&d);
	free_buffers(&d);
	return (0);
}