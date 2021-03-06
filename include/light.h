#ifndef LIGHT_H
#define LIGHT_H

#include "KEngine.h"
#include "vertex.h"
#include "material.h"
#include "fragment.h"

double *gLights[2][3];
int lightNum;

void light_add(double l[2][3]);

pixel_t* pixel_lerp(pixel_t* p1, pixel_t* p2, double t);
double double_lerp(double d0, double d1, double t);

pixel_t ref_phong(Vec4_t* n, Vec4_t* v, pixel_t* alight, mtl_t* mat, double t[2] );

pixel_t ref_phong_a (pixel_t* alight, mtl_t* mat, double t[2]);
pixel_t ref_phong_d (Vec4_t* n, mtl_t* mat, double t[2]);
pixel_t ref_phong_s (Vec4_t* n, Vec4_t* v, mtl_t* mat, double t[2]);

pixel_t ref_blinn(Vec4_t* n, Vec4_t* v, pixel_t* alight, mtl_t* mat, double t[2] );

pixel_t ref_blinn_a (pixel_t* alight, mtl_t* mat, double t[2]);
pixel_t ref_blinn_d (Vec4_t* n, mtl_t* mat, double t[2]);
pixel_t ref_blinn_s (Vec4_t* n, Vec4_t* v, mtl_t* mat, double t[2]);

void color_limit(byte_t *color[3]);
void pixel_print(pixel_t* p);

pixel_t shade_phong(frag_t *f);
pixel_t shade_gouraud(frag_t *f);
pixel_t shade_flat(frag_t *f);
pixel_t shade_wireframe(frag_t *f);

#endif