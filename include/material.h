#ifndef MATERIAL_H
#define MATERIAL_H

#include "KEngine.h"
#include "texture.h"
#include "uthash.h"

typedef struct {
	char *name;
	double k[3][3];// Ambient, diffuse, and specular components
	double ns; //Specular exponent
	double d; //Also maybe Tr
	double ni; //Optical density
	int iModel; //Illumination model
	tex_t *map_ka; //Ambient texture map
	tex_t *map_kd; //Diffuse texture map
	tex_t *map_ks; //Specular texture map
	tex_t *map_ns; //Specular highlight map
	tex_t *map_d; //Alpha texture map
	tex_t *map_bump; //Bump texture map
	UT_hash_handle hh;
} mtl_t;

mtl_t *gMaterials;

void material_add(char* name);
void material_delete(char* name);
void material_delete_all();
mtl_t* material_find(char* name);
void material_print(char* name);
void material_print_all();

#endif