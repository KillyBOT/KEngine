#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <png.h>
#include <time.h>

#include "KEngine.h"
#include "draw.h"



extern int SCREEN_HEIGHT;
extern int SCREEN_WIDTH;

extern int input_width;
extern int input_height;

extern pixel_t ** inputBuffer;
extern pixel_t ** frameBuffer;
extern pixel_t ** frameBuffer_final;

extern int MSAA_DEPTH;
extern int MSAA_DEPTH_LOG;

void print_pixel(pixel_t* p){
	printf("R: [%d] G: [%d] B: [%d]\n", p->c[COLOR_R], p->c[COLOR_G], p->c[COLOR_B]);
}

void init_frameBuffer(){

	//printf("%d %d\n", SCREEN_WIDTH, SCREEN_HEIGHT);

	frameBuffer = (pixel_t**)malloc(sizeof(pixel_t *) * SCREEN_WIDTH);

	for(int x = 0; x < SCREEN_WIDTH; x++) 
		frameBuffer[x] = (pixel_t*)malloc(sizeof(pixel_t) * SCREEN_HEIGHT);

	inputBuffer = NULL;

	clear_frameBuffer();
}

void clear_frameBuffer(){

	for(int x = 0; x < SCREEN_WIDTH; x++){
		for(int y = 0; y < SCREEN_HEIGHT; y++){
			frameBuffer[x][y].c[COLOR_R] = DEFAULT_COLOR;
			frameBuffer[x][y].c[COLOR_G] = DEFAULT_COLOR;
			frameBuffer[x][y].c[COLOR_B] = DEFAULT_COLOR;
			frameBuffer[x][y].c[COLOR_A] = 255;
		}
	}
}

void set_frameBuffer_random(){

	srand(time(0));

	for(int x = 0; x < SCREEN_WIDTH; x++){
		for(int y = 0; y < SCREEN_HEIGHT; y++){
			frameBuffer[x][y].c[COLOR_R] = (byte_t)(rand() % 256);
			frameBuffer[x][y].c[COLOR_G] = (byte_t)(rand() % 256);
			frameBuffer[x][y].c[COLOR_B] = (byte_t)(rand() % 256);
		}
	}
}

void free_frameBuffer(){
	for(int x = 0; x < SCREEN_WIDTH; x++){
		free(frameBuffer[x]);
	}
	free(frameBuffer);

	if(inputBuffer != NULL){
		for(int x = 0; x < input_width; x++){
			free(inputBuffer[x]);
		}
		free(inputBuffer);
	}
}