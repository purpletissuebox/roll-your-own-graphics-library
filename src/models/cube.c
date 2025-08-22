#include "cube.h"
#include "gfx/draw3d.h"
#include "gfx/gfxbuffer.h"

struct vertex CUBE_VERTICES[] = {
	{{1, 1, 1, 1}},
	{{1, 1, -1, 1}},
	{{1, -1, 1, 1}},
	{{1, -1, -1, 1}},
	{{-1, 1, 1, 1}},
	{{-1, 1, -1, 1}},
	{{-1, -1, 1, 1}},
	{{-1, -1, -1, 1}},
};

struct face CUBE_FACES[] = {
	{{0, 1, 4}, COLOR(5,5,0)},
	{{1, 5, 4}, COLOR(5,5,0)},
	{{1, 3, 5}, COLOR(5,0,0)},
	{{3, 7, 5}, COLOR(5,0,0)},
	{{4, 5, 7}, COLOR(5,2,0)},
	{{4, 7, 6}, COLOR(5,2,0)},
	{{0, 4, 6}, COLOR(0,5,0)},
	{{0, 6, 2}, COLOR(0,5,0)},
	{{0, 2, 1}, COLOR(0,0,5)},
	{{1, 2, 3}, COLOR(0,0,5)},
	{{2, 6, 7}, COLOR(3,0,3)},
	{{2, 7, 3}, COLOR(3,0,3)},
};

struct model3d CUBE_MODEL = {
	CUBE_FACES,
	CUBE_VERTICES,
	sizeof(CUBE_FACES) / sizeof(*CUBE_FACES),
};