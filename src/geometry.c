#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utarray.h"

#include "KEngine.h"
#include "vertex.h"
#include "matrix.h"
#include "light.h"
#include "material.h"
#include "geometry.h"

extern UT_array *pQueue;
extern UT_icd polygon_icd;

extern Vec4_t* vPlaneNear;
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
	pixel_t c;

	p->m = material_find_id((int)mTextures->m[POS_Z][point]);

	p->p = (Vec4_t**)malloc(sizeof(Vec4_t*) * 3);
	p->n = (Vec4_t**)malloc(sizeof(Vec4_t*) * 3);
	p->c = (pixel_t**)malloc(sizeof(pixel_t*) * 3);

	p->ifLight = 1;
	p->shadeType = -1;

	int iTop, iMid, iBot;
	pixel_t *cTop, *cMid, *cBot;
	double yMax, yMin;
	Vec4_t *vCenter;

	yMax = -99999999;
	yMin = 99999999;

	Vec4_t** pToAdd = (Vec4_t**)malloc(sizeof(Vec4_t*) * 3);
	Vec4_t** nToAdd = (Vec4_t**)malloc(sizeof(Vec4_t*) * 3);

	for(int n = 0; n < 3; n++){
		pToAdd[n] = matrix_find(mPoints,point+n);
		nToAdd[n] = matrix_find(mNormals,point+n);
		p->p[n] = vertex_init(0,0,0);
		p->n[n] = vertex_init(0,0,0);
		p->c[n] = (pixel_t*)malloc(sizeof(pixel_t));
	}

	p->sN = vertex_surface_normal(pToAdd[0],pToAdd[1],pToAdd[2]);

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


	//Change the colors later

	switch(p->shadeType){

		default:
			c.c[COLOR_R] = rand() % 256;
			c.c[COLOR_G] = rand() % 256;
			c.c[COLOR_B] = rand() % 256;
			c.c[COLOR_A] = 255;

			for(int poly = 0; poly < 3; poly++){
				for(int color = 0; color < 4; color++){
					p->c[poly]->c[color] = c.c[color];
				}
			}

			break;
	}

	//Set them to random colors for now

	for(int n = 0; n < 3; n++){
		free(pToAdd[n]);
		free(nToAdd[n]);
	}
	free(pToAdd);
	free(nToAdd);

	//utarray_push_back(pQueue,p);
	if(vertex_dot_product(p->sN,vPlaneNear) < 0){
		utarray_push_back(pQueue,p);
	} else {
		polygon_dtor_icd(p);
		free(p);
	}
	
}
void polygon_dtor_icd(void *_elt){
	polygon_t* p = (polygon_t*)_elt;

	for(int n = 0; n < 3; n++){
		free(p->p[n]);
		free(p->n[n]);
		free(p->c[n]);
	}
	free(p->p);
	free(p->n);
	free(p->c);
	free(p->sN);
}
void polygon_print(polygon_t* p){
	printf("Position vertices:\n");
	printf("Top:\n\t");
	vertex_print(p->p[POLYGON_TOP]);
	printf("Middle:\n\t");
	vertex_print(p->p[POLYGON_MID]);
	printf("Bottom:\n\t");
	vertex_print(p->p[POLYGON_BOT]);
	printf("\n");

	printf("Normal vertices:\n");
	printf("Top:\n\t");
	vertex_print(p->n[POLYGON_TOP]);
	printf("Middle:\n\t");
	vertex_print(p->n[POLYGON_MID]);
	printf("Bottom:\n\t");
	vertex_print(p->n[POLYGON_BOT]);
	printf("\n");

	printf("Texture coordinates:\n");
	printf("Top:\n\t");
	printf("U: [%.2lf]\tV: [%.2lf]\n", p->t[POLYGON_TOP][TEXTURE_U], p->t[POLYGON_TOP][TEXTURE_V]);
	printf("Middle:\n\t");
	printf("U: [%.2lf]\tV: [%.2lf]\n", p->t[POLYGON_MID][TEXTURE_U], p->t[POLYGON_MID][TEXTURE_V]);
	printf("Bottom:\n\t");
	printf("U: [%.2lf]\tV: [%.2lf]\n", p->t[POLYGON_BOT][TEXTURE_U], p->t[POLYGON_BOT][TEXTURE_V]);
	printf("\n");

	printf("Surface Normal:\n\t");
	vertex_print(p->sN);

	printf("Material: [%s]\n", p->m->name);
	printf("\n");
}

void polygon_print_all(){
	polygon_t *p;
	p = NULL;

	while( (p = (polygon_t*)utarray_next(pQueue,p))){
		polygon_print(p);
	}
	printf("Total polygon count: [%d]\n\n", utarray_len(pQueue));
}