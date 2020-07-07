#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "material.h"
#include "matrix.h"
#include "shade.h"
#include "texture.h"
#include "vertex.h"
#include "light.h"

extern Vec4_t* vPlaneNear;
extern Vec4_t* vPlaneLeft;
extern Vec4_t* vPlaneRight;
extern Vec4_t* vPlaneTop;
extern Vec4_t* vPlaneBot;

extern mat_t* mPoints;
extern mat_t* mNormals;
extern mat_t* mTextures;

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern int CANVAS_WIDTH;
extern int CANVAS_HEIGHT;
extern int CANVAS_DEPTH;

mat_t* mPointsFinal;
mat_t* mNormalsFinal;
mat_t* mTexturesFinal;

void shade_vertex_all(){
	if(mPoints->lastcol > -1){

		//matrix_print(mPoints);
		cstack_apply();
		mPointsFinal = matrix_create(4,mPoints->lastcol+1);
		mNormalsFinal = matrix_create(4,mPointsFinal->cols);
		mTexturesFinal = matrix_create(4,mPointsFinal->cols);
		//matrix_print(mPoints);

		for(int p = 0; p <= mPoints->lastcol;){
			if(mTextures->m[POS_T][p] == SHAPE_TYPE_POLYGON){
				shade_vertex_clipping(p);
				p+=3;
			}


		}

		matrix_copy(mPoints,mPointsFinal);
		matrix_copy(mNormals,mNormalsFinal);
		matrix_copy(mTextures,mTexturesFinal);

		//matrix_print(mPoints);

		for(int p = 0; p <= mPoints->lastcol; p++)
			shade_vertex_perspective(p);

		matrix_free(mPointsFinal);
		matrix_free(mNormalsFinal);
		matrix_free(mTexturesFinal);

	}
}

void shade_vertex_perspective(int p){
	//This is where the prospective projection will happen. I may add other stuff too here that should happen during the initial steps

	Vec4_t* vf = vertex_init(0,0,0);
	Vec4_t* v = matrix_find(mPoints,p);

	vf->v[POS_X] = v->v[POS_X] * (CANVAS_DEPTH / v->v[POS_Z]);
	vf->v[POS_Y] = v->v[POS_Y] * (CANVAS_DEPTH / v->v[POS_Z]);
	vf->v[POS_Z] = v->v[POS_Z];

	vf->v[POS_X] *= SCREEN_WIDTH / CANVAS_WIDTH;
	vf->v[POS_Y] *= SCREEN_HEIGHT / CANVAS_HEIGHT;

	matrix_set_point(mPoints,p,vf);

	free(vf);
	free(v);
}

void shade_vertex_clipping(int p){
	Vec4_t *v[3];
	Vec4_t *vn[3];
	Vec4_t *vt[3];
	Vec4_t *vPlanes[5];
	Vec4_t *vTemp, *vnTemp, *vtTemp;
	int inside, outside;
	double d[3][5];

	double t;
	int n;

	int inPlanes[3][5];
	int insideFull[3];

	for(n = 0; n < 3; n++){
		v[n] = matrix_find(mPoints,p+n);
		vn[n] = matrix_find(mNormals,p+n);
		vt[n] = matrix_find(mTextures,p+n);

		d[n][0] = -CANVAS_DEPTH;
		d[n][1] = 0;
		d[n][2] = 0;
		d[n][3] = 0;
		d[n][4] = 0;
	}

	vPlanes[0] = vPlaneNear;
	vPlanes[1] = vPlaneLeft;
	vPlanes[2] = vPlaneRight;
	vPlanes[3] = vPlaneTop;
	vPlanes[4] = vPlaneBot;

	for(n = 0; n < 3; n++){

		insideFull[n] = 1;

		for(int m = 0; m < 5; m++){
			inPlanes[n][m] = (vertex_dot_product(v[n], vPlanes[m]) + d[n][m]) >= 0;
			insideFull[n] = insideFull[n] && inPlanes[n][m];
		}

	}

	// vertex_print(v[0]);
	// vertex_print(v[1]);
	// vertex_print(v[2]);
	// for(n = 0; n < 3; n++){
	// 	for(int m = 0; m < 5; m++) printf("%d ", inPlanes[n][m]);
	// 	printf("\n");
	// }
	// printf("\n");

	if(insideFull[0] || insideFull[1] || insideFull[2]){

		if(insideFull[0] + insideFull[1] + insideFull[2] == 1){ //One vertex inside
			// printf("\n");
			printf("One inside\n");
			if(insideFull[0]) inside = 0;
			if(insideFull[1]) inside = 1;
			if(insideFull[2]) inside = 2;
			// printf("Inside %d\n\t", inside);
			// vertex_print(v[inside]);


			for(int plane = 0; plane < 5; plane++){

				for(n = 0; n < 3; n++){

					if(n != inside && !inPlanes[n][plane]){

						//printf("Plane %d\t Vertex %d\n", plane,n);

						vTemp = vertex_init(0,0,0);
						vertex_copy(vTemp,v[n]);
						vertex_scalar(v[inside],-1.0);
						vertex_add(vTemp,v[inside]); // Current - Inside
						vertex_scalar(v[inside],-1.0);

						t = (-d[n][plane] - vertex_dot_product(vPlanes[plane],v[inside])) / vertex_dot_product(vPlanes[plane],vTemp);
						//printf("%lf\n", t);

						free(vTemp);

						vTemp = vertex_lerp(v[inside],v[n],t);
						vtTemp = vertex_lerp(vt[inside],vt[n],t);
						vnTemp = vertex_lerp(vn[inside],vn[n],t);

						// vertex_print(v[inside]);
						// vertex_print(v[n]);
						// vertex_print(vTemp);

						vertex_copy(v[n],vTemp);
						vertex_copy(vn[n],vnTemp);
						vertex_copy(vt[n],vtTemp);

						free(vTemp);
						free(vnTemp);
						free(vtTemp);

					}
				}
			}

			// printf("Final:\n");
			// vertex_print(v[0]);
			// vertex_print(v[1]);
			// vertex_print(v[2]);
		}

		for(n = 0; n < 3; n++){
			matrix_add_point(mPointsFinal,v[n]);
			matrix_add_point(mNormalsFinal,vn[n]);
			matrix_add_point(mTexturesFinal,vt[n]);
		}
	}
	//printf("\n");

	for(n = 0; n < 3; n++){
		free(v[n]);
		free(vn[n]);
		free(vt[n]);
	}
	

	
}