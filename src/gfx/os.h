#pragma once

#ifdef WIN32
	#define WINDOWS
	#include <Windows.h>

#elif __linux__
	#define LINUX
	#include <sys/ioctl.h>
	#include <termios.h>

#endif

void *GetStdIO();
void QueryConsoleSize(void *, int *, int *);
