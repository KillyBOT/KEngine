%{
#include <stdio.h>
#include "mtl.tab.h"
%}

%%

[\t\n ]+ ;

#.* {
	return COMMENT;
}

newmtl {
	//printf("[%s] is a NEWMTL\n",yytext);
	return NEWMTL;
}

Ka {
	//printf("[%s] is a KA\n",yytext);
	return KA;
}

Kd {
	//printf("[%s] is a KD\n",yytext);
	return KD;
}

Ks {
	//printf("[%s] is a KS\n",yytext);
	return KS;
}

Ns {
	//printf("[%s] is an NS\n",yytext);
	return NS;
}

d {
	//printf("[%s] is a D\n",yytext);
	return D;
}

Tr {
	//printf("[%s] is a TR\n",yytext);
	return TR;
}

Ni {
	//printf("[%s] is an NI\n",yytext);
	return NI;
}

illum {
	//printf("[%s] is an ILLUM\n",yytext);
	return ILLUM;
}

map_Ka {
	//printf("[%s] is a MAP_KA\n",yytext);
	return MAP_KA;
}

map_Kd {
	//printf("[%s] is a MAP_KD\n",yytext);
	return MAP_KD;
}

map_Ks {
	//printf("[%s] is a MAP_KS\n",yytext);
	return MAP_KS;
}

map_Ns {
	//printf("[%s] is a MAP_NS\n",yytext);
	return MAP_NS;
}

map_d {
	//printf("[%s] is a MAP_D\n",yytext);
	return MAP_D;
}

map_Bump |
bump {
	//printf("[%s] is a BUMP\n",yytext);
	return BUMP;
}

disp {
	//printf("[%s] is a DISP\n",yytext);
	return DISP;
}

decal {
	//printf("[%s] is a DECAL\n",yytext);
	return DECAL;
}

refl {
	//printf("[%s] is a REFL\n",yytext);
	return REFL;
}

\-blendu {
	//printf("[%s] is a _BLENDU\n",yytext);
	return _BLENDU;
}

\-blendv {
	//printf("[%s] is a _BLENDV\n",yytext);
	return _BLENDV;
}

\-boost {
	//printf("[%s] is a _BOOST\n",yytext);
	return _BOOST;
}

\-mm {
	//printf("[%s] is an _MM\n",yytext);
	return _MM;
}

\-o {
	//printf("[%s] is an _O\n",yytext);
	return _O;
}

\-s {
	//printf("[%s] is an _S\n",yytext);
	return _S;
}

\-t {
	//printf("[%s] is an _T\n",yytext);
	return _T;
}

\-texres {
	//printf("[%s] is a _TEXRES\n",yytext);
	return _TEXRES;
}

\-clamp {
	//printf("[%s] is a _CLAMP\n",yytext);
	return _CLAMP;
}

\-bm {
	//printf("[%s] is a _BM\n",yytext);
	return _BM;
}

\-imfchan {
	//printf("[%s] is an _IMFCHAN\n",yytext);
	return _IMFCHAN;
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
	strcpy(yylval.string,yytext);
	return STRING;
}

%%