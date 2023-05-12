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
	d->fileptr = fopen("input.bmp", "rb");
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
	d->buffer = d->buffer_start;
	d->fileptr = fopen("output.bmp", "wb");
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
	long	rn;
	long	s1;
	long	s2;

	rn = (rand() % ((d->i) / 2));
	s1 = (d->i - (rand() % (d->i / 2))) / 2;
	s2 = (d->i - (rand() % (d->i / 2))) / 4;
	if ((s1 + rn) > d->i || (s2 + rn) > d->i)
		buffer_shuffle(d);
	d->buffer += s1;
	d->buffer1 += s2;
	memmove(d->buffer, d->buffer1, rn);
	d->buffer1 = d->buffer1_start;
	d->buffer = d->buffer_start;
}

void	random_minus(t_d *d)
{
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

int	main()
{
	t_d	d;
	int	index;
	int index1;

	index = 50000;
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
	index1 = 5;
	while (index1)
	{
		random_minus(&d);
		index1--;
	}
	buffer_to_file(&d);
	free_buffers(&d);
	return (0);
}