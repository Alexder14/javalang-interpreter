/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    IDENTIFIER = 258,
    STRING_LITERAL = 259,
    INT_LITERAL = 260,
    FLOAT_LITERAL = 261,
    CHAR_LITERAL = 262,
    TRUE = 263,
    FALSE = 264,
    PUBLIC = 265,
    PRIVATE = 266,
    PROTECTED = 267,
    STATIC = 268,
    FINAL = 269,
    VOID = 270,
    MAIN = 271,
    INT = 272,
    FLOAT = 273,
    DOUBLE = 274,
    BOOLEAN = 275,
    CHAR = 276,
    STRING_TYPE = 277,
    IF = 278,
    ELSE = 279,
    SWITCH = 280,
    CASE = 281,
    DEFAULT = 282,
    WHILE = 283,
    FOR = 284,
    DO = 285,
    BREAK = 286,
    CONTINUE = 287,
    RETURN = 288,
    NULL_VAL = 289,
    NEW = 290,
    THIS = 291,
    PLUS = 292,
    MINUS = 293,
    MULTIPLY = 294,
    DIVIDE = 295,
    MODULO = 296,
    INCREMENT = 297,
    DECREMENT = 298,
    ASSIGN = 299,
    PLUS_ASSIGN = 300,
    MINUS_ASSIGN = 301,
    MULT_ASSIGN = 302,
    DIV_ASSIGN = 303,
    MOD_ASSIGN = 304,
    EQUAL = 305,
    NOT_EQUAL = 306,
    LESS = 307,
    LESS_EQUAL = 308,
    GREATER = 309,
    GREATER_EQUAL = 310,
    AND = 311,
    OR = 312,
    NOT = 313,
    BIT_AND = 314,
    BIT_OR = 315,
    BIT_XOR = 316,
    BIT_NOT = 317,
    LEFT_SHIFT = 318,
    RIGHT_SHIFT = 319,
    LPAREN = 320,
    RPAREN = 321,
    LBRACE = 322,
    RBRACE = 323,
    LBRACKET = 324,
    RBRACKET = 325,
    SEMICOLON = 326,
    COMMA = 327,
    DOT = 328,
    COLON = 329,
    QUESTION = 330,
    PRINTLN = 331,
    PRINT = 332,
    PARSE_INT = 333,
    PARSE_FLOAT = 334,
    PARSE_DOUBLE = 335,
    VALUE_OF = 336,
    STRING_JOIN = 337,
    ARRAY_INDEX_OF = 338,
    UNARY_MINUS = 339,
    UNARY_PLUS = 340
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "parser/parser.y"

    int int_val;
    float float_val;
    char char_val;
    char *str_val;
    ASTNode *node;
    bool bool_val;

#line 152 "parser/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_PARSER_TAB_H_INCLUDED  */
