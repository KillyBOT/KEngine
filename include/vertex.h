#ifndef VERTEX_H
#define VERTEX_H

#include "KEngine.h"
#include "material.h"

typedef struct vertex {
	double v[3]; //The position of the vertex
	double n[3]; //The vertex normal
	material mat;
} vertex;

#endif