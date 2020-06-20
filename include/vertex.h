#ifndef VERTEX_H
#define VERTEX_H

#include "KEngine.h"
#include "material.h"

typedef struct {
	double v[4];
} Vec4_t;

void vertex_print(Vec4_t* v);
double vertex_element(Vec4_t* v, int vElement);
Vec4_t *vertex_add(Vec4_t* a, Vec4_t* b);
Vec4_t *vertex_mult(Vec4_t* a, Vec4_t* b);
void vertex_copy(Vec4_t* dest, Vec4_t* src);

Vec4_t* vertex_lerp(Vec4_t* v1, Vec4_t* v2, double t);
void vertex_normalize(Vec4_t* v);
Vec4_t *vertex_dot_product(Vec4_t* a, Vec4_t* b);
Vec4_t *vertex_surface_normal(Vec4_t* a, Vec4_t* b, Vec4_t* c);

#endif