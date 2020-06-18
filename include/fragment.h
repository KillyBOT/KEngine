#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "KEngine.h"
#include "vertex.h"
#include "material.h"

typedef struct fragment {
	//int p[2];
	int ifLight;
	int shadeType;
	Vec4 p; //Position. I may get rid of this later, since I may be using a grid to store the fragments.
	Vec4 n; //Normal 
	double t[2]; //Texture coords
	material *m;
} fragment;

#endif