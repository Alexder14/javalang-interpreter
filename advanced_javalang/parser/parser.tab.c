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

#include "../include/javalang.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE *yyin;
extern int line_num;
extern int col_num;

void yyerror(const char *s);

ASTNode *ast_root = NULL;

#line 87 "parser/parser.tab.c"

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

#line 201 "parser/parser.tab.c"

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
typedef yytype_uint8 yy_state_t;

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
#define YYLAST   423

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  25
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  175

#define YYUNDEFTOK  2
#define YYMAXUTOK   309


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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    58,    58,    65,    69,    75,    79,    83,    89,    93,
      98,   103,   111,   115,   119,   125,   128,   134,   138,   142,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   159,
     162,   166,   169,   173,   177,   181,   187,   194,   199,   208,
     216,   226,   234,   238,   242,   251,   261,   265,   269,   275,
     276,   277,   281,   286,   291,   296,   301,   306,   311,   316,
     324,   328,   335,   338,   342,   346,   349,   353,   357,   360,
     361,   365,   369,   376,   380,   384
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IDENTIFIER", "STRING_LITERAL",
  "INT_LITERAL", "FLOAT_LITERAL", "PUBLIC", "STATIC", "VOID", "INT",
  "FLOAT", "DOUBLE", "BOOLEAN", "STRING", "CLASS", "MAIN", "IF", "ELSE",
  "WHILE", "FOR", "SWITCH", "CASE", "DEFAULT", "BREAK", "CONTINUE",
  "RETURN", "TRUE", "FALSE", "NULL_LITERAL", "PRINTLN", "LBRACE", "RBRACE",
  "LPAREN", "RPAREN", "LBRACKET", "RBRACKET", "SEMICOLON", "COMMA",
  "COLON", "ASSIGN", "PLUS", "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "EQ",
  "NE", "LT", "LE", "GT", "GE", "AND", "OR", "NOT", "$accept", "program",
  "class_declaration", "method_list", "method_declaration",
  "parameter_list", "parameter", "statement_list", "statement",
  "variable_declaration", "assignment", "if_statement", "while_statement",
  "for_statement", "switch_statement", "case_list", "case_statement",
  "expression_statement", "return_statement", "expression",
  "binary_expression", "unary_expression", "primary_expression",
  "function_call", "argument_list", YY_NULLPTR
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
     305,   306,   307,   308,   309
};
# endif

#define YYPACT_NINF (-88)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       0,     7,    34,   -88,    38,   -88,    15,    -4,    41,   -88,
      -3,   -88,    50,   -88,   -88,     2,    49,    43,    53,    59,
      17,    -1,    17,    68,    60,    10,   -88,    65,    13,    35,
     -88,    67,    73,    17,   322,    76,    78,   107,   322,   -88,
     -23,   -88,   -88,   -88,     3,   108,   111,    82,    83,    84,
      85,    87,    88,    52,   -88,   -88,   -88,    86,   322,    52,
      52,    52,   117,   -88,    89,    92,   -88,   -88,   -88,   -88,
      93,    98,   110,   -88,   -88,   -88,   -88,   322,   322,   -88,
     158,    52,    52,    99,   104,   115,   125,    52,    52,   163,
      52,   -88,   -88,   134,   110,    52,   199,   324,    40,   -88,
     -88,   -88,   -88,   -88,   -88,   -88,    52,    52,    52,    52,
      52,    52,    52,    52,   240,   281,   -88,   110,    36,   110,
      52,   167,    52,    52,   339,   350,   133,   137,   361,    55,
     -88,   -88,    40,    40,   -88,   -88,   -18,   -18,    58,    58,
     -88,   -88,   -88,    52,   110,   -88,   110,   110,   322,   322,
      52,   145,   -88,   110,   162,   -88,   373,   159,   322,   163,
     187,   -11,   -88,   -88,   160,   154,   156,   -88,   -88,   322,
     322,   322,   -88,   322,   322
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     0,     1,     0,     0,     0,     4,
       0,     6,     0,     3,     5,     0,     0,     0,     0,     0,
      14,    14,    14,     0,     0,     0,    13,     0,     0,     0,
      15,     0,     0,     0,    19,     0,     0,     0,    19,    12,
      62,    65,    63,    64,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    48,    66,    67,    68,     0,    19,     0,
       0,     0,     0,    18,     0,     0,    23,    24,    25,    26,
       0,     0,    46,    49,    50,    51,    69,    19,    19,    16,
       0,    75,     0,    31,     0,     0,     0,     0,     0,     0,
       0,    28,    29,    62,    47,    75,     0,     0,    61,    60,
       8,    17,    20,    21,    22,    27,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    11,    74,     0,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      30,    70,    52,    53,    54,    55,    56,    57,    58,    59,
       9,    10,    72,     0,    32,    35,    33,    34,     0,     0,
       0,     0,    71,    73,    37,    39,     0,     0,     0,     0,
       0,     0,    43,    38,     0,     0,     0,    41,    42,     0,
      19,    19,    40,    45,    44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -88,   -88,   -88,   -88,   186,    69,   164,   -38,   -61,   -88,
     -87,   -88,   -88,   -88,   -88,   -88,    37,   -88,   -88,   -45,
     -88,   -88,   -88,   -88,   106
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    10,    11,    25,    26,    62,    63,    64,
      65,    66,    67,    68,    69,   161,   162,    70,    71,    72,
      73,    74,    75,    76,   118
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      80,   101,   127,     8,     8,    17,    83,     1,    94,    23,
      81,   160,   166,    24,    97,    98,    99,    82,    18,   101,
      96,   167,     4,   106,   107,   108,   109,    23,     9,    13,
     112,    24,   113,    27,     5,   101,   117,   119,    84,   114,
     115,     6,   124,   125,    32,   128,     7,    35,    33,    12,
     117,    33,    19,   101,   101,    93,    41,    42,    43,    15,
      16,   132,   133,   134,   135,   136,   137,   138,   139,    36,
     142,    30,   164,    33,   143,   144,    20,   146,   147,    54,
      55,    56,    57,   108,   109,    59,    21,   154,   155,   152,
      28,    29,    22,   143,    60,    31,    34,   163,   153,   106,
     107,   108,   109,    37,    38,   156,    61,    77,   172,    78,
      79,    85,   101,   101,    86,    87,    88,    89,    90,    95,
      40,    41,    42,    43,    91,    92,   102,    44,    45,   103,
     104,    46,   173,   174,    47,   105,    48,    49,    50,   120,
     121,    51,    52,    53,    54,    55,    56,    57,    58,   100,
      59,   106,   107,   108,   109,   122,   110,   111,   112,    60,
     113,    40,    41,    42,    43,   123,   126,    81,    44,    45,
     145,    61,    46,    82,   150,    47,   157,    48,    49,    50,
     158,   160,    51,    52,    53,    54,    55,    56,    57,    58,
     116,    59,   165,   170,   169,   171,    14,    39,   168,     0,
      60,   129,    40,    41,    42,    43,     0,     0,     0,    44,
      45,     0,    61,    46,     0,     0,    47,     0,    48,    49,
      50,     0,     0,    51,    52,    53,    54,    55,    56,    57,
      58,   130,    59,     0,     0,     0,     0,     0,     0,     0,
       0,    60,     0,    40,    41,    42,    43,     0,     0,     0,
      44,    45,     0,    61,    46,     0,     0,    47,     0,    48,
      49,    50,     0,     0,    51,    52,    53,    54,    55,    56,
      57,    58,   140,    59,     0,     0,     0,     0,     0,     0,
       0,     0,    60,     0,    40,    41,    42,    43,     0,     0,
       0,    44,    45,     0,    61,    46,     0,     0,    47,     0,
      48,    49,    50,     0,     0,    51,    52,    53,    54,    55,
      56,    57,    58,   141,    59,     0,     0,     0,     0,     0,
       0,     0,     0,    60,     0,    40,    41,    42,    43,     0,
       0,     0,    44,    45,     0,    61,    46,     0,     0,    47,
       0,    48,    49,    50,     0,     0,    51,    52,    53,    54,
      55,    56,    57,    58,     0,    59,     0,     0,   131,     0,
       0,     0,     0,     0,    60,   106,   107,   108,   109,     0,
     110,   111,   112,   148,   113,     0,    61,     0,     0,     0,
     106,   107,   108,   109,   149,   110,   111,   112,     0,   113,
       0,   106,   107,   108,   109,   151,   110,   111,   112,     0,
     113,     0,   106,   107,   108,   109,     0,   110,   111,   112,
     159,   113,     0,     0,   106,   107,   108,   109,     0,   110,
     111,   112,     0,   113
};

static const yytype_int16 yycheck[] =
{
      38,    62,    89,     7,     7,     3,     3,     7,    53,    10,
      33,    22,    23,    14,    59,    60,    61,    40,    16,    80,
      58,    32,    15,    41,    42,    43,    44,    10,    32,    32,
      48,    14,    50,    34,     0,    96,    81,    82,    35,    77,
      78,     3,    87,    88,    34,    90,    31,    34,    38,     8,
      95,    38,     3,   114,   115,     3,     4,     5,     6,     9,
      10,   106,   107,   108,   109,   110,   111,   112,   113,    34,
      34,     3,   159,    38,    38,   120,    33,   122,   123,    27,
      28,    29,    30,    43,    44,    33,    33,   148,   149,    34,
      21,    22,    33,    38,    42,    35,    31,   158,   143,    41,
      42,    43,    44,    36,    31,   150,    54,    31,   169,    31,
       3,     3,   173,   174,     3,    33,    33,    33,    33,    33,
       3,     4,     5,     6,    37,    37,    37,    10,    11,    37,
      37,    14,   170,   171,    17,    37,    19,    20,    21,    40,
      36,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    41,    42,    43,    44,    40,    46,    47,    48,    42,
      50,     3,     4,     5,     6,    40,     3,    33,    10,    11,
       3,    54,    14,    40,    37,    17,    31,    19,    20,    21,
      18,    22,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,     5,    39,    34,    39,    10,    33,   161,    -1,
      42,    95,     3,     4,     5,     6,    -1,    -1,    -1,    10,
      11,    -1,    54,    14,    -1,    -1,    17,    -1,    19,    20,
      21,    -1,    -1,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    42,    -1,     3,     4,     5,     6,    -1,    -1,    -1,
      10,    11,    -1,    54,    14,    -1,    -1,    17,    -1,    19,
      20,    21,    -1,    -1,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    42,    -1,     3,     4,     5,     6,    -1,    -1,
      -1,    10,    11,    -1,    54,    14,    -1,    -1,    17,    -1,
      19,    20,    21,    -1,    -1,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    42,    -1,     3,     4,     5,     6,    -1,
      -1,    -1,    10,    11,    -1,    54,    14,    -1,    -1,    17,
      -1,    19,    20,    21,    -1,    -1,    24,    25,    26,    27,
      28,    29,    30,    31,    -1,    33,    -1,    -1,    34,    -1,
      -1,    -1,    -1,    -1,    42,    41,    42,    43,    44,    -1,
      46,    47,    48,    34,    50,    -1,    54,    -1,    -1,    -1,
      41,    42,    43,    44,    34,    46,    47,    48,    -1,    50,
      -1,    41,    42,    43,    44,    34,    46,    47,    48,    -1,
      50,    -1,    41,    42,    43,    44,    -1,    46,    47,    48,
      37,    50,    -1,    -1,    41,    42,    43,    44,    -1,    46,
      47,    48,    -1,    50
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,    56,    57,    15,     0,     3,    31,     7,    32,
      58,    59,     8,    32,    59,     9,    10,     3,    16,     3,
      33,    33,    33,    10,    14,    60,    61,    34,    60,    60,
       3,    35,    34,    38,    31,    34,    34,    36,    31,    61,
       3,     4,     5,     6,    10,    11,    14,    17,    19,    20,
      21,    24,    25,    26,    27,    28,    29,    30,    31,    33,
      42,    54,    62,    63,    64,    65,    66,    67,    68,    69,
      72,    73,    74,    75,    76,    77,    78,    31,    31,     3,
      62,    33,    40,     3,    35,     3,     3,    33,    33,    33,
      33,    37,    37,     3,    74,    33,    62,    74,    74,    74,
      32,    63,    37,    37,    37,    37,    41,    42,    43,    44,
      46,    47,    48,    50,    62,    62,    32,    74,    79,    74,
      40,    36,    40,    40,    74,    74,     3,    65,    74,    79,
      32,    34,    74,    74,    74,    74,    74,    74,    74,    74,
      32,    32,    34,    38,    74,     3,    74,    74,    34,    34,
      37,    34,    34,    74,    63,    63,    74,    31,    18,    37,
      22,    70,    71,    63,    65,     5,    23,    32,    71,    34,
      39,    39,    63,    62,    62
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    55,    56,    57,    57,    58,    58,    58,    59,    59,
      59,    59,    60,    60,    60,    61,    61,    62,    62,    62,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    64,    64,    64,    64,    64,    65,    66,    66,    67,
      68,    69,    70,    70,    70,    71,    72,    73,    73,    74,
      74,    74,    75,    75,    75,    75,    75,    75,    75,    75,
      76,    76,    77,    77,    77,    77,    77,    77,    77,    77,
      77,    78,    78,    79,    79,    79
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     6,     5,     2,     1,     0,     9,    10,
      10,    10,     3,     1,     0,     2,     4,     2,     1,     0,
       2,     2,     2,     1,     1,     1,     1,     2,     2,     2,
       3,     2,     4,     4,     4,     4,     3,     5,     7,     5,
       9,     7,     2,     1,     4,     4,     1,     2,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     4,     4,     3,     1,     0
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
#line 58 "parser/parser.y"
                      {
        ast_root = (yyvsp[0].node);
        (yyval.node) = (yyvsp[0].node);
    }
#line 1549 "parser/parser.tab.c"
    break;

  case 3:
#line 65 "parser/parser.y"
                                                      {
        (yyval.node) = create_node(NODE_CLASS, (yyvsp[-3].string_val), line_num, col_num);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1558 "parser/parser.tab.c"
    break;

  case 4:
#line 69 "parser/parser.y"
                                            {
        (yyval.node) = create_node(NODE_CLASS, (yyvsp[-2].string_val), line_num, col_num);
    }
#line 1566 "parser/parser.tab.c"
    break;

  case 5:
#line 75 "parser/parser.y"
                                   {
        (yyval.node) = (yyvsp[-1].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1575 "parser/parser.tab.c"
    break;

  case 6:
#line 79 "parser/parser.y"
                         {
        (yyval.node) = create_node(NODE_PROGRAM, "methods", line_num, col_num);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1584 "parser/parser.tab.c"
    break;

  case 7:
#line 83 "parser/parser.y"
                  {
        (yyval.node) = create_node(NODE_PROGRAM, "empty_methods", line_num, col_num);
    }
#line 1592 "parser/parser.tab.c"
    break;

  case 8:
#line 89 "parser/parser.y"
                                                                       {
        (yyval.node) = create_node(NODE_MAIN_METHOD, "main", line_num, col_num);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1601 "parser/parser.tab.c"
    break;

  case 9:
#line 93 "parser/parser.y"
                                                                                        {
        (yyval.node) = create_node(NODE_MAIN_METHOD, "main", line_num, col_num);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1611 "parser/parser.tab.c"
    break;

  case 10:
#line 98 "parser/parser.y"
                                                                                             {
        (yyval.node) = create_node(NODE_METHOD, (yyvsp[-6].string_val), line_num, col_num);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1621 "parser/parser.tab.c"
    break;

  case 11:
#line 103 "parser/parser.y"
                                                                                              {
        (yyval.node) = create_node(NODE_METHOD, (yyvsp[-6].string_val), line_num, col_num);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1631 "parser/parser.tab.c"
    break;

  case 12:
#line 111 "parser/parser.y"
                                   {
        (yyval.node) = (yyvsp[-2].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1640 "parser/parser.tab.c"
    break;

  case 13:
#line 115 "parser/parser.y"
                {
        (yyval.node) = create_node(NODE_BLOCK, "parameters", line_num, col_num);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1649 "parser/parser.tab.c"
    break;

  case 14:
#line 119 "parser/parser.y"
                  {
        (yyval.node) = create_node(NODE_BLOCK, "empty_params", line_num, col_num);
    }
#line 1657 "parser/parser.tab.c"
    break;

  case 15:
#line 125 "parser/parser.y"
                   {
        (yyval.node) = create_node(NODE_VAR_DECL, (yyvsp[0].string_val), line_num, col_num);
    }
#line 1665 "parser/parser.tab.c"
    break;

  case 16:
#line 128 "parser/parser.y"
                                          {
        (yyval.node) = create_node(NODE_ARRAY_DECL, (yyvsp[0].string_val), line_num, col_num);
    }
#line 1673 "parser/parser.tab.c"
    break;

  case 17:
#line 134 "parser/parser.y"
                             {
        (yyval.node) = (yyvsp[-1].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1682 "parser/parser.tab.c"
    break;

  case 18:
#line 138 "parser/parser.y"
                {
        (yyval.node) = create_node(NODE_BLOCK, "statements", line_num, col_num);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1691 "parser/parser.tab.c"
    break;

  case 19:
#line 142 "parser/parser.y"
                  {
        (yyval.node) = create_node(NODE_BLOCK, "empty_block", line_num, col_num);
    }
#line 1699 "parser/parser.tab.c"
    break;

  case 20:
#line 148 "parser/parser.y"
                                   { (yyval.node) = (yyvsp[-1].node); }
#line 1705 "parser/parser.tab.c"
    break;

  case 21:
#line 149 "parser/parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 1711 "parser/parser.tab.c"
    break;

  case 22:
#line 150 "parser/parser.y"
                                     { (yyval.node) = (yyvsp[-1].node); }
#line 1717 "parser/parser.tab.c"
    break;

  case 23:
#line 151 "parser/parser.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1723 "parser/parser.tab.c"
    break;

  case 24:
#line 152 "parser/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1729 "parser/parser.tab.c"
    break;

  case 25:
#line 153 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1735 "parser/parser.tab.c"
    break;

  case 26:
#line 154 "parser/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 1741 "parser/parser.tab.c"
    break;

  case 27:
#line 155 "parser/parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 1747 "parser/parser.tab.c"
    break;

  case 28:
#line 156 "parser/parser.y"
                      {
        (yyval.node) = create_node(NODE_BREAK, "break", line_num, col_num);
    }
#line 1755 "parser/parser.tab.c"
    break;

  case 29:
#line 159 "parser/parser.y"
                         {
        (yyval.node) = create_node(NODE_CONTINUE, "continue", line_num, col_num);
    }
#line 1763 "parser/parser.tab.c"
    break;

  case 30:
#line 162 "parser/parser.y"
                                   { (yyval.node) = (yyvsp[-1].node); }
#line 1769 "parser/parser.tab.c"
    break;

  case 31:
#line 166 "parser/parser.y"
                   {
        (yyval.node) = create_node(NODE_VAR_DECL, (yyvsp[0].string_val), line_num, col_num);
    }
#line 1777 "parser/parser.tab.c"
    break;

  case 32:
#line 169 "parser/parser.y"
                                       {
        (yyval.node) = create_node(NODE_VAR_DECL, (yyvsp[-2].string_val), line_num, col_num);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1786 "parser/parser.tab.c"
    break;

  case 33:
#line 173 "parser/parser.y"
                                         {
        (yyval.node) = create_node(NODE_VAR_DECL, (yyvsp[-2].string_val), line_num, col_num);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1795 "parser/parser.tab.c"
    break;

  case 34:
#line 177 "parser/parser.y"
                                          {
        (yyval.node) = create_node(NODE_VAR_DECL, (yyvsp[-2].string_val), line_num, col_num);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1804 "parser/parser.tab.c"
    break;

  case 35:
#line 181 "parser/parser.y"
                                       {
        (yyval.node) = create_node(NODE_ARRAY_DECL, (yyvsp[0].string_val), line_num, col_num);
    }
#line 1812 "parser/parser.tab.c"
    break;

  case 36:
#line 187 "parser/parser.y"
                                 {
        (yyval.node) = create_node(NODE_ASSIGNMENT, (yyvsp[-2].string_val), line_num, col_num);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1821 "parser/parser.tab.c"
    break;

  case 37:
#line 194 "parser/parser.y"
                                          {
        (yyval.node) = create_node(NODE_IF, "if", line_num, col_num);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1831 "parser/parser.tab.c"
    break;

  case 38:
#line 199 "parser/parser.y"
                                                           {
        (yyval.node) = create_node(NODE_IF, "if", line_num, col_num);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1842 "parser/parser.tab.c"
    break;

  case 39:
#line 208 "parser/parser.y"
                                             {
        (yyval.node) = create_node(NODE_WHILE, "while", line_num, col_num);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1852 "parser/parser.tab.c"
    break;

  case 40:
#line 216 "parser/parser.y"
                                                                                     {
        (yyval.node) = create_node(NODE_FOR, "for", line_num, col_num);
        add_child((yyval.node), (yyvsp[-6].node));
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1864 "parser/parser.tab.c"
    break;

  case 41:
#line 226 "parser/parser.y"
                                                            {
        (yyval.node) = create_node(NODE_SWITCH, "switch", line_num, col_num);
        add_child((yyval.node), (yyvsp[-4].node));
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 1874 "parser/parser.tab.c"
    break;

  case 42:
#line 234 "parser/parser.y"
                             {
        (yyval.node) = (yyvsp[-1].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1883 "parser/parser.tab.c"
    break;

  case 43:
#line 238 "parser/parser.y"
                     {
        (yyval.node) = create_node(NODE_BLOCK, "cases", line_num, col_num);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1892 "parser/parser.tab.c"
    break;

  case 44:
#line 242 "parser/parser.y"
                                             {
        (yyval.node) = (yyvsp[-3].node);
        ASTNode *def = create_node(NODE_DEFAULT, "default", line_num, col_num);
        add_child(def, (yyvsp[0].node));
        add_child((yyval.node), def);
    }
#line 1903 "parser/parser.tab.c"
    break;

  case 45:
#line 251 "parser/parser.y"
                                          {
        (yyval.node) = create_node(NODE_CASE, "case", line_num, col_num);
        ASTNode *val = create_node(NODE_INT_LITERAL, "", line_num, col_num);
        val->int_val = (yyvsp[-2].int_val);
        add_child((yyval.node), val);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1915 "parser/parser.tab.c"
    break;

  case 46:
#line 261 "parser/parser.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1921 "parser/parser.tab.c"
    break;

  case 47:
#line 265 "parser/parser.y"
                      {
        (yyval.node) = create_node(NODE_RETURN, "return", line_num, col_num);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1930 "parser/parser.tab.c"
    break;

  case 48:
#line 269 "parser/parser.y"
             {
        (yyval.node) = create_node(NODE_RETURN, "return", line_num, col_num);
    }
#line 1938 "parser/parser.tab.c"
    break;

  case 49:
#line 275 "parser/parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1944 "parser/parser.tab.c"
    break;

  case 50:
#line 276 "parser/parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 1950 "parser/parser.tab.c"
    break;

  case 51:
#line 277 "parser/parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1956 "parser/parser.tab.c"
    break;

  case 52:
#line 281 "parser/parser.y"
                               {
        (yyval.node) = create_node(NODE_BINARY_OP, "+", line_num, col_num);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1966 "parser/parser.tab.c"
    break;

  case 53:
#line 286 "parser/parser.y"
                                  {
        (yyval.node) = create_node(NODE_BINARY_OP, "-", line_num, col_num);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1976 "parser/parser.tab.c"
    break;

  case 54:
#line 291 "parser/parser.y"
                                     {
        (yyval.node) = create_node(NODE_BINARY_OP, "*", line_num, col_num);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1986 "parser/parser.tab.c"
    break;

  case 55:
#line 296 "parser/parser.y"
                                   {
        (yyval.node) = create_node(NODE_BINARY_OP, "/", line_num, col_num);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 1996 "parser/parser.tab.c"
    break;

  case 56:
#line 301 "parser/parser.y"
                               {
        (yyval.node) = create_node(NODE_BINARY_OP, "==", line_num, col_num);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2006 "parser/parser.tab.c"
    break;

  case 57:
#line 306 "parser/parser.y"
                               {
        (yyval.node) = create_node(NODE_BINARY_OP, "!=", line_num, col_num);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2016 "parser/parser.tab.c"
    break;

  case 58:
#line 311 "parser/parser.y"
                               {
        (yyval.node) = create_node(NODE_BINARY_OP, "<", line_num, col_num);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2026 "parser/parser.tab.c"
    break;

  case 59:
#line 316 "parser/parser.y"
                               {
        (yyval.node) = create_node(NODE_BINARY_OP, ">", line_num, col_num);
        add_child((yyval.node), (yyvsp[-2].node));
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2036 "parser/parser.tab.c"
    break;

  case 60:
#line 324 "parser/parser.y"
                   {
        (yyval.node) = create_node(NODE_UNARY_OP, "!", line_num, col_num);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2045 "parser/parser.tab.c"
    break;

  case 61:
#line 328 "parser/parser.y"
                       {
        (yyval.node) = create_node(NODE_UNARY_OP, "-", line_num, col_num);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2054 "parser/parser.tab.c"
    break;

  case 62:
#line 335 "parser/parser.y"
               {
        (yyval.node) = create_node(NODE_IDENTIFIER, (yyvsp[0].string_val), line_num, col_num);
    }
#line 2062 "parser/parser.tab.c"
    break;

  case 63:
#line 338 "parser/parser.y"
                  {
        (yyval.node) = create_node(NODE_INT_LITERAL, "", line_num, col_num);
        (yyval.node)->int_val = (yyvsp[0].int_val);
    }
#line 2071 "parser/parser.tab.c"
    break;

  case 64:
#line 342 "parser/parser.y"
                    {
        (yyval.node) = create_node(NODE_FLOAT_LITERAL, "", line_num, col_num);
        (yyval.node)->float_val = (yyvsp[0].float_val);
    }
#line 2080 "parser/parser.tab.c"
    break;

  case 65:
#line 346 "parser/parser.y"
                     {
        (yyval.node) = create_node(NODE_STRING_LITERAL, (yyvsp[0].string_val), line_num, col_num);
    }
#line 2088 "parser/parser.tab.c"
    break;

  case 66:
#line 349 "parser/parser.y"
           {
        (yyval.node) = create_node(NODE_BOOLEAN_LITERAL, "true", line_num, col_num);
        (yyval.node)->bool_val = true;
    }
#line 2097 "parser/parser.tab.c"
    break;

  case 67:
#line 353 "parser/parser.y"
            {
        (yyval.node) = create_node(NODE_BOOLEAN_LITERAL, "false", line_num, col_num);
        (yyval.node)->bool_val = false;
    }
#line 2106 "parser/parser.tab.c"
    break;

  case 68:
#line 357 "parser/parser.y"
                   {
        (yyval.node) = create_node(NODE_NULL_LITERAL, "null", line_num, col_num);
    }
#line 2114 "parser/parser.tab.c"
    break;

  case 69:
#line 360 "parser/parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2120 "parser/parser.tab.c"
    break;

  case 70:
#line 361 "parser/parser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 2126 "parser/parser.tab.c"
    break;

  case 71:
#line 365 "parser/parser.y"
                                        {
        (yyval.node) = create_node(NODE_FUNCTION_CALL, "println", line_num, col_num);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 2135 "parser/parser.tab.c"
    break;

  case 72:
#line 369 "parser/parser.y"
                                             {
        (yyval.node) = create_node(NODE_FUNCTION_CALL, (yyvsp[-3].string_val), line_num, col_num);
        add_child((yyval.node), (yyvsp[-1].node));
    }
#line 2144 "parser/parser.tab.c"
    break;

  case 73:
#line 376 "parser/parser.y"
                                   {
        (yyval.node) = (yyvsp[-2].node);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2153 "parser/parser.tab.c"
    break;

  case 74:
#line 380 "parser/parser.y"
                 {
        (yyval.node) = create_node(NODE_BLOCK, "arguments", line_num, col_num);
        add_child((yyval.node), (yyvsp[0].node));
    }
#line 2162 "parser/parser.tab.c"
    break;

  case 75:
#line 384 "parser/parser.y"
                  {
        (yyval.node) = create_node(NODE_BLOCK, "empty_args", line_num, col_num);
    }
#line 2170 "parser/parser.tab.c"
    break;


#line 2174 "parser/parser.tab.c"

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
#line 389 "parser/parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error en línea %d, columna %d: %s\n", line_num, col_num, s);
}
