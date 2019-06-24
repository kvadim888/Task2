#ifndef LIBDSP_H
#define LIBDSP_H

#include "libfix.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/*
**	Convert gain entered in dB to scale coeficient.
**	The gain can be negative (in dB) only.
*/

int32_t		dsp_db2gain(double gain);

//void		dsp_ringproc(t_ringbuff *input, t_ringbuff *output,
//						uint32_t (*func)(uint32_t val));



#endif // LIBDSP_H
