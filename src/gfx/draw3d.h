#pragma once

#define ROTATE(a, b, c) \
{ \
	{cos(b)*cos(c), sin(a)*sin(b)*cos(c) - cos(a)*sin(c), cos(a)*sin(b)*cos(c) + sin(a)*sin(c)}, \
	{cos(b)*sin(c), sin(a)*sin(b)*sin(c) + cos(a)*cos(c), cos(a)*sin(b)*sin(c) - sin(a)*cos(c)}, \
	{   -sin(b),               sin(a)*cos(b),                        cos(a)*cos(b)            }, \
}

struct face
{
	int vertices[3];
	unsigned char color;
};

struct vertex
{
	double x;
	double y;
	double z;
};

struct model3d
{
	int num_triangles, num_vertices;
	struct face *faces;
	struct vertex *vertices;
};

struct transform
{
	double position[3];
	double rotation[3][3];
	double scale[3];
};

struct instance
{
	struct model3d *graphic;
	struct transform transform;
};

struct poly
{
	struct vertex points[3];
	unsigned char color;
};

void ProjectPoint(double, double, double, double *, double *);
void DrawObject(struct instance *);
void DrawFace(struct poly *);
struct poly TransformFace(struct face *, struct vertex *, struct transform *);
struct vertex TransformVertex(struct vertex *, struct transform *);
