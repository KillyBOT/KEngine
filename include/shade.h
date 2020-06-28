#ifndef SHADE_H
#define SHADE_H

#include "KEngine.h"
#include "matrix.h"
#include "vertex.h"
#include "geometry.h"
#include "fragment.h"

void shade_vertex_all();
void shade_geometry_all();
void shade_fragment_all();

void shade_vertex(Vec4_t* v, int type);
void shade_geometry(Vec4_t* p, Vec4_t* n, Vec4_t* t);
void shade_fragment(frag_t* f);

void rasterize_all();
void rasterize_polygon(polygon_t* p);

#endif