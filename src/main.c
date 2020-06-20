#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

extern mtl_t* gMaterials;
extern tex_t* gTextures;
extern UT_array* polyQueue;

int main(){

	gMaterials = NULL;
	gTextures = NULL;
	polyQueue = NULL;

	printf("Hello world!\n");

	return 0;
}