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
Vec4_t* planes[5];

void shade_vertex_all(){
	if(mPoints->lastcol > -1){

		planes[0] = vPlaneNear;
		planes[1] = vPlaneLeft;
		planes[2] = vPlaneRight;
		planes[3] = vPlaneTop;
		planes[4] = vPlaneBot;

		//matrix_print(mPoints);
		cstack_apply();
		//matrix_print(mPoints);

		for(int plane = 0; plane < 5; plane++){
			mPointsFinal = matrix_create(4,mPoints->lastcol+1);
			mNormalsFinal = matrix_create(4,mPointsFinal->cols);
			mTexturesFinal = matrix_create(4,mPointsFinal->cols);

			for(int p = 0; p <= mPoints->lastcol;){
				if(mTextures->m[POS_T][p] == SHAPE_TYPE_POLYGON){
					shade_vertex_clipping(p, planes[plane]);
					p+=3;
				}

			}

			matrix_copy(mPoints,mPointsFinal);
			matrix_copy(mNormals,mNormalsFinal);
			matrix_copy(mTextures,mTexturesFinal);

			matrix_free(mPointsFinal);
			matrix_free(mNormalsFinal);
			matrix_free(mTexturesFinal);
		}
		

		

		//matrix_print(mPoints);

		for(int p = 0; p <= mPoints->lastcol; p++)
			shade_vertex_perspective(p);

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
	vf->v[POS_Z] = 1 / vf->v[POS_Z];

	matrix_set_point(mPoints,p,vf);

	free(vf);
	free(v);
}

void shade_vertex_clipping(int p, Vec4_t* plane){
	Vec4_t *v[3];
	Vec4_t *vn[3];
	Vec4_t *vt[3];
	Vec4_t *vTemp, *vnTemp, *vtTemp;
	int inside, outside;
	double d;

	double t;
	int n;

	int vInside[3];

	for(n = 0; n < 3; n++){
		v[n] = matrix_find(mPoints,p+n);
		vn[n] = matrix_find(mNormals,p+n);
		vt[n] = matrix_find(mTextures,p+n);

		if(plane == vPlaneNear) d = -CANVAS_DEPTH;
		else d = 0;
	}

	for(n = 0; n < 3; n++){

		vInside[n] = vertex_dot_product(v[n], plane) + d >= 0;

	}

	// vertex_print(v[0]);
	// vertex_print(v[1]);
	// vertex_print(v[2]);
	// for(n = 0; n < 3; n++){
	// 	for(int m = 0; m < 5; m++) printf("%d ", inPlanes[n][m]);
	// 	printf("\n");
	// }
	// printf("\n");

	if(vInside[0] || vInside[1] || vInside[2]){

		if(vInside[0] + vInside[1] + vInside[2] == 1){ //One vertex inside

			//printf("One inside\n");
			if(vInside[0]) inside = 0;
			else if(vInside[1]) inside = 1;
			else if(vInside[2]) inside = 2;
			// printf("Inside %d\n\t", inside);
			// vertex_print(v[inside]);


			for(n = 0; n < 3; n++){

				if(n != inside){

					//printf("Plane %d\t Vertex %d\n", plane,n);

					vTemp = vertex_init(0,0,0);
					vertex_copy(vTemp,v[n]);
					vertex_scalar(v[inside],-1.0);
					vertex_add(vTemp,v[inside]); // Current - Inside
					vertex_scalar(v[inside],-1.0);

					t = (-d - vertex_dot_product(plane,v[inside])) / vertex_dot_product(plane,vTemp);
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

			// printf("Final:\n");
			// vertex_print(v[0]);
			// vertex_print(v[1]);
			// vertex_print(v[2]);

			for(n = 0; n < 3; n++){
				matrix_add_point(mPointsFinal,v[n]);
				matrix_add_point(mNormalsFinal,vn[n]);
				matrix_add_point(mTexturesFinal,vt[n]);
			}
		}

		else if(vInside[0] + vInside[1] + vInside[2] == 2){ //Two vertices inside

			//printf("Two inside\n");
			if(!vInside[0]) outside = 0;
			else if(!vInside[1]) outside = 1;
			else if(!vInside[2]) outside = 2;

			int a, b, c;
			Vec4_t *bTemp, *btTemp, *bnTemp;

			c = outside;
			if(outside == 2) a = 0;
			else a = c + 1;
			if(outside == 0) b = 2;
			else b = c - 1;

			vTemp = vertex_init(0,0,0);
			vertex_copy(vTemp,v[c]);
			vertex_scalar(v[b],-1.0);
			vertex_add(vTemp,v[b]); // Current - Inside
			vertex_scalar(v[b],-1.0);

			t = (-d - vertex_dot_product(plane,v[b])) / vertex_dot_product(plane,vTemp);
			//printf("%lf\n", t);

			free(vTemp);

			bTemp = vertex_lerp(v[b], v[c], t);
			btTemp = vertex_lerp(vt[b], vt[c], t);
			bnTemp = vertex_lerp(vn[b], vn[c], t);

			matrix_add_point(mPointsFinal,v[b]);
			matrix_add_point(mNormalsFinal,vn[b]);
			matrix_add_point(mTexturesFinal,vt[b]);

			matrix_add_point(mPointsFinal,bTemp);
			matrix_add_point(mNormalsFinal,bnTemp);
			matrix_add_point(mTexturesFinal,btTemp);

			matrix_add_point(mPointsFinal,v[a]);
			matrix_add_point(mNormalsFinal,vn[a]);
			matrix_add_point(mTexturesFinal,vt[a]);



			vTemp = vertex_init(0,0,0);
			vertex_copy(vTemp,v[c]);
			vertex_scalar(v[a],-1.0);
			vertex_add(vTemp,v[a]); // Current - Inside
			vertex_scalar(v[a],-1.0);

			t = (-d - vertex_dot_product(plane,v[a])) / vertex_dot_product(plane,vTemp);
			//printf("%lf\n", t);

			free(vTemp);

			vTemp = vertex_lerp(v[a], v[c], t);
			vtTemp = vertex_lerp(vt[a], vt[c], t);
			vnTemp = vertex_lerp(vn[a], vn[c], t);

			matrix_add_point(mPointsFinal,bTemp);
			matrix_add_point(mNormalsFinal,bnTemp);
			matrix_add_point(mTexturesFinal,btTemp);

			matrix_add_point(mPointsFinal,vTemp);
			matrix_add_point(mNormalsFinal,vnTemp);
			matrix_add_point(mTexturesFinal,vtTemp);

			matrix_add_point(mPointsFinal,v[a]);
			matrix_add_point(mNormalsFinal,vn[a]);
			matrix_add_point(mTexturesFinal,vt[a]);

			free(vTemp);
			free(vtTemp);
			free(vnTemp);
			free(bTemp);
			free(btTemp);
			free(bnTemp);


		} else {
			for(n = 0; n < 3; n++){
				matrix_add_point(mPointsFinal,v[n]);
				matrix_add_point(mNormalsFinal,vn[n]);
				matrix_add_point(mTexturesFinal,vt[n]);
			}
		}

	}
	//printf("\n");

	for(n = 0; n < 3; n++){
		free(v[n]);
		free(vn[n]);
		free(vt[n]);
	}
	

	
}