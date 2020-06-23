#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <math.h>
#include <png.h>

#include "utarray.h"
#include "uthash.h"

#include "vertex.h"
#include "material.h"
#include "texture.h"
#include "matrix.h"
#include "geometry.h"
#include "fragment.h"

#include "parse.h"
#include "light.h"
#include "shade.h"
#include "process.h"
#include "draw.h"



extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH_FINAL;
extern int SCREEN_HEIGHT_FINAL;



extern mat_t* mPoints;
extern mat_t* mNormals;
extern mat_t* mTextures;



extern mtl_t* gMaterials;
extern tex_t* gTextures;
extern UT_array* pQueue;
extern UT_array* fQueue;

extern UT_icd polygon_icd;
extern UT_icd fragment_icd;



extern png_structp png_ptr;
extern png_infop info_ptr;

extern png_byte color_type;
extern png_byte bit_depth;

extern png_bytep* row_pointers;



extern pixel_t ** frameBuffer;
extern pixel_t ** frameBuffer_final;

void abort_(const char* s, ...){
	va_list args;
	va_start(args, s);
	vfprintf(stderr, s, args);
	fprintf(stderr,"\n");
	va_end(args);
	abort();
}

int main(){

	gMaterials = NULL;
	gTextures = NULL;
	pQueue = NULL;
	fQueue = NULL;

	color_type = PNG_COLOR_TYPE_RGBA;
	bit_depth = 8;

	int test_mxaa_depth = 8;

	SCREEN_WIDTH_FINAL = 640;
	SCREEN_HEIGHT_FINAL = 480;

	SCREEN_WIDTH = SCREEN_WIDTH_FINAL * (int)(log(test_mxaa_depth)/log(2));
	SCREEN_HEIGHT = SCREEN_HEIGHT_FINAL * (int)(log(test_mxaa_depth)/log(2));

	init_buffers();

	printf("Buffer initialized\n");

	set_buffers_random();
	mxaa(test_mxaa_depth);

	write_buffer("test.png");

	printf("Testing...\n");

	free_buffers();

	return 0;
}