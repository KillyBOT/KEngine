#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "KEngine.h"
#include "process.h"
#include "draw.h"



extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern int MSAA_ENABLED;
extern int MSAA_DEPTH;
extern int MSAA_DEPTH_LOG;
extern pixel_t ** frameBuffer;



void msaa(){

	int finalColor[3];
	pixel_t ** frameBuffer_tmp;
	int SCREEN_WIDTH_FINAL;
	int SCREEN_HEIGHT_FINAL;

	if(!MSAA_ENABLED || MSAA_DEPTH % 2 != 0 || MSAA_DEPTH <= 2) return;
	else{

		SCREEN_WIDTH_FINAL = SCREEN_WIDTH / MSAA_DEPTH_LOG;
		SCREEN_HEIGHT_FINAL = SCREEN_HEIGHT / MSAA_DEPTH_LOG;

		frameBuffer_tmp = (pixel_t**)malloc(sizeof(pixel_t*) * (SCREEN_WIDTH_FINAL));
		for(int x = 0; x < SCREEN_WIDTH/MSAA_DEPTH_LOG; x++)
			frameBuffer_tmp[x] = (pixel_t*)malloc(sizeof(pixel_t*) * (SCREEN_HEIGHT_FINAL));

		for(int x = 0; x < SCREEN_WIDTH_FINAL; x++){
			for(int y = 0; y < SCREEN_HEIGHT_FINAL; y++){

				finalColor[0] = 0;
				finalColor[1] = 0;
				finalColor[2] = 0;

				for(int px = 0; px < MSAA_DEPTH_LOG; px++){
					for(int py = 0; py < MSAA_DEPTH_LOG; py++){
						
						for(int c = 0; c < 3; c++)
							finalColor[c] += (int)frameBuffer[ (x * (MSAA_DEPTH_LOG)) + px][(y * (MSAA_DEPTH_LOG)) + py].c[c];
						
					}
				}

				for(int c = 0; c < 3; c++){
					finalColor[c] /= MSAA_DEPTH;
					if(finalColor[c] > 255) finalColor[c] = 255;
					if(finalColor[c] < 0) finalColor[c] = 0;
					frameBuffer_tmp[x][y].c[c] = (byte_t)finalColor[c];
				}
				frameBuffer_tmp[x][y].c[COLOR_A] = 255;
		
			}
		}

		free_frameBuffer();

		SCREEN_WIDTH = SCREEN_WIDTH_FINAL;
		SCREEN_HEIGHT = SCREEN_HEIGHT_FINAL;

		init_frameBuffer();

		//printf("%ld %ld %d\n",sizeof(frameBuffer),sizeof(frameBuffer)/sizeof(pixel_t*), SCREEN_WIDTH);


		for(int w = 0; w < SCREEN_WIDTH; w++){

			for(int h = 0; h < SCREEN_HEIGHT; h++){
				for(int c = 0; c < 4; c++)
					frameBuffer[w][h].c[c] = frameBuffer_tmp[w][h].c[c];
			}
		}

		for(int w = 0; w < SCREEN_WIDTH; w++)
			free(frameBuffer_tmp[w]);
		free(frameBuffer_tmp);

	}

	
}

