#include <stdio.h>
#include <stdlib.h>
#include "libwav.h"
#include "libfix.h"
#include "libdsp.h"

int main(int ac, char **av)
{
	size_t		len = 0;
	int16_t		*buffer_in;
	int16_t		*buffer_out;

	if (ac != 4)
	{
		printf("Not enought input arguments\n");
		exit(1);
	}
	t_wavfile *input = wav_rdopen(av[1]);
	t_wavfile *output = wav_wropen(av[2], &input->header);
	int32_t gain = dsp_db2gain(atof(av[3]));

	printf("\n gain = %.8f\n Control: 20log(%.8f)=%.8f\n",
			fix_to_float(gain), fix_to_float(gain), atof(av[3]));

	buffer_in = input->buffer.data;
	buffer_out = output->buffer.data;

	while ((len = wav_read(input)) > 0)
	{
		wav_buffclear(output);
		for (int i = 0; i < input->buffer.datalen; i++)
			buffer_out[i] = (int16_t)fix_mul(buffer_in[i], gain);
		wav_write(output);
		wav_buffclear(input);
	}

	wav_close(&input);
	wav_close(&output);
	return 0;
}
