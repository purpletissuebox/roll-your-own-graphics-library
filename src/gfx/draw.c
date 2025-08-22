#include "draw.h"
#include "gfxbuffer.h"
#include "math.h"

void PaintUpTriangle(double *tip_pos, double bottom, double left_slope, double right_slope, double left_dslope, double right_dslope, unsigned char color)
{
	double acc_L = tip_pos[0];
	double acc_R = tip_pos[0];
	double acc_dL = tip_pos[2];
	double acc_dR = tip_pos[2];
	double depth_slope, d;

	int i, j;
	for (i = lround(tip_pos[1]); i >= lround(bottom); i--)
	{
		depth_slope = (acc_dR - acc_dL) / (acc_R - acc_L);
		for (j = lround(acc_L); j <= lround(acc_R); j++)
		{
			d = acc_dL;
			PlotPixel(j, i, color, d);
			d += depth_slope;
		}
		acc_L -= left_slope;
		acc_R -= right_slope;
		acc_dL -= left_dslope;
		acc_dR -= right_dslope;
	}
}

void PaintDownTriangle(double *tip_pos, double top, double left_slope, double right_slope, double left_dslope, double right_dslope, unsigned char color)
{
	double acc_L = tip_pos[0];
	double acc_R = tip_pos[0];
	double acc_dL = tip_pos[2];
	double acc_dR = tip_pos[2];
	double depth_slope, d;

	int i, j;
	for (i = lround(tip_pos[1]); i <= lround(top); i++)
	{
		depth_slope = (acc_dR - acc_dL) / (acc_R - acc_L);
		for (j = lround(acc_L); j <= lround(acc_R); j++)
		{
			d = acc_dL;
			PlotPixel(j, i, color, d);
			d += depth_slope;
		}
		acc_L += left_slope;
		acc_R += right_slope;
		acc_dL += left_dslope;
		acc_dR += right_dslope;
	}
}
