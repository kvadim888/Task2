#include "libdsp.h"

int32_t		dsp_db2gain(double gain)
{
	double scale = pow(10, gain / 20);
	return float_to_fix(scale);
}

//void dsp_ringproc(t_ringbuff * input, t_ringbuff * output, uint32_t(*func)(uint32_t val))
//{
//	for (int i = 0; i < input->len; i++)
//		output->buff[i] = func(input->buff[i]);
//}
