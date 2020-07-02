#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "geometry.h"
#include "shade.h"
#include "vertex.h"
#include "matrix.h"

#include "utarray.h"

extern mat_t* mPoints;
extern mat_t* mTextures;
extern mat_t* mNormals;

extern UT_array *pQueue;

void shade_geometry(){
	if(mPoints->lastcol > -1){

		polygon_t* p;
		int clipping[3];

		for(int point = 0; point <= mPoints->lastcol;){
			if(mTextures->m[POS_T][point] == SHAPE_TYPE_POLYGON){
				polygon_add(point);
				point+=3;
			} else {
				point++;
			}
		}


		//Here I will also do clipping later.

	}
}