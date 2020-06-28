%{
#include "obj.tab.h"
%}

%%

[ \t\n ]+ ;

\/ {
	//printf("[%s] is a SLASH\n",yytext);
	return SLASH;
}

#.* {
	//printf("[%s] is a COMMENT\n",yytext);
	return COMMENT;
}

mtllib {
	//printf("[%s] is an MTLLIB\n",yytext);
	return MTLLIB;
}


v {
	//printf("[%s] is a VERTEX\n",yytext);
	return VERTEX;
}

vt {
	//printf("[%s] is a TCOORD\n",yytext);
	return TCOORD;
}

vn {
	//printf("[%s] is a NORMAL\n",yytext);
	return NORMAL;
}

f {
	//printf("[%s] is a POLYGON\n",yytext);
	return POLYGON;
}

o {
	//printf("[%s] is an OBJECT_DECLARATION\n",yytext);
	return OBJECT_DECLARATION;
}

s {
	//printf("[%s] is a SMOOTH_SHADING\n",yytext);
	return SMOOTH_SHADING;
}

usemtl {
	//printf("[%s] is a USEMTL\n",yytext);
	return USEMTL;
}

\-?[0-9]+\.[0-9]* |
\-?[0-9]*\.[0-9]+ |
\-?[0-9]+ {
	//printf("[%s] is a VALUE\n",yytext);
	yylval.value = atof(yytext);
	return VALUE;
}

[a-zA-Z][\.a-zA-Z0-9_]* {
	//printf("[%s] is a STRING\n",yytext);
	strcpy(yylval.string, yytext);
	return STRING;
}

.

%%