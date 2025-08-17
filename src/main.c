#include "gfx/os.h"
#include "gfx/gfxbuffer.h"
#include "gfx/draw3d.h"
#include "models/pyramid.h"

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int main(void)
{
	void *stdio = GetStdIO();
	int x, y;
	QueryConsoleSize(stdio, &x, &y);
	CreateGfxBuffers(x, y, 1.6, 0.5);

	struct instance pyramid = {
		&PYRAMID_MODEL,
		{
			{ 0.0, -1.0, 4.0 },
			ROTATE(0,0,0),
			{1.0,1.0,1.0},
		},
	};

	DrawObject(&pyramid);

	RenderCanvas();
	puts((char*)gfx_string);
}

