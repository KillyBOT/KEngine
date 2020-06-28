#ifndef VERTEX_H
#define VERTEX_H

#include "KEngine.h"
#include "material.h"

typedef struct {
	double v[4];
} Vec4_t;

Vec4_t *vertex_init(double x, double y, double z);
void vertex_free(Vec4_t* v);
void vertex_print(Vec4_t* v);
double vertex_element(Vec4_t* v, int vElement);
Vec4_t *vertex_add(Vec4_t* a, Vec4_t* b);
void vertex_copy(Vec4_t* dest, Vec4_t* src);
void vertex_dtor_icd(void *_elt);

Vec4_t* vertex_lerp(Vec4_t* v1, Vec4_t* v2, double t);
void vertex_normalize(Vec4_t* v);
double vertex_dot_product(Vec4_t* a, Vec4_t* b);
Vec4_t *vertex_surface_normal(Vec4_t* a, Vec4_t* b, Vec4_t* c);

#endif