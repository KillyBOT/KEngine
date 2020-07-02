#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "material.h"
#include "texture.h"
#include "fragment.h"
#include "vertex.h"

#include "utarray.h"

extern UT_array *** fArray;
extern UT_icd fragment_icd;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

void frag_array_init(){
	fragment_icd.sz = sizeof(frag_t);
	fragment_icd.init = NULL;
	fragment_icd.copy = NULL;
	fragment_icd.dtor = frag_dtor_icd;

	fArray = (UT_array***)malloc(sizeof(UT_array**) * SCREEN_WIDTH);

	for(int x = 0; x < SCREEN_WIDTH; x++){
		fArray[x] = (UT_array**)malloc(sizeof(UT_array*) * SCREEN_HEIGHT);
		for(int y = 0; y < SCREEN_HEIGHT; y++){
			utarray_new(fArray[x][y],&fragment_icd);
		}
	}
}
void frag_array_free(){
	for(int x = 0; x < SCREEN_WIDTH; x++){
		for(int y = 0; y < SCREEN_HEIGHT; y++){
			utarray_free(fArray[x][y]);
		}
		free(fArray[x]);
	}
	free(fArray);
}

void frag_copy_icd(void *_dst, const void *_src);
void frag_init_icd(void *_elt);
void frag_dtor_icd(void *_elt){
	frag_t* f = (frag_t*)_elt;

	if(f->n != NULL)free(f->n);
	if(f->c != NULL)free(f->c);
}

frag_t* frag_init(int x, int y, double z){
	frag_t* f = (frag_t*)malloc(sizeof(frag_t));

	f->n = NULL;
	f->c = NULL;

	f->ifLight = 1;
	f->shadeType = SHADE_FLAT;
	f->x = x;
	f->y = y;
	f->z = z;

	return f;
}
void frag_add(frag_t* f){
	if(f->x >= 0 && f->y >= 0 && f->x < SCREEN_WIDTH && f->y < SCREEN_HEIGHT){
		if(utarray_len(fArray[f->x][f->y]) == 0)
			utarray_push_back(fArray[f->x][f->y],f);
		else {
			int p;
			frag_t *tmp;


			for(p = 0; p < utarray_len(fArray[f->x][f->y]); p++){
				tmp = (frag_t*)utarray_eltptr(fArray[f->x][f->y],p);
				if(tmp->z >= f->z){
					utarray_insert(fArray[f->x][f->y],f,p);
					return;
				}
			}
		}
	}
}
frag_t* frag_find(int x, int y){ //NOTE: This gets the element with the highest z value
	return (frag_t*)utarray_front(fArray[x][y]);
}