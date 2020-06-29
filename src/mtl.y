%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%union {
	double value;
	char string[512];
}

%token <value> MTL_VALUE
%token <string> MTL_COMMENT MTL_STRING
%token <string> NEWMTL KA KD KS NS D TR NI ILLUM
%token <string> MAP_KA MAP_KD MAP_KS MAP_NS MAP_D BUMP DISP DECAL REFL
%token <string> _BLENDU _BLENDV _BOOST _MM _GAIN_VALUE _O _S _T _TEXRES _CLAMP _BM _IMFCHAN _TYPE

%%

input:
| input command
;

command:

MTL_COMMENT 
{}
|

NEWMTL str
{
	printf("Specifying a new material\n\n");
}
|

KA val val val
{
	printf("Specifying ambient reflection constants\n\n");
}
|

KD val val val
{
	printf("Specifying diffuse reflection constants\n\n");
}
|

KS val val val
{
	printf("Specifying specular reflection constants\n\n");
}
|

NS val
{
	printf("Specifying specular exponent\n\n");
}
|

D val
{
	printf("Specifying opaqueness\n\n");
}
|

TR val
{
	printf("Specifying transparency\n\n");
}
|

NI val
{
	printf("Specifying optical density\n\n");
}
|

ILLUM val
{
	printf("Specifying illumination model\n\n");
}
|

MAP_KA argument str
{
	printf("Specifying ambient texture\n\n");
}
|

MAP_KD argument str
{
	printf("Specifying diffuse texture\n\n");
}
|

MAP_KS argument str
{
	printf("Specifying specular texture\n\n");
}
|

MAP_NS argument str
{
	printf("Specifying specular highlight component\n\n");
}
|

MAP_D argument str
{
	printf("Specifying alpha texture\n\n");
}
|

BUMP argument str
{
	printf("Specifying bump map\n\n");
}
|

DISP argument str
{
	printf("Specifying displacement map\n\n");
}
|

DECAL argument str
{
	printf("Specifying decal texture\n\n");
}
|

REFL argument str
{
	printf("Specifying reflection map\n\n");
}
|

str
{}
|

val
{}

;

argument: 
| _blendu argument
| _blendv argument
| _boost argument
| _mm argument
| _o argument
| _s argument
| _t argument
| _texres argument
| _clamp argument
| _bm argument
| _imfchan
| _type
;

_blendu: _BLENDU str
{
	printf("Specifying horizontal texture blending (default on)\n\n");
}
;

_blendv: _BLENDV str
{
	printf("Specifying vertical texture blending (default on)\n\n");
}
;

_boost: _BOOST val
{
	printf("Modifying mip-map sharpness\n\n");
}
;

_mm: _MM val val
{
	printf("Modifying texture map values (default 0 1)\n\n");
}
;

_o: _O val{
	printf("Specifying origin offset\n\n");
}
| _O val val{
	printf("Specifying origin offset\n\n");
}
| _O val val val{
	printf("Specifying origin offset\n\n");
}
;

_s: _S val{
	printf("Specifying scale\n\n");
}
| _S val val{
	printf("Specifying scale\n\n");
}
| _S val val val{
	printf("Specifying scale\n\n");
}
;

_t: _T val{
	printf("Specifying texture turbulence\n\n");
}
| _T val val{
	printf("Specifying texture turbulence\n\n");
}
| _T val val val{
	printf("Specifying texture turbulence\n\n");
}
;

_texres: _TEXRES val {
	printf("Specifying texture resolution to create\n\n");
}
;

_clamp: _CLAMP str {
	printf("Specifying clamp; can texture coords go past 0-1 (default off)\n\n");
}
;

_bm: _BM val {
	printf("Specifying bump multiplier (should only be used with bump maps)\n\n");
}
;

_imfchan: _IMFCHAN str {
	printf("Specifying which channel is used to create the scalar or bump texture\n\n");
}
;

_type: _TYPE str {
	printf("Specifying which reflection model to use");
}
;

str: MTL_STRING
{
	printf("String value: [%s]\n",$1);
}
;

val: MTL_VALUE
{
	printf("Double value: [%.3lf]\n",$1);
};	

%%

int mtl_yyerror(char *s){
	fprintf(stderr, "YYERROR: %s\n\n",s);
	return 0;
}

int mtl_yywrap(){
	return 1;
}