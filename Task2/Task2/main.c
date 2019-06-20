#include <stdio.h>
#include <stdlib.h>
#include "libwav.h"
#include "libfix.h"
#include <math.h>

typedef	union
{
	uint8_t		bytes[100];
	uint16_t	words[50];
}		t_buffer;

int32_t		fix_scale(double gain)
{
	double scale = pow(10, gain / 20);
	return float_to_fix(scale);
}

int main(int ac, char **av)
{
	uint8_t header[44];
	t_buffer buffer;
	size_t len = 0;
	FILE *input;
	FILE *output;

	if (fopen_s(&input, av[1], "rb") || fopen_s(&output, av[2], "wb"))
		exit(1);

	int32_t scale = fix_scale(atof(av[3]));

	if (fread(header, sizeof(uint8_t), 44, input) < 44)
	{
		printf("%s: Invalid file\n", av[1]);
		exit(1);
	}

	if (fwrite(header, sizeof(uint8_t), 44, output) < 44)
	{
		printf("%s: Unnable to write a file\n", av[2]);
		exit(1);
	}
	while ((len = fread(buffer.bytes, sizeof(uint8_t), 100, input)) > 0)
	{
		for (size_t i = 0; i < len / 2; i++)
			fix_mul(buffer.words[i], scale);
		if (fwrite(buffer.bytes, sizeof(uint8_t), len, output) < len)
		{
			printf("%s: Unnable to write a file\n", av[2]);
			exit(1);
		}
		printf("len = %d |%s|\n", len, buffer.bytes);
		memset(buffer.bytes, 0, 100);
	}
	printf("complete\n");
	fclose(input);
	fclose(output);
	return 0;
}