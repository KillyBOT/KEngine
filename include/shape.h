#ifndef SHAPE_H
#define SHAPE_H

#include "KEngine.h"
#include "vertex.h"
#include "matrix.h"

#define STEP_3D 30
#define STEP_3D_1 30

void shape_sphere(double x, double y, double z, double r);
void shape_box(double x, double y, double z, double w, double h, double d);
void shape_cylinder(double x, double y, double z, double r, double h);
void shape_cone(double x, double y, double z, double r, double h);
void shape_pyramid(double x, double y, double z, int s, double h);
void generate_normals();

#endif