#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utarray.h"

#include "KEngine.h"
#include "vertex.h"
#include "matrix.h"
#include "material.h"
#include "geometry.h"

extern UT_array *pQueue;
extern UT_icd polygon_icd;

extern mat_t* mPoints;
extern mat_t* mNormals;
extern mat_t* mTextures;

void polygons_init(){
	polygon_icd.sz = sizeof(polygon_t);
	polygon_icd.init = NULL;
	polygon_icd.copy = NULL;
	polygon_icd.dtor = polygon_dtor_icd;
	utarray_new(pQueue,&polygon_icd);
}

void polygons_free(){
	utarray_free(pQueue);
}

void polygon_add(int point){

	if(point < 0 || point > mPoints->lastcol-2) return;

	polygon_t* p = (polygon_t*)malloc(sizeof(polygon_t));

	p->m = material_find_id((int)mTextures->m[POS_Z][point]);

	p->p = (Vec4_t**)malloc(sizeof(Vec4_t*) * 3);
	p->n = (Vec4_t**)malloc(sizeof(Vec4_t*) * 3);

	int iTop, iMid, iBot;
	double yMax, yMin;

	yMax = -99999999;
	yMin = 99999999;

	Vec4_t** pToAdd = (Vec4_t**)malloc(sizeof(Vec4_t*) * 3);
	Vec4_t** nToAdd = (Vec4_t**)malloc(sizeof(Vec4_t*) * 3);

	for(int n = 0; n < 3; n++){
		pToAdd[n] = matrix_find(mPoints,point+n);
		nToAdd[n] = matrix_find(mNormals,point+n);
		p->p[n] = vertex_init(0,0,0);
		p->p[n] = vertex_init(0,0,0);
	}

	for(int n = 0; n < 3; n++){
		if(pToAdd[n]->v[POS_Y] > yMax){
			yMax = pToAdd[n]->v[POS_Y];
			iTop = n;
		}
		if(pToAdd[n]->v[POS_Y] <= yMin){
			yMin = pToAdd[n]->v[POS_Y];
			iBot = n;
		}
	}

	iMid = (6 / (iTop+1) / (iBot+1)) - 1;

	vertex_copy(p->p[POLYGON_TOP],pToAdd[iTop]);
	vertex_copy(p->p[POLYGON_MID],pToAdd[iMid]);
	vertex_copy(p->p[POLYGON_BOT],pToAdd[iBot]);

	vertex_copy(p->n[POLYGON_TOP],nToAdd[iTop]);
	vertex_copy(p->n[POLYGON_MID],nToAdd[iMid]);
	vertex_copy(p->n[POLYGON_BOT],nToAdd[iBot]);

	p->t[POLYGON_TOP][TEXTURE_U] = mTextures->m[TEXTURE_U][point+iTop];
	p->t[POLYGON_TOP][TEXTURE_V] = mTextures->m[TEXTURE_V][point+iTop];

	p->t[POLYGON_MID][TEXTURE_U] = mTextures->m[TEXTURE_U][point+iMid];
	p->t[POLYGON_MID][TEXTURE_V] = mTextures->m[TEXTURE_V][point+iMid];

	p->t[POLYGON_BOT][TEXTURE_U] = mTextures->m[TEXTURE_U][point+iBot];
	p->t[POLYGON_BOT][TEXTURE_V] = mTextures->m[TEXTURE_V][point+iBot];

	for(int n = 0; n < 3; n++){
		free(pToAdd[n]);
		free(nToAdd[n]);
	}
	free(pToAdd);
	free(nToAdd);

	utarray_push_back(pQueue,p);
}
void polygon_dtor_icd(void *_elt){
	polygon_t* p = (polygon_t*)_elt;

	for(int n = 0; n < 3; n++){
		free(p->p[n]);
		free(p->n[n]);
	}
	free(p->p);
	free(p->n);
}
void polygon_copy();