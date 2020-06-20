#ifndef MATRIX_H
#define MATRIX_H

#include "KEngine.h"
#include "vertex.h"

typedef struct {
	double ** m;
	int rows, cols;
	int lastcol;
} mat_t;


//Matrix general functions
mat_t matrix_create(int rows, int cols);
void matrix_free(mat_t* m);
void matrix_grow(mat_t* m, int newcols);
void matrix_copy(mat_t* dest, mat_t* src);
void matrix_print(mat_t* m);
void matrix_print_point(mat_t* m, int p);
Vec4_t *matrix_find(mat_t* m, int p);

//Matrix mathematical operations
void matrix_mult(mat_t* a, mat_t* b);
void mat_translate(mat_t* m, double x, double y, double z);
void matrix_scale(mat_t* m, double x, double y, double z);
void matrix_rotate(mat_t* m, int rotType, double theta);
void matrix_ident(mat_t* m);

double matrix_det(mat_t* m);
void matrix_minor(mat_t* m);
void mat_transpose(mat_t* m);
void matrix_adjugate(mat_t* m);
void matrix_inverse(mat_t* m);

#endif