#ifndef MATERIAL_H
#define MATERIAL_H

#include "KEngine.h"
#include "texture.h"

typedef struct material {
	char *name;
	double k[3][3];// Ambient, diffuse, and specular components
	double ns; //Specular exponent
	double d; //Also maybe Tr
	double ni; //Optical density
	int iModel; //Illumination model
	texture *map_ka; //Ambient texture map
	texture *map_kd; //Diffuse texture map
	texture *map_ks; //Specular texture map
	texture *map_ns; //Specular highlight map
	texture *map_d; //Alpha texture map
	texture *map_bump; //Bump texture map
} material;

#endif