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
extern int CANVAS_WIDTH;
extern int CANVAS_HEIGHT;
extern int CANVAS_DEPTH;

extern UT_array*** fArray;
extern pixel_t ** frameBuffer;

extern mtl_t* gMaterials;
extern tex_t* gTextures;

void shade_fragment_all(){

	frag_t* f = NULL;
	Vec4_t* p = vertex_init(0,0,0);
	Vec4_t* v = vertex_init(0,0,0);
	pixel_t* c;

	for(int x = 0; x < SCREEN_WIDTH; x++){
		for(int y = 0; y < SCREEN_HEIGHT; y++){
			//if(utarray_len(fArray[x][y]) != 0) printf("%d %d\n", x, y);
			// while( (f = (frag_t*)utarray_next(fArray[x][y],f)) ){
			// 	frag_print(f);
			// }
			f = frag_find(x,y);

			if(f != NULL){

				p->v[POS_X] = (f->x) * ((double)CANVAS_WIDTH / (double)SCREEN_WIDTH);
				p->v[POS_Y] = (f->y) * ((double)CANVAS_HEIGHT / (double)SCREEN_HEIGHT);

				p->v[POS_X] /= ((double)CANVAS_DEPTH * f->z);
				p->v[POS_Y] /= ((double)CANVAS_DEPTH * f->z);

				p->v[POS_Z] = 1.0 / (f->z);

				c = ref_phong(f->n, p, f->m, f->t);

				for(int n = 0; n < 4; n++)
						frameBuffer[x][y].c[n] = c->c[n];
				

				free(c);
			}

		}
	}

	free(p);
	free(v);
}