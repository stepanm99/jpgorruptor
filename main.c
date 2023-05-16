#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct s_d {
	char	filename_i[50];
	char	filename_o[50];
	FILE	*fileptr;
	unsigned char	*buffer;
	unsigned char	*buffer1;
	unsigned char	*buffer_start;
	unsigned char	*buffer1_start;
	long	flen;
	long	i;
	long	rn;				//random number
	long	rv;				//random value
	long	s1;
	long	s2;
}	t_d;

void	dinit(t_d *d)
{
	d->i = 0;
//	d->s1 = 500000;
//	d->s2 = d->s1 + 5000;
//	d->rn = 5000;
}

void	file_to_buffer(t_d *d)
{
	printf("file to buffer\n");
	d->fileptr = fopen("input.png", "rb");
	fseek(d->fileptr, 0, SEEK_END);
	d->flen = ftell(d->fileptr);
	rewind(d->fileptr);
	d->buffer = (unsigned char *)malloc((d->flen + 1) * sizeof(unsigned char));
	d->buffer1 = (unsigned char *)malloc((d->flen + 1) * sizeof(unsigned char));
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
	memmove(d->buffer1, d->buffer, d->flen);
}

void	buffer_to_file(t_d *d)
{
	printf("buffer to file\n");
	d->i = d->flen;
	d->buffer = d->buffer_start;
	d->fileptr = fopen("output.png", "wb");
	while (d->i != 0)
	{
		fprintf(d->fileptr, "%c", *d->buffer);
		d->buffer++;
		d->i--;
	}
	fclose(d->fileptr);
}

void	buffer1_to_file(t_d *d)
{
	printf("buffer1 to file\n");
	d->i = d->flen;
	d->buffer1 = d->buffer1_start;
	d->fileptr = fopen("output1.png", "wb");
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

void	free_buffers(t_d *d)
{
	free(d->buffer_start);
	free(d->buffer1_start);
}

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

void	random_minus(t_d *d)
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

int	main()
{
	t_d	d;
	int	index;
	int index1;

	printf("How many random bytes: ");;
	scanf("%i", &index);
	printf("\nHow many shuffles: ");
	scanf("%i", &index1);
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

/*
old function
void	buffer_shuffle(t_d *d)
{
	printf("buffer shuffle\n");
	long	rn;
	long	s1;
	long	s2;

	d->buffer1 = d->buffer1_start;
	d->buffer = d->buffer_start;
	rn = (rand() % ((d->flen)) / 4);
	s1 = (d->flen - (rand() % (d->flen / 2)));
	s2 = (d->flen - (rand() % (d->flen / 2)));
	printf("s1: %lu\ns2: %lu\nrn: %lu\n\n", s1, s2, rn);
	if ((s1 + rn) > d->flen || (s2 + rn) > d->flen)
	{
		printf("buffer overflow!\n");
		return ;
	}
	d->buffer += s1;
	d->buffer1 += d->flen - s2;
	memmove(d->buffer, d->buffer1, rn);
	memmove(d->buffer1, d->buffer, d->flen);
}*/