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
	double depth;
};

extern struct gfx_cell *gfx_string;
extern struct pixel *canvas;
extern int canvas_width, canvas_height;
extern double viewport_width, viewport_height, viewport_depth;

void CreateGfxBuffers(int, int, double, double);
void DestroyGfxBuffers();
void PlotPixel(int, int, unsigned char, double);
void RenderCanvas();
void ClearCanvas();
void WriteColorChar(unsigned char, char *);
