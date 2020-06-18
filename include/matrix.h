#ifndef MATRIX_H
#define MATRIX_H

typedef struct matrix {
	double ** m;
	int rows;
	int cols;
	int lastcol;
} matrix;

#endif