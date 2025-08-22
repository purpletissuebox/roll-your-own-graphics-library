#pragma once

#define ROTATE(a,b,c) ROTATE_RAD(a*M_PI/180.0, b*M_PI/180.0, c*M_PI/180.0)

#define ROTATE_RAD(a, b, c) \
{ \
	{cos(b)*cos(c), sin(a)*sin(b)*cos(c) - cos(a)*sin(c), cos(a)*sin(b)*cos(c) + sin(a)*sin(c)}, \
	{cos(b)*sin(c), sin(a)*sin(b)*sin(c) + cos(a)*cos(c), cos(a)*sin(b)*sin(c) - sin(a)*cos(c)}, \
	{   -sin(b),               sin(a)*cos(b),                        cos(a)*cos(b)            }, \
}

struct face
{
	int vertex_ids[3];
	unsigned char color;
};

struct vertex
{
	double position[4];
	double u;
	double v;
	double r;
	double g;
	double b;
};

struct model3d
{
	const struct face *faces;
	const struct vertex *vertices;
	int num_triangles;
};

struct instance
{
	const struct model3d *graphic;
	double transform[4][4];
};

void DrawObject(struct instance *, double(*)[4]);
int FrontFacing(struct vertex *);
struct vertex *ClipTriangle(struct vertex *);
void RenderTriangle(struct vertex *, unsigned char);
void ProjectVertices(struct vertex *);
void SortVertices(struct vertex *, struct vertex **, struct vertex **, struct vertex **);
