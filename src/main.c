#include "gfx/os.h"
#include "gfx/gfxbuffer.h"
#include "gfx/draw3d.h"
#include "math/matrix.h"
#include "models/pyramid.h"
#include "models/cube.h"

#include "stdio.h"
#include "math.h"

#ifdef LINUX
#include "time.h"
const struct timespec waittime = { 0, 20000000 };
#endif

int main(void)
{
	void *stdio = GetStdIO();
	int x, y;
	QueryConsoleSize(stdio, &x, &y);
	CreateGfxBuffers(x, y, 1.6, 0.5);

	double camera[4][4];
	FillTransformMatrix(0, 0, 0, 0, 0, 0, 1.0, camera);

	struct instance pyramid, cube;
	cube.graphic = &CUBE_MODEL;
	pyramid.graphic = &PYRAMID_MODEL;

	double angle[3] = { 0.0, 0.0, 0.0 };

	do
	{
		angle[0] += 0.05;
		angle[1] += M_PI / 100;
		angle[2] += 0.01371420;
		FillTransformMatrix(0, 0, 10, angle[0], angle[1], angle[2], 1.0, pyramid.transform);
		FillTransformMatrix(2, 0, 15, angle[1], angle[0], angle[2], 1.0, cube.transform);
		DrawObject(&pyramid, camera);
		DrawObject(&cube, camera);
		RenderCanvas();
		puts((char *)gfx_string);
		ClearCanvas();
		clock_nanosleep(CLOCK_REALTIME, 0, &waittime, NULL);
	} while (1);
}

