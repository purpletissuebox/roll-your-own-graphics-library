#include "gfx/os.h"
#include "gfx/gfxbuffer.h"
#include "gfx/draw.h"

#include "stdio.h"
#include "stdlib.h"

int main(void)
{
	void *stdio = GetStdIO();
	int x, y;
	QueryConsoleSize(stdio, &x, &y);
	CreateGfxBuffers(x, y, 1.6);
	DrawTriangle(35, 0, 50, 4, 20, 14, COLOR(0, 5, 0));
	RenderCanvas();
	puts((char*)gfx_string);
}

