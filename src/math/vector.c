#include "vector.h"

void VecCross(const double *vec1, const double *vec2, double *result)
{
	result[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
	result[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
	result[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];
}

double VecDot(const double *vec1, const double *vec2)
{
	return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2];
}

void VecAdd(const double *vec1, const double *vec2, double *result)
{
	*result++ = *vec1++ + *vec2++;
	*result++ = *vec1++ + *vec2++;
	*result = *vec1 + *vec2;
}

void VecSub(const double *vec1, const double *vec2, double *result)
{
	*result++ = *vec1++ - *vec2++;
	*result++ = *vec1++ - *vec2++;
	*result = *vec1 - *vec2;
}

void VecMul(const double *vec, const double scale, double *result)
{
	*result++ = *vec++ * scale;
	*result++ = *vec++ * scale;
	*result = *vec * scale;
}
