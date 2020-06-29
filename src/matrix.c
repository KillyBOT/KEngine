#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "matrix.h"
#include "vertex.h"
#include "utarray.h"

extern mat_t* mPoints;
extern mat_t* mNormals;
extern mat_t* mTextures;
extern UT_array* cstack;

mat_t* matrix_create(int rows, int cols){
	mat_t* m = (mat_t*)malloc(sizeof(mat_t));

	m->rows = rows;
	m->cols = cols;
	m->lastcol = 0;

	m->m = (double**)malloc(sizeof(double*) * m->rows);
	for(int r = 0; r < m->rows; r++)
		m->m[r] = (double*)malloc(sizeof(double) * m->cols);

	return m;
}

void matrices_init(){
	matrix_icd.sz = sizeof(mat_t);
	matrix_icd.init = NULL;
	matrix_icd.copy = NULL;
	matrix_icd.dtor = matrix_dtor_icd;
	utarray_new(cstack, &matrix_icd);

	mat_t* cstackInit = matrix_create(4, 4);
	matrix_ident(cstackInit);
	utarray_push_back(cstack,cstackInit);

	mPoints = matrix_create(4,1024);
	mNormals = matrix_create(4,1024);
	mTextures = matrix_create(4,1024);
}

void matrix_free(mat_t* m){
	for(int r = 0; r < m->rows; r++)
		free(m->m[r]);
	free(m->m);

	free(m);
}

void matrices_free(){
	matrix_free(mPoints);
	matrix_free(mNormals);
	matrix_free(mTextures);
	utarray_free(cstack);
}

void matrix_grow(mat_t* m, int newcols){

	for(int i = 0; i < m->rows; i++){
		m->m[i] = realloc(m->m[i],sizeof(double)*newcols);
	}

	m->cols = newcols;
	if(newcols <= m->lastcol) m->lastcol = newcols-1;
}
void matrix_copy(mat_t* dest, mat_t* src){
	if(dest->rows != src->rows) return;

	dest->lastcol = src->lastcol;
	dest->cols = src->cols;
	dest->rows = src->rows;

	matrix_grow(dest,src->cols);

	for(int r = 0; r < dest->rows; r++){
		for(int c = 0; c < src->cols; c++){
			dest->m[r][c] = src->m[r][c];
		}
	}
}

void matrix_copy_icd(void *_dst, const void *_src){

	mat_t* dest = (mat_t*)_dst;
	mat_t* src = (mat_t*)_src;

	matrix_copy(dest, src);
}

void matrix_dtor_icd(void *_elt){
	mat_t* elt = (mat_t*)_elt;

	if(elt->m){
		for(int r = 0; r < elt->rows; r++)
			free(elt->m[r]);
		free(elt->m);
	}
}

void matrix_print(mat_t* m){
	for(int r = 0; r < m->rows; r++){
		for(int c = 0; c <= m->lastcol; c++){
			printf("%.3lf ", m->m[r][c]);
		}
		printf("\n");
	}
}
void matrix_print_point(mat_t* m, int p){
	printf("x:[%.3lf]\ty:[%.3lf]z:[%.3lf]\n", m->m[POS_X][p], m->m[POS_Y][p], m->m[POS_Z][p]);
}
Vec4_t *matrix_find(mat_t* m, int p){

	if(p < 0 || p > m->lastcol) {
		printf("Error! Trying to access vertex outside of matrix!\n");
		return NULL;
	}

	Vec4_t* v = vertex_init(m->m[POS_X][p],m->m[POS_Y][p],m->m[POS_Z][p]);
	return v;
}
void matrix_add_point(mat_t* m, Vec4_t* v){
	//vertex_print(v);
	m->m[POS_X][m->lastcol] = v->v[POS_X];
	m->m[POS_Y][m->lastcol] = v->v[POS_Y];
	m->m[POS_Z][m->lastcol] = v->v[POS_Z];
	m->m[3][m->lastcol] = 1;

	m->lastcol++;

	if(m->lastcol == m->cols) matrix_grow(m, m->cols * 2);
}
void matrix_set_point(mat_t* m, int p, Vec4_t* v){

	if(p < 0 || p > m->lastcol) return;

	m->m[POS_X][p] = v->v[POS_X];
	m->m[POS_Y][p] = v->v[POS_Y];
	m->m[POS_Z][p] = v->v[POS_Z];
}

void cstack_push(){
	mat_t* tmp = matrix_create(4,4);
	matrix_copy(tmp,cstack_peek());
	utarray_push_back(cstack, tmp);
	//matrix_free(tmp);
}

void cstack_pop(mat_t* m){
	utarray_pop_back(cstack);
}

mat_t* cstack_peek(){
	return (mat_t*)utarray_back(cstack);
}

void cstack_print(){
	mat_t* p;
	int n;

	p = NULL;
	n = 0;

	while((p = (mat_t*)utarray_next(cstack,p))){
		printf("Index %d\n",n);
		matrix_print(p);
		printf("\n");
		n++;
	}
}