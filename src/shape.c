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

typedef struct Vec4_hash_t{
	Vec4_t vertex;
	Vec4_t normal;
	UT_hash_handle hh;
} Vec4_hash_t;

void generate_normals(){

	Vec4_hash_t* vHash = NULL;
	Vec4_hash_t *h, *tmp, *toAdd;

	Vec4_t *v[3], *sn, *vTemp, *vTemp2;
	
	for(int point = 0; point < mPoints->lastcol; point+=3){

		for(int i = 0; i < 3; i++){
			v[i] = (Vec4_t*)malloc(sizeof(Vec4_t));
			memset(v[i],0,sizeof(Vec4_t));

			vTemp = matrix_find(mPoints,point+i);
			vertex_copy(v[i],vTemp);

			free(vTemp);
		}



		sn = vertex_surface_normal(v[0],v[1],v[2]);

		for(int i = 0; i < 3; i++){
			HASH_FIND(hh, vHash, v[i], sizeof(Vec4_t), h);

			if(!h){
				toAdd = (Vec4_hash_t*)malloc(sizeof(Vec4_hash_t));
				memset(toAdd,0,sizeof(Vec4_hash_t));

				vertex_copy(&toAdd->vertex,v[i]);
				vertex_copy(&toAdd->normal,sn);

				// vertex_print(&toAdd->vertex);
				// vertex_print(&toAdd->normal);
				// printf("\n");

				HASH_ADD(hh, vHash, vertex, sizeof(Vec4_t), toAdd);
			} else {
				h->normal.v[POS_X] += sn->v[POS_X];
				h->normal.v[POS_Y] += sn->v[POS_Y];
				h->normal.v[POS_Z] += sn->v[POS_Z];
			}
		}
	}

	for(int i = 0; i < 3; i++)
		free(v[i]);

	HASH_ITER(hh, vHash, h, tmp){
		vertex_normalize(&h->normal);
	}

	for(int point = 0; point <= mPoints->lastcol; point++){
		
		vTemp = (Vec4_t*)malloc(sizeof(Vec4_t));
		memset(vTemp,0,sizeof(Vec4_t));

		vTemp2 = matrix_find(mPoints,point);
		vertex_copy(vTemp,vTemp2);
		free(vTemp2);

		HASH_FIND(hh, vHash, vTemp, sizeof(Vec4_t), h);
		matrix_add_point(mNormals,&h->normal);

		free(vTemp);
	}

	HASH_ITER(hh, vHash, h, tmp){
		HASH_DEL(vHash,h);
		free(h);
	}

}