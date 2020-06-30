/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_MTL_YY_MTL_TAB_H_INCLUDED
# define YY_MTL_YY_MTL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int mtl_yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MTL_VALUE = 258,
    MTL_COMMENT = 259,
    MTL_STRING = 260,
    MTL_STRING_LONG = 261,
    NEWMTL = 262,
    KA = 263,
    KD = 264,
    KS = 265,
    NS = 266,
    D = 267,
    TR = 268,
    NI = 269,
    ILLUM = 270,
    MAP_KA = 271,
    MAP_KD = 272,
    MAP_KS = 273,
    MAP_NS = 274,
    MAP_D = 275,
    BUMP = 276,
    DISP = 277,
    DECAL = 278,
    REFL = 279,
    _BLENDU = 280,
    _BLENDV = 281,
    _BOOST = 282,
    _MM = 283,
    _GAIN_VALUE = 284,
    _O = 285,
    _S = 286,
    _T = 287,
    _TEXRES = 288,
    _CLAMP = 289,
    _BM = 290,
    _IMFCHAN = 291,
    _TYPE = 292
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 18 "mtl.y" /* yacc.c:1909  */

	double value;
	char string[512];

#line 97 "mtl.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE mtl_yylval;

int mtl_yyparse (void);

#endif /* !YY_MTL_YY_MTL_TAB_H_INCLUDED  */
