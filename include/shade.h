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
void shade_vertex(Vec4_t* v);
void shade_fragment(frag_t* f);

void rasterize_all();
void *rasterize_help(void *ptr);
void rasterize_polygon(polygon_t* p);

#endif