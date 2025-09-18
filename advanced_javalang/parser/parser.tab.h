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
    PUBLIC = 262,
    STATIC = 263,
    VOID = 264,
    INT = 265,
    FLOAT = 266,
    DOUBLE = 267,
    BOOLEAN = 268,
    STRING = 269,
    CLASS = 270,
    MAIN = 271,
    IF = 272,
    ELSE = 273,
    WHILE = 274,
    FOR = 275,
    SWITCH = 276,
    CASE = 277,
    DEFAULT = 278,
    BREAK = 279,
    CONTINUE = 280,
    RETURN = 281,
    TRUE = 282,
    FALSE = 283,
    NULL_LITERAL = 284,
    PRINTLN = 285,
    LBRACE = 286,
    RBRACE = 287,
    LPAREN = 288,
    RPAREN = 289,
    LBRACKET = 290,
    RBRACKET = 291,
    SEMICOLON = 292,
    COMMA = 293,
    COLON = 294,
    ASSIGN = 295,
    PLUS = 296,
    MINUS = 297,
    MULTIPLY = 298,
    DIVIDE = 299,
    MODULO = 300,
    EQ = 301,
    NE = 302,
    LT = 303,
    LE = 304,
    GT = 305,
    GE = 306,
    AND = 307,
    OR = 308,
    NOT = 309
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 18 "parser/parser.y"

    int int_val;
    double float_val;
    char *string_val;
    ASTNode *node;

#line 119 "parser/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_PARSER_TAB_H_INCLUDED  */
