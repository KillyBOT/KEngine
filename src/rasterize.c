#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "KEngine.h"
#include "shade.h"
#include "geometry.h"
#include "vertex.h"
#include "material.h"
#include "texture.h"
#include "fragment.h"
#include "light.h"

#include "utarray.h"

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

extern UT_array *pQueue;
extern UT_array ***fArray;

pthread_mutex_t fArray_mutex[THREAD_NUM];
pthread_mutex_t mutex_init = PTHREAD_MUTEX_INITIALIZER;

void rasterize_all(){
	pthread_t threadID[THREAD_NUM];
	int threadNumTable[THREAD_NUM];

	for(int n = 0; n < THREAD_NUM; n++){
		pthread_mutex_init(&fArray_mutex[n],NULL);
	}

	for(int n = 0; n < THREAD_NUM; n++){
		threadNumTable[n] = n;
		pthread_create( &threadID[n], NULL, rasterize_help, &threadNumTable[n]);
	}

	for(int n = 0; n < THREAD_NUM; n++){
		pthread_join(threadID[n],NULL);
	}

}

void *rasterize_help(void* ptr){

	Vec4_t *top, *mid, *bot;
	Vec4_t *topN, *midN, *botN;
	pixel_t *topC, *midC, *botC;
	double topU, midU, botU;
	double topV, midV, botV;
	double x0, x1;
	double z0, z1, zf;
	double u0, u1, v0, v1;
	double y0, y1, y2;
	int x0f, x1f, xTemp;
	double z0f, z1f, zTemp;
	double u0f, u1f, v0f, v1f, uTemp, vTemp;
	Vec4_t *n0f, *n1f, *nTemp;
	pixel_t *c0f, *c1f, *cTemp;
	int d0, d1, d2;
	Vec4_t *n0, *n1;
	pixel_t *c0, *c1;
	int x, y;
	double t0, t1, t2, dt0, dt1, dt2;
	int groups[THREAD_NUM];
	int phase;

	int flip, lineDirection;
	double xCompare, yCompare;
	int gXT, gYT, gXM, gYM, gXB, gYB;

	int pStart, pEnd, threadNum;
	double pIncrease;

	polygon_t* p;
	frag_t* f;

	pIncrease = ((double)utarray_len(pQueue))/(double)THREAD_NUM;
	threadNum = (*((int*)ptr));

	pStart = (int)((double)threadNum * pIncrease);
	pEnd = (int)((double)(threadNum+1) * pIncrease);

	xCompare = 0;
	yCompare = 0;

	//printf("%d %d %d\n", pStart, pEnd, threadNum);

	for(int point = pStart; point < pEnd; point++){

		//pthread_mutex_lock(&test_mutex);

		p = (polygon_t*)utarray_eltptr(pQueue,point);

		top = p->p[POLYGON_TOP];
		mid = p->p[POLYGON_MID];
		bot = p->p[POLYGON_BOT];

		topN = p->n[POLYGON_TOP];
		midN = p->n[POLYGON_MID];
		botN = p->n[POLYGON_BOT];

		topC = p->c[POLYGON_TOP];
		midC = p->c[POLYGON_MID];
		botC = p->c[POLYGON_BOT];

		topU = p->t[POLYGON_TOP][TEXTURE_U];
		midU = p->t[POLYGON_MID][TEXTURE_U];
		botU = p->t[POLYGON_BOT][TEXTURE_U];

		topV = p->t[POLYGON_TOP][TEXTURE_V];
		midV = p->t[POLYGON_MID][TEXTURE_V];
		botV = p->t[POLYGON_BOT][TEXTURE_V];

		flip = 0;
		t0 = 0;
		t1 = 0;
		y = (int)vertex_element(bot,POS_Y);

		d0 = (int)(vertex_element(top,POS_Y) - vertex_element(bot,POS_Y)) + 1;
		d1 = (int)(vertex_element(mid,POS_Y) - vertex_element(bot,POS_Y)) + 1;
		d2 = (int)(vertex_element(top,POS_Y) - vertex_element(mid,POS_Y)) + 1;

		dt0 = 1.0 / (double)d0;
		dt1 = 1.0 / (double)d1;

		for(int n = 0; n < THREAD_NUM; n++)
			groups[n] = 0;

		gXT = (vertex_element(top,POS_X) > xCompare) ? 1 : 0;
		gYT = (vertex_element(top,POS_Y) > yCompare) ? 1 : 0;
		gXM = (vertex_element(mid,POS_X) > xCompare) ? 1 : 0;
		gYM = (vertex_element(mid,POS_Y) > yCompare) ? 1 : 0;
		gXB = (vertex_element(bot,POS_X) > xCompare) ? 1 : 0;
		gYB = (vertex_element(bot,POS_Y) > yCompare) ? 1 : 0;

		if((gXT && gYT) || (gXM && gYM) || (gXB && gYB)) groups[3] = 1;
		if((!gXT && !gYT) || (!gXM && !gYM) || (!gXB && !gYB)) groups[0] = 1;

		if((!gXT && gYT) || (!gXM && gYM) || (!gXB && gYB)) groups[2] = 1;
		if((gXT && !gYT) || (gXM && !gYM) || (gXB && !gYB)) groups[1] = 1;

		pthread_mutex_lock(&mutex_init);

		// vertex_print(top);
		// vertex_print(mid);
		// vertex_print(bot);
		// printf("%d %d %d %lf %lf\n", d0, d1, d2, dt0, dt1);
		// printf("%d %d %d %d\n", groups[0], groups[1], groups[2], groups[3]);
		// printf("\n");

		for(int n = 0; n < THREAD_NUM; n++){
			if(groups[n]) pthread_mutex_lock(&fArray_mutex[n]);
		}

		pthread_mutex_unlock(&mutex_init);

		while(y <= (int)vertex_element(top,POS_Y)){
			if(!flip && y >= vertex_element(mid,POS_Y)){
				t1 = 0;
				dt1 = 1.0 / (double)d2;
				flip = 1;
			}

			x0 = double_lerp(vertex_element(bot,POS_X), vertex_element(top,POS_X), t0);
			z0 = double_lerp(vertex_element(bot,POS_Z), vertex_element(top,POS_Z), t0);
			n0 = vertex_lerp(botN,topN,t0);
			c0 = pixel_lerp(botC,topC,t0);
			u0 = double_lerp(botU, topU, t0);
			v0 = double_lerp(botV, topV, t0);

			if(flip){
				x1 = double_lerp(vertex_element(mid,POS_X),vertex_element(top,POS_X), t1);
				z1 = double_lerp(vertex_element(mid,POS_Z),vertex_element(top,POS_Z), t1);
				n1 = vertex_lerp(midN,topN,t1);
				c1 = pixel_lerp(midC,topC,t1);//
				u1 = double_lerp(midU, topU, t1);
				v1 = double_lerp(midV, topV, t1);
			} else {
				x1 = double_lerp(vertex_element(bot,POS_X),vertex_element(mid,POS_X), t1);
				z1 = double_lerp(vertex_element(bot,POS_Z),vertex_element(mid,POS_Z), t1);
				n1 = vertex_lerp(botN,midN,t1);
				c1 = pixel_lerp(botC,midC,t1);
				u1 = double_lerp(botU, midU, t1);
				v1 = double_lerp(botV, midV, t1);
			}

			x0f = (int)x0;
			x1f = (int)x1;
			z0f = z0;
			z1f = z1;
			u0f = u0;
			u1f = u1;
			v0f = v0;
			v1f = v1;

			n0f = vertex_init(0,0,0);
			vertex_copy(n0f,n0);
			n1f = vertex_init(0,0,0);
			vertex_copy(n1f,n1);

			c0f = (pixel_t*)malloc(sizeof(pixel_t));
			for(int c = 0; c < 4; c++) 
				c0f->c[c] = c0->c[c];

			c1f = (pixel_t*)malloc(sizeof(pixel_t));
			for(int c = 0; c < 4; c++)
				c1f->c[c] = c1->c[c];


			if(x0f > x1f){
				xTemp = x0f;
				zTemp = z0f;
				uTemp = u0f;
				vTemp = v0f;
				nTemp = vertex_init(0,0,0);
				vertex_copy(nTemp,n0f);
				cTemp = (pixel_t*)malloc(sizeof(pixel_t));
				for(int c = 0; c < 4; c++)
					cTemp->c[c] = c0f->c[c];

				x0f = x1f;
				z0f = z1f;
				u0f = u1f;
				v0f = v1f;
				vertex_copy(n0f,n1f);
				for(int c = 0; c < 4; c++)
					c0f->c[c] = c1f->c[c];

				x1f = xTemp;
				z1f = zTemp;
				u1f = uTemp;
				v1f = vTemp;
				vertex_copy(n1f,nTemp);
				for(int c = 0; c < 4; c++){
					c1f->c[c] = cTemp->c[c];
				}

				free(nTemp);
				free(cTemp);
			}

			t2 = 0;
			dt2 = 1.0 / (x1f - x0f + 1);

			//pthread_mutex_lock(&fArray_mutex);

			for(x = x0f; x <= x1f; x++){

				f = frag_init(x,y,double_lerp(z0f,z1f,t2));

				f->n = vertex_lerp(n0f,n1f,t2);
				f->c = pixel_lerp(c0f,c1f,t2);

				//pthread_mutex_lock(&fArray_mutex);

				//pthread_mutex_lock(&fArray_mutex);
				frag_add(f);
				//pthread_mutex_unlock(&fArray_mutex);

				//pthread_mutex_unlock(&fArray_mutex);

				t2 += dt2;
			}

			free(n0f);
			free(n1f);
			free(c0f);
			free(c1f);

			//pthread_mutex_unlock(&fArray_mutex);

			t0 += dt0;
			t1 += dt1;
			y++;

			free(n0);
			free(n1);
			free(c0);
			free(c1);
		}

		//pthread_mutex_lock(&mutex_init);

		for(int n = 0; n < THREAD_NUM; n++){
			if(groups[n])pthread_mutex_unlock(&fArray_mutex[n]);
		}
		//pthread_mutex_unlock(&mutex_init);

	}
}

// void rasterize_polygon(polygon_t* p){
// 	double x0, x1;
// 	double z0, z1;
// 	double y0, y1, y2;
// 	double dx0, dx1;
// 	double dz0, dz1;
// 	Vec4_t* n0, n1;
// 	Vec4_t* dn0, dn1;
// 	int y;

// 	int flip = 0;

// 	x0 = p->p[POLYGON_BOT]->v[POS_X];
// 	x1 = x0;
// 	z0 = p->p[POLYGON_BOT]->v[POS_Z];
// 	z1 = z0;
// 	y = (int)p->p[POLYGON_BOT]->v[POS_Y];
// }