%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%union{
	double value;
	char string[512];
}

%token <string> VERTEX TCOORD NORMAL POLYGON NAME OBJECT_DECLARATION SMOOTH_SHADING MTLLIB USEMTL 
%token <string> OBJ_STRING SLASH
%token <value> OBJ_VALUE
%token OBJ_COMMENT

%%

input:
| input command
;

command:

MTLLIB str
{
	printf("This specifies the mtl file\n");
}|

OBJECT_DECLARATION str
{
	printf("This declares an object\n");
}|

OBJECT_DECLARATION val
{
	printf("This declares an object\n");
}|

VERTEX coords
{
	printf("This is a vertex definition\n");
}|

NORMAL coords
{
	printf("This is a normal definition\n");
}|

TCOORD coords
{
	printf("This is a texture coordinate definition\n");
}|

USEMTL str
{
	printf("This specifies the mtl file\n");
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

coords: val val val val
|	val val val
|	val val
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