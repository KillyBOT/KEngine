#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "KEngine.h"
#include "vertex.h"

Vec4_t* vertex_init(double x, double y, double z){
	Vec4_t* v = (Vec4_t*)malloc(sizeof(Vec4_t));

	v->v[POS_X] = x;
	v->v[POS_Y] = y;
	v->v[POS_Z] = z;
	v->v[3] = 1;

	return v;
}
void vertex_print(Vec4_t* v){
	printf("X:[%.2lf]\tY:[%.2lf]\tZ:[%.2lf]\tT:[%.2lf]\n", v->v[POS_X], v->v[POS_Y], v->v[POS_Z], v->v[3]);
}
double vertex_element(Vec4_t* v, int vElement){
	if(vElement < 0 || vElement > 3) return -1;
	return v->v[vElement];
}
void vertex_add(Vec4_t* a, Vec4_t* b){
	for(int n = 0; n < 3; n++)
		a->v[n] = a->v[n] + b->v[n];
}
void vertex_copy(Vec4_t* dest, Vec4_t* src){
	for(int n = 0; n < 4; n++)
		dest->v[n] = src->v[n];
}

void vertex_dtor_icd(void *_elt){
	Vec4_t* elt = (Vec4_t*)_elt;

	if(elt) free(elt->v);
}

Vec4_t* vertex_lerp(Vec4_t* v1, Vec4_t* v2, double t){
	Vec4_t* v = vertex_init(0,0,0);

	for(int n = 0; n < 4; n++)
		v->v[n] = ((t-1) * v1->v[n]) + (t * v2->v[n]);

	return v;
}
void vertex_normalize(Vec4_t* v){

	double length = sqrt( (v->v[POS_X] * v->v[POS_X]) + (v->v[POS_Y] * v->v[POS_Y]) + (v->v[POS_Z] * v->v[POS_Z]) );

	if(length == 0) return;

	v->v[POS_X] /= length;
	v->v[POS_Y] /= length;
	v->v[POS_Z] /= length;
}
double vertex_dot_product(Vec4_t* a, Vec4_t* b){
	return a->v[POS_X] * b->v[POS_X] + a->v[POS_Y] * b->v[POS_Y] + a->v[POS_Z] + b->v[POS_Z];
}
Vec4_t *vertex_surface_normal(Vec4_t* a, Vec4_t* b, Vec4_t* c){
	Vec4_t* sn = vertex_init(0,0,0);
	double m[3];
	double n[3];

	m[POS_X] = b->v[POS_X] - a->v[POS_X];
	m[POS_Y] = b->v[POS_Y] - a->v[POS_Y];
	m[POS_Z] = b->v[POS_Z] - a->v[POS_Z];

	n[POS_X] = c->v[POS_X] - a->v[POS_X];
	n[POS_Y] = c->v[POS_Y] - a->v[POS_Y];
	n[POS_Z] = c->v[POS_Z] - a->v[POS_Z];

	sn->v[POS_X] = m[POS_Y] * n[POS_Z] - m[POS_Z] * n[POS_Y];
	sn->v[POS_Y] = m[POS_Z] * n[POS_X] - m[POS_X] * n[POS_Z];
	sn->v[POS_Z] = m[POS_X] * n[POS_Y] - m[POS_Y] * n[POS_X];

	vertex_normalize(sn);
	return sn;
}