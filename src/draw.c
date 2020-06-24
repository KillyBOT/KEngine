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
extern int SCREEN_HEIGHT_FINAL;
extern int SCREEN_WIDTH_FINAL;



extern png_structp png_ptr;
extern png_infop info_ptr;

extern png_byte color_type;
extern png_byte bit_depth;

extern png_bytep* row_pointers;

extern pixel_t ** frameBuffer;
extern pixel_t ** frameBuffer_final;

void print_pixel(pixel_t* p){
	printf("R: [%d] G: [%d] B: [%d]\n", p->c[COLOR_R], p->c[COLOR_G], p->c[COLOR_B]);
}

void init_frameBuffers(){

	frameBuffer = (struct pixel_t**)malloc(sizeof(struct pixel_t *) * SCREEN_WIDTH);

	for(int x = 0; x < SCREEN_WIDTH; x++) 
		frameBuffer[x] = (struct pixel_t*)malloc(sizeof(struct pixel_t) * SCREEN_HEIGHT);

	frameBuffer_final = (struct pixel_t**)malloc(sizeof(struct pixel_t *) * SCREEN_WIDTH_FINAL);

	for(int x = 0; x < SCREEN_WIDTH_FINAL; x++) 
		frameBuffer_final[x] = (struct pixel_t*)malloc(sizeof(struct pixel_t) * SCREEN_HEIGHT_FINAL);

	clear_frameBuffers();
}

void clear_frameBuffers(){

	for(int x = 0; x < SCREEN_WIDTH; x++){
		for(int y = 0; y < SCREEN_HEIGHT; y++){
			frameBuffer[x][y].c[COLOR_R] = DEFAULT_COLOR;
			frameBuffer[x][y].c[COLOR_G] = DEFAULT_COLOR;
			frameBuffer[x][y].c[COLOR_B] = DEFAULT_COLOR;
			frameBuffer[x][y].c[COLOR_A] = 255;
		}
	}

	for(int x = 0; x < SCREEN_WIDTH_FINAL; x++){
		for(int y = 0; y < SCREEN_HEIGHT_FINAL; y++){
			frameBuffer_final[x][y].c[COLOR_R] = DEFAULT_COLOR;
			frameBuffer_final[x][y].c[COLOR_G] = DEFAULT_COLOR;
			frameBuffer_final[x][y].c[COLOR_B] = DEFAULT_COLOR;
			frameBuffer_final[x][y].c[COLOR_A] = 255;
		}
	}
}

void set_frameBuffers_random(){

	srand(time(0));

	for(int x = 0; x < SCREEN_WIDTH; x++){
		for(int y = 0; y < SCREEN_HEIGHT; y++){
			frameBuffer[x][y].c[COLOR_R] = (byte)(rand() % 256);
			frameBuffer[x][y].c[COLOR_G] = (byte)(rand() % 256);
			frameBuffer[x][y].c[COLOR_B] = (byte)(rand() % 256);
		}
	}

	for(int x = 0; x < SCREEN_WIDTH_FINAL; x++){
		for(int y = 0; y < SCREEN_HEIGHT_FINAL; y++){
			frameBuffer_final[x][y].c[COLOR_R] = (byte)(rand() % 256);
			frameBuffer_final[x][y].c[COLOR_G] = (byte)(rand() % 256);
			frameBuffer_final[x][y].c[COLOR_B] = (byte)(rand() % 256);
		}
	}
}

void free_frameBuffers(){
	for(int x = 0; x < SCREEN_WIDTH_FINAL; x++){
		free(frameBuffer_final[x]);
	}
	free(frameBuffer_final);

	for(int x = 0; x < SCREEN_WIDTH; x++){
		free(frameBuffer[x]);
	}
	free(frameBuffer);
}

void write_buffer(char* filename){

	png_byte* currentRow;
	png_byte* currentPixel;

	if(row_pointers == NULL){
		row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * SCREEN_HEIGHT_FINAL);

		for(int y = 0; y < SCREEN_HEIGHT_FINAL; y++)
			row_pointers[y] = (png_byte*) malloc(4 * SCREEN_WIDTH_FINAL);
	}

	for(int y = 0; y < SCREEN_HEIGHT_FINAL; y++){
		currentRow = row_pointers[y];
		for(int x = 0; x < SCREEN_WIDTH_FINAL; x++){
			currentPixel = &(currentRow[x*4]);
			//printf("Position: (%d,%d)\t",x,y);
			//print_pixel(&frameBuffer_final[x][y]);

			currentPixel[COLOR_R] = frameBuffer_final[x][y].c[COLOR_R];
			currentPixel[COLOR_G] = frameBuffer_final[x][y].c[COLOR_G];
			currentPixel[COLOR_B] = frameBuffer_final[x][y].c[COLOR_B];
			currentPixel[COLOR_A] = frameBuffer_final[x][y].c[COLOR_A];
		}
	}

	write_png_file(filename);

	for(int y = 0; y < SCREEN_HEIGHT_FINAL; y++)
		free(row_pointers[y]);
	free(row_pointers);

	row_pointers = NULL;
}