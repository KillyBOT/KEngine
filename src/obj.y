%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "material.h"
#include "vertex.h"
#include "matrix.h"
#include "parse.h"

#include "mtl.tab.h"

extern mat_t* mPoints;
extern mat_t* mTextures;
extern mat_t* mNormals;

extern mtl_t* gMaterials;

extern FILE* mtl_yyin;

int currentMatID = 0;
Vec4_t vTemp;
char finalName[512];

%}

%union{
	double value;
	char string[512];
}

%token <string> VERTEX TCOORD NORMAL POLYGON NAME OBJECT_DECLARATION OBJECT_GROUP SMOOTH_SHADING MTLLIB USEMTL 
%token <string> OBJ_STRING SLASH
%token <value> OBJ_VALUE
%token OBJ_COMMENT

%%

input:
| input command
;

command:

MTLLIB OBJ_STRING
{
	printf("This specifies the mtl file\n");
	strcpy(finalName,"../wavefront/");
	strcat(finalName,$2);
	mtl_yyin = fopen(finalName, "r");
	mtl_yyparse();
}|

OBJECT_DECLARATION str
{
	//printf("This declares an object\n");
}|

OBJECT_DECLARATION val
{
	//printf("This declares an object\n");
}|

OBJECT_GROUP str
{

}|

OBJECT_GROUP val
{

}|

VERTEX coords
{
	printf("This is a vertex definition\n");
	matrix_add_point(mPoints,&vTemp);

}|

NORMAL coords
{
	printf("This is a normal definition\n");
	matrix_add_point(mNormals,&vTemp);
}|

TCOORD coords
{
	printf("This is a texture coordinate definition\n");
	matrix_add_point(mNormals,&vTemp);
}|

USEMTL OBJ_STRING
{
	printf("This specifies the mtl file\n");
	currentMatID = material_find($2);
}|

SMOOTH_SHADING val
{
	printf("This specifies the smooth shading group\n");
}|

POLYGON rectangle
{
	printf("This is a rectangle polygon\n");
}|

POLYGON triangle
{
	printf("This is a triangle polygon\n");
}|

OBJ_COMMENT
{
	printf("This is a comment\n");
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

rectangle: vtn vtn vtn vtn
| vn vn vn vn
| vt vt vt vt
| val val val val
;

triangle: vtn vtn vtn
| vn vn vn
| vt vt vt
| val val val
;


vt: val SLASH val
;

vn: val SLASH SLASH val
;

vtn: val SLASH val SLASH val
;

str: OBJ_STRING
{
	printf("String value: [%s]\n",$1);
}
;

val: OBJ_VALUE
{
	printf("Double or location value: [%.3lf]\n",$1);
};

%%

int obj_yyerror(char *s){
	fprintf(stderr,"YYERROR: %s\n",s);
	return 0;
}

int obj_yywrap(){
	return 1;
}