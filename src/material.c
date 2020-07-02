#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "texture.h"
#include "uthash.h"
#include "material.h"

extern mtl_t* gMaterials;
extern mtlID_t* gMaterialsID;
extern int toAddID;

void material_add(char* name){
	if(material_find(name) == NULL){
		mtl_t* m = (mtl_t*)malloc(sizeof(mtl_t));
		mtlID_t* mID = (mtlID_t*)malloc(sizeof(mtlID_t));

		m->name = (char*)malloc(sizeof(char) * 512);
		strcpy(m->name,name);

		mID->name = (char*)malloc(sizeof(char) * 512);
		strcpy(mID->name,name);

		m->id = toAddID;
		mID->id = toAddID;
		toAddID++;

		for(int n = 0; n < 3; n++){
			m->ka[n] = 0;
			m->kd[n] = 0;
			m->ks[n] = 0;
		}

		m->ns = 0;
		m->d = 1;
		m->ni = 1;
		m->iModel = 2;

		m->map_ka = NULL;
		m->map_kd = NULL;
		m->map_ks = NULL;
		m->map_ns = NULL;
		m->map_d = NULL;
		m->map_bump = NULL;
		m->map_disp = NULL;
		m->map_decal = NULL;
		m->map_refl = NULL;

		HASH_ADD_KEYPTR(hh, gMaterials, m->name, strlen(m->name), m);
		HASH_ADD_INT(gMaterialsID, id, mID);
	}
}

void material_delete(char* name){
	mtl_t* m = material_find(name);
	mtlID_t* mID;
	if(m == NULL) return;

	HASH_FIND_INT(gMaterialsID,&m->id,mID);

	HASH_DEL(gMaterials,m);
	HASH_DEL(gMaterials,mID);

	free(mID->name);
	free(mID);

	free(m->name);
	free(m);
}

void material_delete_all(){
	mtl_t* m, *tmp;
	mtlID_t* mID, *tmpID;

	HASH_ITER(hh, gMaterialsID,mID,tmpID){
		HASH_DEL(gMaterialsID,mID);
		free(mID->name);
		free(mID);
	}

	HASH_ITER(hh, gMaterials,m,tmp){
		HASH_DEL(gMaterials,m);

		free(m->name);
		free(m);
	}

	
}

mtl_t* material_find(char* name){
	mtl_t* m;

	HASH_FIND_STR(gMaterials,name,m);
	if(m == NULL) HASH_FIND_STR(gMaterials,"Default",m);
	return m;
}

mtl_t* material_find_id(int id){
	mtlID_t* mID;

	HASH_FIND_INT(gMaterialsID,&id,mID);
	if(mID != NULL)
		return material_find(mID->name);
	else
		return NULL;
}
void material_print(char* name){
	mtl_t* m = material_find(name);
	printf("Material #%d\t[%s]\n\n", m->id,m->name);
	printf("Ka: [%.2lf]\t[%.2lf]\t[%.2lf]\n", m->ka[0], m->ka[1], m->ka[2]);
	printf("Kd: [%.2lf]\t[%.2lf]\t[%.2lf]\n", m->kd[0], m->kd[1], m->kd[2]);
	printf("Ks: [%.2lf]\t[%.2lf]\t[%.2lf]\n", m->ks[0], m->ks[1], m->ks[2]);
	printf("Ns: [%.2lf]\n", m->ns);
	printf("d: [%.2lf]\n", m->d);
	printf("Ni: [%.2lf]\n", m->ni);
	printf("Illumination model: [%d]\n", m->iModel);
	if(m->map_ka != NULL)printf("map_Ka: [%s]\n", m->map_ka->name);
	if(m->map_kd != NULL)printf("map_Kd: [%s]\n", m->map_kd->name);
	if(m->map_ks != NULL)printf("map_Ks: [%s]\n", m->map_ks->name);
	if(m->map_ns != NULL)printf("map_Ns: [%s]\n", m->map_ns->name);
	if(m->map_d != NULL)printf("map_d: [%s]\n", m->map_d->name);
	if(m->map_bump != NULL)printf("map_Bump: [%s]\n", m->map_bump->name);
	if(m->map_disp != NULL)printf("map_Disp: [%s]\n", m->map_disp->name);
	if(m->map_decal != NULL)printf("map_Decal: [%s]\n", m->map_decal->name);
	if(m->map_refl != NULL)printf("map_Refl: [%s]\n", m->map_refl->name);
	printf("\n");
}
void material_print_all(){
	mtl_t* m, *tmp;

	HASH_ITER(hh, gMaterials, m, tmp){
		printf("Material #%d\t[%s]\n\n", m->id,m->name);
		printf("Ka: [%.2lf]\t[%.2lf]\t[%.2lf]\n", m->ka[0], m->ka[1], m->ka[2]);
		printf("Kd: [%.2lf]\t[%.2lf]\t[%.2lf]\n", m->kd[0], m->kd[1], m->kd[2]);
		printf("Ks: [%.2lf]\t[%.2lf]\t[%.2lf]\n", m->ks[0], m->ks[1], m->ks[2]);
		printf("Ns: [%.2lf]\n", m->ns);
		printf("d: [%.2lf]\n", m->d);
		printf("Ni: [%.2lf]\n", m->ni);
		printf("Illumination model: [%d]\n", m->iModel);
		if(m->map_ka != NULL)printf("map_Ka: [%s]\n", m->map_ka->name);
		if(m->map_kd != NULL)printf("map_Kd: [%s]\n", m->map_kd->name);
		if(m->map_ks != NULL)printf("map_Ks: [%s]\n", m->map_ks->name);
		if(m->map_ns != NULL)printf("map_Ns: [%s]\n", m->map_ns->name);
		if(m->map_d != NULL)printf("map_d: [%s]\n", m->map_d->name);
		if(m->map_bump != NULL)printf("map_Bump: [%s]\n", m->map_bump->name);
		if(m->map_disp != NULL)printf("map_Disp: [%s]\n", m->map_disp->name);
		if(m->map_decal != NULL)printf("map_Decal: [%s]\n", m->map_decal->name);
		if(m->map_refl != NULL)printf("map_Refl: [%s]\n", m->map_refl->name);
		printf("\n");
	}
}
