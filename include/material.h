#ifndef MATERIAL_H
#define MATERIAL_H

typedef struct material {
	double ref_k[3][3];
	double ns;
} material;

#endif