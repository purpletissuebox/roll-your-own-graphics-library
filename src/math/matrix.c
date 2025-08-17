#include "matrix.h"

#include "math.h"

void FillRotationMatrix(double a, double b, double c, double(*matrix)[3])
{
	matrix[0][0] = cos(b) * cos(c);
	matrix[0][1] = sin(a) * sin(b) * cos(c) - cos(a) * sin(c);
	matrix[0][2] = cos(a) * sin(b) * cos(c) + sin(a) * sin(c);
	matrix[1][0] = cos(b) * sin(c);
	matrix[1][1] = sin(a) * sin(b) * sin(c) + cos(a) * cos(c);
	matrix[1][2] = cos(a) * sin(b) * sin(c) - sin(a) * cos(c);
	matrix[2][0] = sin(b) * -1.0;
	matrix[2][1] = sin(a) * cos(b);
	matrix[2][3] = cos(a) * cos(b);
}

void MatrixMultiply3x3(double(*matrix)[3], double *vector, double *result)
{
	int i, j;
	double acc;

	for (i = 0; i < 3; i++)
	{
		acc = 0.0;
		for (j = 0; j < 3; j++)
		{
			acc += vector[j] * matrix[i][j];
		}
		result[i] = acc;
	}
}
