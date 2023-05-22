#include "corruptor.h"

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

void	free_buffers(t_d *d)
{
	free(d->buffer_start);
	free(d->buffer1_start);
}
