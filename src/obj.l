%{
#include "obj.tab.h"
%}

%%

[ \t\n ]+ ;

\/ {
	//printf("[%s] is a SLASH\n",obj_yytext);
	return SLASH;
}

#.* {
	//printf("[%s] is a OBJ_COMMENT\n",obj_yytext);
	return OBJ_COMMENT;
}

mtllib {
	//printf("[%s] is an MTLLIB\n",obj_yytext);
	return MTLLIB;
}


v {
	//printf("[%s] is a VERTEX\n",obj_yytext);
	return VERTEX;
}

vt {
	//printf("[%s] is a TCOORD\n",obj_yytext);
	return TCOORD;
}

vn {
	//printf("[%s] is a NORMAL\n",obj_yytext);
	return NORMAL;
}

f {
	//printf("[%s] is a POLYGON\n",obj_yytext);
	return POLYGON;
}

o {
	//printf("[%s] is an OBJECT_DECLARATION\n",obj_yytext);
	return OBJECT_DECLARATION;
}

s {
	//printf("[%s] is a SMOOTH_SHADING\n",obj_yytext);
	return SMOOTH_SHADING;
}

usemtl {
	//printf("[%s] is a USEMTL\n",obj_yytext);
	return USEMTL;
}

\-?[0-9]+\.[0-9]* |
\-?[0-9]*\.[0-9]+ |
\-?[0-9]+ {
	//printf("[%s] is a OBJ_VALUE\n",obj_yytext);
	obj_yylval.value = atof(obj_yytext);
	return OBJ_VALUE;
}

[a-zA-Z][\.a-zA-Z0-9_]* {
	//printf("[%s] is a OBJ_STRING\n",obj_yytext);
	strcpy(obj_yylval.string, obj_yytext);
	return OBJ_STRING;
}

.

%%