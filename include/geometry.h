#ifndef GEO_H
#define GEO_H

#include "KEngine.h"
#include "vertex.h"
#include "material.h"

#include "utarray.h"

typedef struct {
	Vec4_t **p; //Top, middle, and bottom vertices
	//Vec4_t *dP; //Where the vertices are on screen. These will be used for drawing, but now lerping for lighting or anything like that
	Vec4_t **n; //Top, middle, and bottom normals
	pixel_t **c; //Top, middle, and bottom colors
	double t[3][2]; //Top, middle, and bottom texture coords

	int ifLight;
	int shadeType;
	mtl_t *m;

} polygon_t;

typedef struct {
	Vec4_t p[2]; //Start and end vertices
	Vec4_t n[2]; //Start and end normals
	double t[2][2]; //Start and end texture coords

	int ifLight;
	int shadeType;
	mtl_t *m;
} line_t;

UT_array *pQueue;
UT_icd polygon_icd;

void polygon_add(int point);
void polygon_copy_icd(void *_dst, void *_src);
void polygon_init_icd(void *_elt);
void polygon_dtor_icd(void *_elt);
void polygon_copy();
void polygon_print(polygon_t* p);
void polygon_print_all();

void polygons_init();
void polygons_free();

#endif