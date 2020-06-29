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

#include "obj.tab.h"
#include "mtl.tab.h"



extern FILE* mtl_yyin;
extern FILE* obj_yyin;



extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int input_width;
extern int input_height;



extern int MSAA_DEPTH;
extern int MSAA_DEPTH_LOG;
extern int MSAA_ENABLED;



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

	SCREEN_WIDTH = 640;
	SCREEN_HEIGHT = 480;
	MSAA_ENABLED = 0;

	if(MSAA_ENABLED){
		MSAA_DEPTH = 8;
		MSAA_DEPTH_LOG = (int)(log(MSAA_DEPTH)/log(2));

		SCREEN_WIDTH *= MSAA_DEPTH_LOG;
		SCREEN_HEIGHT *= MSAA_DEPTH_LOG;
	}

	init_frameBuffer();
	matrices_init();

	printf("General structures initialized\n");

	shape_box(0,0,0,50,50,50);
	generate_normals();

	//read_jpg_file("SpiderTex.jpg");

	set_frameBuffer_random();
	if(MSAA_ENABLED)msaa();

	printf("Drawing picture...\n");
	write_png_file("test.png");

	printf("Freeing structures\n");

	free_frameBuffer();
	matrices_free();

	//mtl_yyin = fopen("../wavefront/spider.mtl","r");

	//mtl_yyparse();


	return 0;
}