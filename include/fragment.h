#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "KEngine.h"
#include "vertex.h"
#include "material.h"

typedef struct {
	//int p[2];
	int ifLight;
	int shadeType;

	Vec4_t *p; //Position. I may get rid of this later, since I may be using a grid to store the fragments.
	Vec4_t *n; //Normal
	pixel *c; //Color (For gouraud and flat)
	double t[2]; //Texture coords
	mtl_t *m;
} frag_t;

frag_t **fragBuffer;

void frag_buffer_init();
void frag_buffer_free();
void frag_create(int x, int y);
frag_t* frag_find(int x, int y);

#endif