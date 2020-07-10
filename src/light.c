#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "KEngine.h"
#include "light.h"
#include "vertex.h"

#include "utarray.h"

extern UT_array* gLights;
extern UT_icd light_icd;

pixel_t* pixel_lerp(pixel_t* p1, pixel_t* p2, double t){
	pixel_t* p = (pixel_t*)malloc(sizeof(pixel_t));

	for(int c = 0; c < 4; c++){
		p->c[c] = (p1->c[c] * (1 - t)) + (p2->c[c] * t);
	}

	return p;
}
double double_lerp(double d0, double d1, double t){
	return (d0 * (1 - t)) + (d1 * t);
}

void pixel_print(pixel_t* p){
	printf("R: [%d]\tG: [%d]\tB: [%d]\tA: [%d]\n", (int)p->c[COLOR_R], (int)p->c[COLOR_G], (int)p->c[COLOR_B], (int)p->c[COLOR_A]);
}

light_t* light_init(int type, double lx, double ly, double lz, double ir, double ig, double ib){
	light_t* l = (light_t*)malloc(sizeof(light_t));

	l->type = type;
	l->v = vertex_init(lx,ly,lz);
	l->i = vertex_init(ir,ig,ib);

	return l;
}
void lights_init(){
	light_icd.sz = sizeof(light_t);
	light_icd.init = NULL;
	light_icd.copy = NULL;
	light_icd.dtor = light_dtor_icd;

	utarray_new(gLights,&light_icd);

	light_t* alight = light_init(LIGHT_AMBIENT, 0, 0, 0, .2, .4, .7);
	light_add(alight);

	light_t* plight = light_init(LIGHT_POINT, 0, 0, 0, .3, .8, .4);
	light_add(plight);

	light_t* dlight = light_init(LIGHT_DIRECTIONAL, 1, 4, 4, .9, .5, .1);
	light_add(dlight);
}
void lights_free(){
	utarray_free(gLights);
}
void light_add(light_t* l){
	utarray_push_back(gLights, l);
}

void light_dtor_icd(void *_elt){
	light_t* l = (light_t*)_elt;

	free(l->v);
	free(l->i);
}
