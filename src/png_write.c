#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <png.h>

#include "KEngine.h"
#include "parse.h"
#include "draw.h"



extern pixel_t** frameBuffer;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;



void write_png_file(char* filename){

	png_byte* currentRow;
	png_byte* currentPixel;
	FILE* fp;

	png_structp png_ptr;
	png_infop info_ptr;

	png_byte color_type = PNG_COLOR_TYPE_RGBA;
	png_byte bit_depth = 8;

	png_bytep* row_pointers;

	row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * SCREEN_HEIGHT);

	for(int y = 0; y < SCREEN_HEIGHT; y++)
		row_pointers[y] = (png_byte*) malloc(4 * SCREEN_WIDTH);

	for(int y = 0; y < SCREEN_HEIGHT; y++){
		currentRow = row_pointers[y];
		for(int x = 0; x < SCREEN_WIDTH; x++){
			currentPixel = &(currentRow[x*4]);
			//printf("Position: (%d,%d)\t",x,y);
			//print_pixel(&frameBuffer_final[x][y]);

			currentPixel[COLOR_R] = frameBuffer[x][y].c[COLOR_R];
			currentPixel[COLOR_G] = frameBuffer[x][y].c[COLOR_G];
			currentPixel[COLOR_B] = frameBuffer[x][y].c[COLOR_B];
			currentPixel[COLOR_A] = frameBuffer[x][y].c[COLOR_A];
		}
	}

	fp = fopen(filename, "wb");

	if(!fp) 
		abort_("File %s could not be opened for writing!", filename);

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png_ptr)
		abort_("png_create_write_struct failed!");

	info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr)
		abort_("png_create_info_struct failed!");

	if(setjmp(png_jmpbuf(png_ptr)))
		abort_("Error during init_io!");

	png_init_io(png_ptr, fp);

	png_set_IHDR(png_ptr, info_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
	bit_depth, color_type, PNG_INTERLACE_NONE,
	PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE	);

	png_write_info(png_ptr, info_ptr);

	if(setjmp(png_jmpbuf(png_ptr)))
		abort_("Error during writing bytes!");

	png_write_image(png_ptr, row_pointers);

	if(setjmp(png_jmpbuf(png_ptr)))
		abort_("Error during end of write!");

	png_write_end(png_ptr, NULL);

	fclose(fp);

	for(int y = 0; y < SCREEN_HEIGHT; y++)
		free(row_pointers[y]);
	free(row_pointers);
}