/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "ast.h"
#include "utils.h"

// Function declarations
int yylex(void);
void yyerror(const char *msg);

// Helper functions
ast_node *make_pair(char *key, ast_node *val, const char *file, int line);
ast_node *append_pair(ast_node *list, ast_node *newpair, const char *file, int line);
ast_node *append_elem(ast_node *list, ast_node *val, const char *file, int line);

// Structure definitions
typedef struct table_schema {
    char *name;
    char *shape;
    char **columns;
    int num_columns;
    int next_id;
    FILE *fp;
} TableSchema;

typedef struct table_list {
    TableSchema *schema;
    struct table_list *next;
} TableList;

// Global variables
ast_node *root = NULL;
int print_ast_flag = 0;
char *output_dir = ".";
TableList *tables = NULL;
int table_count = 0;

// Function prototypes
ast_node* create_node(enum node_type type, const char *file, int line);
void print_ast(ast_node *node, int depth);
void free_ast(ast_node *node);
void process_ast(ast_node *root, char *output_dir);
TableSchema* find_or_create_table(char *table_name, char **scalar_keys, int num_scalar, char **object_keys, int num_object, char *output_dir);
int process_object(ast_node *node, TableSchema *parent_schema, int parent_id, char *key, char *output_dir);
void process_array(ast_node *node, TableSchema *parent_schema, int parent_id, char *key, char *output_dir);
void write_csv_row(FILE *fp, char **values, int num_values);

#line 121 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_LBRACE = 3,                     /* LBRACE  */
  YYSYMBOL_RBRACE = 4,                     /* RBRACE  */
  YYSYMBOL_LBRACK = 5,                     /* LBRACK  */
  YYSYMBOL_RBRACK = 6,                     /* RBRACK  */
  YYSYMBOL_COLON = 7,                      /* COLON  */
  YYSYMBOL_COMMA = 8,                      /* COMMA  */
  YYSYMBOL_STRING = 9,                     /* STRING  */
  YYSYMBOL_NUMBER = 10,                    /* NUMBER  */
  YYSYMBOL_TRUE = 11,                      /* TRUE  */
  YYSYMBOL_FALSE = 12,                     /* FALSE  */
  YYSYMBOL_T_NULL = 13,                    /* T_NULL  */
  YYSYMBOL_YYACCEPT = 14,                  /* $accept  */
  YYSYMBOL_json = 15,                      /* json  */
  YYSYMBOL_value = 16,                     /* value  */
  YYSYMBOL_object = 17,                    /* object  */
  YYSYMBOL_members = 18,                   /* members  */
  YYSYMBOL_pair = 19,                      /* pair  */
  YYSYMBOL_array = 20,                     /* array  */
  YYSYMBOL_elems = 21                      /* elems  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_int8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if 1

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
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  19
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   28

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  14
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  8
/* YYNRULES -- Number of rules.  */
#define YYNRULES  18
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  28

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   268


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
       5,     6,     7,     8,     9,    10,    11,    12,    13
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int8 yyrline[] =
{
       0,    72,    72,    76,    77,    78,    79,    80,    81,    82,
      86,    87,    91,    92,    96,   105,   110,   120,   126
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "LBRACE", "RBRACE",
  "LBRACK", "RBRACK", "COLON", "COMMA", "STRING", "NUMBER", "TRUE",
  "FALSE", "T_NULL", "$accept", "json", "value", "object", "members",
  "pair", "array", "elems", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-4)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      14,    -3,    -1,    -4,    -4,    -4,    -4,    -4,     3,    -4,
      -4,    -4,    -4,     0,    12,    -4,    -4,    -4,     7,    -4,
      14,    -4,     5,    -4,    14,    -4,    -4,    -4
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     5,     6,     7,     8,     9,     0,     2,
       3,     4,    10,     0,     0,    12,    15,    17,     0,     1,
       0,    11,     0,    16,     0,    14,    13,    18
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
      -4,    -4,    -2,    -4,    -4,     6,    -4,    -4
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     8,     9,    10,    14,    15,    11,    18
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      17,    12,     1,    19,     2,    16,    13,    20,     3,     4,
       5,     6,     7,    23,    13,    24,    21,     1,    25,     2,
      22,     0,    27,     3,     4,     5,     6,     7,    26
};

static const yytype_int8 yycheck[] =
{
       2,     4,     3,     0,     5,     6,     9,     7,     9,    10,
      11,    12,    13,     6,     9,     8,     4,     3,    20,     5,
       8,    -1,    24,     9,    10,    11,    12,    13,    22
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     5,     9,    10,    11,    12,    13,    15,    16,
      17,    20,     4,     9,    18,    19,     6,    16,    21,     0,
       7,     4,     8,     6,     8,    16,    19,    16
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    14,    15,    16,    16,    16,    16,    16,    16,    16,
      17,    17,    18,    18,    19,    20,    20,    21,    21
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     1,     3,     3,     2,     3,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
  YYLTYPE *yylloc;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
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
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
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
# endif
#endif

#ifndef yytnamerr
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
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
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
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
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
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
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
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
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


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* json: value  */
#line 72 "parser.y"
                                  { debug_log("Parsed json rule", __FILE__, __LINE__); root = (yyvsp[0].node); }
#line 1518 "parser.tab.c"
    break;

  case 3: /* value: object  */
#line 76 "parser.y"
                                  { debug_log("Parsed object value", __FILE__, __LINE__); (yyval.node) = (yyvsp[0].node); }
#line 1524 "parser.tab.c"
    break;

  case 4: /* value: array  */
#line 77 "parser.y"
                                  { debug_log("Parsed array value", __FILE__, __LINE__); (yyval.node) = (yyvsp[0].node); }
#line 1530 "parser.tab.c"
    break;

  case 5: /* value: STRING  */
#line 78 "parser.y"
                                  { debug_log("Parsed STRING value", __FILE__, __LINE__); (yyval.node) = create_node(NODE_STRING, __FILE__, __LINE__); (yyval.node)->data.string = (yyvsp[0].str); }
#line 1536 "parser.tab.c"
    break;

  case 6: /* value: NUMBER  */
#line 79 "parser.y"
                                  { debug_log("Parsed NUMBER value", __FILE__, __LINE__); (yyval.node) = create_node(NODE_NUMBER, __FILE__, __LINE__); (yyval.node)->data.number = (yyvsp[0].str); }
#line 1542 "parser.tab.c"
    break;

  case 7: /* value: TRUE  */
#line 80 "parser.y"
                                  { debug_log("Parsed TRUE value", __FILE__, __LINE__); (yyval.node) = create_node(NODE_TRUE, __FILE__, __LINE__); }
#line 1548 "parser.tab.c"
    break;

  case 8: /* value: FALSE  */
#line 81 "parser.y"
                                  { debug_log("Parsed FALSE value", __FILE__, __LINE__); (yyval.node) = create_node(NODE_FALSE, __FILE__, __LINE__); }
#line 1554 "parser.tab.c"
    break;

  case 9: /* value: T_NULL  */
#line 82 "parser.y"
                                  { debug_log("Parsed NULL value", __FILE__, __LINE__); (yyval.node) = create_node(NODE_NULL, __FILE__, __LINE__); }
#line 1560 "parser.tab.c"
    break;

  case 10: /* object: LBRACE RBRACE  */
#line 86 "parser.y"
                                  { debug_log("Parsed empty object", __FILE__, __LINE__); (yyval.node) = create_node(NODE_OBJECT, __FILE__, __LINE__); (yyval.node)->data.object.value = NULL; }
#line 1566 "parser.tab.c"
    break;

  case 11: /* object: LBRACE members RBRACE  */
#line 87 "parser.y"
                                  { debug_log("Parsed object with members", __FILE__, __LINE__); (yyval.node) = create_node(NODE_OBJECT, __FILE__, __LINE__); (yyval.node)->data.object.value = (yyvsp[-1].node); }
#line 1572 "parser.tab.c"
    break;

  case 12: /* members: pair  */
#line 91 "parser.y"
                                  { debug_log("Parsed single pair", __FILE__, __LINE__); (yyval.node) = (yyvsp[0].node); }
#line 1578 "parser.tab.c"
    break;

  case 13: /* members: members COMMA pair  */
#line 92 "parser.y"
                                  { debug_log("Appending pair to members", __FILE__, __LINE__); (yyval.node) = append_pair((yyvsp[-2].node), (yyvsp[0].node), __FILE__, __LINE__); }
#line 1584 "parser.tab.c"
    break;

  case 14: /* pair: STRING COLON value  */
#line 96 "parser.y"
                                  { 
        char msg[128];
        snprintf(msg, sizeof(msg), "Parsed pair with key: %s", (yyvsp[-2].str));
        debug_log(msg, __FILE__, __LINE__); 
        (yyval.node) = make_pair((yyvsp[-2].str), (yyvsp[0].node), __FILE__, __LINE__); 
    }
#line 1595 "parser.tab.c"
    break;

  case 15: /* array: LBRACK RBRACK  */
#line 105 "parser.y"
                                  { 
        debug_log("Parsed empty array", __FILE__, __LINE__); 
        (yyval.node) = create_node(NODE_ARRAY, __FILE__, __LINE__); 
        (yyval.node)->data.array.elements = NULL; 
    }
#line 1605 "parser.tab.c"
    break;

  case 16: /* array: LBRACK elems RBRACK  */
#line 110 "parser.y"
                                  { 
        char msg[128];
        snprintf(msg, sizeof(msg), "Parsed array with elements, head type: %d", (yyvsp[-1].node) ? (yyvsp[-1].node)->type : -1);
        debug_log(msg, __FILE__, __LINE__); 
        (yyval.node) = create_node(NODE_ARRAY, __FILE__, __LINE__); 
        (yyval.node)->data.array.elements = (yyvsp[-1].node); 
    }
#line 1617 "parser.tab.c"
    break;

  case 17: /* elems: value  */
#line 120 "parser.y"
                                  { 
        char msg[128];
        snprintf(msg, sizeof(msg), "Parsed single element of type: %d", (yyvsp[0].node) ? (yyvsp[0].node)->type : -1);
        debug_log(msg, __FILE__, __LINE__); 
        (yyval.node) = append_elem(NULL, (yyvsp[0].node), __FILE__, __LINE__); 
    }
#line 1628 "parser.tab.c"
    break;

  case 18: /* elems: elems COMMA value  */
#line 126 "parser.y"
                                  { 
        char msg[128];
        snprintf(msg, sizeof(msg), "Appending element of type %d to elements list of type %d", 
                 (yyvsp[0].node) ? (yyvsp[0].node)->type : -1, (yyvsp[-2].node) ? (yyvsp[-2].node)->type : -1);
        debug_log(msg, __FILE__, __LINE__); 
        (yyval.node) = append_elem((yyvsp[-2].node), (yyvsp[0].node), __FILE__, __LINE__); 
    }
#line 1640 "parser.tab.c"
    break;


#line 1644 "parser.tab.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken, &yylloc};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 135 "parser.y"


int main(int argc, char *argv[]) {
    debug_log("Starting main", __FILE__, __LINE__);
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--print-ast") == 0) {
            print_ast_flag = 1;
        } else if (strcmp(argv[i], "--out-dir") == 0 && i + 1 < argc) {
            output_dir = argv[i + 1];
            i++;
        }
    }

    if (yyparse() == 0) {
        debug_log("Parsing successful", __FILE__, __LINE__);
        if (print_ast_flag && root) {
            debug_log("Printing AST", __FILE__, __LINE__);
            printf("AST:\n");
            print_ast(root, 0);
        }
        debug_log("Processing AST", __FILE__, __LINE__);
        process_ast(root, output_dir);
    } else {
        debug_log("Parsing failed", __FILE__, __LINE__);
        exit(1);
    }

    debug_log("Freeing AST", __FILE__, __LINE__);
    free_ast(root);
    TableList *current = tables;
    while (current) {
        TableList *next = current->next;
        if (current->schema->fp) fclose(current->schema->fp);
        for (int i = 0; i < current->schema->num_columns; i++) {
            free(current->schema->columns[i]);
        }
        free(current->schema->columns);
        free(current->schema->name);
        free(current->schema->shape);
        free(current->schema);
        free(current);
        current = next;
    }
    debug_log("Exiting main", __FILE__, __LINE__);
    return 0;
}

void yyerror(const char *msg) {
    fprintf(stderr, "[ERROR %s:%d] %s at line %d, column %d\n",
            __FILE__, __LINE__, msg, yylloc.first_line, yylloc.first_column);
    exit(1);
}

ast_node* create_node(enum node_type type, const char *file, int line) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Creating node of type %d", type);
    debug_log(msg, file, line);
    ast_node *node = (ast_node*)malloc(sizeof(ast_node));
    if (!node) {
        fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for node\n", file, line);
        exit(1);
    }
    node->type = type;
    node->next = NULL;
    memset(&node->data, 0, sizeof(node->data));
    return node;
}

ast_node *make_pair(char *key, ast_node *val, const char *file, int line) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Creating pair with key: %s", key ? key : "NULL");
    debug_log(msg, file, line);
    if (!key || !val) {
        fprintf(stderr, "[ERROR %s:%d] Null key or value in make_pair\n", file, line);
        exit(1);
    }
    ast_node *n = create_node(NODE_OBJECT, file, line);
    n->data.object.key = key;
    n->data.object.value = val;
    n->next = NULL;
    return n;
}

ast_node *append_pair(ast_node *list, ast_node *newpair, const char *file, int line) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Appending pair, list: %p, newpair: %p", list, newpair);
    debug_log(msg, file, line);
    if (!newpair) {
        fprintf(stderr, "[ERROR %s:%d] Null newpair in append_pair\n", file, line);
        exit(1);
    }
    if (!list) return newpair;
    ast_node *cur = list;
    while (cur->next) cur = cur->next;
    cur->next = newpair;
    newpair->next = NULL;
    return list;
}

ast_node *append_elem(ast_node *list, ast_node *val, const char *file, int line) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Appending element, list: %p, val: %p, type: %d", list, val, val ? val->type : -1);
    debug_log(msg, file, line);
    if (!val) {
        fprintf(stderr, "[ERROR %s:%d] Null value in append_elem\n", file, line);
        exit(1);
    }
    val->next = NULL;
    if (!list) {
        return val;
    }
    ast_node *cur = list;
    while (cur->next) cur = cur->next;
    cur->next = val;
    return list;
}

void print_ast(ast_node *node, int depth) {
    if (!node) {
        debug_log("Printing empty node", __FILE__, __LINE__);
        for (int i = 0; i < depth; i++) printf("  ");
        printf("Empty\n");
        return;
    }
    char msg[128];
    snprintf(msg, sizeof(msg), "Printing node of type %d", node->type);
    debug_log(msg, __FILE__, __LINE__);
    for (int i = 0; i < depth; i++) printf("  ");
    switch (node->type) {
        case NODE_OBJECT:
            if (node->data.object.key) {
                printf("\"%s\":\n", node->data.object.key);
                print_ast(node->data.object.value, depth + 1);
            } else {
                printf("Object:\n");
                for (ast_node *pair = node->data.object.value; pair; pair = pair->next) {
                    if (!pair) {
                        fprintf(stderr, "[ERROR %s:%d] Null pair in object\n", __FILE__, __LINE__);
                        exit(1);
                    }
                    if (!pair->data.object.key) {
                        fprintf(stderr, "[ERROR %s:%d] Null key in object pair\n", __FILE__, __LINE__);
                        exit(1);
                    }
                    for (int i = 0; i < depth + 1; i++) printf("  ");
                    printf("\"%s\":\n", pair->data.object.key);
                    print_ast(pair->data.object.value, depth + 2);
                }
            }
            break;
        case NODE_ARRAY:
            printf("Array:\n");
            for (ast_node *elem = node->data.array.elements; elem; elem = elem->next) {
                if (!elem) {
                    fprintf(stderr, "[ERROR %s:%d] Null element in array\n", __FILE__, __LINE__);
                    exit(1);
                }
                print_ast(elem, depth + 1);
            }
            break;
        case NODE_STRING:
            printf("String: \"%s\"\n", node->data.string ? node->data.string : "");
            break;
        case NODE_NUMBER:
            printf("Number: %s\n", node->data.number ? node->data.number : "");
            break;
        case NODE_TRUE:
            printf("True\n");
            break;
        case NODE_FALSE:
            printf("False\n");
            break;
        case NODE_NULL:
            printf("Null\n");
            break;
    }
}

void free_ast(ast_node *node) {
    if (!node) return;
    char msg[128];
    snprintf(msg, sizeof(msg), "Freeing node of type %d", node->type);
    debug_log(msg, __FILE__, __LINE__);
    switch (node->type) {
        case NODE_OBJECT:
            if (node->data.object.key) {
                free(node->data.object.key);
                free_ast(node->data.object.value);
            } else {
                ast_node *pair = node->data.object.value;
                while (pair) {
                    ast_node *next = pair->next;
                    free(pair->data.object.key);
                    free_ast(pair->data.object.value);
                    free(pair);
                    pair = next;
                }
            }
            free(node);
            break;
        case NODE_ARRAY:
            ast_node *elem = node->data.array.elements;
            while (elem) {
                ast_node *next = elem->next;
                free_ast(elem);
                elem = next;
            }
            free(node);
            break;
        case NODE_STRING:
            free(node->data.string);
            free(node);
            break;
        case NODE_NUMBER:
            free(node->data.number);
            free(node);
            break;
        case NODE_TRUE:
        case NODE_FALSE:
        case NODE_NULL:
            free(node);
            break;
    }
}

void process_ast(ast_node *root, char *output_dir) {
    debug_log("Processing AST", __FILE__, __LINE__);
    if (!root) {
        fprintf(stderr, "[ERROR %s:%d] Null root in process_ast\n", __FILE__, __LINE__);
        return;
    }
    if (root->type == NODE_OBJECT) {
        process_object(root, NULL, 0, "root", output_dir);
    } else if (root->type == NODE_ARRAY) {
        process_array(root, NULL, 0, "root", output_dir);
    }
}

TableSchema* find_or_create_table(char *table_name, char **scalar_keys, int num_scalar, char **object_keys, int num_object, char *output_dir) {
    debug_log("Finding or creating table", __FILE__, __LINE__);
    char shape[1024] = {0};
    strcat(shape, "scalar:");
    for (int i = 0; i < num_scalar; i++) {
        strcat(shape, scalar_keys[i]);
        if (i < num_scalar - 1) strcat(shape, ",");
    }
    strcat(shape, ";object:");
    for (int i = 0; i < num_object; i++) {
        strcat(shape, object_keys[i]);
        if (i < num_object - 1) strcat(shape, ",");
    }

    for (TableList *current = tables; current; current = current->next) {
        if (strcmp(current->schema->shape, shape) == 0) {
            return current->schema;
        }
    }

    TableSchema *table = (TableSchema*)malloc(sizeof(TableSchema));
    if (!table) {
        fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for table schema\n", __FILE__, __LINE__);
        exit(1);
    }
    table->name = strdup(table_name);
    table->shape = strdup(shape);
    table->num_columns = 1 + num_scalar + num_object;
    table->columns = (char**)malloc(sizeof(char*) * table->num_columns);
    if (!table->columns) {
        fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for table columns\n", __FILE__, __LINE__);
        exit(1);
    }
    table->columns[0] = strdup("id");
    for (int i = 0; i < num_scalar; i++) {
        table->columns[1 + i] = strdup(scalar_keys[i]);
    }
    for (int i = 0; i < num_object; i++) {
        char fk_column[64];
        snprintf(fk_column, sizeof(fk_column), "%s_id", object_keys[i]);
        table->columns[1 + num_scalar + i] = strdup(fk_column);
    }
    table->next_id = 1;

    char filename[256];
    snprintf(filename, sizeof(filename), "%s/%s.csv", output_dir, table->name);
    table->fp = fopen(filename, "w");
    if (!table->fp) {
        fprintf(stderr, "[ERROR %s:%d] Error opening file %s\n", __FILE__, __LINE__, filename);
        exit(1);
    }
    write_csv_row(table->fp, table->columns, table->num_columns);

    TableList *new_table = (TableList*)malloc(sizeof(TableList));
    if (!new_table) {
        fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for table list\n", __FILE__, __LINE__);
        exit(1);
    }
    new_table->schema = table;
    new_table->next = tables;
    tables = new_table;
    return table;
}

int process_object(ast_node *node, TableSchema *parent_schema, int parent_id, char *key, char *output_dir) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Processing object with key: %s", key);
    debug_log(msg, __FILE__, __LINE__);
    if (!node) {
        fprintf(stderr, "[ERROR %s:%d] Null node in process_object\n", __FILE__, __LINE__);
        return 0;
    }
    char *scalar_keys[32];
    int num_scalar = 0;
    char *object_keys[32];
    int num_object = 0;
    char *array_keys[32];
    int num_array = 0;

    for (ast_node *pair = node->data.object.value; pair; pair = pair->next) {
        if (!pair->data.object.value) {
            fprintf(stderr, "[ERROR %s:%d] Null value in object pair\n", __FILE__, __LINE__);
            continue;
        }
        ast_node *value = pair->data.object.value;
        if (value->type == NODE_STRING || value->type == NODE_NUMBER ||
            value->type == NODE_TRUE || value->type == NODE_FALSE || value->type == NODE_NULL) {
            scalar_keys[num_scalar++] = pair->data.object.key;
        } else if (value->type == NODE_OBJECT) {
            object_keys[num_object++] = pair->data.object.key;
        } else if (value->type == NODE_ARRAY) {
            array_keys[num_array++] = pair->data.object.key;
        }
    }

    char table_name[64];
    if (strcmp(key, "root") == 0) {
        snprintf(table_name, sizeof(table_name), "table%d", table_count);
    } else {
        snprintf(table_name, sizeof(table_name), "%s", key);
    }
    TableSchema *table = find_or_create_table(table_name, scalar_keys, num_scalar, object_keys, num_object, output_dir);
    int id = table->next_id++;

    char **values = (char**)malloc(sizeof(char*) * table->num_columns);
    if (!values) {
        fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for values\n", __FILE__, __LINE__);
        exit(1);
    }
    char id_str[16];
    snprintf(id_str, sizeof(id_str), "%d", id);
    values[0] = id_str;
    for (int i = 0; i < num_scalar; i++) {
        values[1 + i] = "";
        for (ast_node *pair = node->data.object.value; pair; pair = pair->next) {
            if (strcmp(pair->data.object.key, scalar_keys[i]) == 0) {
                ast_node *value = pair->data.object.value;
                switch (value->type) {
                    case NODE_STRING: values[1 + i] = value->data.string; break;
                    case NODE_NUMBER: values[1 + i] = value->data.number; break;
                    case NODE_TRUE: values[1 + i] = "true"; break;
                    case NODE_FALSE: values[1 + i] = "false"; break;
                    case NODE_NULL: values[1 + i] = ""; break;
                    default: values[1 + i] = "";
                }
                break;
            }
        }
    }
    for (int i = 0; i < num_object; i++) {
        values[1 + num_scalar + i] = "";
        for (ast_node *pair = node->data.object.value; pair; pair = pair->next) {
            if (strcmp(pair->data.object.key, object_keys[i]) == 0) {
                int child_id = process_object(pair->data.object.value, table, id, object_keys[i], output_dir);
                char *fk_value = (char*)malloc(16);
                snprintf(fk_value, 16, "%d", child_id);
                values[1 + num_scalar + i] = fk_value;
                break;
            }
        }
    }

    write_csv_row(table->fp, values, table->num_columns);

    for (int i = 0; i < num_array; i++) {
        for (ast_node *pair = node->data.object.value; pair; pair = pair->next) {
            if (strcmp(pair->data.object.key, array_keys[i]) == 0) {
                process_array(pair->data.object.value, table, id, array_keys[i], output_dir);
                break;
            }
        }
    }

    for (int i = 1 + num_scalar; i < table->num_columns; i++) {
        if (values[i] && values[i] != "" && values[i] != "true" && values[i] != "false") {
            free(values[i]);
        }
    }
    free(values);
    return id;
}

void process_array(ast_node *node, TableSchema *parent_schema, int parent_id, char *key, char *output_dir) {
    char msg[128];
    snprintf(msg, sizeof(msg), "Processing array with key: %s", key);
    debug_log(msg, __FILE__, __LINE__);
    if (!node || !node->data.array.elements) {
        fprintf(stderr, "[ERROR %s:%d] Null node or empty array in process_array\n", __FILE__, __LINE__);
        return;
    }
    ast_node *first = node->data.array.elements;

    if (first->type == NODE_STRING || first->type == NODE_NUMBER ||
        first->type == NODE_TRUE || first->type == NODE_FALSE || first->type == NODE_NULL) {
        char table_name[64];
        snprintf(table_name, sizeof(table_name), "%s", key);
        char filename[256];
        snprintf(filename, sizeof(filename), "%s/%s.csv", output_dir, table_name);
        FILE *fp = fopen(filename, "w");
        if (!fp) {
            fprintf(stderr, "[ERROR %s:%d] Error opening file %s\n", __FILE__, __LINE__, filename);
            exit(1);
        }
        char *header[] = {"parent_id", "index", "value"};
        write_csv_row(fp, header, 3);

        int index = 0;
        for (ast_node *elem = node->data.array.elements; elem; elem = elem->next) {
            char parent_id_str[16], index_str[16], *value_str;
            snprintf(parent_id_str, sizeof(parent_id_str), "%d", parent_id);
            snprintf(index_str, sizeof(index_str), "%d", index++);
            switch (elem->type) {
                case NODE_STRING: value_str = elem->data.string; break;
                case NODE_NUMBER: value_str = elem->data.number; break;
                case NODE_TRUE: value_str = "true"; break;
                case NODE_FALSE: value_str = "false"; break;
                case NODE_NULL: value_str = ""; break;
                default: value_str = "";
            }
            char *row[] = {parent_id_str, index_str, value_str};
            write_csv_row(fp, row, 3);
        }
        fclose(fp);
    } else if (first->type == NODE_OBJECT) {
        char table_name[64];
        snprintf(table_name, sizeof(table_name), "%s", key);
        char filename[256];
        snprintf(filename, sizeof(filename), "%s/%s.csv", output_dir, table_name);
        FILE *fp = fopen(filename, "w");
        if (!fp) {
            fprintf(stderr, "[ERROR %s:%d] Error opening file %s\n", __FILE__, __LINE__, filename);
            exit(1);
        }

        char *scalar_keys[32];
        int num_scalar = 0;
        for (ast_node *pair = first->data.object.value; pair; pair = pair->next) {
            ast_node *value = pair->data.object.value;
            if (value->type == NODE_STRING || value->type == NODE_NUMBER ||
                value->type == NODE_TRUE || value->type == NODE_FALSE || value->type == NODE_NULL) {
                scalar_keys[num_scalar++] = pair->data.object.key;
            }
        }

        char **header = (char**)malloc(sizeof(char*) * (2 + num_scalar));
        if (!header) {
            fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for header\n", __FILE__, __LINE__);
            exit(1);
        }
        char parent_id_col[64];
        snprintf(parent_id_col, sizeof(parent_id_col), "%s_id", parent_schema->name);
        header[0] = strdup(parent_id_col);
        header[1] = strdup("seq");
        for (int i = 0; i < num_scalar; i++) {
            header[2 + i] = strdup(scalar_keys[i]);
        }
        write_csv_row(fp, header, 2 + num_scalar);

        int seq = 0;
        for (ast_node *elem = node->data.array.elements; elem; elem = elem->next) {
            char **values = (char**)malloc(sizeof(char*) * (2 + num_scalar));
            if (!values) {
                fprintf(stderr, "[ERROR %s:%d] Memory allocation failed for values\n", __FILE__, __LINE__);
                exit(1);
            }
            char parent_id_str[16], seq_str[16];
            snprintf(parent_id_str, sizeof(parent_id_str), "%d", parent_id);
            snprintf(seq_str, sizeof(seq_str), "%d", seq++);
            values[0] = parent_id_str;
            values[1] = seq_str;
            for (int i = 0; i < num_scalar; i++) {
                values[2 + i] = "";
                for (ast_node *pair = elem->data.object.value; pair; pair = pair->next) {
                    if (strcmp(pair->data.object.key, scalar_keys[i]) == 0) {
                        ast_node *value = pair->data.object.value;
                        switch (value->type) {
                            case NODE_STRING: values[2 + i] = value->data.string; break;
                            case NODE_NUMBER: values[2 + i] = value->data.number; break;
                            case NODE_TRUE: values[2 + i] = "true"; break;
                            case NODE_FALSE: values[2 + i] = "false"; break;
                            case NODE_NULL: values[2 + i] = ""; break;
                            default: values[2 + i] = "";
                        }
                        break;
                    }
                }
            }
            write_csv_row(fp, values, 2 + num_scalar);
            free(values);
        }
        for (int i = 0; i < 2 + num_scalar; i++) {
            free(header[i]);
        }
        free(header);
        fclose(fp);
    }
}

void write_csv_row(FILE *fp, char **values, int num_values) {
    debug_log("Writing CSV row", __FILE__, __LINE__);
    for (int i = 0; i < num_values; i++) {
        if (i > 0) fprintf(fp, ",");
        if (!values[i] || strlen(values[i]) == 0) {
            // Empty for null
        } else if (strcmp(values[i], "true") == 0 || strcmp(values[i], "false") == 0) {
            fprintf(fp, "%s", values[i]);
        } else if (strspn(values[i], "-0123456789.") == strlen(values[i])) {
            fprintf(fp, "%s", values[i]);
        } else {
            fprintf(fp, "\"");
            for (char *c = values[i]; *c; c++) {
                if (*c == '"') fprintf(fp, "\"");
                fprintf(fp, "%c", *c);
            }
            fprintf(fp, "\"");
        }
    }
    fprintf(fp, "\n");
}
