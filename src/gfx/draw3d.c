#include "draw3d.h"

#include "gfxbuffer.h"
#include "draw.h"
#include "math/matrix.h"
#include "math/vector.h"
#include "stdlib.h"
#include "math.h"

void DrawObject(struct instance *obj, double (*camera)[4])
{
	int i, j;
	const struct face *tri = obj->graphic->faces;
	const struct vertex *model_vertices = obj->graphic->vertices;

	for (i = 0; i < obj->graphic->num_triangles; i++)
	{
		struct vertex new_triangle[3];
		struct vertex *bonus_triangle;
		double tmp[4];
		for (j = 0; j < 3; j++)
		{
			new_triangle[j] = model_vertices[tri->vertex_ids[j]];
			MatrixMultiplyV4(obj->transform, new_triangle[j].position, tmp);
			MatrixMultiplyV4(camera, tmp, new_triangle[j].position);
		}
		if(FrontFacing(new_triangle))
		{
			bonus_triangle = ClipTriangle(new_triangle);
			if (bonus_triangle)
			{
				RenderTriangle(bonus_triangle, tri->color);
				free(bonus_triangle);
			}
			RenderTriangle(new_triangle, tri->color);
		}
		tri++;
	}
}

int FrontFacing(struct vertex *tri)
{
	double left_leg[3], right_leg[3], normal[3];

	VecSub(tri[1].position, tri[0].position, left_leg);
	VecSub(tri[2].position, tri[0].position, right_leg);
	VecCross(left_leg, right_leg, normal);
	return (VecDot(normal, tri[0].position) < 0.0);
}

struct vertex *ClipTriangle(struct vertex *tri)
{
	return NULL;
}

void RenderTriangle(struct vertex *tri, unsigned char color)
{
	struct vertex *top, *bottom, *middle;

	ProjectVertices(tri);
	SortVertices(tri, &top, &bottom, &middle);

	double slope_shape[3], slope_depth[3];
	slope_shape[0] = (bottom->position[0] - top->position[0]) / (bottom->position[1] - top->position[1]);
	slope_shape[1] = (middle->position[0] - top->position[0]) / (middle->position[1] - top->position[1]);
	slope_shape[2] = (bottom->position[0] - middle->position[0]) / (bottom->position[1] - middle->position[1]);
	slope_depth[0] = (bottom->position[2] - top->position[2]) / (bottom->position[1] - top->position[1]);
	slope_depth[1] = (middle->position[2] - top->position[2]) / (middle->position[1] - top->position[1]);
	slope_depth[2] = (bottom->position[2] - middle->position[2]) / (bottom->position[1] - middle->position[1]);

	double x3 = top->position[0] - slope_shape[0] * (top->position[1] - middle->position[1]);
	if (x3 < middle->position[0])
	{
		//long end on left
		PaintUpTriangle(top->position, middle->position[1], slope_shape[0], slope_shape[1], slope_depth[0], slope_depth[1], color);
		PaintDownTriangle(bottom->position, middle->position[1], slope_shape[0], slope_shape[2], slope_depth[0], slope_depth[2], color);
	}
	else
	{
		//long end on the right
		PaintUpTriangle(top->position, middle->position[1], slope_shape[1], slope_shape[0], slope_depth[1], slope_depth[0], color);
		PaintDownTriangle(bottom->position, middle->position[1], slope_shape[2], slope_shape[0], slope_depth[2], slope_depth[0], color);
	}
}

void ProjectVertices(struct vertex *tri)
{
	double z;
	int i;
	for (i = 0; i < 3; i++)
	{
		z = tri->position[2];
		tri->position[0] *= (viewport_depth / z) * (canvas_width / viewport_width) * -1.0;
		tri->position[1] *= (viewport_depth / z) * (canvas_height / viewport_height);

		tri->position[0] = round(tri->position[0]);
		tri->position[1] = round(tri->position[1]);

		tri->position[2] = 1 / z;
		tri++;
	}
}

void SortVertices(struct vertex *tri, struct vertex **top, struct vertex **bottom, struct vertex **middle)
{
	*top = tri;
	*middle = tri + 1;
	*bottom = tri + 2;
	struct vertex *tmp;

	if ((*top)->position[1] < (*middle)->position[1])
	{
		tmp = *top;
		*top = *middle;
		*middle = tmp;
	}
	if ((*top)->position[1] < (*bottom)->position[1])
	{
		tmp = *top;
		*top = *bottom;
		*bottom = tmp;
	}
	if ((*middle)->position[1] < (*bottom)->position[1])
	{
		tmp = *middle;
		*middle = *bottom;
		*bottom = tmp;
	}
}
