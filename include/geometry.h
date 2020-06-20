#ifndef GEO_H
#define GEO_H

#include "KEngine.h"
#include "vertex.h"
#include "material.h"

typedef struct {
	Vec4_t p[3]; //Top, middle, and bottom vertices
	Vec4_t n[3]; //Top, middle, and bottom normals
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

UT_array *polyQueue;

#endif