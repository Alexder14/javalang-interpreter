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
extern ASTNode *ast_root;

#line 90 "parser/parser.tab.c"

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
#define YYLAST   1506

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  264

#define YYUNDEFTOK  2
#define YYMAXUTOK   340


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
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    97,    97,   104,   107,   114,   119,   124,   128,   135,
     140,   147,   152,   160,   163,   169,   174,   178,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   197,   200,
     205,   213,   218,   223,   228,   233,   243,   249,   256,   257,
     258,   259,   260,   261,   265,   273,   276,   282,   288,   296,
     302,   311,   320,   325,   332,   338,   347,   348,   351,   354,
     357,   360,   363,   366,   369,   372,   375,   378,   381,   384,
     387,   390,   393,   396,   399,   402,   405,   408,   413,   418,
     423,   428,   431,   432,   436,   440,   443,   446,   450,   453,
     456,   459,   465,   468,   471,   474,   477,   481,   485,   488,
     491,   497,   502,   509,   514,   520,   527,   534,   544,   545,
     546,   547,   548,   549,   550
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
  "STRING_JOIN", "ARRAY_INDEX_OF", "UNARY_MINUS", "UNARY_PLUS", "$accept",
  "program", "main_class", "function_declaration", "parameter_list",
  "parameter", "block_statement", "statement_list", "statement",
  "variable_declaration", "assignment_statement", "assignment_operator",
  "expression_statement", "if_statement", "while_statement",
  "for_statement", "do_while_statement", "switch_statement", "case_list",
  "case_statement", "expression", "primary_expression", "function_call",
  "argument_list", "array_access", "array_initialization",
  "type_specifier", YY_NULLPTR
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
     335,   336,   337,   338,   339,   340
};
# endif

#define YYPACT_NINF (-217)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      26,    10,    18,  -217,    11,  -217,    22,   -13,    -1,    -9,
      19,    21,   366,  -217,    75,    71,  -217,  -217,  -217,  -217,
    -217,  -217,   155,  -217,  -217,  -217,  -217,  -217,  -217,  -217,
      33,    34,    59,    62,   524,    64,    66,   570,  -217,   800,
     800,   135,   136,   800,   800,   800,  -217,    76,    77,    78,
      79,    81,  -217,    25,  -217,  -217,  -217,  -217,  -217,  -217,
    -217,  -217,  -217,   832,  -217,  -217,   113,     4,    85,  -217,
    -217,  -217,  -217,  -217,  -217,  -217,  -217,   616,   800,   800,
     144,   800,   800,   800,   239,   124,  -217,  -217,    80,  -217,
     857,    84,  -217,  -217,  -217,  -217,  -217,  -217,  1107,   662,
     708,   800,   800,   800,   141,  -217,  -217,  -217,   800,   800,
     800,   800,   800,   800,   800,   800,   800,   800,   800,   800,
     800,   800,   800,   800,  -217,   800,   800,    -7,   108,    19,
    -217,  1347,     8,  1032,   882,   111,  1137,  1167,  1197,   119,
     800,   800,   113,   115,  -217,  -217,  -217,    13,  -217,    16,
    1227,  1257,  1287,   395,    30,    30,  -217,  -217,  -217,   290,
     290,    92,    92,    92,    92,  1397,  1372,   313,  1422,  1447,
    1057,   907,   800,  -217,   178,  -217,  -217,   800,  -217,  -217,
     800,   524,   116,   524,   932,   957,   800,  -217,  -217,  -217,
    -217,  -217,   181,   182,  -217,  -217,   982,     5,  1347,  1007,
     162,    70,  -217,   184,   184,  1317,   125,   128,  -217,   -16,
    -217,  -217,   524,   800,   120,    -2,  -217,   123,   129,   133,
      -5,    90,   155,   754,   134,  -217,   261,   524,  -217,  -217,
     524,   524,  -217,    19,    23,  -217,     6,    19,    28,   127,
    -217,     9,  -217,   524,   445,  -217,  -217,  -217,    19,   155,
    -217,   137,  -217,    19,   800,  -217,   445,  -217,  -217,   196,
    -217,  1082,  -217,  -217
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     0,     0,     0,
       0,     0,     0,     3,     0,    84,    87,    85,    86,    88,
      89,    90,     0,   114,   108,   109,   110,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     0,     0,    91,     0,
       0,     0,     0,     0,     0,     0,    14,     0,     0,     0,
       0,     0,    26,     0,    15,    18,    19,    20,    21,    22,
      23,    24,    25,     0,    56,    82,    83,     0,     0,    77,
      78,    38,    39,    40,    41,    42,    43,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    27,    28,    84,    29,
       0,    83,    76,    75,    79,    80,    73,    74,     0,     0,
       0,     0,     0,     0,     0,    13,    17,    16,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    44,     0,     0,     0,     0,     0,
      97,   101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    30,    81,    93,     0,    95,     0,
       0,     0,     0,     0,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
       0,     0,     0,    31,     0,     4,    96,     0,   103,    36,
       0,     0,     0,     0,     0,     0,     0,    92,    94,    98,
      99,   100,     0,     0,   104,    37,     0,     0,   102,     0,
      45,     0,    47,     0,     0,     0,     0,     0,    32,     0,
      33,    35,     0,     0,     0,     0,    52,     0,     0,     0,
       0,     0,     0,     0,     0,    46,     0,     0,    51,    53,
       0,     0,    50,     0,     0,     9,     0,     0,     0,     0,
     107,     0,    34,     0,    55,    49,    48,     8,     0,     0,
      11,     0,     6,     0,     0,   106,    54,     7,    10,     0,
       5,     0,    12,   105
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -217,  -217,  -217,  -217,   -11,   -32,    -8,  -216,   -33,   132,
     -78,   -58,  -217,  -217,  -217,  -217,  -217,  -217,  -217,     7,
     169,  -217,  -217,   -95,   -12,  -217,   -19
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,   106,   234,   235,    52,    53,    54,    55,
      56,    79,    57,    58,    59,    60,    61,    62,   215,   216,
      63,    64,    65,   132,    91,   224,    67
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,    85,    13,    80,   147,   149,   141,   127,   126,   250,
      23,   244,    24,    25,    26,    27,    28,    29,     5,   222,
     107,     9,    66,     4,   213,   214,     6,   256,    15,    16,
      17,    18,    19,    20,    21,   104,     1,   172,     7,    22,
      23,    66,    24,    25,    26,    27,    28,    29,    30,   209,
      31,   223,     8,    32,    33,    34,    35,    36,    37,    38,
      11,   233,    39,    40,   173,    10,   228,    41,    42,   110,
     111,   112,   142,   128,   176,   251,   210,   255,    68,   187,
     177,   177,   188,    43,   126,   177,    12,    44,   177,   248,
      45,    14,    12,   105,   253,   249,   213,   214,    81,    82,
     249,    47,    48,    49,    50,    23,    51,    24,    25,    26,
      27,    28,    29,    69,    70,    71,    72,    73,    74,    75,
      76,   175,    69,    70,    83,   217,   218,    84,   241,   108,
     109,   110,   111,   112,   193,    86,    77,    87,    94,    95,
      78,    99,   100,   101,   102,    77,   103,   135,   200,    78,
     202,   129,   143,   125,   153,   180,   237,    71,    72,    73,
      74,    75,    76,    71,    72,    73,    74,    75,    76,    66,
      23,    66,    24,    25,    26,    27,    28,    29,   174,   225,
     186,   197,   125,   201,   206,   207,   212,   139,    78,   230,
     220,   142,   142,   221,   227,   231,   254,   245,   246,   262,
      66,   236,   236,   239,   232,   242,    90,   259,    92,    93,
     238,   107,    96,    97,    98,    66,   140,   258,    66,    66,
       0,     0,   229,   107,     0,   247,     0,     0,     0,   252,
     236,    66,    66,     0,     0,     0,     0,     0,     0,     0,
     257,     0,   139,     0,    66,   260,   131,   133,   134,     0,
     136,   137,   138,    22,    23,     0,    24,    25,    26,    27,
      28,    29,     0,     0,     0,     0,     0,     0,   131,   131,
     150,   151,   152,     0,     0,     0,     0,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,   169,     0,   170,   171,     0,     0,   108,   109,
     110,   111,   112,     0,     0,     0,     0,     0,     0,   184,
     185,   113,   114,   115,   116,   117,   118,   119,   120,     0,
     121,   122,   123,     0,     0,     0,     0,   108,   109,   110,
     111,   112,     0,     0,     0,   243,     0,     0,     0,     0,
       0,   196,   115,   116,   117,   118,   198,     0,     0,   199,
     108,   109,   110,   111,   112,   205,     0,     0,     0,     0,
       0,     0,     0,   113,   114,   115,   116,   117,   118,    15,
      16,    17,    18,    19,    20,    21,     0,     0,     0,     0,
      22,    23,   226,    24,    25,    26,    27,    28,    29,    30,
       0,    31,   131,     0,    32,    33,    34,    35,    36,    37,
      38,     0,     0,    39,    40,     0,     0,     0,    41,    42,
     192,     0,    24,    25,    26,    27,    28,    29,     0,     0,
       0,     0,     0,   261,    43,     0,     0,     0,    44,     0,
       0,    45,     0,    12,    46,     0,     0,     0,     0,     0,
       0,     0,    47,    48,    49,    50,     0,    51,    15,    16,
      17,    18,    19,    20,    21,   104,     0,     0,     0,    22,
      23,     0,    24,    25,    26,    27,    28,    29,    30,     0,
      31,     0,     0,    32,    33,    34,    35,    36,    37,    38,
       0,     0,    39,    40,     0,     0,     0,    41,    42,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    43,     0,     0,     0,    44,     0,     0,
      45,     0,    12,     0,     0,     0,     0,     0,     0,     0,
       0,    47,    48,    49,    50,     0,    51,    15,    16,    17,
      18,    19,    20,    21,     0,     0,     0,     0,    22,    23,
       0,    24,    25,    26,    27,    28,    29,    30,     0,    31,
       0,     0,    32,    33,    34,    35,    36,    37,    38,     0,
       0,    39,    40,     0,     0,     0,    41,    42,     0,     0,
       0,     0,     0,    88,    16,    17,    18,    19,    20,    21,
       0,     0,    43,     0,     0,     0,    44,     0,     0,    45,
       0,    12,     0,     0,     0,     0,     0,     0,     0,     0,
      47,    48,    49,    50,    38,    51,     0,    39,    40,     0,
       0,     0,    41,    42,     0,     0,     0,     0,     0,    88,
      16,    17,    18,    19,    20,    21,     0,     0,    43,     0,
       0,     0,    44,     0,     0,    45,     0,     0,     0,     0,
       0,    89,     0,     0,     0,     0,    47,    48,    49,    50,
      38,    51,     0,    39,    40,     0,     0,     0,    41,    42,
       0,     0,     0,     0,     0,    88,    16,    17,    18,    19,
      20,    21,     0,     0,    43,     0,     0,     0,    44,     0,
       0,    45,   130,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    47,    48,    49,    50,    38,    51,     0,    39,
      40,     0,     0,     0,    41,    42,     0,     0,     0,     0,
       0,    88,    16,    17,    18,    19,    20,    21,     0,     0,
      43,     0,     0,     0,    44,     0,     0,    45,   146,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    47,    48,
      49,    50,    38,    51,     0,    39,    40,     0,     0,     0,
      41,    42,     0,     0,     0,     0,     0,    88,    16,    17,
      18,    19,    20,    21,     0,     0,    43,     0,     0,     0,
      44,     0,     0,    45,   148,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    47,    48,    49,    50,    38,    51,
       0,    39,    40,     0,     0,     0,    41,    42,     0,     0,
       0,     0,     0,    88,    16,    17,    18,    19,    20,    21,
       0,     0,    43,     0,     0,     0,    44,     0,     0,    45,
       0,     0,   240,     0,     0,     0,     0,     0,     0,     0,
      47,    48,    49,    50,    38,    51,     0,    39,    40,     0,
       0,     0,    41,    42,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    43,     0,
       0,     0,    44,     0,     0,    45,     0,     0,     0,   108,
     109,   110,   111,   112,     0,     0,    47,    48,    49,    50,
       0,    51,   113,   114,   115,   116,   117,   118,   119,   120,
       0,   121,   122,   123,   108,   109,   110,   111,   112,     0,
       0,     0,     0,   124,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,   108,
     109,   110,   111,   112,     0,     0,     0,     0,   144,     0,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
       0,   121,   122,   123,   108,   109,   110,   111,   112,     0,
       0,     0,     0,   179,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,   108,
     109,   110,   111,   112,     0,     0,     0,     0,   195,     0,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
       0,   121,   122,   123,   108,   109,   110,   111,   112,     0,
       0,     0,     0,   203,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,   108,
     109,   110,   111,   112,     0,     0,     0,     0,   204,     0,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
       0,   121,   122,   123,   108,   109,   110,   111,   112,     0,
       0,     0,     0,   208,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,   108,
     109,   110,   111,   112,     0,     0,     0,     0,   211,     0,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
       0,   121,   122,   123,   108,   109,   110,   111,   112,     0,
       0,     0,   178,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,   108,
     109,   110,   111,   112,     0,     0,     0,   194,     0,     0,
       0,     0,   113,   114,   115,   116,   117,   118,   119,   120,
       0,   121,   122,   123,   108,   109,   110,   111,   112,     0,
       0,     0,   263,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,     0,
       0,     0,     0,   145,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,     0,
       0,     0,     0,   181,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,     0,
       0,     0,     0,   182,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,     0,
       0,     0,     0,   183,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,     0,
       0,     0,     0,   189,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,     0,
       0,     0,     0,   190,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,     0,
       0,     0,     0,   191,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,     0,
       0,     0,     0,   219,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,   119,   120,     0,   121,   122,   123,   108,
     109,   110,   111,   112,     0,     0,     0,     0,     0,     0,
       0,     0,   113,   114,   115,   116,   117,   118,   119,     0,
       0,   121,   122,   123,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,     0,     0,     0,   121,   122,   123,   108,
     109,   110,   111,   112,     0,     0,     0,     0,     0,     0,
       0,     0,   113,   114,   115,   116,   117,   118,     0,     0,
       0,   121,     0,   123,   108,   109,   110,   111,   112,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,     0,     0,     0,   121
};

static const yytype_int16 yycheck[] =
{
      12,    34,    10,    22,    99,   100,    84,     3,    66,     3,
      15,   227,    17,    18,    19,    20,    21,    22,     0,    35,
      53,    22,    34,    13,    26,    27,    15,   243,     3,     4,
       5,     6,     7,     8,     9,    10,    10,    44,    16,    14,
      15,    53,    17,    18,    19,    20,    21,    22,    23,    44,
      25,    67,    65,    28,    29,    30,    31,    32,    33,    34,
      69,    66,    37,    38,    71,    66,    68,    42,    43,    39,
      40,    41,    84,    69,    66,    69,    71,    68,     3,    66,
      72,    72,    66,    58,   142,    72,    67,    62,    72,    66,
      65,    70,    67,    68,    66,    72,    26,    27,    65,    65,
      72,    76,    77,    78,    79,    15,    81,    17,    18,    19,
      20,    21,    22,    42,    43,    44,    45,    46,    47,    48,
      49,   129,    42,    43,    65,   203,   204,    65,   223,    37,
      38,    39,    40,    41,   153,    71,    65,    71,     3,     3,
      69,    65,    65,    65,    65,    65,    65,     3,   181,    69,
     183,    66,    28,    69,    13,    44,    66,    44,    45,    46,
      47,    48,    49,    44,    45,    46,    47,    48,    49,   181,
      15,   183,    17,    18,    19,    20,    21,    22,    70,   212,
      65,     3,    69,    67,     3,     3,    24,     3,    69,    66,
      65,   203,   204,    65,    74,    66,    69,   230,   231,     3,
     212,   220,   221,   222,    71,    71,    37,    70,    39,    40,
     221,   244,    43,    44,    45,   227,    84,   249,   230,   231,
      -1,    -1,   215,   256,    -1,   233,    -1,    -1,    -1,   237,
     249,   243,   244,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     248,    -1,     3,    -1,   256,   253,    77,    78,    79,    -1,
      81,    82,    83,    14,    15,    -1,    17,    18,    19,    20,
      21,    22,    -1,    -1,    -1,    -1,    -1,    -1,    99,   100,
     101,   102,   103,    -1,    -1,    -1,    -1,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,    -1,   125,   126,    -1,    -1,    37,    38,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,   140,
     141,    50,    51,    52,    53,    54,    55,    56,    57,    -1,
      59,    60,    61,    -1,    -1,    -1,    -1,    37,    38,    39,
      40,    41,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,
      -1,   172,    52,    53,    54,    55,   177,    -1,    -1,   180,
      37,    38,    39,    40,    41,   186,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    -1,    -1,
      14,    15,   213,    17,    18,    19,    20,    21,    22,    23,
      -1,    25,   223,    -1,    28,    29,    30,    31,    32,    33,
      34,    -1,    -1,    37,    38,    -1,    -1,    -1,    42,    43,
      15,    -1,    17,    18,    19,    20,    21,    22,    -1,    -1,
      -1,    -1,    -1,   254,    58,    -1,    -1,    -1,    62,    -1,
      -1,    65,    -1,    67,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    -1,    81,     3,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    -1,    14,
      15,    -1,    17,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,    -1,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    37,    38,    -1,    -1,    -1,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    -1,    -1,    -1,    62,    -1,    -1,
      65,    -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    78,    79,    -1,    81,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    -1,    -1,    14,    15,
      -1,    17,    18,    19,    20,    21,    22,    23,    -1,    25,
      -1,    -1,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    37,    38,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      -1,    -1,    58,    -1,    -1,    -1,    62,    -1,    -1,    65,
      -1,    67,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    78,    79,    34,    81,    -1,    37,    38,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,     3,
       4,     5,     6,     7,     8,     9,    -1,    -1,    58,    -1,
      -1,    -1,    62,    -1,    -1,    65,    -1,    -1,    -1,    -1,
      -1,    71,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      34,    81,    -1,    37,    38,    -1,    -1,    -1,    42,    43,
      -1,    -1,    -1,    -1,    -1,     3,     4,     5,     6,     7,
       8,     9,    -1,    -1,    58,    -1,    -1,    -1,    62,    -1,
      -1,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    34,    81,    -1,    37,
      38,    -1,    -1,    -1,    42,    43,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    -1,    -1,
      58,    -1,    -1,    -1,    62,    -1,    -1,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    34,    81,    -1,    37,    38,    -1,    -1,    -1,
      42,    43,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,     8,     9,    -1,    -1,    58,    -1,    -1,    -1,
      62,    -1,    -1,    65,    66,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    77,    78,    79,    34,    81,
      -1,    37,    38,    -1,    -1,    -1,    42,    43,    -1,    -1,
      -1,    -1,    -1,     3,     4,     5,     6,     7,     8,     9,
      -1,    -1,    58,    -1,    -1,    -1,    62,    -1,    -1,    65,
      -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    78,    79,    34,    81,    -1,    37,    38,    -1,
      -1,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,
      -1,    -1,    62,    -1,    -1,    65,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    -1,    -1,    76,    77,    78,    79,
      -1,    81,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    71,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    71,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    71,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    71,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    71,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    71,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    71,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    71,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    70,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    57,
      -1,    59,    60,    61,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      -1,    -1,    -1,    66,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      -1,    -1,    -1,    66,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      -1,    -1,    -1,    66,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      -1,    -1,    -1,    66,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      -1,    -1,    -1,    66,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      -1,    -1,    -1,    66,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      -1,    -1,    -1,    66,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    -1,
      -1,    -1,    -1,    66,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    57,    -1,    59,    60,    61,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    59,    60,    61,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    59,    60,    61,    37,
      38,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    59,    -1,    61,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    59
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    87,    88,    13,     0,    15,    16,    65,    22,
      66,    69,    67,    92,    70,     3,     4,     5,     6,     7,
       8,     9,    14,    15,    17,    18,    19,    20,    21,    22,
      23,    25,    28,    29,    30,    31,    32,    33,    34,    37,
      38,    42,    43,    58,    62,    65,    68,    76,    77,    78,
      79,    81,    92,    93,    94,    95,    96,    98,    99,   100,
     101,   102,   103,   106,   107,   108,   110,   112,     3,    42,
      43,    44,    45,    46,    47,    48,    49,    65,    69,    97,
     112,    65,    65,    65,    65,    94,    71,    71,     3,    71,
     106,   110,   106,   106,     3,     3,   106,   106,   106,    65,
      65,    65,    65,    65,    10,    68,    89,    94,    37,    38,
      39,    40,    41,    50,    51,    52,    53,    54,    55,    56,
      57,    59,    60,    61,    71,    69,    97,     3,    69,    66,
      66,   106,   109,   106,   106,     3,   106,   106,   106,     3,
      95,    96,   110,    28,    71,    66,    66,   109,    66,   109,
     106,   106,   106,    13,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,    44,    71,    70,    92,    66,    72,    70,    71,
      44,    66,    66,    66,   106,   106,    65,    66,    66,    66,
      66,    66,    15,   112,    70,    71,   106,     3,   106,   106,
      94,    67,    94,    71,    71,   106,     3,     3,    71,    44,
      71,    71,    24,    26,    27,   104,   105,    96,    96,    66,
      65,    65,    35,    67,   111,    94,   106,    74,    68,   105,
      66,    66,    71,    66,    90,    91,   112,    66,    90,   112,
      68,   109,    71,    74,    93,    94,    94,    92,    66,    72,
       3,    69,    92,    66,    69,    68,    93,    92,    91,    70,
      92,   106,     3,    70
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    86,    87,    88,    88,    89,    89,    89,    89,    90,
      90,    91,    91,    92,    92,    93,    93,    93,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    94,    94,
      94,    95,    95,    95,    95,    95,    96,    96,    97,    97,
      97,    97,    97,    97,    98,    99,    99,   100,   101,   101,
     102,   103,   104,   104,   105,   105,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   107,   107,   107,   107,   107,   107,
     107,   107,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   109,   109,   110,   110,   111,   111,   111,   112,   112,
     112,   112,   112,   112,   112
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     7,    11,     8,     7,     8,     7,     1,
       3,     2,     4,     3,     2,     1,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       3,     3,     5,     5,     7,     6,     4,     4,     1,     1,
       1,     1,     1,     1,     2,     5,     7,     5,     8,     8,
       7,     7,     1,     2,     4,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     2,     2,     2,     2,     2,     2,
       2,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     3,     4,     3,     4,     3,     4,     4,
       4,     1,     3,     4,     4,     5,     3,     2,     1,     1,
       1,     1,     1,     1,     1
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
#line 97 "parser/parser.y"
               {
        ast_root = create_program_node((yyvsp[0].node));
        (yyval.node) = ast_root;
    }
#line 1854 "parser/parser.tab.c"
    break;

  case 3:
#line 104 "parser/parser.y"
                                                          {
        (yyval.node) = create_main_class_node((yyvsp[0].node));
    }
#line 1862 "parser/parser.tab.c"
    break;

  case 4:
#line 107 "parser/parser.y"
                                                                                                     {
        (yyval.node) = create_main_class_node((yyvsp[0].node));
        free((yyvsp[-2].str_val)); // Liberar nombre del parámetro args
    }
#line 1871 "parser/parser.tab.c"
    break;

  case 5:
#line 114 "parser/parser.y"
                                                                                         {
        (yyval.node) = create_function_decl_node((yyvsp[-5].str_val), (yyvsp[-4].str_val), (yyvsp[-2].node), (yyvsp[0].node));
        free((yyvsp[-5].str_val));
        free((yyvsp[-4].str_val));
    }
#line 1881 "parser/parser.tab.c"
    break;

  case 6:
#line 119 "parser/parser.y"
                                                                            {
        (yyval.node) = create_function_decl_node((yyvsp[-4].str_val), (yyvsp[-3].str_val), NULL, (yyvsp[0].node));
        free((yyvsp[-4].str_val));
        free((yyvsp[-3].str_val));
    }
#line 1891 "parser/parser.tab.c"
    break;

  case 7:
#line 124 "parser/parser.y"
                                                                                 {
        (yyval.node) = create_function_decl_node("void", (yyvsp[-4].str_val), (yyvsp[-2].node), (yyvsp[0].node));
        free((yyvsp[-4].str_val));
    }
#line 1900 "parser/parser.tab.c"
    break;

  case 8:
#line 128 "parser/parser.y"
                                                                  {
        (yyval.node) = create_function_decl_node("void", (yyvsp[-3].str_val), NULL, (yyvsp[0].node));
        free((yyvsp[-3].str_val));
    }
#line 1909 "parser/parser.tab.c"
    break;

  case 9:
#line 135 "parser/parser.y"
              {
        ASTNode *list = create_list_node();
        add_to_list(list, (yyvsp[0].node));
        (yyval.node) = list;
    }
#line 1919 "parser/parser.tab.c"
    break;

  case 10:
#line 140 "parser/parser.y"
                                     {
        add_to_list((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 1928 "parser/parser.tab.c"
    break;

  case 11:
#line 147 "parser/parser.y"
                              {
        (yyval.node) = create_parameter_node((yyvsp[-1].str_val), (yyvsp[0].str_val), false);
        free((yyvsp[-1].str_val));
        free((yyvsp[0].str_val));
    }
#line 1938 "parser/parser.tab.c"
    break;

  case 12:
#line 152 "parser/parser.y"
                                                  {
        (yyval.node) = create_parameter_node((yyvsp[-3].str_val), (yyvsp[0].str_val), true);
        free((yyvsp[-3].str_val));
        free((yyvsp[0].str_val));
    }
#line 1948 "parser/parser.tab.c"
    break;

  case 13:
#line 160 "parser/parser.y"
                                 {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1956 "parser/parser.tab.c"
    break;

  case 14:
#line 163 "parser/parser.y"
                    {
        (yyval.node) = create_list_node();
    }
#line 1964 "parser/parser.tab.c"
    break;

  case 15:
#line 169 "parser/parser.y"
              {
        ASTNode *list = create_list_node();
        add_to_list(list, (yyvsp[0].node));
        (yyval.node) = list;
    }
#line 1974 "parser/parser.tab.c"
    break;

  case 16:
#line 174 "parser/parser.y"
                               {
        add_to_list((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1983 "parser/parser.tab.c"
    break;

  case 17:
#line 178 "parser/parser.y"
                                          {
        add_to_list((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 1992 "parser/parser.tab.c"
    break;

  case 18:
#line 185 "parser/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1998 "parser/parser.tab.c"
    break;

  case 19:
#line 186 "parser/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2004 "parser/parser.tab.c"
    break;

  case 20:
#line 187 "parser/parser.y"
                           { (yyval.node) = (yyvsp[0].node); }
#line 2010 "parser/parser.tab.c"
    break;

  case 21:
#line 188 "parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2016 "parser/parser.tab.c"
    break;

  case 22:
#line 189 "parser/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2022 "parser/parser.tab.c"
    break;

  case 23:
#line 190 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2028 "parser/parser.tab.c"
    break;

  case 24:
#line 191 "parser/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2034 "parser/parser.tab.c"
    break;

  case 25:
#line 192 "parser/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2040 "parser/parser.tab.c"
    break;

  case 26:
#line 193 "parser/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 2046 "parser/parser.tab.c"
    break;

  case 27:
#line 194 "parser/parser.y"
                      {
        (yyval.node) = create_node(NODE_BREAK_STMT, line_num, col_num);
    }
#line 2054 "parser/parser.tab.c"
    break;

  case 28:
#line 197 "parser/parser.y"
                         {
        (yyval.node) = create_node(NODE_CONTINUE_STMT, line_num, col_num);
    }
#line 2062 "parser/parser.tab.c"
    break;

  case 29:
#line 200 "parser/parser.y"
                       {
        ASTNode *node = create_node(NODE_RETURN_STMT, line_num, col_num);
        node->data.return_stmt.value = NULL;
        (yyval.node) = node;
    }
#line 2072 "parser/parser.tab.c"
    break;

  case 30:
#line 205 "parser/parser.y"
                                  {
        ASTNode *node = create_node(NODE_RETURN_STMT, line_num, col_num);
        node->data.return_stmt.value = (yyvsp[-1].node);
        (yyval.node) = node;
    }
#line 2082 "parser/parser.tab.c"
    break;

  case 31:
#line 213 "parser/parser.y"
                                        {
        (yyval.node) = create_var_decl_node((yyvsp[-2].str_val), (yyvsp[-1].str_val), NULL, false, 0);
        free((yyvsp[-2].str_val));
        free((yyvsp[-1].str_val));
    }
#line 2092 "parser/parser.tab.c"
    break;

  case 32:
#line 218 "parser/parser.y"
                                                            {
        (yyval.node) = create_var_decl_node((yyvsp[-4].str_val), (yyvsp[-3].str_val), (yyvsp[-1].node), false, 0);
        free((yyvsp[-4].str_val));
        free((yyvsp[-3].str_val));
    }
#line 2102 "parser/parser.tab.c"
    break;

  case 33:
#line 223 "parser/parser.y"
                                                            {
        (yyval.node) = create_var_decl_node((yyvsp[-4].str_val), (yyvsp[-1].str_val), NULL, true, 0);
        free((yyvsp[-4].str_val));
        free((yyvsp[-1].str_val));
    }
#line 2112 "parser/parser.tab.c"
    break;

  case 34:
#line 228 "parser/parser.y"
                                                                                        {
        (yyval.node) = create_var_decl_node((yyvsp[-6].str_val), (yyvsp[-3].str_val), (yyvsp[-1].node), true, 0);
        free((yyvsp[-6].str_val));
        free((yyvsp[-3].str_val));
    }
#line 2122 "parser/parser.tab.c"
    break;

  case 35:
#line 233 "parser/parser.y"
                                                                  {
        ASTNode *node = create_var_decl_node((yyvsp[-4].str_val), (yyvsp[-3].str_val), (yyvsp[-1].node), false, 0);
        // Marcar como constante (se puede agregar un flag al nodo)
        (yyval.node) = node;
        free((yyvsp[-4].str_val));
        free((yyvsp[-3].str_val));
    }
#line 2134 "parser/parser.tab.c"
    break;

  case 36:
#line 243 "parser/parser.y"
                                                        {
        ASTNode *left = create_identifier_node((yyvsp[-3].str_val));
        (yyval.node) = create_assignment_node(left, (yyvsp[-2].str_val), (yyvsp[-1].node));
        free((yyvsp[-3].str_val));
        free((yyvsp[-2].str_val));
    }
#line 2145 "parser/parser.tab.c"
    break;

  case 37:
#line 249 "parser/parser.y"
                                                            {
        (yyval.node) = create_assignment_node((yyvsp[-3].node), (yyvsp[-2].str_val), (yyvsp[-1].node));
        free((yyvsp[-2].str_val));
    }
#line 2154 "parser/parser.tab.c"
    break;

  case 38:
#line 256 "parser/parser.y"
           { (yyval.str_val) = strdup("="); }
#line 2160 "parser/parser.tab.c"
    break;

  case 39:
#line 257 "parser/parser.y"
                  { (yyval.str_val) = strdup("+="); }
#line 2166 "parser/parser.tab.c"
    break;

  case 40:
#line 258 "parser/parser.y"
                   { (yyval.str_val) = strdup("-="); }
#line 2172 "parser/parser.tab.c"
    break;

  case 41:
#line 259 "parser/parser.y"
                  { (yyval.str_val) = strdup("*="); }
#line 2178 "parser/parser.tab.c"
    break;

  case 42:
#line 260 "parser/parser.y"
                 { (yyval.str_val) = strdup("/="); }
#line 2184 "parser/parser.tab.c"
    break;

  case 43:
#line 261 "parser/parser.y"
                 { (yyval.str_val) = strdup("%="); }
#line 2190 "parser/parser.tab.c"
    break;

  case 44:
#line 265 "parser/parser.y"
                         {
        ASTNode *node = create_node(NODE_EXPRESSION_STMT, line_num, col_num);
        node->data.program.body = (yyvsp[-1].node); // Reutilizar campo para expresión
        (yyval.node) = node;
    }
#line 2200 "parser/parser.tab.c"
    break;

  case 45:
#line 273 "parser/parser.y"
                                          {
        (yyval.node) = create_if_node((yyvsp[-2].node), (yyvsp[0].node), NULL);
    }
#line 2208 "parser/parser.tab.c"
    break;

  case 46:
#line 276 "parser/parser.y"
                                                           {
        (yyval.node) = create_if_node((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2216 "parser/parser.tab.c"
    break;

  case 47:
#line 282 "parser/parser.y"
                                             {
        (yyval.node) = create_while_node((yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2224 "parser/parser.tab.c"
    break;

  case 48:
#line 288 "parser/parser.y"
                                                                                               {
        // Crear nodo for sin punto y coma extra
        ASTNode *init = (yyvsp[-5].node);
        ASTNode *condition = (yyvsp[-4].node);
        ASTNode *update = (yyvsp[-2].node);
        ASTNode *body = (yyvsp[0].node);
        (yyval.node) = create_for_node(init, condition, update, body);
    }
#line 2237 "parser/parser.tab.c"
    break;

  case 49:
#line 296 "parser/parser.y"
                                                                                                 {
        (yyval.node) = create_for_node((yyvsp[-5].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2245 "parser/parser.tab.c"
    break;

  case 50:
#line 302 "parser/parser.y"
                                                          {
        ASTNode *node = create_node(NODE_DO_WHILE_STMT, line_num, col_num);
        node->data.while_stmt.body = (yyvsp[-5].node);
        node->data.while_stmt.condition = (yyvsp[-2].node);
        (yyval.node) = node;
    }
#line 2256 "parser/parser.tab.c"
    break;

  case 51:
#line 311 "parser/parser.y"
                                                            {
        ASTNode *node = create_node(NODE_SWITCH_STMT, line_num, col_num);
        node->data.switch_stmt.expression = (yyvsp[-4].node);
        node->data.switch_stmt.cases = (yyvsp[-1].node);
        (yyval.node) = node;
    }
#line 2267 "parser/parser.tab.c"
    break;

  case 52:
#line 320 "parser/parser.y"
                   {
        ASTNode *list = create_list_node();
        add_to_list(list, (yyvsp[0].node));
        (yyval.node) = list;
    }
#line 2277 "parser/parser.tab.c"
    break;

  case 53:
#line 325 "parser/parser.y"
                               {
        add_to_list((yyvsp[-1].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2286 "parser/parser.tab.c"
    break;

  case 54:
#line 332 "parser/parser.y"
                                         {
        ASTNode *node = create_node(NODE_CASE_STMT, line_num, col_num);
        node->data.case_stmt.value = (yyvsp[-2].node);
        node->data.case_stmt.statements = (yyvsp[0].node);
        (yyval.node) = node;
    }
#line 2297 "parser/parser.tab.c"
    break;

  case 55:
#line 338 "parser/parser.y"
                                   {
        ASTNode *node = create_node(NODE_CASE_STMT, line_num, col_num);
        node->data.case_stmt.value = NULL;  // NULL indica default
        node->data.case_stmt.statements = (yyvsp[0].node);
        (yyval.node) = node;
    }
#line 2308 "parser/parser.tab.c"
    break;

  case 56:
#line 347 "parser/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 2314 "parser/parser.tab.c"
    break;

  case 57:
#line 348 "parser/parser.y"
                                 {
        (yyval.node) = create_binary_op_node("+", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2322 "parser/parser.tab.c"
    break;

  case 58:
#line 351 "parser/parser.y"
                                  {
        (yyval.node) = create_binary_op_node("-", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2330 "parser/parser.tab.c"
    break;

  case 59:
#line 354 "parser/parser.y"
                                     {
        (yyval.node) = create_binary_op_node("*", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2338 "parser/parser.tab.c"
    break;

  case 60:
#line 357 "parser/parser.y"
                                   {
        (yyval.node) = create_binary_op_node("/", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2346 "parser/parser.tab.c"
    break;

  case 61:
#line 360 "parser/parser.y"
                                   {
        (yyval.node) = create_binary_op_node("%", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2354 "parser/parser.tab.c"
    break;

  case 62:
#line 363 "parser/parser.y"
                                  {
        (yyval.node) = create_binary_op_node("==", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2362 "parser/parser.tab.c"
    break;

  case 63:
#line 366 "parser/parser.y"
                                      {
        (yyval.node) = create_binary_op_node("!=", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2370 "parser/parser.tab.c"
    break;

  case 64:
#line 369 "parser/parser.y"
                                 {
        (yyval.node) = create_binary_op_node("<", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2378 "parser/parser.tab.c"
    break;

  case 65:
#line 372 "parser/parser.y"
                                       {
        (yyval.node) = create_binary_op_node("<=", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2386 "parser/parser.tab.c"
    break;

  case 66:
#line 375 "parser/parser.y"
                                    {
        (yyval.node) = create_binary_op_node(">", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2394 "parser/parser.tab.c"
    break;

  case 67:
#line 378 "parser/parser.y"
                                          {
        (yyval.node) = create_binary_op_node(">=", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2402 "parser/parser.tab.c"
    break;

  case 68:
#line 381 "parser/parser.y"
                                {
        (yyval.node) = create_binary_op_node("&&", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2410 "parser/parser.tab.c"
    break;

  case 69:
#line 384 "parser/parser.y"
                               {
        (yyval.node) = create_binary_op_node("||", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2418 "parser/parser.tab.c"
    break;

  case 70:
#line 387 "parser/parser.y"
                                    {
        (yyval.node) = create_binary_op_node("&", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2426 "parser/parser.tab.c"
    break;

  case 71:
#line 390 "parser/parser.y"
                                   {
        (yyval.node) = create_binary_op_node("|", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2434 "parser/parser.tab.c"
    break;

  case 72:
#line 393 "parser/parser.y"
                                    {
        (yyval.node) = create_binary_op_node("^", (yyvsp[-2].node), (yyvsp[0].node));
    }
#line 2442 "parser/parser.tab.c"
    break;

  case 73:
#line 396 "parser/parser.y"
                     {
        (yyval.node) = create_unary_op_node("!", (yyvsp[0].node), true);
    }
#line 2450 "parser/parser.tab.c"
    break;

  case 74:
#line 399 "parser/parser.y"
                         {
        (yyval.node) = create_unary_op_node("~", (yyvsp[0].node), true);
    }
#line 2458 "parser/parser.tab.c"
    break;

  case 75:
#line 402 "parser/parser.y"
                                         {
        (yyval.node) = create_unary_op_node("-", (yyvsp[0].node), true);
    }
#line 2466 "parser/parser.tab.c"
    break;

  case 76:
#line 405 "parser/parser.y"
                                       {
        (yyval.node) = create_unary_op_node("+", (yyvsp[0].node), true);
    }
#line 2474 "parser/parser.tab.c"
    break;

  case 77:
#line 408 "parser/parser.y"
                           {
        ASTNode *id = create_identifier_node((yyvsp[-1].str_val));
        (yyval.node) = create_unary_op_node("++", id, false);
        free((yyvsp[-1].str_val));
    }
#line 2484 "parser/parser.tab.c"
    break;

  case 78:
#line 413 "parser/parser.y"
                           {
        ASTNode *id = create_identifier_node((yyvsp[-1].str_val));
        (yyval.node) = create_unary_op_node("--", id, false);
        free((yyvsp[-1].str_val));
    }
#line 2494 "parser/parser.tab.c"
    break;

  case 79:
#line 418 "parser/parser.y"
                           {
        ASTNode *id = create_identifier_node((yyvsp[0].str_val));
        (yyval.node) = create_unary_op_node("++", id, true);
        free((yyvsp[0].str_val));
    }
#line 2504 "parser/parser.tab.c"
    break;

  case 80:
#line 423 "parser/parser.y"
                           {
        ASTNode *id = create_identifier_node((yyvsp[0].str_val));
        (yyval.node) = create_unary_op_node("--", id, true);
        free((yyvsp[0].str_val));
    }
#line 2514 "parser/parser.tab.c"
    break;

  case 81:
#line 428 "parser/parser.y"
                               {
        (yyval.node) = (yyvsp[-1].node);
    }
#line 2522 "parser/parser.tab.c"
    break;

  case 82:
#line 431 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2528 "parser/parser.tab.c"
    break;

  case 83:
#line 432 "parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 2534 "parser/parser.tab.c"
    break;

  case 84:
#line 436 "parser/parser.y"
               {
        (yyval.node) = create_identifier_node((yyvsp[0].str_val));
        free((yyvsp[0].str_val));
    }
#line 2543 "parser/parser.tab.c"
    break;

  case 85:
#line 440 "parser/parser.y"
                  {
        (yyval.node) = create_int_literal_node((yyvsp[0].int_val));
    }
#line 2551 "parser/parser.tab.c"
    break;

  case 86:
#line 443 "parser/parser.y"
                    {
        (yyval.node) = create_float_literal_node((yyvsp[0].float_val));
    }
#line 2559 "parser/parser.tab.c"
    break;

  case 87:
#line 446 "parser/parser.y"
                     {
        (yyval.node) = create_string_literal_node((yyvsp[0].str_val));
        free((yyvsp[0].str_val));
    }
#line 2568 "parser/parser.tab.c"
    break;

  case 88:
#line 450 "parser/parser.y"
                   {
        (yyval.node) = create_char_literal_node((yyvsp[0].char_val));
    }
#line 2576 "parser/parser.tab.c"
    break;

  case 89:
#line 453 "parser/parser.y"
           {
        (yyval.node) = create_boolean_literal_node(true);
    }
#line 2584 "parser/parser.tab.c"
    break;

  case 90:
#line 456 "parser/parser.y"
            {
        (yyval.node) = create_boolean_literal_node(false);
    }
#line 2592 "parser/parser.tab.c"
    break;

  case 91:
#line 459 "parser/parser.y"
               {
        (yyval.node) = create_null_literal_node();
    }
#line 2600 "parser/parser.tab.c"
    break;

  case 92:
#line 465 "parser/parser.y"
                                        {
        (yyval.node) = create_function_call_node("System.out.println", (yyvsp[-1].node));
    }
#line 2608 "parser/parser.tab.c"
    break;

  case 93:
#line 468 "parser/parser.y"
                            {
        (yyval.node) = create_function_call_node("System.out.println", NULL);
    }
#line 2616 "parser/parser.tab.c"
    break;

  case 94:
#line 471 "parser/parser.y"
                                        {
        (yyval.node) = create_function_call_node("System.out.print", (yyvsp[-1].node));
    }
#line 2624 "parser/parser.tab.c"
    break;

  case 95:
#line 474 "parser/parser.y"
                          {
        (yyval.node) = create_function_call_node("System.out.print", NULL);
    }
#line 2632 "parser/parser.tab.c"
    break;

  case 96:
#line 477 "parser/parser.y"
                                             {
        (yyval.node) = create_function_call_node((yyvsp[-3].str_val), (yyvsp[-1].node));
        free((yyvsp[-3].str_val));
    }
#line 2641 "parser/parser.tab.c"
    break;

  case 97:
#line 481 "parser/parser.y"
                               {
        (yyval.node) = create_function_call_node((yyvsp[-2].str_val), NULL);
        free((yyvsp[-2].str_val));
    }
#line 2650 "parser/parser.tab.c"
    break;

  case 98:
#line 485 "parser/parser.y"
                                         {
        (yyval.node) = create_function_call_node("Integer.parseInt", (yyvsp[-1].node));
    }
#line 2658 "parser/parser.tab.c"
    break;

  case 99:
#line 488 "parser/parser.y"
                                           {
        (yyval.node) = create_function_call_node("Float.parseFloat", (yyvsp[-1].node));
    }
#line 2666 "parser/parser.tab.c"
    break;

  case 100:
#line 491 "parser/parser.y"
                                        {
        (yyval.node) = create_function_call_node("String.valueOf", (yyvsp[-1].node));
    }
#line 2674 "parser/parser.tab.c"
    break;

  case 101:
#line 497 "parser/parser.y"
               {
        ASTNode *list = create_list_node();
        add_to_list(list, (yyvsp[0].node));
        (yyval.node) = list;
    }
#line 2684 "parser/parser.tab.c"
    break;

  case 102:
#line 502 "parser/parser.y"
                                     {
        add_to_list((yyvsp[-2].node), (yyvsp[0].node));
        (yyval.node) = (yyvsp[-2].node);
    }
#line 2693 "parser/parser.tab.c"
    break;

  case 103:
#line 509 "parser/parser.y"
                                            {
        ASTNode *array = create_identifier_node((yyvsp[-3].str_val));
        (yyval.node) = create_array_access_node(array, (yyvsp[-1].node));
        free((yyvsp[-3].str_val));
    }
#line 2703 "parser/parser.tab.c"
    break;

  case 104:
#line 514 "parser/parser.y"
                                                {
        (yyval.node) = create_array_access_node((yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 2711 "parser/parser.tab.c"
    break;

  case 105:
#line 520 "parser/parser.y"
                                                    {
        ASTNode *node = create_node(NODE_ARRAY_INIT, line_num, col_num);
        node->data.array_init.type = (yyvsp[-3].str_val);
        node->data.array_init.size = (yyvsp[-1].node);
        node->data.array_init.values = NULL;
        (yyval.node) = node;
    }
#line 2723 "parser/parser.tab.c"
    break;

  case 106:
#line 527 "parser/parser.y"
                                  {
        ASTNode *node = create_node(NODE_ARRAY_INIT, line_num, col_num);
        node->data.array_init.type = NULL;
        node->data.array_init.size = NULL;
        node->data.array_init.values = (yyvsp[-1].node);
        (yyval.node) = node;
    }
#line 2735 "parser/parser.tab.c"
    break;

  case 107:
#line 534 "parser/parser.y"
                    {
        ASTNode *node = create_node(NODE_ARRAY_INIT, line_num, col_num);
        node->data.array_init.type = NULL;
        node->data.array_init.size = NULL;
        node->data.array_init.values = create_list_node();
        (yyval.node) = node;
    }
#line 2747 "parser/parser.tab.c"
    break;

  case 108:
#line 544 "parser/parser.y"
        { (yyval.str_val) = strdup("int"); }
#line 2753 "parser/parser.tab.c"
    break;

  case 109:
#line 545 "parser/parser.y"
            { (yyval.str_val) = strdup("float"); }
#line 2759 "parser/parser.tab.c"
    break;

  case 110:
#line 546 "parser/parser.y"
             { (yyval.str_val) = strdup("double"); }
#line 2765 "parser/parser.tab.c"
    break;

  case 111:
#line 547 "parser/parser.y"
              { (yyval.str_val) = strdup("boolean"); }
#line 2771 "parser/parser.tab.c"
    break;

  case 112:
#line 548 "parser/parser.y"
           { (yyval.str_val) = strdup("char"); }
#line 2777 "parser/parser.tab.c"
    break;

  case 113:
#line 549 "parser/parser.y"
                  { (yyval.str_val) = strdup("String"); }
#line 2783 "parser/parser.tab.c"
    break;

  case 114:
#line 550 "parser/parser.y"
           { (yyval.str_val) = strdup("void"); }
#line 2789 "parser/parser.tab.c"
    break;


#line 2793 "parser/parser.tab.c"

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
#line 553 "parser/parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error sintáctico en línea %d, columna %d: %s\n", line_num, col_num, s);
    add_error(ERROR_SYNTACTIC, s, "Global", line_num, col_num);
}
