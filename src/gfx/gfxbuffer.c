#include "gfxbuffer.h"

#include "stdlib.h"
#include "string.h"
#include "math.h"

struct gfx_cell *gfx_string;
struct pixel *canvas;
int canvas_width, canvas_height;
double viewport_width, viewport_height, viewport_depth;

void CreateGfxBuffers(int x, int y, double fov, double character_ratio)
{
	gfx_string = malloc(x*y*sizeof(*gfx_string) + 4);
	canvas = malloc(x*y*sizeof(*canvas));
	ClearCanvas();

	const char terminator[] = "\x1B[H";
	const char one_pixel[] = { '\x1B','[','4','8',';','5',';','0','0','0','m',' ' };

	int i, j;
	struct gfx_cell *p = gfx_string;

	for (i = 0; i < y; i++)
	{
		for (j = 0; j < x; j++)
		{
			memcpy(p++, one_pixel, sizeof(one_pixel));
			canvas[j + y * i].depth = 0.0;
		}
	}
	memcpy(p, terminator, sizeof(terminator));

	canvas_width = x;
	canvas_height = y;
	viewport_depth = 1.0;
	viewport_width = 2.0 * viewport_depth * tan(fov / 2.0) * character_ratio;
	viewport_height = viewport_width * canvas_height / canvas_width / character_ratio;
}

void DestroyGfxBuffers()
{
	free(gfx_string);
	free(canvas);
}

void PlotPixel(int x, int y, unsigned char color, double depth)
{
	int screen_x = canvas_width/2 + x;
	int screen_y = canvas_height/2 - y;

	struct pixel *mypx = canvas + screen_y*canvas_width + screen_x;

	if (depth > mypx->depth)
	{
		mypx->color = color;
		mypx->depth = depth;
	}
}

void RenderCanvas()
{
	int i, j;
	struct gfx_cell *p = gfx_string;
	struct pixel *px = canvas;

	for (i = 0; i < canvas_height; i++)
	{
		for (j = 0; j < canvas_width; j++)
		{
			WriteColorChar(px->color, p->color_code);
			p++;
			px++;
		}
	}
}

void ClearCanvas()
{
	struct pixel *p = canvas;
	int i, j;

	for (i = 0; i < canvas_height; i++)
	{
		for (j = 0; j < canvas_width; j++)
		{
			p->color = 0;
			p->depth = 0;
			p++;
		}
	}
}

void WriteColorChar(unsigned char color, char *text)
{
	const char LUT[] = "000_001_002_003_004_005_006_007_008_009_010_011_012_013_014_015_016_017_018_019_020_021_022_023_024_025_026_027_028_029_030_031_032_033_034_035_036_037_038_039_040_041_042_043_044_045_046_047_048_049_050_051_052_053_054_055_056_057_058_059_060_061_062_063_064_065_066_067_068_069_070_071_072_073_074_075_076_077_078_079_080_081_082_083_084_085_086_087_088_089_090_091_092_093_094_095_096_097_098_099_100_101_102_103_104_105_106_107_108_109_110_111_112_113_114_115_116_117_118_119_120_121_122_123_124_125_126_127_128_129_130_131_132_133_134_135_136_137_138_139_140_141_142_143_144_145_146_147_148_149_150_151_152_153_154_155_156_157_158_159_160_161_162_163_164_165_166_167_168_169_170_171_172_173_174_175_176_177_178_179_180_181_182_183_184_185_186_187_188_189_190_191_192_193_194_195_196_197_198_199_200_201_202_203_204_205_206_207_208_209_210_211_212_213_214_215_216_217_218_219_220_221_222_223_224_225_226_227_228_229_230_231";
	const char *p = LUT + (color << 2);

	*text++ = *p++;
	*text++ = *p++;
	*text++ = *p++;
}