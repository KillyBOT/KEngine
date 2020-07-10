#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "KEngine.h"
#include "light.h"
#include "vertex.h"
#include "material.h"
#include "texture.h"
#include "fragment.h"

extern UT_array* gLights;
extern Vec4_t* cPos;
extern Vec4_t* vView;

pixel_t* ref_phong(Vec4_t* n, Vec4_t* p, mtl_t* m, double t[2] ){
	pixel_t* cf = (pixel_t*)malloc(sizeof(pixel_t));
	Vec4_t* i = vertex_init(0.0,0.0,0.0);
	Vec4_t *lv,*li;
	Vec4_t *tmp;
	light_t* l = NULL;

	while( (l = (light_t*)utarray_next(gLights,l)) ){

		li = vertex_init(0,0,0);
		lv = vertex_init(0,0,0);

		vertex_copy(li,l->i);
		vertex_copy(lv,l->v);

		if(l->type == LIGHT_AMBIENT){
			tmp = ref_phong_a(li, m, t);
			vertex_add(i, tmp);
			free(tmp);
		}
		else{
			
			if(l->type == LIGHT_POINT){
				vertex_scalar(p, -1);
				vertex_copy(lv, l->v);
				vertex_add(lv,p);
				vertex_scalar(p, -1);
			} 
			else if(l->type == LIGHT_DIRECTIONAL){
				vertex_copy(lv, l->v);
			}

			vertex_normalize(lv);

			tmp = ref_phong_d(lv, li, n, m, t);
			vertex_add(i, tmp);
			free(tmp);

			vertex_scalar(vView, -1);
			tmp = ref_phong_s(lv, li, n, vView, m, t);
			vertex_add(i,tmp);
			vertex_scalar(vView, -1);
			free(tmp);
		}

		free(li);
		free(lv);

	}

	for(int c = 0; c < 3; c++){
		if(i->v[c] > 1.0) i->v[c] = 1.0;
		if(i->v[c] < 0.0) i->v[c] = 0;
		cf->c[c] = (byte_t)(i->v[c] * 255);

	}
	cf->c[COLOR_A] = 255;

	return cf;
}

Vec4_t* ref_phong_a (Vec4_t* li, mtl_t* m, double t[2]){
	Vec4_t* i = vertex_init(0,0,0);

	for(int c = 0; c < 3; c++){
		i->v[c] = m->ka[c] * li->v[c];
	}
	
	return i;
}
Vec4_t* ref_phong_d (Vec4_t* lv, Vec4_t* li, Vec4_t* n, mtl_t* m, double t[2]){
	Vec4_t* i = vertex_init(0,0,0);
	double dot = vertex_dot_product(lv, n);

	for(int c = 0; c < 3; c++){
		i->v[c] = m->kd[c] * li->v[c] * dot;
	}

	return i;
}
Vec4_t* ref_phong_s (Vec4_t* lv, Vec4_t* li, Vec4_t* n, Vec4_t* v, mtl_t* m, double t[2]){
	Vec4_t* i = vertex_init(0,0,0);
	Vec4_t* r = vertex_init(0,0,0);

	vertex_copy(r, n);
	vertex_scalar(r, 2 * vertex_dot_product(lv, n));
	vertex_scalar(lv, -1);
	vertex_add(r, lv);
	vertex_scalar(lv, -1);

	for(int c = 0; c < 3; c++){
		i->v[c] = m->ks[c] * pow(vertex_dot_product(r, v), m->ns) * li->v[c];
	}

	free(r);

	return i;

}