#ifndef KENGINE_H
#define KENGINE_H

#define SCREEN_WIDTH_FINAL 640
#define SCREEN_HEIGHT_FINAL 480
#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1920

#define POS_X 0
#define POS_Y 1
#define POS_Z 2

#define COLOR_R 0
#define COLOR_G 1
#define COLOR_B 2

#define MATERIAL_KA 0
#define MATERIAL_KD 1
#define MATERIAL_KS 2

typedef unsigned char byte;
typedef double coord;

typedef struct pixel {
	byte c[3];
} pixel;

#endif