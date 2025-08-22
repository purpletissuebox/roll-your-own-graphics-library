#include "matrix.h"

#include "math.h"

void FillRotationMatrix(double a, double b, double c, double(*matrix)[4])
{
	double *p = (double*)matrix;
	*p++ = cos(b) * cos(c);
	*p++ = sin(a) * sin(b) * cos(c) - cos(a) * sin(c);
	*p++ = cos(a) * sin(b) * cos(c) + sin(a) * sin(c);
	*p++ = 0.0;
	*p++ = cos(b) * sin(c);
	*p++ = sin(a) * sin(b) * sin(c) + cos(a) * cos(c);
	*p++ = cos(a) * sin(b) * sin(c) - sin(a) * cos(c);
	*p++ = 0.0;
	*p++ = sin(b) * -1.0;
	*p++ = sin(a) * cos(b);
	*p++ = cos(a) * cos(b);
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 1.0;
}

void FillScaleMatrix(double x, double y, double z, double(*matrix)[4])
{
	double *p = (double*)matrix;
	*p++ = x;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = y;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = z;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 1.0;
}

void FillTranslationMatrix(double x, double y, double z, double(*matrix)[4])
{
	double *p = (double*)matrix;
	*p++ = 1.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = x;
	*p++ = 0.0;
	*p++ = 1.0;
	*p++ = 0.0;
	*p++ = y;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 1.0;
	*p++ = z;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 1.0;
}

void FillProjectionMatrix(double vx, double vy, double cx, double cy, double d, double(*matrix)[4])
{
	double *p = (double*)matrix;
	*p++ = d * cx / vx;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = d * cy / vy;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 0.0;
	*p++ = 1.0;
	*p++ = 0.0;
}

void MatrixMultiplyM4(double(*mat1)[4], double(*mat2)[4], double(*result)[4])
{
	int i, j, k;
	double acc;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			acc = 0.0;
			for (k = 0; k < 4; k++)
			{
				acc += mat1[i][k] * mat2[k][j];
			}
			result[i][j] = acc;
		}
	}
}

void MatrixMultiplyV4(double(*matrix)[4], double *vector, double *result)
{
	int i, j;
	double acc;

	for (i = 0; i < 4; i++)
	{
		acc = 0.0;
		for (j = 0; j < 4; j++)
		{
			acc += vector[j] * matrix[i][j];
		}
		result[i] = acc;
	}
}

void FillTransformMatrix(double x, double y, double z, double a, double b, double c, double s, double(*result)[4])
{
	double translation[4][4];
	double rotation[4][4];
	double scale[4][4];
	double tmp[4][4];

	FillTranslationMatrix(x, y, z, translation);
	FillRotationMatrix(a, b, c, rotation);
	FillScaleMatrix(s, s, s, scale);
	MatrixMultiplyM4(rotation, scale, tmp);
	MatrixMultiplyM4(translation, tmp, result);
}
