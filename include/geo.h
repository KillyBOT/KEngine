#ifndef GEO_H
#define GEO_H

#include "KEngine.h"
#include "vertex.h"
#include "material.h"

typedef struct polygon {
	Vec4 p[3]; //Top, middle, and bottom vertices
	Vec4 n[3]; //Top, middle, and bottom normals
	double t[3][2]; //Top, middle, and bottom texture coords

	int ifLight;
	int shadeType;
	material *m;

} polygon;

typedef struct line {
	Vec4 p[2]; //Start and end vertices
	Vec4 n[2]; //Start and end normals
	double t[2][2]; //Start and end texture coords

	int ifLight;
	int shadeType;
	material *m;
} line;

#endif