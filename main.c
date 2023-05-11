#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int	main()
{
	FILE	*fileptr;
	char	*buffer;
	char	*buffer_start;
	long	flen;
	long	i;
	long	rn;
	char	rv;

	i = 0;
	srand(time(0));
	fileptr = fopen("input.jpg", "rb");
	fseek(fileptr, 0, SEEK_END);
	flen = ftell(fileptr);
	rewind(fileptr);
	buffer = (char *)malloc((flen + 1) * sizeof(char));
	if (!buffer)
	{
		printf("Allocation failed :(\n");
		return (0);
	}
	buffer_start = buffer;
	while (i < flen)
	{
		fread(buffer, 1, 1, fileptr);
		buffer++;
		i++;
	}
	fclose(fileptr);
	buffer = buffer_start;

	rn = rand() % flen;
	rv = rand() % 250;
	fopen("output.jpg", "wb");
	while (i != 0)
	{
		if (i == rn)
		{
			fprintf(fileptr, "%c", rv);
			buffer++;
			i--;
		}
		fprintf(fileptr, "%c", *buffer);
		buffer++;
		i--;
	}
	fclose(fileptr);
	free(buffer_start);
	return (0);
}