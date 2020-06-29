#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "texture.h"
#include "uthash.h"
#include "parse.h"

extern tex_t* gTextures;

extern int input_width;
extern int input_height;
extern pixel_t** inputBuffer;

void texture_add(char* name){
	tex_t* t = (tex_t*)malloc(sizeof(tex_t));

	char finalName[512];

	strcpy(finalName, "../wavefront/");
	strcat(finalName, name);

	t->name = (char*)malloc(sizeof(char) * 512);
	strcpy(t->name,finalName);

	read_jpg_file(finalName);

	t->width = input_width;
	t->height = input_height;

	//TODO: acoomodate for all those flags that were talked about earlier

	t->data = (pixel_t**)malloc(sizeof(pixel_t*) * input_width);
	for(int w = 0; w < input_width; w++)
		t->data[w] = (pixel_t*)malloc(sizeof(pixel_t) * input_height);

	for(int w = 0; w < input_width; w++){
		for(int h = 0; h < input_height; h++){
			for(int c = 0; c < 4; c++){
				t->data[w][h].c[c] = inputBuffer[w][h].c[c];
			}
		}
	}

	HASH_ADD_KEYPTR(hh, gTextures, t->name, strlen(t->name),t);
}

void texture_delete(char* name){
	tex_t* t;

	t = texture_find(name);

	HASH_DEL(gTextures,t);
	free(t->name);
	for(int w = 0; w < t->width; w++)
		free(t->data[w]);
	free(t->data);
}

void texture_delete_all(){
	tex_t* t, *tmp;

	HASH_ITER(hh, gTextures, t, tmp){
		HASH_DEL(gTextures,t);
		free(t->name);
		for(int w = 0; w < t->width; w++)
			free(t->data[w]);
		free(t->data);
	}
}
tex_t* texture_find(char* name){
	tex_t* t;
	char finalName[512];

	strcpy(finalName,"../wavefront/");
	strcat(finalName,name);

	HASH_FIND_STR(gTextures,finalName,t);
	//if(t == NULL) printf("Texture [%s] could not be found!\n", name);
	return t;
}

void texture_print(char* name){
	tex_t* t;

	t = texture_find(name);

	printf("Texture\t[%s]\n", t->name);
	printf("Dimensions:\t[%d] x [%d]\n", t->width, t->height);
	printf("\n");
}
void texture_print_all(){
	tex_t* t, *tmp;

	HASH_ITER(hh, gTextures, t, tmp){
		printf("Texture\t[%s]\n", t->name);
		printf("Dimensions:\t[%d] x [%d]\n", t->width, t->height);
		printf("\n");
	}
}