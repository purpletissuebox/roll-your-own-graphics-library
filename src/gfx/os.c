#include "os.h"

#include "stdio.h"
#include "stdlib.h"

void *GetStdIO()
{
	int *fds = malloc(2 * sizeof(*fds));
	fds[0] = 0;
	fds[1] = 1;
	return fds;
}

void QueryConsoleSize(void *std_io, int *x, int *y)
{
#ifdef LINUX
	struct winsize current_size;
	ioctl(((int*)std_io)[1], TIOCGWINSZ, &current_size);

	*x = current_size.ws_col;
	*y = current_size.ws_row;

	printf("the window is now %d by %d.", *x, *y);
#endif
}
