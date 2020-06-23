#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <png.h>

#include "KEngine.h"
#include "draw.h"



extern int SCREEN_HEIGHT_FINAL;
extern int SCREEN_WIDTH_FINAL;



extern png_structp png_ptr;
extern png_infop info_ptr;

extern png_byte color_type;
extern png_byte bit_depth;

extern png_bytep* row_pointers;

void write_png_file(char* filename){
	FILE* fp = fopen(filename, "wb");

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

	png_set_IHDR(png_ptr, info_ptr, SCREEN_WIDTH_FINAL, SCREEN_HEIGHT_FINAL,
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
}