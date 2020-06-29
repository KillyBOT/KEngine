#ifndef PARSE_H
#define PARSE_H

#include <png.h>
#include <jpeglib.h>

#include "KEngine.h"

void parse_obj(char* filename);
void parse_mtl(char* filename);

void write_png_file(char* filename);
void read_png_file(char* filename);
GLOBAL(void) write_jpg_file(char* filename);
GLOBAL(void) read_jpg_file(char* filename);

JSAMPLE * jpg_buffer;

int input_width;
int input_height;
pixel_t ** inputBuffer;

#endif