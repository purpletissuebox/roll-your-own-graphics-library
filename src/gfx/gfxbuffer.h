#pragma once

#define COLOR(R,G,B) (16+(R)*36+(G)*6+(B))

struct gfx_cell
{
	char header[7]; /* ESC [ 3 8 ; 5 ; */
	char color_code[3];
	char letter_M;
	char displayed_character;
};

struct pixel
{
	unsigned char color;
};

struct gfx_cell *gfx_string;
struct pixel *canvas;
int canvas_width, canvas_height;
float viewport_depth;

void CreateGfxBuffers(int, int, double);
void DestroyGfxBuffers();
void PlotPixel(double, double, unsigned char);
void RenderCanvas();
void WriteColorChar(unsigned char, char *);
