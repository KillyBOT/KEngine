#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "KEngine.h"
#include "process.h"
#include "draw.h"



extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH_FINAL;
extern int SCREEN_HEIGHT_FINAL;



extern pixel_t ** frameBuffer;
extern pixel_t ** frameBuffer_final;



void mxaa(int depth){

	int finalColor[3];

	int logDepth = (int)(log(depth)/log(2));

	for(int x = 0; x < SCREEN_WIDTH_FINAL; x++){
		for(int y = 0; y < SCREEN_HEIGHT_FINAL; y++){

			finalColor[0] = 0;
			finalColor[1] = 0;
			finalColor[2] = 0;

			for(int px = 0; px < logDepth; px++){
				for(int py = 0; py < logDepth; py++){
					
					for(int c = 0; c < 3; c++)
						finalColor[c] += (int)frameBuffer[ (x * (logDepth)) + px][(y * (logDepth)) + py].c[c];
					
				}
			}

			for(int c = 0; c < 3; c++){
				finalColor[c] /= depth;
				frameBuffer_final[x][y].c[c] = (byte)finalColor[c];
			}
	
		}
	}
}