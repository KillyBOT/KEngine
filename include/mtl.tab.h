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
    NEWMTL = 261,
    KA = 262,
    KD = 263,
    KS = 264,
    NS = 265,
    D = 266,
    TR = 267,
    NI = 268,
    ILLUM = 269,
    MAP_KA = 270,
    MAP_KD = 271,
    MAP_KS = 272,
    MAP_NS = 273,
    MAP_D = 274,
    BUMP = 275,
    DISP = 276,
    DECAL = 277,
    REFL = 278,
    _BLENDU = 279,
    _BLENDV = 280,
    _BOOST = 281,
    _MM = 282,
    _GAIN_VALUE = 283,
    _O = 284,
    _S = 285,
    _T = 286,
    _TEXRES = 287,
    _CLAMP = 288,
    _BM = 289,
    _IMFCHAN = 290,
    _TYPE = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 7 "mtl.y" /* yacc.c:1909  */

	double value;
	char string[512];

#line 96 "mtl.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE mtl_yylval;

int mtl_yyparse (void);

#endif /* !YY_MTL_YY_MTL_TAB_H_INCLUDED  */