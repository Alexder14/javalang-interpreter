/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "common.h"

// Funciones externas
extern int yylex();
extern FILE *yyin;
extern int line_num;
extern int col_num;

// Función de error
void yyerror(const char *s);

// Variables globales
ASTNode *ast_root = NULL;
bool has_syntax_errors = false;

#line 92 "parser/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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
    ARRAY_INDEX_OF = 338
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 24 "parser/parser.y"

    int int_val;
    float float_val;
    char char_val;
    char *str_val;
    ASTNode *node;
    bool bool_val;

#line 237 "parser/parser.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_PARSER_TAB_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1499

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  84
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  109
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  258

#define YYUNDEFTOK  2
#define YYMAXUTOK   338


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    99,    99,   106,   109,   116,   119,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     144,   149,   154,   159,   164,   174,   179,   187,   192,   199,
     204,   212,   217,   222,   227,   232,   237,   243,   247,   250,
     256,   262,   265,   268,   274,   283,   292,   297,   304,   310,
     319,   330,   337,   344,   349,   357,   358,   359,   363,   366,
     369,   372,   375,   378,   381,   384,   387,   390,   393,   396,
     399,   402,   405,   408,   414,   417,   420,   423,   426,   431,
     436,   441,   449,   452,   456,   459,   462,   466,   469,   472,
     475,   478,   479,   480,   484,   487,   490,   494,   501,   506,
     513,   521,   529,   539,   540,   541,   542,   543,   544,   545
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING_LITERAL",
  "INT_LITERAL", "FLOAT_LITERAL", "CHAR_LITERAL", "TRUE", "FALSE",
  "PUBLIC", "PRIVATE", "PROTECTED", "STATIC", "FINAL", "VOID", "MAIN",
  "INT", "FLOAT", "DOUBLE", "BOOLEAN", "CHAR", "STRING_TYPE", "IF", "ELSE",
  "SWITCH", "CASE", "DEFAULT", "WHILE", "FOR", "DO", "BREAK", "CONTINUE",
  "RETURN", "NULL_VAL", "NEW", "THIS", "PLUS", "MINUS", "MULTIPLY",
  "DIVIDE", "MODULO", "INCREMENT", "DECREMENT", "ASSIGN", "PLUS_ASSIGN",
  "MINUS_ASSIGN", "MULT_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "EQUAL",
  "NOT_EQUAL", "LESS", "LESS_EQUAL", "GREATER", "GREATER_EQUAL", "AND",
  "OR", "NOT", "BIT_AND", "BIT_OR", "BIT_XOR", "BIT_NOT", "LEFT_SHIFT",
  "RIGHT_SHIFT", "LPAREN", "RPAREN", "LBRACE", "RBRACE", "LBRACKET",
  "RBRACKET", "SEMICOLON", "COMMA", "DOT", "COLON", "QUESTION", "PRINTLN",
  "PRINT", "PARSE_INT", "PARSE_FLOAT", "PARSE_DOUBLE", "VALUE_OF",
  "STRING_JOIN", "ARRAY_INDEX_OF", "$accept", "program", "main_class",
  "statement_list", "statement", "variable_declaration",
  "function_declaration", "parameter_list", "parameter",
  "assignment_statement", "expression_statement", "if_statement",
  "while_statement", "for_statement", "do_while_statement",
  "switch_statement", "case_list", "case_statement", "block_statement",
  "break_statement", "continue_statement", "return_statement",
  "expression", "binary_expression", "unary_expression",
  "primary_expression", "function_call", "argument_list", "array_access",
  "array_initialization", "type_specifier", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338
};
# endif

#define YYPACT_NINF (-71)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      26,    -1,    46,   -71,    49,   -71,    63,   -39,   -16,    23,
      24,    36,   -71,   104,    10,    52,   683,   -71,   -71,   -71,
     -71,   -71,   -71,   402,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,    56,    69,    70,    73,   571,    72,    79,   267,   -71,
     402,   700,   700,   117,   137,   700,   700,   700,   700,   -71,
      86,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,   -71,
     -71,   -71,   -71,   -71,   -71,   731,   -71,   -71,   -71,   -71,
     113,   -71,     1,    91,   -71,   -71,   700,   700,   700,   700,
     700,   614,   700,   157,   700,   700,   700,   127,   136,   -71,
     -71,    20,   700,   -71,   756,   -71,    96,    55,    55,   -71,
     -71,   -71,   -71,  1106,    94,  1346,    -3,   657,   700,   700,
     700,   700,   700,   700,   700,   700,   700,   700,   700,   700,
     700,   700,   700,   700,   -71,   700,    22,    97,   -71,   781,
     806,   831,   856,   881,   -71,    16,  1056,   122,  1136,  1166,
    1196,   155,   700,   700,   700,   113,     2,   106,   -71,   700,
     -71,   -71,   -71,   700,   -71,    38,    55,    55,   -71,   -71,
     -71,   225,   225,   274,   274,   274,   274,   312,  1371,  1444,
    1396,  1421,   906,   700,    39,   -71,   166,   373,   -71,   -71,
     -71,   -71,   -71,   -71,   -71,   700,   571,   115,   571,   931,
     956,   981,   -37,   700,  1081,  1346,   -71,   -71,  1006,   116,
      67,   -71,     5,   -22,   -71,  1031,   149,    57,   -71,   700,
     700,   700,  1226,   -71,   -71,   -71,   118,   402,   -71,   114,
     -12,   -71,   -71,   571,   172,   120,   -17,   -71,  1256,  1286,
    1316,   121,   439,   -71,   -71,   184,   124,   -71,    11,   131,
     -71,   -71,   -71,   571,   571,   571,   -71,   -71,   505,   -71,
     -71,   -71,   571,   -71,   -71,   -71,   -71,   571
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     0,     0,     0,
       0,     0,     5,     0,     0,     0,    83,    86,    84,    85,
      87,    88,    89,     0,   109,   103,   104,   105,   106,   107,
     108,     0,     0,     0,     0,     0,     0,     0,     0,    90,
       0,     0,     0,     0,     0,     0,     0,     0,     5,     3,
       0,     6,     7,    19,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,     0,    55,    56,    57,    91,
      92,    93,     0,     0,    80,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      52,    83,     0,    53,     0,    92,     0,    77,    76,    78,
      79,    74,    75,     0,     0,    98,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,     0,     0,     0,     5,     0,
       0,     0,     0,     0,    97,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,     0,
      82,    50,   102,     0,    95,     0,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,     0,     0,     0,    20,     0,     0,    31,    32,
      33,    34,    35,    96,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    99,    94,    36,     0,     0,
       0,    27,     0,     0,     4,     0,    38,     0,    40,     0,
       0,     0,     0,   101,    21,     5,     0,     0,    29,     0,
       0,    22,    24,     0,     0,     0,     0,    46,     0,     0,
       0,     0,     0,     5,    28,     0,     0,    39,    83,     0,
       5,    45,    47,     0,     0,     0,    44,    26,     0,    30,
      23,     5,    49,    43,    41,    42,    25,    48
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -71,   -71,   -71,   -47,   -33,   101,   -71,   -71,   -28,   109,
     -71,   -71,   -71,   -71,   -71,   -71,   -71,   -35,   -71,   -71,
     -71,   -71,   175,   -71,   -71,   -10,   -71,   -70,   -14,    -5,
     -20
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    14,    51,    52,    53,   200,   201,    54,
      55,    56,    57,    58,    59,    60,   226,   227,    61,    62,
      63,    64,    65,    66,    67,    68,    69,   106,    95,    71,
      72
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,   104,    88,    83,   126,   192,     9,   173,   218,   224,
     225,   135,     4,    16,    17,    18,    19,    20,    21,    22,
      96,    70,   220,    40,    23,    24,     8,    25,    26,    27,
      28,    29,    30,    31,   175,    32,     1,   155,    33,    34,
      35,    36,    37,    38,    39,    40,     5,    41,    42,   221,
      10,   241,    43,    44,    24,    92,    25,    26,    27,    28,
      29,    30,    74,    75,     6,   152,   173,   146,    45,   153,
     127,   127,    46,   145,   219,    47,    81,    48,    49,     7,
      82,   177,   183,   224,   225,    81,    50,   174,   153,    82,
      70,    12,    11,   175,   110,   111,   112,    16,    17,    18,
      19,    20,    21,    22,   196,   199,    13,    15,    23,    24,
     153,    25,    26,    27,    28,    29,    30,    31,    73,    32,
      99,    84,    33,    34,    35,    36,    37,    38,    39,    40,
     141,    41,    42,   216,    85,    86,    43,    44,    87,   217,
     100,    23,    24,    89,    25,    26,    27,    28,    29,    30,
      90,   107,    45,   206,   202,   208,    46,   125,   128,    47,
     137,    48,   151,    70,   147,   149,   185,   176,   232,   203,
      50,   193,    70,   223,    70,   238,    17,    18,    19,    20,
      21,    22,   207,   215,   235,   233,   248,   249,   143,   234,
     237,   242,   246,   252,   240,   250,   144,   202,   142,    76,
      77,    78,    79,    80,   257,   251,    39,    40,     0,    70,
     253,   254,   255,    94,   239,   236,    97,    98,    70,     0,
     101,   102,   103,   105,    82,     0,     0,     0,     0,    70,
      70,    70,     0,     0,    70,     0,     0,    47,    70,    92,
       0,     0,     0,    70,     0,     0,     0,     0,    50,     0,
       0,   129,   130,   131,   132,   133,   105,   136,     0,   138,
     139,   140,   108,   109,   110,   111,   112,   105,     0,     0,
      91,    17,    18,    19,    20,    21,    22,   115,   116,   117,
     118,     0,   105,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,     0,
     172,    39,    40,     0,    41,    42,     0,     0,     0,    43,
      44,   108,   109,   110,   111,   112,     0,   189,   190,   191,
       0,     0,     0,     0,   194,    45,     0,     0,   195,    46,
       0,     0,    47,     0,    92,     0,     0,     0,    93,     0,
       0,     0,     0,    50,     0,     0,     0,     0,   198,   108,
     109,   110,   111,   112,     0,     0,     0,     0,     0,     0,
     205,     0,   113,   114,   115,   116,   117,   118,   212,     0,
       0,   121,   122,   123,     0,     0,    16,    17,    18,    19,
      20,    21,    22,     0,   228,   229,   230,    23,    24,     0,
      25,    26,    27,    28,    29,    30,    31,     0,    32,     0,
       0,    33,    34,    35,    36,    37,    38,    39,    40,     0,
      41,    42,     0,     0,     0,    43,    44,    24,     0,    25,
      26,    27,    28,    29,    30,     0,     0,     0,     0,     0,
       0,    45,     0,     0,     0,    46,     0,     0,    47,     0,
      48,   204,    16,    17,    18,    19,    20,    21,    22,    50,
       0,     0,     0,    23,    24,     0,    25,    26,    27,    28,
      29,    30,    31,     0,    32,     0,     0,    33,    34,    35,
      36,    37,    38,    39,    40,     0,    41,    42,     0,     0,
       0,    43,    44,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    45,     0,     0,
       0,    46,     0,     0,    47,     0,    48,   247,    16,    17,
      18,    19,    20,    21,    22,    50,     0,     0,     0,    23,
      24,     0,    25,    26,    27,    28,    29,    30,    31,     0,
      32,     0,     0,    33,    34,    35,    36,    37,    38,    39,
      40,     0,    41,    42,     0,     0,     0,    43,    44,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45,     0,     0,     0,    46,     0,     0,
      47,     0,    48,   256,    16,    17,    18,    19,    20,    21,
      22,    50,     0,     0,     0,    23,    24,     0,    25,    26,
      27,    28,    29,    30,    31,     0,    32,     0,     0,    33,
      34,    35,    36,    37,    38,    39,    40,     0,    41,    42,
       0,     0,     0,    43,    44,     0,     0,    91,    17,    18,
      19,    20,    21,    22,     0,     0,     0,     0,     0,    45,
       0,     0,     0,    46,     0,     0,    47,     0,    48,     0,
       0,     0,     0,     0,     0,     0,     0,    50,    39,    40,
       0,    41,    42,     0,     0,     0,    43,    44,     0,     0,
      91,    17,    18,    19,    20,    21,    22,     0,     0,     0,
       0,     0,    45,     0,     0,     0,    46,     0,     0,    47,
     134,    92,     0,     0,     0,     0,     0,     0,     0,     0,
      50,    39,    40,     0,    41,    42,     0,     0,     0,    43,
      44,     0,     0,    91,    17,    18,    19,    20,    21,    22,
       0,     0,     0,     0,     0,    45,     0,     0,     0,    46,
       0,     0,    47,   154,    92,    74,    75,    76,    77,    78,
      79,    80,     0,    50,    39,    40,     0,    41,    42,     0,
       0,     0,    43,    44,     0,     0,     0,     0,    81,     0,
       0,     0,    82,     0,     0,     0,     0,     0,    45,     0,
       0,     0,    46,     0,     0,    47,     0,    92,   108,   109,
     110,   111,   112,     0,     0,     0,    50,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   119,   120,     0,
     121,   122,   123,   108,   109,   110,   111,   112,     0,     0,
       0,     0,   124,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,   108,   109,
     110,   111,   112,     0,     0,     0,     0,   148,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   119,   120,     0,
     121,   122,   123,   108,   109,   110,   111,   112,     0,     0,
       0,     0,   178,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,   108,   109,
     110,   111,   112,     0,     0,     0,     0,   179,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   119,   120,     0,
     121,   122,   123,   108,   109,   110,   111,   112,     0,     0,
       0,     0,   180,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,   108,   109,
     110,   111,   112,     0,     0,     0,     0,   181,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   119,   120,     0,
     121,   122,   123,   108,   109,   110,   111,   112,     0,     0,
       0,     0,   182,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,   108,   109,
     110,   111,   112,     0,     0,     0,     0,   197,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   119,   120,     0,
     121,   122,   123,   108,   109,   110,   111,   112,     0,     0,
       0,     0,   209,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,   108,   109,
     110,   111,   112,     0,     0,     0,     0,   210,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   119,   120,     0,
     121,   122,   123,   108,   109,   110,   111,   112,     0,     0,
       0,     0,   211,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,   108,   109,
     110,   111,   112,     0,     0,     0,     0,   214,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   119,   120,     0,
     121,   122,   123,   108,   109,   110,   111,   112,     0,     0,
       0,     0,   222,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,   108,   109,
     110,   111,   112,     0,     0,     0,   184,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   119,   120,     0,
     121,   122,   123,   108,   109,   110,   111,   112,     0,     0,
       0,   213,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,     0,     0,
       0,     0,   150,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,     0,     0,
       0,     0,   186,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,     0,     0,
       0,     0,   187,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,     0,     0,
       0,     0,   188,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,     0,     0,
       0,     0,   231,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,     0,     0,
       0,     0,   243,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,     0,     0,
       0,     0,   244,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,     0,     0,
       0,     0,   245,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,     0,   121,   122,   123,   108,   109,
     110,   111,   112,     0,     0,     0,     0,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   119,     0,     0,
     121,   122,   123,   108,   109,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,     0,     0,     0,   121,     0,   123,   108,   109,
     110,   111,   112,     0,     0,     0,     0,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,     0,     0,     0,
     121,   108,   109,   110,   111,   112,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   114,   115,   116,   117,   118
};

static const yytype_int16 yycheck[] =
{
      14,    48,    35,    23,     3,     3,    22,    44,     3,    26,
      27,    81,    13,     3,     4,     5,     6,     7,     8,     9,
      40,    35,    44,    35,    14,    15,    65,    17,    18,    19,
      20,    21,    22,    23,    71,    25,    10,   107,    28,    29,
      30,    31,    32,    33,    34,    35,     0,    37,    38,    71,
      66,    68,    42,    43,    15,    67,    17,    18,    19,    20,
      21,    22,    42,    43,    15,    68,    44,    87,    58,    72,
      69,    69,    62,    87,    69,    65,    65,    67,    68,    16,
      69,   128,    66,    26,    27,    65,    76,    65,    72,    69,
     104,    67,    69,    71,    39,    40,    41,     3,     4,     5,
       6,     7,     8,     9,    66,    66,    70,     3,    14,    15,
      72,    17,    18,    19,    20,    21,    22,    23,    66,    25,
       3,    65,    28,    29,    30,    31,    32,    33,    34,    35,
       3,    37,    38,    66,    65,    65,    42,    43,    65,    72,
       3,    14,    15,    71,    17,    18,    19,    20,    21,    22,
      71,    65,    58,   186,   174,   188,    62,    44,    67,    65,
       3,    67,    68,   177,    28,    69,    44,    70,   215,     3,
      76,    65,   186,    24,   188,     3,     4,     5,     6,     7,
       8,     9,    67,    67,    70,    67,   233,     3,    87,   217,
     223,   226,    71,   240,    74,    71,    87,   217,    71,    44,
      45,    46,    47,    48,   251,    74,    34,    35,    -1,   223,
     243,   244,   245,    38,   224,   220,    41,    42,   232,    -1,
      45,    46,    47,    48,    69,    -1,    -1,    -1,    -1,   243,
     244,   245,    -1,    -1,   248,    -1,    -1,    65,   252,    67,
      -1,    -1,    -1,   257,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    76,    77,    78,    79,    80,    81,    82,    -1,    84,
      85,    86,    37,    38,    39,    40,    41,    92,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    52,    53,    54,
      55,    -1,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,    -1,
     125,    34,    35,    -1,    37,    38,    -1,    -1,    -1,    42,
      43,    37,    38,    39,    40,    41,    -1,   142,   143,   144,
      -1,    -1,    -1,    -1,   149,    58,    -1,    -1,   153,    62,
      -1,    -1,    65,    -1,    67,    -1,    -1,    -1,    71,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,   173,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
     185,    -1,    50,    51,    52,    53,    54,    55,   193,    -1,
      -1,    59,    60,    61,    -1,    -1,     3,     4,     5,     6,
       7,     8,     9,    -1,   209,   210,   211,    14,    15,    -1,
      17,    18,    19,    20,    21,    22,    23,    -1,    25,    -1,
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      37,    38,    -1,    -1,    -1,    42,    43,    15,    -1,    17,
      18,    19,    20,    21,    22,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    -1,    -1,    -1,    62,    -1,    -1,    65,    -1,
      67,    68,     3,     4,     5,     6,     7,     8,     9,    76,
      -1,    -1,    -1,    14,    15,    -1,    17,    18,    19,    20,
      21,    22,    23,    -1,    25,    -1,    -1,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    37,    38,    -1,    -1,
      -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    62,    -1,    -1,    65,    -1,    67,    68,     3,     4,
       5,     6,     7,     8,     9,    76,    -1,    -1,    -1,    14,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    37,    38,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    62,    -1,    -1,
      65,    -1,    67,    68,     3,     4,     5,     6,     7,     8,
       9,    76,    -1,    -1,    -1,    14,    15,    -1,    17,    18,
      19,    20,    21,    22,    23,    -1,    25,    -1,    -1,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    37,    38,
      -1,    -1,    -1,    42,    43,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    -1,    -1,    58,
      -1,    -1,    -1,    62,    -1,    -1,    65,    -1,    67,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    34,    35,
      -1,    37,    38,    -1,    -1,    -1,    42,    43,    -1,    -1,
       3,     4,     5,     6,     7,     8,     9,    -1,    -1,    -1,
      -1,    -1,    58,    -1,    -1,    -1,    62,    -1,    -1,    65,
      66,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    34,    35,    -1,    37,    38,    -1,    -1,    -1,    42,
      43,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,    62,
      -1,    -1,    65,    66,    67,    42,    43,    44,    45,    46,
      47,    48,    -1,    76,    34,    35,    -1,    37,    38,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    65,    -1,
      -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    62,    -1,    -1,    65,    -1,    67,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    71,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    71,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    71,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    71,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    71,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    71,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    71,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    71,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    70,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    70,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    -1,    -1,
      -1,    -1,    66,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    56,    57,    -1,    59,    60,    61,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    56,    -1,    -1,
      59,    60,    61,    37,    38,    39,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    -1,    -1,    -1,    59,    -1,    61,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      59,    37,    38,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,    55
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    85,    86,    13,     0,    15,    16,    65,    22,
      66,    69,    67,    70,    87,     3,     3,     4,     5,     6,
       7,     8,     9,    14,    15,    17,    18,    19,    20,    21,
      22,    23,    25,    28,    29,    30,    31,    32,    33,    34,
      35,    37,    38,    42,    43,    58,    62,    65,    67,    68,
      76,    88,    89,    90,    93,    94,    95,    96,    97,    98,
      99,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     112,   113,   114,    66,    42,    43,    44,    45,    46,    47,
      48,    65,    69,   114,    65,    65,    65,    65,    88,    71,
      71,     3,    67,    71,   106,   112,   114,   106,   106,     3,
       3,   106,   106,   106,    87,   106,   111,    65,    37,    38,
      39,    40,    41,    50,    51,    52,    53,    54,    55,    56,
      57,    59,    60,    61,    71,    44,     3,    69,    67,   106,
     106,   106,   106,   106,    66,   111,   106,     3,   106,   106,
     106,     3,    71,    89,    93,   112,   114,    28,    71,    69,
      66,    68,    68,    72,    66,   111,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,    44,    65,    71,    70,    87,    71,    71,
      71,    71,    71,    66,    70,    44,    66,    66,    66,   106,
     106,   106,     3,    65,   106,   106,    66,    71,   106,    66,
      91,    92,   114,     3,    68,   106,    88,    67,    88,    71,
      71,    71,   106,    70,    71,    67,    66,    72,     3,    69,
      44,    71,    71,    24,    26,    27,   100,   101,   106,   106,
     106,    66,    87,    67,    92,    70,   113,    88,     3,   109,
      74,    68,   101,    66,    66,    66,    71,    68,    87,     3,
      71,    74,    87,    88,    88,    88,    68,    87
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    84,    85,    86,    86,    87,    87,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      89,    89,    89,    89,    89,    90,    90,    91,    91,    92,
      92,    93,    93,    93,    93,    93,    93,    94,    95,    95,
      96,    97,    97,    97,    98,    99,   100,   100,   101,   101,
     102,   103,   104,   105,   105,   106,   106,   106,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   108,   108,   108,   108,   108,   108,
     108,   108,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   110,   110,   110,   110,   111,   111,
     112,   113,   113,   114,   114,   114,   114,   114,   114,   114
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     9,    13,     0,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     5,     5,     7,     6,     8,     7,     1,     3,     2,
       4,     4,     4,     4,     4,     4,     4,     2,     5,     7,
       5,     8,     8,     8,     7,     7,     1,     2,     4,     3,
       3,     2,     2,     2,     3,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     2,     2,     2,     2,
       2,     2,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     3,     4,     3,     1,     3,
       4,     5,     3,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 99 "parser/parser.y"
               {
        ast_root = create_program_node((yyvsp[0].node));
        (yyval.node) = ast_root;
    }
#line 1848 "parser/parser.tab.c"
    break;

  case 3:
#line 106 "parser/parser.y"
                                                                       {
        (yyval.node) = create_main_class_node((yyvsp[-1].node));
    }
#line 1856 "parser/parser.tab.c"
    break;

  case 4:
#line 109 "parser/parser.y"
                                                                                                                  {
        (yyval.node) = create_main_class_node((yyvsp[-1].node));
        free((yyvsp[-4].str_val)); // liberar nombre del parámetro args
    }
#line 1865 "parser/parser.tab.c"
    break;

  case 5:
#line 116 "parser/parser.y"
                {
        (yyval.node) = create_list_node();
    }
#line 1873 "parser/parser.tab.c"
    break;

  case 6:
#line 119 "parser/parser.y"
                               {
        if ((yyvsp[0].node) != NULL) {
            add_to_list((yyvsp[-1].node), (yyvsp[0].node));
        }
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1884 "parser/parser.tab.c"
    break;

  case 7:
#line 128 "parser/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1890 "parser/parser.tab.c"
    break;

  case 8:
#line 129 "parser/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1896 "parser/parser.tab.c"
    break;

  case 9:
#line 130 "parser/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1902 "parser/parser.tab.c"
    break;

  case 10:
#line 131 "parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1908 "parser/parser.tab.c"
    break;

  case 11:
#line 132 "parser/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1914 "parser/parser.tab.c"
    break;

  case 12:
#line 133 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1920 "parser/parser.tab.c"
    break;

  case 13:
#line 134 "parser/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1926 "parser/parser.tab.c"
    break;

  case 14:
#line 135 "parser/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 1932 "parser/parser.tab.c"
    break;

  case 15:
#line 136 "parser/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1938 "parser/parser.tab.c"
    break;

  case 16:
#line 137 "parser/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1944 "parser/parser.tab.c"
    break;

  case 17:
#line 138 "parser/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1950 "parser/parser.tab.c"
    break;

  case 18:
#line 139 "parser/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 1956 "parser/parser.tab.c"
    break;

  case 19:
#line 140 "parser/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 1962 "parser/parser.tab.c"
    break;

  case 20:
#line 144 "parser/parser.y"
                                        {
        (yyval.node) = create_var_decl_node((yyvsp[-2].node), (yyvsp[-1].str_val), NULL, false, 0);
        free((yyvsp[-2].node));
        free((yyvsp[-1].str_val));
    }
#line 1972 "parser/parser.tab.c"
    break;

  case 21:
#line 149 "parser/parser.y"
                                                            {
        (yyval.node) = create_var_decl_node((yyvsp[-4].node), (yyvsp[-3].str_val), (yyvsp[-1].node), false, 0);
        free((yyvsp[-4].node));
        free((yyvsp[-3].str_val));
    }
#line 1982 "parser/parser.tab.c"
    break;

  case 22:
#line 154 "parser/parser.y"
                                                            {
        (yyval.node) = create_var_decl_node((yyvsp[-4].node), (yyvsp[-1].str_val), NULL, true, 0);
        free((yyvsp[-4].node));
        free((yyvsp[-1].str_val));
    }
#line 1992 "parser/parser.tab.c"
    break;

  case 23:
#line 159 "parser/parser.y"
                                                                                        {
        (yyval.node) = create_var_decl_node((yyvsp[-6].node), (yyvsp[-3].str_val), (yyvsp[-1].node), true, 0);
        free((yyvsp[-6].node));
        free((yyvsp[-3].str_val));
    }
#line 2002 "parser/parser.tab.c"
    break;

  case 24:
#line 164 "parser/parser.y"
                                                                  {
        ASTNode *node = create_var_decl_node((yyvsp[-4].node), (yyvsp[-3].str_val), (yyvsp[-1].node), false, 0);
        // Marcar como constante (se podría añadir un campo is_const al AST)
        free((yyvsp[-4].node));
        free((yyvsp[-3].str_val));
        (yyval.node) = node;
    }
#line 2014 "parser/parser.tab.c"
    break;

  case 25:
#line 174 "parser/parser.y"
                                                                                        {
        (yyval.node) = create_function_decl_node((yyvsp[-7].node), (yyvsp[-6].str_val), (yyvsp[-4].node), (yyvsp[-1].node));
        free((yyvsp[-7].node));
        free((yyvsp[-6].str_val));
    }
#line 2024 "parser/parser.tab.c"
    break;

  case 26:
#line 179 "parser/parser.y"
                                                                           {
        (yyval.node) = create_function_decl_node((yyvsp[-6].node), (yyvsp[-5].str_val), NULL, (yyvsp[-1].node));
        free((yyvsp[-6].node));
        free((yyvsp[-5].str_val));
    }
#line 2034 "parser/parser.tab.c"
    break;

  case 27:
#line 187 "parser/parser.y"
              {
        ASTNode *list = create_list_node();
        add_to_list(list, (yyvsp[0].node));
        (yyval.node) = list;
    }
#line 2044 "parser/parser.tab.c"
    break;

  case 28:
#line 192 "parser/parser.y"
                                     {
        add_to_list((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2053 "parser/parser.tab.c"
    break;

  case 29:
#line 199 "parser/parser.y"
                              {
        (yyval.node) = create_parameter_node((yyvsp[-1].node), (yyvsp[0].str_val), false);
        free((yyvsp[-1].node));
        free((yyvsp[0].str_val));
    }
#line 2063 "parser/parser.tab.c"
    break;

  case 30:
#line 204 "parser/parser.y"
                                                  {
        (yyval.node) = create_parameter_node((yyvsp[-3].node), (yyvsp[0].str_val), true);
        free((yyvsp[-3].node));
        free((yyvsp[0].str_val));
    }
#line 2073 "parser/parser.tab.c"
    break;

  case 31:
#line 212 "parser/parser.y"
                                           {
        ASTNode *var = create_identifier_node((yyvsp[-3].str_val));
        (yyval.node) = create_assignment_node(var, "=", (yyvsp[-1].node));
        free((yyvsp[-3].str_val));
    }
#line 2083 "parser/parser.tab.c"
    break;

  case 32:
#line 217 "parser/parser.y"
                                                  {
        ASTNode *var = create_identifier_node((yyvsp[-3].str_val));
        (yyval.node) = create_assignment_node(var, "+=", (yyvsp[-1].node));
        free((yyvsp[-3].str_val));
    }
#line 2093 "parser/parser.tab.c"
    break;

  case 33:
#line 222 "parser/parser.y"
                                                   {
        ASTNode *var = create_identifier_node((yyvsp[-3].str_val));
        (yyval.node) = create_assignment_node(var, "-=", (yyvsp[-1].node));
        free((yyvsp[-3].str_val));
    }
#line 2103 "parser/parser.tab.c"
    break;

  case 34:
#line 227 "parser/parser.y"
                                                  {
        ASTNode *var = create_identifier_node((yyvsp[-3].str_val));
        (yyval.node) = create_assignment_node(var, "*=", (yyvsp[-1].node));
        free((yyvsp[-3].str_val));
    }
#line 2113 "parser/parser.tab.c"
    break;

  case 35:
#line 232 "parser/parser.y"
                                                 {
        ASTNode *var = create_identifier_node((yyvsp[-3].str_val));
        (yyval.node) = create_assignment_node(var, "/=", (yyvsp[-1].node));
        free((yyvsp[-3].str_val));
    }
#line 2123 "parser/parser.tab.c"
    break;

  case 36:
#line 237 "parser/parser.y"
                                               {
        (yyval.node) = create_assignment_node((yyvsp[-3].node), "=", (yyvsp[-1].node));
    }
#line 2131 "parser/parser.tab.c"
    break;

  case 37:
#line 243 "parser/parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2137 "parser/parser.tab.c"
    break;

  case 38:
#line 247 "parser/parser.y"
                                          {
        (yyval.node) = create_if_node((yyvsp[-2].node), (yyvsp[0].node), NULL);
    }
#line 2145 "parser/parser.tab.c"
    break;

  case 39:
#line 250 "parser/parser.y"
                                                           {
        (yyval.node) = create_if_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2153 "parser/parser.tab.c"
    break;

  case 40:
#line 256 "parser/parser.y"
                                             {
        (yyval.node) = create_while_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2161 "parser/parser.tab.c"
    break;

  case 41:
#line 262 "parser/parser.y"
                                                                                     {
        (yyval.node) = create_for_node((yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2169 "parser/parser.tab.c"
    break;

  case 42:
#line 265 "parser/parser.y"
                                                                                       {
        (yyval.node) = create_for_node((yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2177 "parser/parser.tab.c"
    break;

  case 43:
#line 268 "parser/parser.y"
                                                                            {
        (yyval.node) = create_for_node(NULL, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2185 "parser/parser.tab.c"
    break;

  case 44:
#line 274 "parser/parser.y"
                                                          {
        // Crear un nodo do-while (podemos usar while_node con un flag)
        ASTNode *node = create_while_node((yyvsp[-2].node), (yyvsp[-5].node));
        // Marcar como do-while si necesario
        (yyval.node) = node;
    }
#line 2196 "parser/parser.tab.c"
    break;

  case 45:
#line 283 "parser/parser.y"
                                                            {
        ASTNode *node = create_node(NODE_SWITCH_STMT, line_num, col_num);
        node->data.switch_stmt.expression = (yyvsp[-4].node);
        node->data.switch_stmt.cases = (yyvsp[-1].node);
        (yyval.node) = node;
    }
#line 2207 "parser/parser.tab.c"
    break;

  case 46:
#line 292 "parser/parser.y"
                   {
        ASTNode *list = create_list_node();
        add_to_list(list, (yyvsp[0].node));
        (yyval.node) = list;
    }
#line 2217 "parser/parser.tab.c"
    break;

  case 47:
#line 297 "parser/parser.y"
                               {
        add_to_list((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2226 "parser/parser.tab.c"
    break;

  case 48:
#line 304 "parser/parser.y"
                                                 {
        ASTNode *node = create_node(NODE_CASE_STMT, line_num, col_num);
        node->data.case_stmt.value = (yyvsp[-2].node);
        node->data.case_stmt.statements = (yyvsp[0].node);
        (yyval.node) = node;
    }
#line 2237 "parser/parser.tab.c"
    break;

  case 49:
#line 310 "parser/parser.y"
                                   {
        ASTNode *node = create_node(NODE_CASE_STMT, line_num, col_num);
        node->data.case_stmt.value = NULL; // default case
        node->data.case_stmt.statements = (yyvsp[0].node);
        (yyval.node) = node;
    }
#line 2248 "parser/parser.tab.c"
    break;

  case 50:
#line 319 "parser/parser.y"
                                 {
        (yyval.node) = create_block_node();
        // Convertir lista en bloque
        for (int i = 0; i < get_list_size((yyvsp[-1].node)); i++) {
            ASTNode *stmt = get_from_list((yyvsp[-1].node), i);
            add_to_list((yyval.node), stmt);
        }
    }
#line 2261 "parser/parser.tab.c"
    break;

  case 51:
#line 330 "parser/parser.y"
                    {
        ASTNode *node = create_node(NODE_BREAK_STMT, line_num, col_num);
        (yyval.node) = node;
    }
#line 2270 "parser/parser.tab.c"
    break;

  case 52:
#line 337 "parser/parser.y"
                       {
        ASTNode *node = create_node(NODE_CONTINUE_STMT, line_num, col_num);
        (yyval.node) = node;
    }
#line 2279 "parser/parser.tab.c"
    break;

  case 53:
#line 344 "parser/parser.y"
                     {
        ASTNode *node = create_node(NODE_RETURN_STMT, line_num, col_num);
        node->data.return_stmt.value = NULL;
        (yyval.node) = node;
    }
#line 2289 "parser/parser.tab.c"
    break;

  case 54:
#line 349 "parser/parser.y"
                                  {
        ASTNode *node = create_node(NODE_RETURN_STMT, line_num, col_num);
        node->data.return_stmt.value = (yyvsp[-1].node);
        (yyval.node) = node;
    }
#line 2299 "parser/parser.tab.c"
    break;

  case 55:
#line 357 "parser/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2305 "parser/parser.tab.c"
    break;

  case 56:
#line 358 "parser/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2311 "parser/parser.tab.c"
    break;

  case 57:
#line 359 "parser/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2317 "parser/parser.tab.c"
    break;

  case 58:
#line 363 "parser/parser.y"
                               {
        (yyval.node) = create_binary_op_node("+", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2325 "parser/parser.tab.c"
    break;

  case 59:
#line 366 "parser/parser.y"
                                  {
        (yyval.node) = create_binary_op_node("-", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2333 "parser/parser.tab.c"
    break;

  case 60:
#line 369 "parser/parser.y"
                                     {
        (yyval.node) = create_binary_op_node("*", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2341 "parser/parser.tab.c"
    break;

  case 61:
#line 372 "parser/parser.y"
                                   {
        (yyval.node) = create_binary_op_node("/", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2349 "parser/parser.tab.c"
    break;

  case 62:
#line 375 "parser/parser.y"
                                   {
        (yyval.node) = create_binary_op_node("%", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2357 "parser/parser.tab.c"
    break;

  case 63:
#line 378 "parser/parser.y"
                                  {
        (yyval.node) = create_binary_op_node("==", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2365 "parser/parser.tab.c"
    break;

  case 64:
#line 381 "parser/parser.y"
                                      {
        (yyval.node) = create_binary_op_node("!=", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2373 "parser/parser.tab.c"
    break;

  case 65:
#line 384 "parser/parser.y"
                                 {
        (yyval.node) = create_binary_op_node("<", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2381 "parser/parser.tab.c"
    break;

  case 66:
#line 387 "parser/parser.y"
                                       {
        (yyval.node) = create_binary_op_node("<=", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2389 "parser/parser.tab.c"
    break;

  case 67:
#line 390 "parser/parser.y"
                                    {
        (yyval.node) = create_binary_op_node(">", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2397 "parser/parser.tab.c"
    break;

  case 68:
#line 393 "parser/parser.y"
                                          {
        (yyval.node) = create_binary_op_node(">=", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2405 "parser/parser.tab.c"
    break;

  case 69:
#line 396 "parser/parser.y"
                                {
        (yyval.node) = create_binary_op_node("&&", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2413 "parser/parser.tab.c"
    break;

  case 70:
#line 399 "parser/parser.y"
                               {
        (yyval.node) = create_binary_op_node("||", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2421 "parser/parser.tab.c"
    break;

  case 71:
#line 402 "parser/parser.y"
                                    {
        (yyval.node) = create_binary_op_node("&", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2429 "parser/parser.tab.c"
    break;

  case 72:
#line 405 "parser/parser.y"
                                   {
        (yyval.node) = create_binary_op_node("|", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2437 "parser/parser.tab.c"
    break;

  case 73:
#line 408 "parser/parser.y"
                                    {
        (yyval.node) = create_binary_op_node("^", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2445 "parser/parser.tab.c"
    break;

  case 74:
#line 414 "parser/parser.y"
                   {
        (yyval.node) = create_unary_op_node("!", (yyvsp[0].node), true);
    }
#line 2453 "parser/parser.tab.c"
    break;

  case 75:
#line 417 "parser/parser.y"
                         {
        (yyval.node) = create_unary_op_node("~", (yyvsp[0].node), true);
    }
#line 2461 "parser/parser.tab.c"
    break;

  case 76:
#line 420 "parser/parser.y"
                       {
        (yyval.node) = create_unary_op_node("-", (yyvsp[0].node), true);
    }
#line 2469 "parser/parser.tab.c"
    break;

  case 77:
#line 423 "parser/parser.y"
                      {
        (yyval.node) = create_unary_op_node("+", (yyvsp[0].node), true);
    }
#line 2477 "parser/parser.tab.c"
    break;

  case 78:
#line 426 "parser/parser.y"
                           {
        ASTNode *var = create_identifier_node((yyvsp[0].str_val));
        (yyval.node) = create_unary_op_node("++", var, true);
        free((yyvsp[0].str_val));
    }
#line 2487 "parser/parser.tab.c"
    break;

  case 79:
#line 431 "parser/parser.y"
                           {
        ASTNode *var = create_identifier_node((yyvsp[0].str_val));
        (yyval.node) = create_unary_op_node("--", var, true);
        free((yyvsp[0].str_val));
    }
#line 2497 "parser/parser.tab.c"
    break;

  case 80:
#line 436 "parser/parser.y"
                           {
        ASTNode *var = create_identifier_node((yyvsp[-1].str_val));
        (yyval.node) = create_unary_op_node("++", var, false);
        free((yyvsp[-1].str_val));
    }
#line 2507 "parser/parser.tab.c"
    break;

  case 81:
#line 441 "parser/parser.y"
                           {
        ASTNode *var = create_identifier_node((yyvsp[-1].str_val));
        (yyval.node) = create_unary_op_node("--", var, false);
        free((yyvsp[-1].str_val));
    }
#line 2517 "parser/parser.tab.c"
    break;

  case 82:
#line 449 "parser/parser.y"
                             {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2525 "parser/parser.tab.c"
    break;

  case 83:
#line 452 "parser/parser.y"
                 {
        (yyval.node) = create_identifier_node((yyvsp[0].str_val));
        free((yyvsp[0].str_val));
    }
#line 2534 "parser/parser.tab.c"
    break;

  case 84:
#line 456 "parser/parser.y"
                  {
        (yyval.node) = create_int_literal_node((yyvsp[0].int_val));
    }
#line 2542 "parser/parser.tab.c"
    break;

  case 85:
#line 459 "parser/parser.y"
                    {
        (yyval.node) = create_float_literal_node((yyvsp[0].float_val));
    }
#line 2550 "parser/parser.tab.c"
    break;

  case 86:
#line 462 "parser/parser.y"
                     {
        (yyval.node) = create_string_literal_node((yyvsp[0].str_val));
        free((yyvsp[0].str_val));
    }
#line 2559 "parser/parser.tab.c"
    break;

  case 87:
#line 466 "parser/parser.y"
                   {
        (yyval.node) = create_char_literal_node((yyvsp[0].char_val));
    }
#line 2567 "parser/parser.tab.c"
    break;

  case 88:
#line 469 "parser/parser.y"
           {
        (yyval.node) = create_boolean_literal_node(true);
    }
#line 2575 "parser/parser.tab.c"
    break;

  case 89:
#line 472 "parser/parser.y"
            {
        (yyval.node) = create_boolean_literal_node(false);
    }
#line 2583 "parser/parser.tab.c"
    break;

  case 90:
#line 475 "parser/parser.y"
               {
        (yyval.node) = create_null_literal_node();
    }
#line 2591 "parser/parser.tab.c"
    break;

  case 91:
#line 478 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2597 "parser/parser.tab.c"
    break;

  case 92:
#line 479 "parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2603 "parser/parser.tab.c"
    break;

  case 93:
#line 480 "parser/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2609 "parser/parser.tab.c"
    break;

  case 94:
#line 484 "parser/parser.y"
                                        {
        (yyval.node) = create_function_call_node("System.out.println", (yyvsp[-1].node));
    }
#line 2617 "parser/parser.tab.c"
    break;

  case 95:
#line 487 "parser/parser.y"
                            {
        (yyval.node) = create_function_call_node("System.out.println", NULL);
    }
#line 2625 "parser/parser.tab.c"
    break;

  case 96:
#line 490 "parser/parser.y"
                                             {
        (yyval.node) = create_function_call_node((yyvsp[-3].str_val), (yyvsp[-1].node));
        free((yyvsp[-3].str_val));
    }
#line 2634 "parser/parser.tab.c"
    break;

  case 97:
#line 494 "parser/parser.y"
                               {
        (yyval.node) = create_function_call_node((yyvsp[-2].str_val), NULL);
        free((yyvsp[-2].str_val));
    }
#line 2643 "parser/parser.tab.c"
    break;

  case 98:
#line 501 "parser/parser.y"
               {
        ASTNode *list = create_list_node();
        add_to_list(list, (yyvsp[0].node));
        (yyval.node) = list;
    }
#line 2653 "parser/parser.tab.c"
    break;

  case 99:
#line 506 "parser/parser.y"
                                     {
        add_to_list((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2662 "parser/parser.tab.c"
    break;

  case 100:
#line 513 "parser/parser.y"
                                            {
        ASTNode *array = create_identifier_node((yyvsp[-3].str_val));
        (yyval.node) = create_array_access_node(array, (yyvsp[-1].node));
        free((yyvsp[-3].str_val));
    }
#line 2672 "parser/parser.tab.c"
    break;

  case 101:
#line 521 "parser/parser.y"
                                                    {
        ASTNode *node = create_node(NODE_ARRAY_INIT, line_num, col_num);
        node->data.array_init.type = strdup((yyvsp[-3].node));
        node->data.array_init.size = (yyvsp[-1].node);
        node->data.array_init.values = NULL;
        free((yyvsp[-3].node));
        (yyval.node) = node;
    }
#line 2685 "parser/parser.tab.c"
    break;

  case 102:
#line 529 "parser/parser.y"
                                  {
        ASTNode *node = create_node(NODE_ARRAY_INIT, line_num, col_num);
        node->data.array_init.type = NULL;
        node->data.array_init.size = NULL;
        node->data.array_init.values = (yyvsp[-1].node);
        (yyval.node) = node;
    }
#line 2697 "parser/parser.tab.c"
    break;

  case 103:
#line 539 "parser/parser.y"
        { (yyval.node) = strdup("int"); }
#line 2703 "parser/parser.tab.c"
    break;

  case 104:
#line 540 "parser/parser.y"
            { (yyval.node) = strdup("float"); }
#line 2709 "parser/parser.tab.c"
    break;

  case 105:
#line 541 "parser/parser.y"
             { (yyval.node) = strdup("double"); }
#line 2715 "parser/parser.tab.c"
    break;

  case 106:
#line 542 "parser/parser.y"
              { (yyval.node) = strdup("boolean"); }
#line 2721 "parser/parser.tab.c"
    break;

  case 107:
#line 543 "parser/parser.y"
           { (yyval.node) = strdup("char"); }
#line 2727 "parser/parser.tab.c"
    break;

  case 108:
#line 544 "parser/parser.y"
                  { (yyval.node) = strdup("String"); }
#line 2733 "parser/parser.tab.c"
    break;

  case 109:
#line 545 "parser/parser.y"
           { (yyval.node) = strdup("void"); }
#line 2739 "parser/parser.tab.c"
    break;


#line 2743 "parser/parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 548 "parser/parser.y"


void yyerror(const char *s) {
    has_syntax_errors = true;
    add_error(ERROR_SYNTACTIC, s, "Global", line_num, col_num);
    fprintf(stderr, "Error sintáctico en línea %d, columna %d: %s\n", line_num, col_num, s);
}

#ifdef TEST_PARSER
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <archivo.usl>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error al abrir archivo");
        return 1;
    }

    yyin = file;
    line_num = 1;
    col_num = 1;
    
    printf("🔍 Analizando archivo: %s\n", argv[1]);
    printf("==============================\n");

    if (yyparse() == 0 && !has_syntax_errors) {
        printf("✅ Análisis sintáctico exitoso!\n\n");
        
        if (ast_root) {
            printf("🌳 Árbol de Sintaxis Abstracta:\n");
            printf("================================\n");
            print_ast(ast_root, 0);
            printf("\n");
        }
        
        printf("📊 Estadísticas:\n");
        printf("- Sin errores sintácticos\n");
        printf("- AST generado correctamente\n");
        
    } else {
        printf("❌ Se encontraron errores sintácticos\n");
        print_errors();
    }
    
    fclose(file);
    
    if (ast_root) {
        free_ast(ast_root);
    }
    
    return has_syntax_errors ? 1 : 0;
}
#endif
