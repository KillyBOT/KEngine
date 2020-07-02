#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "material.h"
#include "matrix.h"
#include "shade.h"
#include "texture.h"
#include "vertex.h"

extern mat_t* mPoints;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern int CANVAS_WIDTH;
extern int CANVAS_HEIGHT;
extern int CANVAS_DEPTH;

void shade_vertex_all(){
	if(mPoints->lastcol > -1){

		Vec4_t* v;
		//matrix_print(mPoints);
		cstack_apply();
		//matrix_print(mPoints);

		for(int p = 0; p <= mPoints->lastcol; p++){
			v = matrix_find(mPoints,p);
			shade_vertex(v);
			matrix_set_point(mPoints,p,v);
			free(v);
		}

	}
}

void shade_vertex(Vec4_t* v){
	//This is where the prospective projection will happen. I may add other stuff too here that should happen during the initial steps

	Vec4_t* vf = vertex_init(0,0,0);

	vf->v[POS_X] = v->v[POS_X] * (CANVAS_DEPTH / v->v[POS_Z]);
	vf->v[POS_Y] = v->v[POS_Y] * (CANVAS_DEPTH / v->v[POS_Z]);
	vf->v[POS_Z] = v->v[POS_Z];

	vf->v[POS_X] *= SCREEN_WIDTH / CANVAS_WIDTH;
	vf->v[POS_Y] *= SCREEN_HEIGHT / CANVAS_HEIGHT;

	vertex_copy(v,vf);

	free(vf);
}