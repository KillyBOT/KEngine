%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "material.h"
#include "vertex.h"
#include "matrix.h"
#include "parse.h"
#include "shape.h"

#include "mtl.tab.h"

extern mat_t* mPoints;
extern mat_t* mTextures;
extern mat_t* mNormals;

extern mat_t* mPointsToAdd;
extern mat_t* mTexturesToAdd;
extern mat_t* mNormalsToAdd;

extern mtl_t* gMaterials;

extern FILE* mtl_yyin;

int currentMatID = 0;
int makeNormals = 0;
Vec4_t vTemp;
Vec4_t pTemp;
Vec4_t tTemp;
Vec4_t nTemp;
char finalName[512];

%}

%union{
	double value;
	char string[512];
}

%token <string> VERTEX TCOORD NORMAL POLYGON NAME OBJECT_DECLARATION OBJECT_GROUP SMOOTH_SHADING MTLLIB USEMTL 
%token <string> OBJ_STRING OBJ_STRING_LONG SLASH 
%token <value> OBJ_VALUE
%token OBJ_COMMENT

%%

input:
| input command
;

command:

MTLLIB OBJ_STRING
{
	//printf("This specifies the mtl file\n");
	strcpy(finalName,"../wavefront/");
	strcat(finalName,$2);
	mtl_yyin = fopen(finalName, "r");
	mtl_yyparse();
}|

OBJECT_DECLARATION str
{
	////printf("This declares an object\n");
}|

OBJECT_DECLARATION OBJ_VALUE
{
	////printf("This declares an object\n");
}|

OBJECT_GROUP str
{

}|

OBJECT_GROUP OBJ_VALUE
{

}|

VERTEX coords
{
	//printf("This is a vertex definition\n");
	matrix_add_point(mPointsToAdd,&vTemp);

}|

NORMAL coords
{
	//printf("This is a normal definition\n");
	matrix_add_point(mNormalsToAdd,&vTemp);
}|

TCOORD coords
{
	//printf("This is a texture coordinate definition\n");
	matrix_add_point(mTexturesToAdd,&vTemp);
}|

USEMTL OBJ_STRING
{
	//printf("This specifies the mtl file\n");
	////printf("%s\n",$2);
	currentMatID = material_find($2)->id;
}|

SMOOTH_SHADING OBJ_VALUE
{
	//printf("This specifies the smooth shading group\n");
}|

POLYGON polygon
{
	//printf("This is a polygon\n");

	if(mPointsTemp->lastcol >= 2){

		for(int n = 1; n < mPointsTemp->lastcol; n++){
			matrix_add_matrix_point(mPoints,mPointsTemp,0);
			matrix_add_matrix_point(mPoints,mPointsTemp,n);
			matrix_add_matrix_point(mPoints,mPointsTemp,n+1);

			matrix_add_matrix_point(mTextures,mTexturesTemp,0);
			mTextures->m[POS_T][mTextures->lastcol] = SHAPE_TYPE_POLYGON;
			matrix_add_matrix_point(mTextures,mTexturesTemp,n);
			mTextures->m[POS_T][mTextures->lastcol] = SHAPE_TYPE_POLYGON;
			matrix_add_matrix_point(mTextures,mTexturesTemp,n+1);
			mTextures->m[POS_T][mTextures->lastcol] = SHAPE_TYPE_POLYGON;

			if(!makeNormals){
				matrix_add_matrix_point(mNormals,mNormalsTemp,0);
				matrix_add_matrix_point(mNormals,mNormalsTemp,n);
				matrix_add_matrix_point(mNormals,mNormalsTemp,n+1);
			}
		}

	}

	mPointsTemp->lastcol = -1;
	mTexturesTemp->lastcol = -1;
	mNormalsTemp->lastcol = -1;
}|

OBJ_COMMENT
{
	//printf("This is a comment\n");
}
;

coords: OBJ_VALUE OBJ_VALUE OBJ_VALUE OBJ_VALUE
{
	vTemp.v[0] = $1;
	vTemp.v[1] = $2;
	vTemp.v[2] = $3;
	vTemp.v[3] = $4;
}
|	OBJ_VALUE OBJ_VALUE OBJ_VALUE
{
	vTemp.v[0] = $1;
	vTemp.v[1] = $2;
	vTemp.v[2] = $3;
	vTemp.v[3] = 1;
}
|	OBJ_VALUE OBJ_VALUE
{
	vTemp.v[0] = $1;
	vTemp.v[1] = $2;
	vTemp.v[2] = (double)currentMatID;
	vTemp.v[3] = 1;
}
;

polygon:
| vtn polygon
| vn polygon
| vt polygon
| v polygon
;


vt: OBJ_VALUE SLASH OBJ_VALUE
{
	makeNormals = 1;

	matrix_add_matrix_point(mPointsTemp,mPointsToAdd,(int)$1);
	matrix_add_matrix_point(mTexturesTemp,mTexturesToAdd,(int)$3);
}
;

vn: OBJ_VALUE SLASH SLASH OBJ_VALUE
{

	makeNormals = 0;

	matrix_add_matrix_point(mPointsTemp,mPointsToAdd,(int)$1);
	matrix_add_matrix_point(mTexturesTemp,mTexturesToAdd,0);
	matrix_add_matrix_point(mNormalsTemp,mNormalsToAdd,(int)$4);
}
;

vtn: OBJ_VALUE SLASH OBJ_VALUE SLASH OBJ_VALUE
{

	makeNormals = 0;

	matrix_add_matrix_point(mPointsTemp,mPointsToAdd,(int)$1);
	matrix_add_matrix_point(mTexturesTemp,mTexturesToAdd,(int)$3);
	matrix_add_matrix_point(mNormalsTemp,mNormalsToAdd,(int)$5);
}
;

v: OBJ_VALUE
{

	makeNormals = 1;

	matrix_add_matrix_point(mPointsTemp,mPointsToAdd,(int)$1);
	matrix_add_matrix_point(mTexturesTemp,mTexturesToAdd,0);
}
;

str: OBJ_STRING
{
	//printf("String OBJ_VALUEue: [%s]\n",$1);
}
;

%%

int obj_yyerror(char *s){
	fprintf(stderr,"YYERROR: %s\n",s);
	return 0;
}

int obj_yywrap(){
	return 1;
}