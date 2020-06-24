#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "matrix.h"
#include "vertex.h"
#include "shape.h"

extern mat_t* mPoints;
extern mat_t* mNormals;
extern mat_t* mTextures;

void shape_box(double x, double y, double z, double w, double h, double d){
	Vec4_t* v1;
	Vec4_t* v2;
	Vec4_t* v3;
	Vec4_t* v4;
	Vec4_t* v5;
	Vec4_t* v6;
	Vec4_t* v7;
	Vec4_t* v8;

	v1 = vertex_init(x,y,z);
	v2 = vertex_init(x+w,y,z);
	v3 = vertex_init(x,y+h,z);
	v4 = vertex_init(x+w,y+h,z);
	v5 = vertex_init(x,y,z+d);
	v6 = vertex_init(x+w,y,z+d);
	v7 = vertex_init(x,y+h,z+d);
	v8 = vertex_init(x+w,y+h,z+d);



	matrix_add_point(mPoints,v1);
	matrix_add_point(mPoints,v3);
	matrix_add_point(mPoints,v2);

	matrix_add_point(mPoints,v3);
	matrix_add_point(mPoints,v4);
	matrix_add_point(mPoints,v2);



	matrix_add_point(mPoints,v6);
	matrix_add_point(mPoints,v8);
	matrix_add_point(mPoints,v5);

	matrix_add_point(mPoints,v8);
	matrix_add_point(mPoints,v7);
	matrix_add_point(mPoints,v5);



	matrix_add_point(mPoints,v7);
	matrix_add_point(mPoints,v8);
	matrix_add_point(mPoints,v3);

	matrix_add_point(mPoints,v8);
	matrix_add_point(mPoints,v4);
	matrix_add_point(mPoints,v3);



	matrix_add_point(mPoints,v7);
	matrix_add_point(mPoints,v3);
	matrix_add_point(mPoints,v5);

	matrix_add_point(mPoints,v3);
	matrix_add_point(mPoints,v1);
	matrix_add_point(mPoints,v5);



	matrix_add_point(mPoints,v4);
	matrix_add_point(mPoints,v8);
	matrix_add_point(mPoints,v2);

	matrix_add_point(mPoints,v8);
	matrix_add_point(mPoints,v6);
	matrix_add_point(mPoints,v2);



	matrix_add_point(mPoints,v1);
	matrix_add_point(mPoints,v1);
	matrix_add_point(mPoints,v1);

	matrix_add_point(mPoints,v1);
	matrix_add_point(mPoints,v1);
	matrix_add_point(mPoints,v1);

	vertex_free(v1);
	vertex_free(v2);
	vertex_free(v3);
	vertex_free(v4);
	vertex_free(v5);
	vertex_free(v6);
	vertex_free(v7);
	vertex_free(v8);
}
