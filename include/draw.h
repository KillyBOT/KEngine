#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <stdarg.h>
#include <png.h>
#include <jpeglib.h>

#include "KEngine.h"

void print_pixel(pixel_t* p);

void init_frameBuffers();
void clear_frameBuffers();
void set_frameBuffers_random();
void free_frameBuffers();
void write_buffer(char* filename);
void write_png_file(char* filename);
void read_png_file(char* filename);
GLOBAL(void) write_jpg_file(char* filename);
GLOBAL(void) read_jpg_file(char* filename);

png_structp png_ptr;
png_infop info_ptr;

png_byte color_type;
png_byte bit_depth;
png_bytep *row_pointers;
int pass_num;

JSAMPLE * jpg_buffer;

int input_width;
int input_height;
pixel_t ** inputBuffer;

pixel_t ** frameBuffer;
pixel_t ** frameBuffer_final;

#endif