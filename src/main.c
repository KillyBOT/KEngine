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



extern Vec4_t* vPlaneNear;
extern Vec4_t* vPlaneLeft;
extern Vec4_t* vPlaneRight;
extern Vec4_t* vPlaneTop;
extern Vec4_t* vPlaneBot;



extern mat_t* mPoints;
extern mat_t* mNormals;
extern mat_t* mTextures;
extern mat_t* mPointsToAdd;
extern mat_t* mNormalsToAdd;
extern mat_t* mTexturesToAdd;
extern UT_array* cstack;



extern UT_array* gLights;
extern mtl_t* gMaterials;
extern tex_t* gTextures;
extern UT_array* pQueue;
extern UT_array*** fArray;



extern pixel_t ** inputBuffer;
extern pixel_t ** frameBuffer;

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
		abort_("Error! Must specify input file!");
	if(argc < 3)
		abort_("Error! Must specify target file!");

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

	CANVAS_WIDTH = 4;
	CANVAS_HEIGHT = 3;
	CANVAS_DEPTH = 1;

	CAMERA_X = 0;
	CAMERA_Y = 0;
	CAMERA_Z = 0;

	MSAA_ENABLED = 1;

	if(MSAA_ENABLED){
		MSAA_DEPTH = 8;
		MSAA_DEPTH_LOG = (int)(log(MSAA_DEPTH)/log(2));

		SCREEN_WIDTH *= MSAA_DEPTH_LOG;
		SCREEN_HEIGHT *= MSAA_DEPTH_LOG;
	}

	init_frameBuffer();
	matrices_init();
	polygons_init();
	vertices_init();
	frag_array_init();
	lights_init();

	material_add("Default");

	mtl_t* dMtl = material_find("Default");

	dMtl->ka[COLOR_R] = 0.4;
	dMtl->ka[COLOR_G] = 0.4;
	dMtl->ka[COLOR_B] = 0.4;

	dMtl->kd[COLOR_R] = 0.6;
	dMtl->kd[COLOR_G] = 0.6;
	dMtl->kd[COLOR_B] = 0.6;

	dMtl->ks[COLOR_R] = 0.3;
	dMtl->ks[COLOR_G] = 0.3;
	dMtl->ks[COLOR_B] = 0.3;



	printf("General structures initialized!\n\n");

	printf("Reading in obj file...\n");


	obj_yyparse();
	if(mNormals->lastcol == -1) generate_normals();



	printf("obj file read!\n\n");

	printf("Executing main loop...\n");

	cstack_translate(0,0,2);
	//cstack_scale(500,500,1);
	cstack_rotate(ROTATE_Y,M_PI/4);
	cstack_rotate(ROTATE_X,M_PI/4);

	printf("\tShading vertices...\n");
	shade_vertex_all();
	printf("\tVertices shaded!\n");

	// matrix_print(mPoints);
	// matrix_print(mNormals);
	// matrix_print(mTextures);

	printf("\tGenerating polygons...\n");
	shade_geometry();
	printf("\tPolygons generated!\n");

	//polygon_print_all();

	printf("\tRasterizing...\n");
	rasterize_all();
	printf("\tRasterization complete!\n");

	printf("\tShading fragments...\n");
	shade_fragment_all();
	printf("\tFragments shaded!\n");

	//material_print_all();
	//texture_print_all();

	//set_frameBuffer_random();
	if(MSAA_ENABLED)msaa();

	printf("Main loop complete!\n\n");

	printf("Drawing picture...\n");
	write_png_file(argv[2]);
	printf("Picture drawn!\n\n");

	printf("Freeing structures...\n");

	free_frameBuffer();
	matrices_free();
	polygons_free();
	vertices_free();
	texture_delete_all();
	material_delete_all();
	frag_array_free();
	lights_free();
	printf("Structures freed!\n\n");


	return 0;
}