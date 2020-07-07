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

	//Vec4_t *p; //Position. I may get rid of this later, since I may be using a grid to store the fragments.
	Vec4_t *n; //Normal
	pixel_t *c; //Color (For gouraud and flat)
	double t[2]; //Texture coords
	mtl_t *m; //Material, also containing the textures
} frag_t;

void frag_array_init();
void frag_array_free();

void frag_copy_icd(void *_dst, const void *_src);
void frag_init_icd(void *_elt);
void frag_dtor_icd(void *_elt);

frag_t* frag_init(int x, int y, double z);
void frag_add(frag_t* f);
frag_t* frag_find(int x, int y);
void frag_print(frag_t* f);

UT_array *** fArray;
UT_icd fragment_icd;

#endif