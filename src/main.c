#include "gfx/os.h"

int main(void)
{
	void *stdio = GetStdIO();
	int x, y;
	QueryConsoleSize(stdio, &x, &y);
}

