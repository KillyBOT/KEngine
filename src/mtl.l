%{
#include <stdio.h>
#include "mtl.tab.h"
%}

%%

[\t\n ]+ ;

#.* {
	return MTL_COMMENT;
}

newmtl {
	//printf("[%s] is a NEWMTL\n",mtl_yytext);
	return NEWMTL;
}

Ka {
	//printf("[%s] is a KA\n",mtl_yytext);
	return KA;
}

Kd {
	//printf("[%s] is a KD\n",mtl_yytext);
	return KD;
}

Ks {
	//printf("[%s] is a KS\n",mtl_yytext);
	return KS;
}

Ns {
	//printf("[%s] is an NS\n",mtl_yytext);
	return NS;
}

d {
	//printf("[%s] is a D\n",mtl_yytext);
	return D;
}

Tr {
	//printf("[%s] is a TR\n",mtl_yytext);
	return TR;
}

Ni {
	//printf("[%s] is an NI\n",mtl_yytext);
	return NI;
}

illum {
	//printf("[%s] is an ILLUM\n",mtl_yytext);
	return ILLUM;
}

map_Ka {
	//printf("[%s] is a MAP_KA\n",mtl_yytext);
	return MAP_KA;
}

map_Kd {
	//printf("[%s] is a MAP_KD\n",mtl_yytext);
	return MAP_KD;
}

map_Ks {
	//printf("[%s] is a MAP_KS\n",mtl_yytext);
	return MAP_KS;
}

map_Ns {
	//printf("[%s] is a MAP_NS\n",mtl_yytext);
	return MAP_NS;
}

map_d {
	//printf("[%s] is a MAP_D\n",mtl_yytext);
	return MAP_D;
}

map_Bump |
bump {
	//printf("[%s] is a BUMP\n",mtl_yytext);
	return BUMP;
}

disp {
	//printf("[%s] is a DISP\n",mtl_yytext);
	return DISP;
}

decal {
	//printf("[%s] is a DECAL\n",mtl_yytext);
	return DECAL;
}

refl {
	//printf("[%s] is a REFL\n",mtl_yytext);
	return REFL;
}

\-blendu {
	//printf("[%s] is a _BLENDU\n",mtl_yytext);
	return _BLENDU;
}

\-blendv {
	//printf("[%s] is a _BLENDV\n",mtl_yytext);
	return _BLENDV;
}

\-boost {
	//printf("[%s] is a _BOOST\n",mtl_yytext);
	return _BOOST;
}

\-mm {
	//printf("[%s] is an _MM\n",mtl_yytext);
	return _MM;
}

\-o {
	//printf("[%s] is an _O\n",mtl_yytext);
	return _O;
}

\-s {
	//printf("[%s] is an _S\n",mtl_yytext);
	return _S;
}

\-t {
	//printf("[%s] is an _T\n",mtl_yytext);
	return _T;
}

\-texres {
	//printf("[%s] is a _TEXRES\n",mtl_yytext);
	return _TEXRES;
}

\-clamp {
	//printf("[%s] is a _CLAMP\n",mtl_yytext);
	return _CLAMP;
}

\-bm {
	//printf("[%s] is a _BM\n",mtl_yytext);
	return _BM;
}

\-imfchan {
	//printf("[%s] is an _IMFCHAN\n",mtl_yytext);
	return _IMFCHAN;
}

\-?[0-9]+\.[0-9]* |
\-?[0-9]*\.[0-9]+ |
\-?[0-9]+ {
	//printf("[%s] is a MTL_VALUE\n",mtl_yytext);
	mtl_yylval.value = atof(mtl_yytext);
	return MTL_VALUE;
}

[a-zA-Z][\.a-zA-Z0-9_]* {
	//printf("[%s] is a MTL_STRING\n",mtl_yytext);
	strcpy(mtl_yylval.string,mtl_yytext);
	return MTL_STRING;
}

%%