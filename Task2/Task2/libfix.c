#include "libfix.h"
#include <stdint.h>
#include <stdio.h>

int32_t	float_to_fix(double num)
{
	int32_t	fixed;

	if (num < -1)
		return INT32_MIN;
	if (num >= 1)
		return INT32_MAX;
	return num * SCALE;
}

double	fix_to_float(int32_t num)
{
	return (num / SCALE);
}

int32_t fix_add(int32_t a, int32_t b)
{
	uint32_t tmp_a = a;
	uint32_t tmp_b = b;
	uint32_t sum = tmp_a + tmp_b;

	if (!((tmp_a ^ tmp_b) & INT32_MIN) && ((tmp_a ^ sum) & INT32_MIN))
	{
		printf("sum overflow \n");
		return (a >= 0) ? INT32_MAX : INT32_MIN;
	}
	return (int32_t)sum;
}

int32_t fix_sub(int32_t a, int32_t b)
{
	uint32_t tmp_a = a;
	uint32_t tmp_b = b;
	uint32_t sub = tmp_a - tmp_b;

	if (((tmp_a ^ tmp_b) & INT32_MIN) && ((tmp_a ^ sub) & INT32_MIN))
	{
		printf("sub overflow \n");
		return (a >= 0) ? INT32_MAX : INT32_MIN;
	}
	return (int32_t)sub;
}

int32_t fix_mul(int32_t a, int32_t b)
{
	int64_t tmp_a = a;
	int64_t tmp_b = b;

	int64_t	mul = (tmp_a * tmp_b) >> 31;

	return (int32_t)mul;
}

// int32_t fix_mac(int32_t acc, int32_t a, int32_t b)
// {
// 	return fix_add(acc, fix_mul(a, b));
// }
// 
// int32_t fix_msub(int32_t acc, int32_t a, int32_t b)
// {
// 	return fix_sub(acc, fix_mul(a, b));
// }

int32_t fix_mac(int32_t acc, int32_t a, int32_t b)
{
	long_fix	mul;
	int64_t		tmp_a = a;
	int64_t		tmp_b = b;

	mul.num = (tmp_a * tmp_b) << 1;
	return fix_add(acc, mul.range[1]);
}

int32_t fix_msub(int32_t acc, int32_t a, int32_t b)
{
	long_fix	mul;
	int64_t		tmp_a = a;
	int64_t		tmp_b = b;

	mul.num = (tmp_a * tmp_b) << 1;
	return fix_sub(acc, mul.range[1]);
}

int32_t	fix_leftshift(int32_t num, int8_t shift)
{
	uint32_t res = num << shift;
	if ((res ^ num) & INT32_MIN)
		return (num > 0) ? INT32_MAX : INT32_MIN;
	return res;
}

int32_t	fix_rightshift(int32_t num, int8_t shift)
{
	return (num >> shift);
}

