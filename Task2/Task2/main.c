#include <stdio.h>
#include <stdlib.h>
#include "libwav.h"
#include "libfix.h"
#include <math.h>

typedef	union
{
	uint8_t		bytes[2];
	uint16_t	word;
}		t_buffer;

int32_t		fix_scale(double gain)
{
	double scale = pow(10, gain / 20);
	return float_to_fix(scale);
}



int main(int ac, char **av)
{
	size_t		len = 0;
	t_buffer	buff;

	if (ac != 4)
	{
		printf("Not enought input arguments\n");
		exit(1);
	}
	t_wavfile *input = wav_rdopen(av[1]);
	t_wavfile *output = wav_wropen(av[2], &input->header);
	double	gain = atof(av[3]);
//	double	gain = 0;
	int32_t scale = fix_scale(gain);

	printf("\nscale = %.8f\nControl: 20log(%.8f)=%.8f\n", fix_to_float(scale), fix_to_float(scale), gain);

	while ((len = wav_read(input)) > 0)
	{
		wav_buffclear(output);
		for (int i = 0; i < len; i += input->header.bits_per_sample/8)
		{
			buff.bytes[0] = input->data[i];
			buff.bytes[1] = input->data[i + 1];
			buff.word = (int16_t)fix_mul(buff.word, scale);
			output->data[i] = buff.bytes[0];
			output->data[i + 1] = buff.bytes[1];
		}
		wav_write(output);
		wav_buffclear(input);
	}

	wav_info(av[2], &output->header);
	wav_close(&input);
	wav_close(&output);
	return 0;
}
