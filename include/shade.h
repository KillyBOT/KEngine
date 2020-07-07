#ifndef SHADE_H
#define SHADE_H

#include "KEngine.h"
#include "matrix.h"
#include "vertex.h"
#include "geometry.h"
#include "fragment.h"

void shade_vertex_all();
void shade_fragment_all();

void shade_geometry();
void shade_vertex_perspective(int p);
void shade_vertex_clipping(int p);

void shade_fragment_all();
void shade_fragment(int x, int y);

void rasterize_all();
void *rasterize_help(void *ptr);
void rasterize_polygon(polygon_t* p);

#endif