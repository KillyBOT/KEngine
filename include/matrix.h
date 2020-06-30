#ifndef MATRIX_H
#define MATRIX_H

#include "KEngine.h"
#include "vertex.h"
#include "utarray.h"

typedef struct {
	double ** m;
	int rows, cols;
	int lastcol;
} mat_t;


//Matrix general functions
mat_t* matrix_create(int rows, int cols);
void matrices_init();
void matrix_init_icd(void *_elt);
void matrix_free(mat_t* m);
void matrices_free();
void matrix_grow(mat_t* m, int newcols);
void matrix_copy(mat_t* dest, mat_t* src);
void matrix_copy_icd(void *_dst, const void *_src);
void matrix_dtor_icd(void *_elt);
void matrix_print(mat_t* m);
void matrix_print_point(mat_t* m, int p);
Vec4_t *matrix_find(mat_t* m, int p);
void matrix_add_point(mat_t* m, Vec4_t* v);
void matrix_add_matrix_point(mat_t* dest, mat_t* src, int p);
void matrix_set_point(mat_t* m, int p, Vec4_t* v);

void cstack_push();
void cstack_pop();
mat_t* cstack_peek();
void cstack_print();

//Matrix mathematical operations
void matrix_mult(mat_t* a, mat_t* b);
void cstack_translate(double x, double y, double z);
void cstack_scale(double x, double y, double z);
void cstack_rotate(int rotType, double theta);
void matrix_ident(mat_t* m);

void cstack_apply();

double matrix_det(mat_t* m);
void matrix_minor(mat_t* m);
void matrix_transpose(mat_t* m);
void matrix_adjugate(mat_t* m);
void matrix_inverse(mat_t* m);

mat_t* mPoints;
mat_t* mNormals;
mat_t* mTextures;

mat_t* mPointsToAdd;
mat_t* mTexturesToAdd;
mat_t* mNormalsToAdd;

mat_t* mPointsTemp;
mat_t* mTexturesTemp;
mat_t* mNormalsTemp;

UT_array* cstack;
UT_icd matrix_icd;

#endif