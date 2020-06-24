#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "shape.h"
#include "vertex.h"
#include "matrix.h"

#include "uthash.h"

extern mat_t* mPoints;
extern mat_t* mNormals;
extern mat_t* mTextures;

typedef struct Vec4_hash_t{
	Vec4_t* p;
	Vec4_t* n;
	UT_hash_handle hh;
} Vec4_hash_t;

void generate_normals(){

	Vec4_hash_t* vHash = NULL;
	Vec4_hash_t *h, *tmp, *toAdd;

	Vec4_t *v[3], *sn, *vTemp;
	
	for(int point = 0; point < mPoints->lastcol; point+=3){

		for(int i = 0; i < 3; i++)
			v[i] = matrix_find(mPoints,point+i);
		
		sn = vertex_surface_normal(v[0],v[1],v[2]);
		vertex_print(sn);

		for(int i = 0; i < 3; i++)
			vertex_free(v[i]);

		for(int i = 0; i < 3; i++){
			v[i] = matrix_find(mPoints,i+point);
			HASH_FIND(hh, vHash, v[i], sizeof(Vec4_t), h);

			if(h == NULL){
				toAdd = (Vec4_hash_t*)malloc(sizeof(Vec4_hash_t));

				toAdd->p = vertex_init(0,0,0);
				toAdd->n = vertex_init(0,0,0);

				vertex_copy(toAdd->p,v[i]);
				vertex_copy(toAdd->n,sn);

				HASH_ADD(hh, vHash, p, sizeof(Vec4_t), toAdd);
			} else {
				h->n->v[POS_X] += sn->v[POS_X];
				h->n->v[POS_Y] += sn->v[POS_Y];
				h->n->v[POS_Z] += sn->v[POS_Z];
			}
		}
	}

	HASH_ITER(hh, vHash, h, tmp){
		vertex_normalize(h->n);
		vertex_print(h->p);
		vertex_print(h->n);
	}

	HASH_ITER(hh, vHash, h, tmp){

		HASH_DEL(vHash,h);
		vertex_free(h->p);
		vertex_free(h->n);
		free(h);
	}

}