#include "pyramid.h"
#include "gfx/draw3d.h"
#include "gfx/gfxbuffer.h"

struct vertex PYRAMID_VERTICES[] = {
	{1, 1, 0},
	{1, -1, 0},
	{-1, 1, 0},
	{-1, -1, 0},
	{0, 0, 2},
};

struct face PYRAMID_FACES[] = {
	{{0, 1, 5}, COLOR(0,5,0)},
	{{1, 2, 5}, COLOR(0,0,5)},
	{{2, 3, 5}, COLOR(5,0,0)},
	{{3, 4, 5}, COLOR(5,5,0)},
	{{0, 1, 2}, COLOR(0,5,5)},
	{{1, 2, 3}, COLOR(0,5,5)},
};

struct model3d PYRAMID_MODEL = {
	sizeof(PYRAMID_FACES)/sizeof(*PYRAMID_FACES),
	sizeof(PYRAMID_VERTICES)/sizeof(*PYRAMID_VERTICES),
	PYRAMID_FACES,
	PYRAMID_VERTICES,
};