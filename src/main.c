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
#include "shape.h"
#include "process.h"
#include "draw.h"



extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH_FINAL;
extern int SCREEN_HEIGHT_FINAL;
extern int input_width;
extern int input_height;



extern mat_t* mPoints;
extern mat_t* mNormals;
extern mat_t* mTextures;
extern UT_array* cstack;
extern UT_icd matrix_icd;



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



extern pixel_t ** inputBuffer;
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

	int test_msaa_depth = 2;

	SCREEN_WIDTH_FINAL = 1280;
	SCREEN_HEIGHT_FINAL = 720;

	SCREEN_WIDTH = SCREEN_WIDTH_FINAL * (int)(log(test_msaa_depth)/log(2));
	SCREEN_HEIGHT = SCREEN_HEIGHT_FINAL * (int)(log(test_msaa_depth)/log(2));

	init_frameBuffers();

	matrix_icd.sz = sizeof(mat_t);
	matrix_icd.init = NULL;
	matrix_icd.copy = NULL;
	matrix_icd.dtor = matrix_dtor_icd;
	utarray_new(cstack, &matrix_icd);

	mat_t* cstackInit = matrix_create(4, 4);
	matrix_ident(cstackInit);
	utarray_push_back(cstack,cstackInit);

	mPoints = matrix_create(4,1024);
	mNormals = matrix_create(4,1024);
	mTextures = matrix_create(4,1024);

	printf("General structures initialized\n");

	shape_box(0,0,0,50,50,50);
	generate_normals();

	read_jpg_file("SpiderTex.jpg");

	set_frameBuffers_random();
	msaa(test_msaa_depth);

	write_buffer("test.png");

	printf("Freeing structures\n");

	free_frameBuffers();
	matrix_free(mPoints);
	matrix_free(mNormals);
	matrix_free(mTextures);
	utarray_free(cstack);

	return 0;
}