#ifndef VERTEX_H
#define VERTEX_H

#include "KEngine.h"
#include "material.h"

typedef struct Vec4 {
	double v[4];
} Vec4;

typedef struct queue_vertex {
	Vec4 p; //The coordinates of the vertex
	double t[2]; //The texture coordinates
	Vec4 n; //The coordinates of the vertex normal
	int vtype; //Vertex type, i.e. if it's a part of a line or a polygon
	material *m; //The material, including the texture
} queue_vertex;

#endif