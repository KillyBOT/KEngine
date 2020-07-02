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
extern int CANVAS_WIDTH;
extern int CANVAS_HEIGHT;
extern int CANVAS_DEPTH;
extern int CAMERA_X;
extern int CAMERA_Y;
extern int CAMERA_Z;



extern int MSAA_DEPTH;
extern int MSAA_DEPTH_LOG;
extern int MSAA_ENABLED;



extern mat_t* mPoints;
extern mat_t* mNormals;
extern mat_t* mTextures;
extern mat_t* mPointsToAdd;
extern mat_t* mNormalsToAdd;
extern mat_t* mTexturesToAdd;
extern UT_array* cstack;
extern UT_icd matrix_icd;



extern mtl_t* gMaterials;
extern tex_t* gTextures;
extern UT_array* pQueue;
extern UT_array*** fArray;



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

int main(int argc, char **argv){

	if(argc < 2)
		abort_("Error! Must specify file!");

	printf("Initializing general structures...\n");

	char finalName[512];
	strcpy(finalName,"../wavefront/");
	strcat(finalName,argv[1]);
	obj_yyin = fopen(finalName,"r");

	gMaterials = NULL;
	gMaterialsID = NULL;
	gTextures = NULL;
	pQueue = NULL;
	fArray = NULL;

	toAddID = 0;

	SCREEN_WIDTH = 640;
	SCREEN_HEIGHT = 480;

	CANVAS_WIDTH = SCREEN_WIDTH;
	CANVAS_HEIGHT = SCREEN_HEIGHT;
	CANVAS_DEPTH = 1;

	CAMERA_X = 0;
	CAMERA_Y = 0;
	CAMERA_Z = 0;

	MSAA_ENABLED = 0;

	if(MSAA_ENABLED){
		MSAA_DEPTH = 8;
		MSAA_DEPTH_LOG = (int)(log(MSAA_DEPTH)/log(2));

		SCREEN_WIDTH *= MSAA_DEPTH_LOG;
		SCREEN_HEIGHT *= MSAA_DEPTH_LOG;
	}

	init_frameBuffer();
	matrices_init();
	polygons_init();
	frag_array_init();

	material_add("Default");



	printf("General structures initialized!\n\n");



	printf("Executing main loop...\n");



	obj_yyparse();
	if(mNormals->lastcol == -1) generate_normals();

	// cstack_translate(50,50,50);
	// cstack_scale(3,3,3);
	// cstack_rotate(ROTATE_Z,M_PI/3);

	shade_vertex_all();
	shade_geometry();

	//polygon_print_all();

	rasterize_all();

	// shape_box(0,0,0,50,50,50);
	// generate_normals();

	//matrix_print(mPoints);
	//matrix_print(mTextures);
	//matrix_print(mNormals);

	//material_print_all();
	//texture_print_all();

	set_frameBuffer_random();
	if(MSAA_ENABLED)msaa();

	printf("Main loop complete!\n\n");

	printf("Drawing picture...\n");
	write_png_file("test.png");
	printf("Picture drawn!\n\n");

	printf("Freeing structures...\n");

	free_frameBuffer();
	matrices_free();
	polygons_free();
	texture_delete_all();
	material_delete_all();
	frag_array_free();
	printf("Structures freed!\n\n");


	return 0;
}