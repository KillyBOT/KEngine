#ifndef FRAGMENT_H
#define FRAGMENT_H

#include "KEngine.h"
#include "vertex.h"
#include "material.h"
#include "utarray.h"

typedef struct frag_t {
	int x,y;
	double z;
	int ifLight;
	int shadeType;

	Vec4_t *p; //Position. I may get rid of this later, since I may be using a grid to store the fragments.
	Vec4_t *n; //Normal
	pixel_t *c; //Color (For gouraud and flat)
	double t[2]; //Texture coords
	mtl_t *m;
} frag_t;

void frag_array_init();
void frag_array_free();

void frag_copy(void *_dst, const void *_src);
void frag_dtor(void *_elt);

frag_t* frag_init();
void frag_add(frag_t* f);
frag_t* frag_find(int x, int y);

UT_array *fQueue;
UT_icd fragment_icd;

#endif