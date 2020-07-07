#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "fragment.h"
#include "vertex.h"
#include "shade.h"
#include "light.h"
#include "material.h"
#include "texture.h"

#include "utarray.h"
#include "uthash.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern UT_array*** fArray;
extern pixel_t ** frameBuffer;

extern mtl_t* gMaterials;
extern tex_t* gTextures;

void shade_fragment_all(){

	frag_t* f = NULL;

	for(int x = 0; x < SCREEN_WIDTH; x++){
		for(int y = 0; y < SCREEN_HEIGHT; y++){
			//if(utarray_len(fArray[x][y]) != 0) printf("%d %d\n", x, y);
			// while( (f = (frag_t*)utarray_next(fArray[x][y],f)) ){
			// 	frag_print(f);
			// }
			f = frag_find(x,y);

			if(f != NULL){
				for(int c = 0; c < 4; c++)
					frameBuffer[x][y].c[c] = f->c->c[c];
			}

		}
	}
}