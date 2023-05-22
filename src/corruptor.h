#ifndef CORRUPTOR_H
# define CORRUPTOR_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>

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

void	file_to_buffer(t_d *d);
void	buffer_to_file(t_d *d);
void	buffer1_to_file(t_d *d);
void	random_bit(t_d *d);
void	random_bit_minus(t_d *d);
void	buffer_shuffle(t_d *d);
void	free_buffers(t_d *d);

#endif