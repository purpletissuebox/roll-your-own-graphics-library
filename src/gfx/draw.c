#include "draw.h"
#include "gfxbuffer.h"

void DrawTriangle(double x0, double y0, double x1, double y1, double x2, double y2, unsigned char color)
{
	OrderPoints(&x0, &y0, &x1, &y1, &x2, &y2);

	double slope02 = (x2 - x0) / (y2 - y0);
	double slope01 = (x1 - x0) / (y1 - y0);
	double slope12 = (x2 - x1) / (y2 - y1);

	double x3 = x0 + slope02*(y1-y0);

	if (x1 < x3)
	{
		DrawFlatTriangle(x0, y0, y1, slope01, slope02, -1, color);
		DrawFlatTriangle(x2, y2, y1, slope12, slope02, +1, color);
	}
	else
	{
		DrawFlatTriangle(x0, y0, y1, slope02, slope01, -1, color);
		DrawFlatTriangle(x2, y2, y1, slope02, slope12, +1, color);
	}

	int i;
	if (x1 < x3)
	{
		for (i = x1; i <= (int)x3; i++)
		{
			PlotPixel(i, y1, color);
		}
	}
	else
	{
		for (i = x3; i <= (int)x1; i++)
		{
			PlotPixel(i, y1, color);
		}
	}
}

void DrawFlatTriangle(double tipX, double tipY, double flatY, double slope_L, double slope_R, int direction, unsigned char color)
{
	double acc_L = tipX, acc_R = tipX;

	int i, j;

	for (i = tipY; i != (int)flatY; i+=direction)
	{
		for (j = acc_L; j <= acc_R; j++)
		{
			PlotPixel(j, i, color);
		}
		acc_L += slope_L*direction;
		acc_R += slope_R*direction;
	}
}

void OrderPoints(double *x0, double *y0, double *x1, double *y1, double *x2, double *y2)
{
	double tmp;

	if (*y1 > *y0)
	{
		tmp = *x0; *x0 = *x1; *x1 = tmp;
		tmp = *y0; *y0 = *y1; *y1 = tmp;
	}
	if (*y2 > *y0)
	{
		tmp = *x0; *x0 = *x2; *x2 = tmp;
		tmp = *y0; *y0 = *y2; *y2 = tmp;
	}
	if (*y2 > *y1)
	{
		tmp = *x1; *x1 = *x2; *x2 = tmp;
		tmp = *y1; *y1 = *y2; *y2 = tmp;
	}
}
