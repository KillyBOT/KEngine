%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KEngine.h"
#include "material.h"
#include "texture.h"

extern mtl_t* gMaterials;
extern mtlID_t* gMaterialsID;
extern tex_t* gTextures;

mtl_t* currentMat;
tex_t* currentTex;
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

NEWMTL MTL_STRING
{
	printf("Specifying a new material\n\n");
	material_add($2);
	currentMat = material_find($2);
}
|

KA MTL_VALUE MTL_VALUE MTL_VALUE
{
	printf("Specifying ambient reflection constants\n\n");
	currentMat->ka[COLOR_R] = $2;
	currentMat->ka[COLOR_G] = $3;
	currentMat->ka[COLOR_B] = $4;

}
|

KD MTL_VALUE MTL_VALUE MTL_VALUE
{
	printf("Specifying diffuse reflection constants\n\n");
	currentMat->kd[COLOR_R] = $2;
	currentMat->kd[COLOR_G] = $3;
	currentMat->kd[COLOR_B] = $4;
}
|

KS MTL_VALUE MTL_VALUE MTL_VALUE
{
	printf("Specifying specular reflection constants\n\n");
	currentMat->ks[COLOR_R] = $2;
	currentMat->ks[COLOR_G] = $3;
	currentMat->ks[COLOR_B] = $4;
}
|

NS MTL_VALUE
{
	printf("Specifying specular exponent\n\n");
	currentMat->ns = $2;
}
|

D MTL_VALUE
{
	printf("Specifying opaqueness\n\n");
	currentMat->d = $2;
}
|

TR MTL_VALUE
{
	printf("Specifying transparency\n\n");
	currentMat->d = 1 - $2;
}
|

NI MTL_VALUE
{
	printf("Specifying optical density\n\n");
	currentMat->ni = $2;
}
|

ILLUM MTL_VALUE
{
	printf("Specifying illumination model\n\n");
	currentMat->iModel = (int)$2;
}
|

MAP_KA argument MTL_STRING
{
	printf("Specifying ambient texture [%s]\n\n",$3);
	texture_add($3);
	currentTex = texture_find($3);
	currentMat->map_ka = currentTex;
}
|

MAP_KD argument MTL_STRING
{
	printf("Specifying diffuse texture [%s]\n\n",$3);
	texture_add($3);
	currentTex = texture_find($3);
	currentMat->map_kd = currentTex;
}
|

MAP_KS argument MTL_STRING
{
	printf("Specifying specular texture\n\n");
	texture_add($3);
	currentTex = texture_find($3);
	currentMat->map_ks = currentTex;
}
|

MAP_NS argument MTL_STRING
{
	printf("Specifying specular highlight component\n\n");
	texture_add($3);
	currentTex = texture_find($3);
	currentMat->map_ns = currentTex;
}
|

MAP_D argument MTL_STRING
{
	printf("Specifying alpha texture\n\n");
	texture_add($3);
	currentTex = texture_find($3);
	currentMat->map_d = currentTex;
}
|

BUMP argument MTL_STRING
{
	printf("Specifying bump map\n\n");
	texture_add($3);
	currentTex = texture_find($3);
	currentMat->map_bump = currentTex;
}
|

DISP argument MTL_STRING
{
	printf("Specifying displacement map\n\n");
	texture_add($3);
	currentTex = texture_find($3);
	currentMat->map_disp = currentTex;
}
|

DECAL argument MTL_STRING
{
	printf("Specifying decal texture\n\n");
	texture_add($3);
	currentTex = texture_find($3);
	currentMat->map_decal = currentTex;
}
|

REFL argument MTL_STRING
{
	printf("Specifying reflection map\n\n");
	texture_add($3);
	currentTex = texture_find($3);
	currentMat->map_refl = currentTex;
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