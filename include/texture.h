#ifndef TEXTURE_H
#define TEXTURE_H

#include "KEngine.h"
#include "uthash.h"

typedef struct {
	char *name;
	pixel_t **data;
	UT_hash_handle hh;
} tex_t;

tex_t *gTextures;

void texture_add(char* name);
void texture_delete(char* name);
void texture_delete_all();
tex_t* texture_find(char* name);
void texture_print(char* name);
void texture_print_all();

#endif