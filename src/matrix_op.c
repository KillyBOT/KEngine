#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "KEngine.h"
#include "vertex.h"
#include "matrix.h"

extern mat_t* mPoints;
extern mat_t* mNormals;
extern mat_t* mTextures;

extern UT_array* cstack;
extern UT_icd matrix_icd;

void matrix_mult(mat_t* a, mat_t* b){
	mat_t* tmp;
	tmp = matrix_create(4, 1);

	for(int c = 0; c <= b->lastcol; c++){

		for(int r = 0; r < b->rows; r++){
			tmp->m[r][0] = b->m[r][c];
		}

		for(int r = 0; r < b->rows; r++){
			b->m[r][c] = 0;
			for(int ar = 0; ar < a->cols; ar++)
				b->m[r][c] += a->m[r][ar] * tmp->m[ar][0];
			
			// b->m[r][c] = a->m[r][0] * tmp->m[0][0] +
			// a->m[r][1] * tmp->m[1][0] +
			// a->m[r][2] * tmp->m[2][0] +
			// a->m[r][3] * tmp->m[3][0];
		}
	}

	matrix_free(tmp);
	
}
void cstack_translate(double x, double y, double z){

	mat_t* m = cstack_peek();

	if(m->rows != 4 || m->cols != 4){
		printf("In cstack_translate: matrix must have 4 rows and 4 cols!\n");
		return;
	}

	mat_t* tmp = matrix_create(4,4);
	matrix_ident(tmp);

	tmp->m[0][3] = x;
	tmp->m[1][3] = y;
	tmp->m[2][3] = z;

	matrix_mult(m,tmp);
	matrix_copy(m,tmp);

	matrix_free(tmp);
}

void cstack_scale(double x, double y, double z){

	mat_t* m = cstack_peek();

	if(m->rows != 4 || m->cols != 4){
		printf("In matrix_scale: matrix must have 4 rows and 4 cols!\n");
		return;
	}

	mat_t* tmp = matrix_create(4, 4);

	matrix_ident(tmp);

	tmp->m[0][0] = x;
	tmp->m[1][1] = y;
	tmp->m[2][2] = z;

	//matrix_print(m);
	matrix_mult(m,tmp);
	//matrix_print(tmp);
	matrix_copy(m,tmp);

	matrix_free(tmp);
}

void cstack_rotate(int rotType, double theta){

	mat_t* m = cstack_peek();

	if(m->rows != 4 || m->cols != 4){
		printf("In matrix_rotate: matrix must have 4 rows and 4 cols!\n");
		return;
	}

	mat_t* tmp = matrix_create(4,4);

	matrix_ident(tmp);

	switch(rotType){
		case ROTATE_X:

			tmp->m[1][1] = cos(theta);
			tmp->m[1][2] = -1 * sin(theta);
			tmp->m[2][1] = sin(theta);
			tmp->m[2][2] = cos(theta);

			break;

		case ROTATE_Y:

			tmp->m[0][0] = cos(theta);
			tmp->m[2][0] = -1 * sin(theta);
			tmp->m[0][2] = sin(theta);
			tmp->m[2][2] = cos(theta);

			break;

		case ROTATE_Z:

			tmp->m[0][0] = cos(theta);
			tmp->m[0][1] = -1 * sin(theta);
			tmp->m[1][0] = sin(theta);
			tmp->m[1][1] = cos(theta);

			break;
	}

	matrix_mult(m,tmp);
	matrix_copy(m,tmp);

	matrix_free(tmp);
}
void matrix_ident(mat_t* m){

	if(m->rows != 4 || m->cols != 4){
		printf("In cstack_translate: matrix must have 4 rows and 4 cols!\n");
		return;
	}

	for(int r = 0; r < 4; r++){
		for(int c = 0; c < 4; c++){
			if(r == c) m->m[r][c] = 1;
			else m->m[r][c] = 0;
		}
	}

	m->lastcol = 3;
}

void matrix_transform(int transformType){

	switch(transformType){
		case TRANSFORM_POSITION:
			matrix_mult(cstack_peek(),mPoints);
			break;
	}
}

double matrix_det(mat_t* m){
	if(m->rows != m->cols)
		abort_("Error! matrix_det only works with nxn matrices");
	else if(m->rows == 2)
		return (m->m[1][1] * m->m[0][0]) - (m->m[0][1] * m->m[1][0]);
	else {

		double final = 0;

		double sign = 1;
		int tmpRow, tmpCol;

		mat_t* tmp = matrix_create(m->rows-1,m->cols-1);

		for(int topCol = 0; topCol < m->cols; topCol++){

			tmpCol = 0;

			for(int col = 0; col < m->cols; col++){
				if(col != topCol){
					tmpRow = 0;

					for(int row = 1; row < m->rows; row++){

						tmp->m[tmpRow][tmpCol] = m->m[row][col];
						tmpRow++;
					}
					tmpCol++;
				}
				
			}

			final += sign * matrix_det(tmp);
			sign *= -1;

		}

		matrix_free(tmp);
	}
}
// void matrix_minor(mat_t* m);
// void mat_transpose(mat_t* m);
// void matrix_adjugate(mat_t* m);
// void matrix_inverse(mat_t* m);