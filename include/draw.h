#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <stdarg.h>
#include <png.h>
#include <jpeglib.h>

#include "KEngine.h"

void print_pixel(pixel_t* p);

void init_frameBuffer();
void clear_frameBuffer();
void set_frameBuffer_random();
void free_frameBuffer();

pixel_t ** frameBuffer;
pixel_t ** frameBuffer_final;

#endif