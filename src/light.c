#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "KEngine.h"
#include "light.h"
#include "vertex.h"

pixel_t* pixel_lerp(pixel_t* p1, pixel_t* p2, double t){
	pixel_t* p = (pixel_t*)malloc(sizeof(pixel_t));

	for(int c = 0; c < 4; c++){
		p->c[c] = (p1->c[c] * (1 - t)) + (p2->c[c] * t);
	}

	return p;
}
double double_lerp(double d0, double d1, double t){
	return (d0 * (1 - t)) + (d1 * t);
}

void pixel_print(pixel_t* p){
	printf("R: [%d]\tG: [%d]\tB: [%d]\tA: [%d]\n", (int)p->c[COLOR_R], (int)p->c[COLOR_G], (int)p->c[COLOR_B], (int)p->c[COLOR_A]);
}