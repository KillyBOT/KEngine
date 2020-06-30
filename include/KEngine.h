#ifndef KENGINE_H
#define KENGINE_H

// #define SCREEN_WIDTH_FINAL 640
// #define SCREEN_HEIGHT_FINAL 480
// #define SCREEN_WIDTH 2560
// #define SCREEN_HEIGHT 1920

#define VTYPE_POLYGON 0
#define VTYPE_LINE 1

#define POS_X 0
#define POS_Y 1
#define POS_Z 2
#define POS_T 3

#define COLOR_R 0
#define COLOR_G 1
#define COLOR_B 2
#define COLOR_A 3

#define DEFAULT_COLOR 50

#define LIGHT_POS 0
#define LIGHT_COLOR 1

#define ROTATE_X 0
#define ROTATE_Y 1
#define ROTATE_Z 2

#define VERTEX_POSITION 0
#define VERTEX_NORMAL 1
#define VERTEX_TEXTURE 2

#define SHAPE_TYPE_POLYGON 0
#define SHAPE_TYPE_LINE 1

#define POLYGON_TOP 0
#define POLYGON_MID 1
#define POLYGON_BOT 2

#define LINE_START 0
#define LINE_END 1

#define TEXTURE_U 0
#define TEXTURE_V 1

#define MATERIAL_KA 0
#define MATERIAL_KD 1
#define MATERIAL_KS 2

#define SHADE_FLAT 0
#define SHADE_PHONG 1
#define SHADE_GOURAUD 2
#define SHADE_WIREFRAME 3

typedef unsigned char byte_t;
typedef double coord_t;

typedef struct pixel_t {
	byte_t c[4];
} pixel_t;

void abort_(const char* s, ...);

int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int SCREEN_WIDTH_FINAL;
int SCREEN_HEIGHT_FINAL;

#endif