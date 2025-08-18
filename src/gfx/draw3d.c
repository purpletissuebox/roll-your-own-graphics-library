#include "draw3d.h"

#include "gfxbuffer.h"
#include "draw.h"
#include "math/matrix.h"

void ProjectPoint(double x, double y, double z, double *cx, double *cy)
{
	double vx = x * viewport_depth / z;
	double vy = y * viewport_depth / z;

	*cx = vx * canvas_width / viewport_width;
	*cy = vy * canvas_height / viewport_height;
}

void DrawObject(struct instance *thing)
{
	int i;
	struct face *tri = thing->graphic->faces;
	struct poly newtri;

	for (i = 0; i < thing->graphic->num_triangles; i++)
	{
		newtri = TransformFace(tri, thing->graphic->vertices, &thing->transform);
		DrawFace(&newtri);
		tri++;
	}
}

void DrawFace(struct poly *face)
{
	double P[6];
	int i;

	for (i = 0; i < 3; i++)
	{
		ProjectPoint(face->points[i].x, face->points[i].y, face->points[i].z, &P[i << 1], &P[(i << 1) | 1]);
	}

	DrawTriangle(P[0], P[1], P[2], P[3], P[4], P[5], face->color);
}

struct poly TransformFace(struct face *base, struct vertex *verts, struct transform *t)
{
	struct poly result;

	result.color = base->color;

	int i;
	for (i = 0; i < 3; i++)
	{
		result.points[i] = TransformVertex(verts + base->vertices[i], t);
	}

	return result;
}

struct vertex TransformVertex(struct vertex *base, struct transform *t)
{
	struct vertex result;
	double tmp[3];

	tmp[0] = base->x * t->scale[0];
	tmp[1] = base->y * t->scale[1];
	tmp[2] = base->z * t->scale[2];

	MatrixMultiply3x3(t->rotation, tmp, (double*)&result);

	result.x += t->position[0];
	result.y += t->position[1];
	result.z += t->position[2];

	return result;
}