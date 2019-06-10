/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         sieveparse
#define yylex           sievelex
#define yyerror         sieveerror
#define yydebug         sievedebug
#define yynerrs         sievenerrs


/* Copy the first part of user declarations.  */
#line 1 "sieve/sieve.y" /* yacc.c:339  */

/* sieve.y -- sieve parser
 * Larry Greenfield
 *
 * Copyright (c) 1994-2008 Carnegie Mellon University.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The name "Carnegie Mellon University" must not be used to
 *    endorse or promote products derived from this software without
 *    prior written permission. For permission or any legal
 *    details, please contact
 *      Carnegie Mellon University
 *      Center for Technology Transfer and Enterprise Creation
 *      4615 Forbes Avenue
 *      Suite 302
 *      Pittsburgh, PA  15213
 *      (412) 268-7393, fax: (412) 268-7395
 *      innovation@andrew.cmu.edu
 *
 * 4. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by Computing Services
 *     at Carnegie Mellon University (http://www.cmu.edu/computing/)."
 *
 * CARNEGIE MELLON UNIVERSITY DISCLAIMS ALL WARRANTIES WITH REGARD TO
 * THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS, IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY BE LIABLE
 * FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "xmalloc.h"
#include "sieve/comparator.h"
#include "sieve/interp.h"
#include "sieve/script.h"
#include "sieve/tree.h"
#include "sieve/flags.h"
#include "sieve/grammar.h"
#include "sieve/sieve_err.h"

#include "imapurl.h"
#include "lib/gmtoff.h"
#include "util.h"
#include "imparse.h"
#include "libconfig.h"
#include "times.h"

#define ERR_BUF_SIZE 1024

/*
 * Definitions
 */

extern int addrparse(sieve_script_t*);
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE addr_scan_string(const char*);
extern void addr_delete_buffer(YY_BUFFER_STATE);

extern int sievelineno;

struct vtags {
    int seconds;
    strarray_t *addresses;
    char *subject;
    char *from;
    char *handle;
    int mime;
};

struct comptags {
    int match;
    int relation;
    char *comparator;  /* only used where comparator can be defined */
    int index;         /* only used where index extension is defined */
};

struct aetags {
    struct comptags comptags;  /* MUST be first so we can typecast */
    int addrtag;
};

struct btags {
    struct comptags comptags;  /* MUST be first so we can typecast */
    int transform;
    int offset;
    strarray_t *content_types;
};

struct ntags {
    char *method;
    char *id;
    strarray_t *options;
    int priority;
    char *message;
};

struct dtags {
    struct comptags comptags;  /* MUST be first so we can typecast */
    void *pattern;
    int priority;
};

struct itags {
    int location;
    int once;
    int optional;
};

struct dttags {
    struct comptags comptags;  /* MUST be first so we can typecast */
    int zonetag;
    char *zone;
};

struct ftags {
    int copy;
    int create;
    strarray_t *flags;
};

struct stags {
    int mod40; /* :lower or :upper */
    int mod30; /* :lowerfirst or :upperfirst */
    int mod20; /* :quotewildcard */
    int mod10; /* :length */
};

static char *check_reqs(sieve_script_t *script, strarray_t *sl);

static test_t *build_address(int t, struct aetags *ae,
                             strarray_t *sl, strarray_t *pl);
static test_t *build_header(int t, struct comptags *c,
                            strarray_t *sl, strarray_t *pl);
static test_t *build_body(int t, struct btags *b, strarray_t *pl);
static test_t *build_date(int t, struct dttags *dt,
                          char *hn, int part, strarray_t *kl);
static test_t *build_mailboxtest(int t, struct comptags *c, const char *extname,
                                 const char *keyname, strarray_t *keylist);

static commandlist_t *build_vacation(int t, struct vtags *h, char *s);
static commandlist_t *build_notify(int t, struct ntags *n);
static commandlist_t *build_denotify(int t, struct dtags *n);
static commandlist_t *build_keep(int t, struct ftags *f);
static commandlist_t *build_fileinto(int t, struct ftags *f, char *folder);
static commandlist_t *build_redirect(int t, int c, char *a);
static commandlist_t *build_include(int, struct itags *, char*);
static commandlist_t *build_set(int t, struct stags *s,
                                char *variable, char *value);
static commandlist_t *build_flag(int t, char *variable, strarray_t *flags);

static struct aetags *new_aetags(void);
static struct aetags *canon_aetags(struct aetags *ae);
static void free_aetags(struct aetags *ae);

static struct comptags *new_comptags(void);
static struct comptags *init_comptags(struct comptags *c);
static struct comptags *canon_comptags(struct comptags *c);
static void free_comptags(struct comptags *c, int destroy);

static struct btags *new_btags(void);
static struct btags *canon_btags(struct btags *b);
static void free_btags(struct btags *b);

static struct vtags *new_vtags(void);
static struct vtags *canon_vtags(sieve_script_t *script, struct vtags *v);
static void free_vtags(struct vtags *v);

static struct ntags *new_ntags(void);
static struct ntags *canon_ntags(struct ntags *n);
static void free_ntags(struct ntags *n);

static struct dtags *new_dtags(void);
static struct dtags *canon_dtags(struct dtags *d);
static void free_dtags(struct dtags *d);

static struct itags *new_itags(void);

static struct dttags *new_dttags(void);
static struct dttags *canon_dttags(struct dttags *dt);
static void free_dttags(struct dttags *b);

static struct ftags *new_ftags(void);
static struct ftags *canon_ftags(struct ftags *f);
static void free_ftags(struct ftags *f);

static struct stags *new_stags(void);
static struct stags *canon_stags(struct stags *s);
static void free_stags(struct stags *s);

static int verify_stringlist(sieve_script_t*, strarray_t *sl,
                             int (*verify)(sieve_script_t*, char *));
static int verify_patternlist(sieve_script_t *parse_script,
                              strarray_t *sl, struct comptags *c,
                              int (*verify)(sieve_script_t*, char *));
static int verify_mailbox(sieve_script_t*, char *s);
static int verify_address(sieve_script_t*, char *s);
static int verify_header(sieve_script_t*, char *s);
static int verify_addrheader(sieve_script_t*, char *s);
static int verify_envelope(sieve_script_t*, char *s);
static int verify_relat(sieve_script_t*, char *s);
static int verify_zone(sieve_script_t*, char *s);
static int verify_date_part(sieve_script_t *parse_script, char *dp);
static int verify_utf8(sieve_script_t*, char *s);
static int verify_identifier(sieve_script_t*, char *s);

static void parse_error(sieve_script_t *parse_script, int err, ...);
void yyerror(sieve_script_t*, const char *msg);
extern int yylex(void*, sieve_script_t*);
extern void sieverestart(FILE *f);

#define YYERROR_VERBOSE /* i want better error messages! */

/* byacc default is 500, bison default is 10000 - go with the
   larger to support big sieve scripts (see Bug #3461) */
#define YYSTACKSIZE 10000

#line 309 "sieve/sieve.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_SIEVE_SIEVE_SIEVE_H_INCLUDED
# define YY_SIEVE_SIEVE_SIEVE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int sievedebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUMBER = 258,
    STRING = 259,
    IF = 260,
    ELSIF = 261,
    ELSE = 262,
    REJCT = 263,
    FILEINTO = 264,
    REDIRECT = 265,
    KEEP = 266,
    STOP = 267,
    DISCARD = 268,
    VACATION = 269,
    REQUIRE = 270,
    MARK = 271,
    UNMARK = 272,
    FLAGS = 273,
    NOTIFY = 274,
    DENOTIFY = 275,
    ANYOF = 276,
    ALLOF = 277,
    EXISTS = 278,
    SFALSE = 279,
    STRUE = 280,
    HEADER = 281,
    NOT = 282,
    SIZE = 283,
    ADDRESS = 284,
    ENVELOPE = 285,
    BODY = 286,
    COMPARATOR = 287,
    IS = 288,
    CONTAINS = 289,
    MATCHES = 290,
    REGEX = 291,
    COUNT = 292,
    VALUE = 293,
    OVER = 294,
    UNDER = 295,
    GT = 296,
    GE = 297,
    LT = 298,
    LE = 299,
    EQ = 300,
    NE = 301,
    ALL = 302,
    LOCALPART = 303,
    DOMAIN = 304,
    USER = 305,
    DETAIL = 306,
    RAW = 307,
    TEXT = 308,
    CONTENT = 309,
    DAYS = 310,
    ADDRESSES = 311,
    SUBJECT = 312,
    FROM = 313,
    HANDLE = 314,
    MIME = 315,
    SECONDS = 316,
    METHOD = 317,
    ID = 318,
    OPTIONS = 319,
    LOW = 320,
    NORMAL = 321,
    HIGH = 322,
    ANY = 323,
    MESSAGE = 324,
    INCLUDE = 325,
    PERSONAL = 326,
    GLOBAL = 327,
    RETURN = 328,
    OPTIONAL = 329,
    ONCE = 330,
    COPY = 331,
    DATE = 332,
    CURRENTDATE = 333,
    INDEX = 334,
    LAST = 335,
    ZONE = 336,
    ORIGINALZONE = 337,
    MAILBOXEXISTS = 338,
    CREATE = 339,
    METADATA = 340,
    METADATAEXISTS = 341,
    SERVERMETADATA = 342,
    SERVERMETADATAEXISTS = 343,
    YEAR = 344,
    MONTH = 345,
    DAY = 346,
    JULIAN = 347,
    HOUR = 348,
    MINUTE = 349,
    SECOND = 350,
    TIME = 351,
    ISO8601 = 352,
    STD11 = 353,
    WEEKDAY = 354,
    STRINGT = 355,
    SET = 356,
    LOWER = 357,
    UPPER = 358,
    LOWERFIRST = 359,
    UPPERFIRST = 360,
    QUOTEWILDCARD = 361,
    LENGTH = 362,
    SETFLAG = 363,
    ADDFLAG = 364,
    REMOVEFLAG = 365,
    HASFLAG = 366
  };
#endif
/* Tokens.  */
#define NUMBER 258
#define STRING 259
#define IF 260
#define ELSIF 261
#define ELSE 262
#define REJCT 263
#define FILEINTO 264
#define REDIRECT 265
#define KEEP 266
#define STOP 267
#define DISCARD 268
#define VACATION 269
#define REQUIRE 270
#define MARK 271
#define UNMARK 272
#define FLAGS 273
#define NOTIFY 274
#define DENOTIFY 275
#define ANYOF 276
#define ALLOF 277
#define EXISTS 278
#define SFALSE 279
#define STRUE 280
#define HEADER 281
#define NOT 282
#define SIZE 283
#define ADDRESS 284
#define ENVELOPE 285
#define BODY 286
#define COMPARATOR 287
#define IS 288
#define CONTAINS 289
#define MATCHES 290
#define REGEX 291
#define COUNT 292
#define VALUE 293
#define OVER 294
#define UNDER 295
#define GT 296
#define GE 297
#define LT 298
#define LE 299
#define EQ 300
#define NE 301
#define ALL 302
#define LOCALPART 303
#define DOMAIN 304
#define USER 305
#define DETAIL 306
#define RAW 307
#define TEXT 308
#define CONTENT 309
#define DAYS 310
#define ADDRESSES 311
#define SUBJECT 312
#define FROM 313
#define HANDLE 314
#define MIME 315
#define SECONDS 316
#define METHOD 317
#define ID 318
#define OPTIONS 319
#define LOW 320
#define NORMAL 321
#define HIGH 322
#define ANY 323
#define MESSAGE 324
#define INCLUDE 325
#define PERSONAL 326
#define GLOBAL 327
#define RETURN 328
#define OPTIONAL 329
#define ONCE 330
#define COPY 331
#define DATE 332
#define CURRENTDATE 333
#define INDEX 334
#define LAST 335
#define ZONE 336
#define ORIGINALZONE 337
#define MAILBOXEXISTS 338
#define CREATE 339
#define METADATA 340
#define METADATAEXISTS 341
#define SERVERMETADATA 342
#define SERVERMETADATAEXISTS 343
#define YEAR 344
#define MONTH 345
#define DAY 346
#define JULIAN 347
#define HOUR 348
#define MINUTE 349
#define SECOND 350
#define TIME 351
#define ISO8601 352
#define STD11 353
#define WEEKDAY 354
#define STRINGT 355
#define SET 356
#define LOWER 357
#define UPPER 358
#define LOWERFIRST 359
#define UPPERFIRST 360
#define QUOTEWILDCARD 361
#define LENGTH 362
#define SETFLAG 363
#define ADDFLAG 364
#define REMOVEFLAG 365
#define HASFLAG 366

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 238 "sieve/sieve.y" /* yacc.c:355  */

    int nval;
    char *sval;
    strarray_t *sl;
    test_t *test;
    testlist_t *testl;
    commandlist_t *cl;
    struct vtags *vtag;
    struct aetags *aetag;
    struct comptags *ctag;
    struct btags *btag;
    struct ntags *ntag;
    struct dtags *dtag;
    struct itags *itag;
    struct dttags *dttag;
    struct ftags *ftag;
    struct stags *stag;

#line 590 "sieve/sieve.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int sieveparse (sieve_script_t *parse_script);

#endif /* !YY_SIEVE_SIEVE_SIEVE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 606 "sieve/sieve.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   419

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  120
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  48
/* YYNRULES -- Number of rules.  */
#define YYNRULES  167
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  244

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   366

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     118,   119,     2,     2,   115,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   112,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   113,     2,   114,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   116,     2,   117,     2,     2,     2,     2,
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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   314,   314,   315,   318,   319,   322,   333,   334,   337,
     338,   339,   342,   343,   344,   347,   362,   377,   385,   386,
     387,   389,   406,   422,   433,   444,   456,   475,   496,   507,
     525,   526,   527,   530,   531,   552,   553,   563,   573,   608,
     620,   621,   623,   624,   626,   628,   631,   632,   642,   652,
     662,   673,   674,   684,   694,   704,   714,   726,   727,   737,
     752,   753,   754,   757,   758,   768,   784,   798,   811,   824,
     837,   849,   850,   856,   860,   866,   867,   870,   871,   872,
     873,   874,   876,   899,   932,   967,   992,  1015,  1044,  1069,
    1070,  1073,  1101,  1127,  1146,  1165,  1184,  1203,  1222,  1225,
    1226,  1237,  1238,  1239,  1242,  1243,  1254,  1255,  1261,  1272,
    1295,  1321,  1344,  1368,  1369,  1370,  1371,  1374,  1375,  1376,
    1379,  1380,  1381,  1384,  1385,  1386,  1389,  1390,  1401,  1412,
    1426,  1427,  1430,  1431,  1442,  1443,  1444,  1445,  1448,  1449,
    1450,  1451,  1457,  1476,  1485,  1486,  1487,  1488,  1498,  1509,
    1510,  1511,  1512,  1524,  1534,  1547,  1548,  1551,  1563,  1575,
    1576,  1587,  1598,  1622,  1623,  1636,  1639,  1640
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "STRING", "IF", "ELSIF",
  "ELSE", "REJCT", "FILEINTO", "REDIRECT", "KEEP", "STOP", "DISCARD",
  "VACATION", "REQUIRE", "MARK", "UNMARK", "FLAGS", "NOTIFY", "DENOTIFY",
  "ANYOF", "ALLOF", "EXISTS", "SFALSE", "STRUE", "HEADER", "NOT", "SIZE",
  "ADDRESS", "ENVELOPE", "BODY", "COMPARATOR", "IS", "CONTAINS", "MATCHES",
  "REGEX", "COUNT", "VALUE", "OVER", "UNDER", "GT", "GE", "LT", "LE", "EQ",
  "NE", "ALL", "LOCALPART", "DOMAIN", "USER", "DETAIL", "RAW", "TEXT",
  "CONTENT", "DAYS", "ADDRESSES", "SUBJECT", "FROM", "HANDLE", "MIME",
  "SECONDS", "METHOD", "ID", "OPTIONS", "LOW", "NORMAL", "HIGH", "ANY",
  "MESSAGE", "INCLUDE", "PERSONAL", "GLOBAL", "RETURN", "OPTIONAL", "ONCE",
  "COPY", "DATE", "CURRENTDATE", "INDEX", "LAST", "ZONE", "ORIGINALZONE",
  "MAILBOXEXISTS", "CREATE", "METADATA", "METADATAEXISTS",
  "SERVERMETADATA", "SERVERMETADATAEXISTS", "YEAR", "MONTH", "DAY",
  "JULIAN", "HOUR", "MINUTE", "SECOND", "TIME", "ISO8601", "STD11",
  "WEEKDAY", "STRINGT", "SET", "LOWER", "UPPER", "LOWERFIRST",
  "UPPERFIRST", "QUOTEWILDCARD", "LENGTH", "SETFLAG", "ADDFLAG",
  "REMOVEFLAG", "HASFLAG", "';'", "'['", "']'", "','", "'{'", "'}'", "'('",
  "')'", "$accept", "start", "reqs", "require", "commands", "command",
  "elsif", "action", "flagaction", "flagtags", "stags", "mod40", "mod30",
  "mod20", "mod10", "itags", "ntags", "dtags", "priority", "vtags",
  "stringlist", "strings", "block", "test", "atags", "etags", "matchtags",
  "comparator", "idxtags", "htags", "strtags", "hftags", "mtags", "btags",
  "dttags", "cdtags", "zone", "datepart", "addrparttag", "match",
  "relmatch", "sizetag", "copy", "creat", "ftags", "rtags", "testlist",
  "tests", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,    59,    91,    93,    44,   123,   125,    40,    41
};
# endif

#define YYPACT_NINF -199

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-199)))

#define YYTABLE_NINF -73

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -9,    -2,    13,   195,    -9,  -199,    20,   -82,  -199,   -75,
     140,    29,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,
    -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,     9,
     -72,  -199,  -199,  -199,   -79,  -199,  -199,  -199,   -76,   -76,
      -2,  -199,  -199,  -199,   140,     7,  -199,  -199,  -199,  -199,
    -199,    -2,  -199,    47,  -199,    -2,  -199,  -199,   -64,  -199,
      23,     1,    -3,   297,   350,   301,   245,   176,  -199,  -199,
      -1,  -199,    51,   140,  -199,  -199,  -199,   220,  -199,  -199,
    -199,    53,   197,   237,    68,   293,    28,  -199,   308,    -2,
     344,  -199,   257,   257,    75,    42,  -199,    -2,  -199,  -199,
    -199,  -199,  -199,  -199,  -199,    54,    -2,    55,    64,    66,
    -199,    71,    67,    74,    -2,  -199,  -199,  -199,    86,  -199,
    -199,  -199,  -199,  -199,  -199,  -199,  -199,    89,  -199,    92,
    -199,  -199,  -199,  -199,  -199,    93,  -199,  -199,  -199,  -199,
    -199,  -199,  -199,  -199,  -199,  -199,   -14,  -199,  -199,    -7,
      -6,   110,   113,  -199,    -2,  -199,  -199,  -199,  -199,  -199,
    -199,  -199,  -199,  -199,    -2,  -199,  -199,  -199,  -199,    -2,
    -199,  -199,  -199,  -199,  -199,    -2,  -199,  -199,  -199,   119,
     120,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,
      -2,   123,  -199,  -199,  -199,    -2,    -2,  -199,  -199,    -2,
    -199,  -199,  -199,    11,   140,   -64,  -199,  -199,  -199,  -199,
    -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,
    -199,   140,  -199,  -199,  -199,  -199,  -199,  -199,  -199,    -2,
    -199,  -199,    -2,  -199,  -199,  -199,  -199,   -64,  -199,  -199,
    -199,  -199,    42,  -199
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     0,     4,    72,     0,     0,     1,     0,
       0,     0,   159,   163,   159,    19,    20,    63,    23,    24,
      51,    57,    46,    28,    35,    31,    30,    32,     3,     0,
       0,    33,     5,    73,     0,     6,    11,    98,     0,     0,
       0,    80,    81,   113,     0,     0,    99,   104,   126,   132,
     138,     0,   123,     0,   123,     0,   117,   120,     0,    15,
       0,     0,    18,     0,    25,    26,     0,     0,     8,     9,
       0,    71,     0,     0,    77,    78,    79,     0,    89,   155,
     156,     0,     0,     0,     0,     0,     0,    93,     0,     0,
       0,    97,     0,     0,     0,    12,    16,     0,   157,   158,
     160,   161,    17,   164,    21,     0,     0,     0,     0,     0,
      70,     0,     0,     0,     0,    60,    61,    62,     0,    55,
     149,   150,   151,   152,   153,   154,    58,     0,   108,     0,
      27,    47,    48,    50,    49,     0,    40,    41,    42,    43,
      44,    45,    36,    37,    38,    39,    34,    22,    74,   166,
       0,     0,     0,   112,     0,   114,   115,   116,    90,   144,
     145,   146,   147,   148,     0,   101,   102,   103,   100,     0,
     106,   107,   105,   127,   128,     0,    88,   130,   131,     0,
       0,   133,   135,   136,   137,   134,   143,   140,   141,   139,
       0,     0,   124,   125,    95,     0,     0,   118,   119,    85,
     121,   122,    76,     0,     0,     0,    10,   162,    64,    66,
      67,    68,    69,    65,    53,    52,    54,    56,    59,   109,
      29,     0,   165,   110,   111,    82,    86,    87,   129,     0,
     142,    92,     0,    96,    83,    84,    75,     0,    14,   167,
      91,    94,    12,    13
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -199,  -199,   125,  -199,   -25,  -199,  -111,  -199,  -199,  -199,
    -199,  -199,  -199,  -199,  -199,  -199,  -199,  -199,    69,  -199,
     -39,  -199,  -198,   -10,  -199,  -199,   306,   318,   -74,  -199,
    -199,  -199,    78,  -199,  -199,  -199,    49,   -46,    56,  -199,
    -199,  -199,    76,  -199,   124,  -199,   101,   -78
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    28,    29,   206,    30,    31,    70,
      67,   142,   143,   144,   145,    66,    64,    65,   119,    63,
       7,    34,    95,   149,    82,    83,   192,   193,   157,    77,
      92,    93,    88,    84,    85,    86,   185,   190,   168,   128,
     129,    81,   100,   101,    60,    61,    74,   150
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      58,    76,     5,   146,    68,   102,     1,   238,   167,    -7,
       9,   184,    87,     8,    10,    97,    91,    11,    12,    13,
      14,    15,    16,    17,    33,    18,    19,    96,    20,    21,
      35,   147,   186,    59,    78,    71,    72,    36,   154,   242,
      69,    97,    73,   164,   169,   176,    79,    80,   204,   205,
     194,    89,    94,   196,   199,   148,   158,   208,   207,   210,
     151,   120,   121,   122,   123,   124,   125,   209,   211,   203,
     212,   214,     5,    98,   213,   216,     9,    98,   215,    22,
      10,    99,    23,    11,    12,    13,    14,    15,    16,    17,
     217,    18,    19,   218,    20,    21,   219,   220,   -72,    98,
     151,   120,   121,   122,   123,   124,   125,    99,   221,   180,
      24,     6,     6,   222,   223,   225,   224,    25,    26,    27,
     173,   174,   175,   186,   230,   226,    -7,   232,   236,    32,
     227,   243,    90,   229,   126,   189,   228,   103,    62,   172,
      75,    37,     0,   239,     0,    22,     0,     0,    23,     0,
       0,   231,     0,     0,     0,     0,   233,   234,     0,     0,
     235,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,     0,     0,     0,     0,    24,     0,     0,     0,
     135,     6,     0,    25,    26,    27,     0,     0,     0,     0,
     240,     0,   202,   241,   237,    -2,     9,     0,     0,     0,
      10,     5,     0,    11,    12,    13,    14,    15,    16,    17,
       0,    18,    19,     0,    20,    21,     0,    49,    50,     0,
       0,     0,     0,    51,     5,    52,    53,    54,    55,   151,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
      56,     5,     0,     0,   159,   160,   161,   162,   163,   130,
       0,    57,   151,   120,   121,   122,   123,   124,   125,     0,
       0,     5,     0,     0,     0,    22,     0,     0,    23,   151,
     120,   121,   122,   123,   124,   125,   152,   153,   136,   137,
     138,   139,   140,   141,   159,   160,   161,   162,   163,   151,
     120,   121,   122,   123,   124,   125,    24,   179,     0,   152,
     153,   104,     0,    25,    26,    27,     0,     0,     0,     0,
       6,     0,   191,     0,     0,     0,   131,   132,     0,   133,
     134,     0,     0,     0,     0,   151,   120,   121,   122,   123,
     124,   125,     0,     6,   120,   121,   122,   123,   124,   125,
     151,   120,   121,   122,   123,   124,   125,     0,   195,     0,
       6,     0,   105,   106,   107,   108,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,   115,   116,   117,     0,
       6,   127,   152,   153,   180,   181,   151,   120,   121,   122,
     123,   124,   125,   155,     0,     0,     0,     0,   165,   170,
     177,   182,   187,     0,     0,   156,     0,     0,   197,   200,
     166,   171,   178,   183,   188,     0,     0,     0,     0,     0,
     198,   201,   112,   113,   114,   115,   116,   117,     0,   118
};

static const yytype_int16 yycheck[] =
{
      10,    40,     4,     4,    29,     4,    15,   205,    82,     0,
       1,    85,    51,     0,     5,    18,    55,     8,     9,    10,
      11,    12,    13,    14,     4,    16,    17,     4,    19,    20,
     112,    70,     4,     4,    44,   114,   115,   112,    77,   237,
     112,    18,   118,    82,    83,    84,    39,    40,     6,     7,
      89,     4,   116,    92,    93,     4,     3,     3,    97,     4,
      32,    33,    34,    35,    36,    37,    38,   106,     4,    94,
       4,     4,     4,    76,     3,   114,     1,    76,     4,    70,
       5,    84,    73,     8,     9,    10,    11,    12,    13,    14,
       4,    16,    17,     4,    19,    20,     4,     4,   112,    76,
      32,    33,    34,    35,    36,    37,    38,    84,   115,    81,
     101,   113,   113,   119,     4,   154,     3,   108,   109,   110,
      52,    53,    54,     4,     4,   164,   117,     4,   117,     4,
     169,   242,    54,   179,    65,    86,   175,    61,    14,    83,
      39,     1,    -1,   221,    -1,    70,    -1,    -1,    73,    -1,
      -1,   190,    -1,    -1,    -1,    -1,   195,   196,    -1,    -1,
     199,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    -1,    -1,    -1,   101,    -1,    -1,    -1,
       4,   113,    -1,   108,   109,   110,    -1,    -1,    -1,    -1,
     229,    -1,   117,   232,   204,     0,     1,    -1,    -1,    -1,
       5,     4,    -1,     8,     9,    10,    11,    12,    13,    14,
      -1,    16,    17,    -1,    19,    20,    -1,    77,    78,    -1,
      -1,    -1,    -1,    83,     4,    85,    86,    87,    88,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
     100,     4,    -1,    -1,    47,    48,    49,    50,    51,     4,
      -1,   111,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,     4,    -1,    -1,    -1,    70,    -1,    -1,    73,    32,
      33,    34,    35,    36,    37,    38,    79,    80,   102,   103,
     104,   105,   106,   107,    47,    48,    49,    50,    51,    32,
      33,    34,    35,    36,    37,    38,   101,     4,    -1,    79,
      80,     4,    -1,   108,   109,   110,    -1,    -1,    -1,    -1,
     113,    -1,     4,    -1,    -1,    -1,    71,    72,    -1,    74,
      75,    -1,    -1,    -1,    -1,    32,    33,    34,    35,    36,
      37,    38,    -1,   113,    33,    34,    35,    36,    37,    38,
      32,    33,    34,    35,    36,    37,    38,    -1,     4,    -1,
     113,    -1,    55,    56,    57,    58,    59,    60,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    -1,
     113,    65,    79,    80,    81,    82,    32,    33,    34,    35,
      36,    37,    38,    77,    -1,    -1,    -1,    -1,    82,    83,
      84,    85,    86,    -1,    -1,    77,    -1,    -1,    92,    93,
      82,    83,    84,    85,    86,    -1,    -1,    -1,    -1,    -1,
      92,    93,    62,    63,    64,    65,    66,    67,    -1,    69
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    15,   121,   122,   123,     4,   113,   140,     0,     1,
       5,     8,     9,    10,    11,    12,    13,    14,    16,    17,
      19,    20,    70,    73,   101,   108,   109,   110,   124,   125,
     127,   128,   122,     4,   141,   112,   112,     1,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    77,
      78,    83,    85,    86,    87,    88,   100,   111,   143,     4,
     164,   165,   164,   139,   136,   137,   135,   130,   124,   112,
     129,   114,   115,   118,   166,   166,   140,   149,   143,    39,
      40,   161,   144,   145,   153,   154,   155,   140,   152,     4,
     152,   140,   150,   151,   116,   142,     4,    18,    76,    84,
     162,   163,     4,   162,     4,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    69,   138,
      33,    34,    35,    36,    37,    38,   138,   146,   159,   160,
       4,    71,    72,    74,    75,     4,   102,   103,   104,   105,
     106,   107,   131,   132,   133,   134,     4,   140,     4,   143,
     167,    32,    79,    80,   140,   146,   147,   148,     3,    47,
      48,    49,    50,    51,   140,   146,   147,   148,   158,   140,
     146,   147,   158,    52,    53,    54,   140,   146,   147,     4,
      81,    82,   146,   147,   148,   156,     4,   146,   147,   156,
     157,     4,   146,   147,   140,     4,   140,   146,   147,   140,
     146,   147,   117,   124,     6,     7,   126,   140,     3,   140,
       4,     4,     4,     3,     4,     4,   140,     4,     4,     4,
       4,   115,   119,     4,     3,   140,   140,   140,   140,   157,
       4,   140,     4,   140,   140,   140,   117,   143,   142,   167,
     140,   140,   142,   126
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   120,   121,   121,   122,   122,   123,   124,   124,   125,
     125,   125,   126,   126,   126,   127,   127,   127,   127,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     128,   128,   128,   129,   129,   130,   130,   130,   130,   130,
     131,   131,   132,   132,   133,   134,   135,   135,   135,   135,
     135,   136,   136,   136,   136,   136,   136,   137,   137,   137,
     138,   138,   138,   139,   139,   139,   139,   139,   139,   139,
     139,   140,   140,   141,   141,   142,   142,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   143,
     143,   143,   143,   143,   143,   143,   143,   143,   143,   144,
     144,   144,   144,   144,   145,   145,   145,   145,   146,   146,
     147,   148,   148,   149,   149,   149,   149,   150,   150,   150,
     151,   151,   151,   152,   152,   152,   153,   153,   153,   153,
     153,   153,   154,   154,   154,   154,   154,   154,   155,   155,
     155,   155,   156,   157,   158,   158,   158,   158,   158,   159,
     159,   159,   159,   160,   160,   161,   161,   162,   163,   164,
     164,   164,   164,   165,   165,   166,   167,   167
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     3,     1,     2,     2,
       4,     2,     0,     4,     2,     2,     3,     3,     2,     1,
       1,     3,     3,     1,     1,     2,     2,     3,     1,     4,
       1,     1,     1,     0,     2,     0,     2,     2,     2,     2,
       1,     1,     1,     1,     1,     1,     0,     2,     2,     2,
       2,     0,     3,     3,     3,     2,     3,     0,     2,     3,
       1,     1,     1,     0,     3,     3,     3,     3,     3,     3,
       2,     3,     1,     1,     3,     3,     2,     2,     2,     2,
       1,     1,     4,     4,     4,     3,     4,     4,     3,     2,
       3,     5,     4,     2,     5,     3,     4,     2,     1,     0,
       2,     2,     2,     2,     0,     2,     2,     2,     1,     2,
       2,     2,     1,     0,     2,     2,     2,     0,     2,     2,
       0,     2,     2,     0,     2,     2,     0,     2,     2,     3,
       2,     2,     0,     2,     2,     2,     2,     2,     0,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       2,     2,     3,     0,     2,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      yyerror (parse_script, YY_("syntax error: cannot back up")); \
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
                  Type, Value, parse_script); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, sieve_script_t *parse_script)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (parse_script);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, sieve_script_t *parse_script)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parse_script);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, sieve_script_t *parse_script)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              , parse_script);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, parse_script); \
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, sieve_script_t *parse_script)
{
  YYUSE (yyvaluep);
  YYUSE (parse_script);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 124: /* commands  */
#line 302 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl)); }
#line 1675 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 125: /* command  */
#line 302 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl)); }
#line 1681 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 126: /* elsif  */
#line 302 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl)); }
#line 1687 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 127: /* action  */
#line 302 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl)); }
#line 1693 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 142: /* block  */
#line 302 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl)); }
#line 1699 "sieve/sieve.c" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (sieve_script_t *parse_script)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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
      yychar = yylex (&yylval, parse_script);
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
#line 314 "sieve/sieve.y" /* yacc.c:1646  */
    { parse_script->cmds = NULL; }
#line 1967 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 3:
#line 315 "sieve/sieve.y" /* yacc.c:1646  */
    { parse_script->cmds = (yyvsp[0].cl); }
#line 1973 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 6:
#line 323 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                    char *err = check_reqs(parse_script, (yyvsp[-1].sl));
                                    if (err) {
                                        yyerror(parse_script, err);
                                        free(err);
                                        YYERROR;
                                    }
                                }
#line 1986 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 7:
#line 333 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = (yyvsp[0].cl); }
#line 1992 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 8:
#line 334 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyvsp[-1].cl)->next = (yyvsp[0].cl); (yyval.cl) = (yyvsp[-1].cl); }
#line 1998 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 9:
#line 337 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = (yyvsp[-1].cl); }
#line 2004 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 10:
#line 338 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_if((yyvsp[-2].test), (yyvsp[-1].cl), (yyvsp[0].cl)); }
#line 2010 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 11:
#line 339 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(STOP); }
#line 2016 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 12:
#line 342 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = NULL; }
#line 2022 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 13:
#line 343 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_if((yyvsp[-2].test), (yyvsp[-1].cl), (yyvsp[0].cl)); }
#line 2028 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 14:
#line 344 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = (yyvsp[0].cl); }
#line 2034 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 15:
#line 348 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.reject) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "reject");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!verify_utf8(parse_script, (yyvsp[0].sval))) {
                                         YYERROR; /* vu should call yyerror() */
                                     }
                                     (yyval.cl) = new_command(REJCT);
                                     (yyval.cl)->u.reject = (yyvsp[0].sval);
                                 }
#line 2052 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 16:
#line 363 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.fileinto) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "fileinto");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!verify_mailbox(parse_script, (yyvsp[0].sval))) {
                                         YYERROR; /* vm should call yyerror() */
                                     }
                                     (yyval.cl) = build_fileinto(FILEINTO,
                                                         canon_ftags((yyvsp[-1].ftag)), (yyvsp[0].sval));
                                 }
#line 2070 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 17:
#line 378 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!verify_address(parse_script, (yyvsp[0].sval))) {
                                         YYERROR; /* va should call yyerror() */
                                     }
                                     (yyval.cl) = build_redirect(REDIRECT, (yyvsp[-1].nval), (yyvsp[0].sval));
                                 }
#line 2081 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 18:
#line 385 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_keep(KEEP,canon_ftags((yyvsp[0].ftag))); }
#line 2087 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 19:
#line 386 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(STOP); }
#line 2093 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 20:
#line 387 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(DISCARD); }
#line 2099 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 21:
#line 390 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.vacation) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "vacation");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (((yyvsp[-1].vtag)->mime == -1) &&
                                         !verify_utf8(parse_script, (yyvsp[0].sval))) {
                                         YYERROR; /* vu should call yyerror() */
                                     }
                                     (yyval.cl) = build_vacation(VACATION,
                                                         canon_vtags(parse_script, (yyvsp[-1].vtag)),
                                                         (yyvsp[0].sval));
                                 }
#line 2119 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 22:
#line 407 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!(parse_script->support.imapflags ||
                                           parse_script->support.imap4flags)) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "imap[4]flags");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!parse_script->support.variables) {
                                         verify_flaglist((yyvsp[0].sl));
                                     }
                                     if (!(yyvsp[0].sl)->count) strarray_add((yyvsp[0].sl), "");
                                     (yyval.cl) = build_flag((yyvsp[-2].nval), (yyvsp[-1].sval), (yyvsp[0].sl));
                                 }
#line 2138 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 23:
#line 423 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.imapflags) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "imapflags");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.cl) = new_command(MARK);
                                 }
#line 2152 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 24:
#line 434 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.imapflags) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "imapflags");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.cl) = new_command(UNMARK);
                                 }
#line 2166 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 25:
#line 445 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.notify) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "notify");
                                         (yyval.cl) = new_command(NOTIFY);
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.cl) = build_notify(NOTIFY, canon_ntags((yyvsp[0].ntag)));
                                 }
#line 2181 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 26:
#line 457 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.notify) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "notify");
                                         (yyval.cl) = new_command(DENOTIFY);
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.cl) = build_denotify(DENOTIFY,
                                                         canon_dtags((yyvsp[0].dtag)));
                                     if ((yyval.cl) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "denotify action");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 2203 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 27:
#line 476 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.include) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "include");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     int i;
                                     for (i = 0; (yyvsp[0].sval)[i] != '\0'; i++) {
                                         if ((yyvsp[0].sval)[i] == '/') {
                                             parse_error(parse_script,
                                                         SIEVE_INVALID_VALUE,
                                                         "script-name");
                                             YYERROR; /* pe should call yyerror() */
                                             break;
                                         }
                                     }
                                     (yyval.cl) = build_include(INCLUDE, (yyvsp[-1].itag), (yyvsp[0].sval));
                                 }
#line 2227 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 28:
#line 497 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.include) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "include");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.cl) = new_command(RETURN);
                                 }
#line 2241 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 29:
#line 508 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.variables) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "variables");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!verify_identifier(parse_script, (yyvsp[-1].sval))) {
                                         YYERROR; /* vi should call yyerror() */
                                     }
                                     if (!verify_utf8(parse_script, (yyvsp[0].sval))) {
                                         YYERROR; /* vu should call yyerror() */
                                     }
                                     (yyval.cl) = build_set(SET, canon_stags((yyvsp[-2].stag)), (yyvsp[-1].sval), (yyvsp[0].sval));
                                 }
#line 2261 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 33:
#line 530 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.sval) = NULL; }
#line 2267 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 34:
#line 532 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!(parse_script->support.imap4flags)) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "imap4flags");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if ((yyvsp[-1].sval)) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_ARG,
                                                     "variablename");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!is_identifier((yyvsp[0].sval))) {
                                         YYERROR; /* id should call yyerror() */
                                     }
                                     (yyval.sval) = (yyvsp[0].sval);
                                 }
#line 2290 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 35:
#line 552 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.stag) = new_stags(); }
#line 2296 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 36:
#line 554 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.stag)->mod40) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "precedence 40 modifier");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.stag)->mod40 = (yyvsp[0].nval);
                                 }
#line 2310 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 37:
#line 564 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.stag)->mod30) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "precedence 30 modifier");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.stag)->mod30 = (yyvsp[0].nval);
                                 }
#line 2324 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 38:
#line 574 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.stag)->mod20) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "precedence 20 modifier");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.stag)->mod20 = (yyvsp[0].nval);
                                 }
#line 2338 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 39:
#line 609 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.stag)->mod10) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "precedence 10 modifier");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.stag)->mod10 = (yyvsp[0].nval);
                                 }
#line 2352 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 46:
#line 631 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.itag) = new_itags(); }
#line 2358 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 47:
#line 633 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.itag)->location != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "location");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.itag)->location = PERSONAL;
                                 }
#line 2372 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 48:
#line 643 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.itag)->location != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "location");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.itag)->location = GLOBAL;
                                 }
#line 2386 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 49:
#line 653 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.itag)->once != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":once");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.itag)->once = 1;
                                 }
#line 2400 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 50:
#line 663 "sieve/sieve.y" /* yacc.c:1646  */
    { if ((yyval.itag)->optional != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":optional");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.itag)->optional = 1;
                                 }
#line 2413 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 51:
#line 673 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.ntag) = new_ntags(); }
#line 2419 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 52:
#line 675 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.ntag)->id != NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":id");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.ntag)->id = (yyvsp[0].sval);
                                 }
#line 2433 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 53:
#line 685 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.ntag)->method != NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":method");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.ntag)->method = (yyvsp[0].sval);
                                 }
#line 2447 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 54:
#line 695 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.ntag)->options != NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":options");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.ntag)->options = (yyvsp[0].sl);
                                 }
#line 2461 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 55:
#line 705 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.ntag)->priority != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "priority");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.ntag)->priority = (yyvsp[0].nval);
                                 }
#line 2475 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 56:
#line 715 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.ntag)->message != NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":message");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.ntag)->message = (yyvsp[0].sval);
                                 }
#line 2489 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 57:
#line 726 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.dtag) = new_dtags(); }
#line 2495 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 58:
#line 728 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.dtag)->priority != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "priority");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.dtag)->priority = (yyvsp[0].nval);
                                 }
#line 2509 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 59:
#line 738 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.dtag)->pattern = (yyvsp[0].sval);

                                     strarray_t sa = STRARRAY_INITIALIZER;
                                     strarray_appendm(&sa, (yyvsp[0].sval));
                                     if (!verify_patternlist(parse_script, &sa,
                                                             &((yyval.dtag)->comptags),
                                                             NULL)) {
                                         YYERROR; /* vp should call yyerror() */
                                     }
                                     strarray_fini(&sa);
                                 }
#line 2526 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 60:
#line 752 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = LOW; }
#line 2532 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 61:
#line 753 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = NORMAL; }
#line 2538 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 62:
#line 754 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = HIGH; }
#line 2544 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 63:
#line 757 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.vtag) = new_vtags(); }
#line 2550 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 64:
#line 759 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.vtag)->seconds != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "period");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.vtag)->seconds = (yyvsp[0].nval) * DAY2SEC;
                                 }
#line 2564 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 65:
#line 769 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.vacation_seconds) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "vacation-seconds");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if ((yyval.vtag)->seconds != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "period");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.vtag)->seconds = (yyvsp[0].nval);
                                 }
#line 2584 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 66:
#line 785 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.vtag)->addresses != NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":addresses");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!verify_stringlist(parse_script, (yyvsp[0].sl),
                                                            verify_address)) {
                                         YYERROR;
                                     }
                                     (yyval.vtag)->addresses = (yyvsp[0].sl);
                                 }
#line 2602 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 67:
#line 799 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.vtag)->subject != NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":subject");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!verify_utf8(parse_script, (yyvsp[0].sval))) {
                                         YYERROR; /* vu should call yyerror() */
                                     }
                                     (yyval.vtag)->subject = (yyvsp[0].sval);
                                 }
#line 2619 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 68:
#line 812 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.vtag)->from != NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":from");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!verify_address(parse_script, (yyvsp[0].sval))) {
                                         YYERROR; /* va should call yyerror() */
                                     }
                                     (yyval.vtag)->from = (yyvsp[0].sval);
                                 }
#line 2636 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 69:
#line 825 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.vtag)->handle != NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":handle");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!verify_utf8(parse_script, (yyvsp[0].sval))) {
                                         YYERROR; /* vu should call yyerror() */
                                     }
                                     (yyval.vtag)->handle = (yyvsp[0].sval);
                                 }
#line 2653 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 70:
#line 838 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.vtag)->mime != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":mime");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.vtag)->mime = MIME;
                                 }
#line 2667 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 71:
#line 849 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.sl) = (yyvsp[-1].sl); }
#line 2673 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 72:
#line 850 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                    (yyval.sl) = strarray_new();
                                    strarray_appendm((yyval.sl), (yyvsp[0].sval));
                                 }
#line 2682 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 73:
#line 856 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                    (yyval.sl) = strarray_new();
                                    strarray_appendm((yyval.sl), (yyvsp[0].sval));
                                 }
#line 2691 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 74:
#line 860 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                    (yyval.sl) = (yyvsp[-2].sl);
                                    strarray_appendm((yyval.sl), (yyvsp[0].sval));
                                 }
#line 2700 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 75:
#line 866 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = (yyvsp[-1].cl); }
#line 2706 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 76:
#line 867 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = NULL; }
#line 2712 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 77:
#line 870 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(ANYOF); (yyval.test)->u.tl = (yyvsp[0].testl); }
#line 2718 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 78:
#line 871 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(ALLOF); (yyval.test)->u.tl = (yyvsp[0].testl); }
#line 2724 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 79:
#line 872 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(EXISTS); (yyval.test)->u.sl = (yyvsp[0].sl); }
#line 2730 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 80:
#line 873 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(SFALSE); }
#line 2736 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 81:
#line 874 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(STRUE); }
#line 2742 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 82:
#line 877 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!verify_stringlist(parse_script,
                                                            (yyvsp[-1].sl), verify_header)) {
                                         YYERROR; /* vh should call yyerror() */
                                     }
                                     (yyvsp[-2].ctag) = canon_comptags((yyvsp[-2].ctag));

                                     if (!verify_patternlist(parse_script,
                                                             (yyvsp[0].sl), (yyvsp[-2].ctag),
                                                             verify_utf8)) {
                                         YYERROR; /* vp should call yyerror() */
                                     }

                                     (yyval.test) = build_header(HEADER, (yyvsp[-2].ctag), (yyvsp[-1].sl), (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "header test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 2768 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 83:
#line 900 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.variables) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "variables");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!verify_stringlist(parse_script,
                                                            (yyvsp[-1].sl), verify_utf8)) {
                                         YYERROR; /* vu should call yyerror() */
                                     }
                                     (yyvsp[-2].ctag) = canon_comptags((yyvsp[-2].ctag));

                                     if (!verify_patternlist(parse_script,
                                                             (yyvsp[0].sl), (yyvsp[-2].ctag),
                                                             verify_utf8)) {
                                         YYERROR; /* vp should call yyerror() */
                                     }

                                     (yyval.test) = build_header(STRINGT, (yyvsp[-2].ctag), (yyvsp[-1].sl), (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "string test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 2800 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 84:
#line 933 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.imap4flags) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "imap4flags");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!parse_script->support.variables) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "variables");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!verify_stringlist(parse_script, (yyvsp[-1].sl),
                                                            verify_identifier)) {
                                         YYERROR; /* vi should call yyerror() */
                                     }
                                     (yyvsp[-2].ctag) = canon_comptags((yyvsp[-2].ctag));

                                     if (!verify_patternlist(parse_script,
                                                             (yyvsp[0].sl), (yyvsp[-2].ctag),
                                                             verify_utf8)) {
                                         YYERROR; /* vp should call yyerror() */
                                     }

                                     (yyval.test) = build_header(HASFLAG, (yyvsp[-2].ctag), (yyvsp[-1].sl), (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "hasflag test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 2838 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 85:
#line 968 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.imap4flags) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "imap4flags");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyvsp[-1].ctag) = canon_comptags((yyvsp[-1].ctag));

                                     if (!verify_patternlist(parse_script,
                                                             (yyvsp[0].sl), (yyvsp[-1].ctag),
                                                             verify_utf8)) {
                                         YYERROR; /* vp should call yyerror() */
                                     }

                                     (yyval.test) = build_header(HASFLAG, (yyvsp[-1].ctag), NULL, (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "hasflag test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 2866 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 86:
#line 993 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!verify_stringlist(parse_script, (yyvsp[-1].sl),
                                                            verify_addrheader)) {
                                         YYERROR; /* vah should call yyerror() */
                                     }
                                     (yyvsp[-2].aetag) = canon_aetags((yyvsp[-2].aetag));

                                     if (!verify_patternlist(parse_script, (yyvsp[0].sl),
                                                             &((yyvsp[-2].aetag)->comptags),
                                                             NULL)) {
                                         YYERROR; /* vp should call yyerror() */
                                     }

                                     (yyval.test) = build_address(ADDRESS, (yyvsp[-2].aetag), (yyvsp[-1].sl), (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "address test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 2892 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 87:
#line 1016 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.envelope) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "envelope");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!verify_stringlist(parse_script, (yyvsp[-1].sl),
                                                            verify_envelope)) {
                                         YYERROR;
                                     }
                                     (yyvsp[-2].aetag) = canon_aetags((yyvsp[-2].aetag));

                                     if (!verify_patternlist(parse_script, (yyvsp[0].sl),
                                                             &((yyvsp[-2].aetag)->comptags),
                                                             NULL)) {
                                         YYERROR; /* vp should call yyerror() */
                                     }

                                     (yyval.test) = build_address(ENVELOPE, (yyvsp[-2].aetag), (yyvsp[-1].sl), (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "envelope test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 2924 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 88:
#line 1045 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.body) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "body");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyvsp[-1].btag) = canon_btags((yyvsp[-1].btag));

                                     if (!verify_patternlist(parse_script, (yyvsp[0].sl),
                                                             &((yyvsp[-1].btag)->comptags),
                                                             verify_utf8)) {
                                         YYERROR; /* vp should call yyerror() */
                                     }

                                     (yyval.test) = build_body(BODY, (yyvsp[-1].btag), (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "body test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 2952 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 89:
#line 1069 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(NOT); (yyval.test)->u.t = (yyvsp[0].test); }
#line 2958 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 90:
#line 1070 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(SIZE); (yyval.test)->u.sz.t = (yyvsp[-1].nval);
                                   (yyval.test)->u.sz.n = (yyvsp[0].nval); }
#line 2965 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 91:
#line 1074 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.date) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "date");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (!verify_header(parse_script, (yyvsp[-2].sval))) {
                                         YYERROR; /* vh should call yyerror() */
                                     }
                                     (yyvsp[-3].dttag) = canon_dttags((yyvsp[-3].dttag));

                                     if (!verify_patternlist(parse_script, (yyvsp[0].sl),
                                                             &((yyvsp[-3].dttag)->comptags),
                                                             NULL)) {
                                         YYERROR; /* vp should call yyerror() */
                                     }

                                     (yyval.test) = build_date(DATE, (yyvsp[-3].dttag), (yyvsp[-2].sval), (yyvsp[-1].nval), (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "date test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 2996 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 92:
#line 1102 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.date) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "date");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyvsp[-2].dttag) = canon_dttags((yyvsp[-2].dttag));

                                     if (!verify_patternlist(parse_script, (yyvsp[0].sl),
                                                             &((yyvsp[-2].dttag)->comptags),
                                                             NULL)) {
                                         YYERROR; /* vp should call yyerror() */
                                     }

                                     (yyval.test) = build_date(CURRENTDATE,
                                                     (yyvsp[-2].dttag), NULL, (yyvsp[-1].nval), (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "currentdate test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 3025 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 93:
#line 1128 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.mailbox) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "mailbox");
                                         YYERROR; /* pe should call yyerror() */
                                     }

                                     (yyval.test) = build_mailboxtest(MAILBOXEXISTS, NULL,
                                                            NULL, NULL, (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "mailboxexists test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 3047 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 94:
#line 1147 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.mboxmetadata) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "mboxmetadata");
                                         YYERROR; /* pe should call yyerror() */
                                     }

                                     (yyval.test) = build_mailboxtest(METADATA,
                                                            (yyvsp[-3].ctag), (yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "metadata test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 3069 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 95:
#line 1166 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.mboxmetadata) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "mboxmetadata");
                                         YYERROR; /* pe should call yyerror() */
                                     }

                                     (yyval.test) = build_mailboxtest(METADATAEXISTS,
                                                            NULL, (yyvsp[-1].sval), NULL, (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "metadataexists test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 3091 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 96:
#line 1185 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.servermetadata) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "servermetadata");
                                         YYERROR; /* pe should call yyerror() */
                                     }

                                     (yyval.test) = build_mailboxtest(SERVERMETADATA,
                                                            (yyvsp[-2].ctag), NULL, (yyvsp[-1].sval), (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "servermetadata test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 3113 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 97:
#line 1204 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.servermetadata) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "servermetadata");
                                         YYERROR; /* pe should call yyerror() */
                                     }

                                     (yyval.test) = build_mailboxtest(SERVERMETADATAEXISTS,
                                                            NULL, NULL, NULL, (yyvsp[0].sl));
                                     if ((yyval.test) == NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_BUILD_FAILURE,
                                                     "servermetadataexists test");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                 }
#line 3135 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 98:
#line 1222 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = NULL; }
#line 3141 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 99:
#line 1225 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.aetag) = new_aetags(); }
#line 3147 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 100:
#line 1227 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.aetag) = (yyvsp[-1].aetag);
                                     if ((yyval.aetag)->addrtag != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "address-part");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.aetag)->addrtag = (yyvsp[0].nval);
                                 }
#line 3162 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 104:
#line 1242 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.aetag) = new_aetags(); }
#line 3168 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1244 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.aetag) = (yyvsp[-1].aetag);
                                     if ((yyval.aetag)->addrtag != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "address-part");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.aetag)->addrtag = (yyvsp[0].nval);
                                 }
#line 3183 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1262 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     struct comptags *ctags = (yyvsp[-1].ctag);
                                     if (ctags->match != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "match-type");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else ctags->match = (yyvsp[0].nval);
                                 }
#line 3198 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 109:
#line 1273 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     struct comptags *ctags = (yyvsp[-2].ctag);
                                     if (ctags->match != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "match-type");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else {
                                         ctags->match = (yyvsp[-1].nval);
                                         ctags->relation =
                                             verify_relat(parse_script, (yyvsp[0].sval));
                                         if (ctags->relation == -1) {
                                             YYERROR; /*vr called yyerror()*/
                                         }
                                     }
                                 }
#line 3220 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1296 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     struct comptags *ctags = (yyvsp[-2].ctag);
                                     if (ctags->comparator != NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":comparator");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else if (!strcmp((yyvsp[0].sval), "i;ascii-numeric") &&
                                              !parse_script->support.i_ascii_numeric) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "comparator-i;ascii-numeric");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else ctags->comparator = (yyvsp[0].sval);
                                 }
#line 3242 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 111:
#line 1322 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     struct comptags *ctags = (yyvsp[-2].ctag);
                                     if (!parse_script->support.index) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "index");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (ctags->index != 0) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":index");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if ((yyvsp[0].nval) <= 0) {
                                         parse_error(parse_script,
                                                     SIEVE_INVALID_VALUE,
                                                     ":index");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else ctags->index = (yyvsp[0].nval);
                                 }
#line 3269 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1345 "sieve/sieve.y" /* yacc.c:1646  */
    { struct comptags *ctags = (yyvsp[-1].ctag);
                                     if (!parse_script->support.index) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "index");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if (ctags->index == 0) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_TAG,
                                                     ":index");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else if (ctags->index < 0) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":last");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else ctags->index *= -1;
                                 }
#line 3295 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 113:
#line 1368 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.ctag) = new_comptags(); }
#line 3301 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 117:
#line 1374 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.ctag) = new_comptags(); }
#line 3307 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1379 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.ctag) = new_comptags(); }
#line 3313 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1384 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.ctag) = new_comptags(); }
#line 3319 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1389 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.btag) = new_btags(); }
#line 3325 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 127:
#line 1391 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.btag) = (yyvsp[-1].btag);
                                     if ((yyval.btag)->transform != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "transform");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.btag)->transform = RAW;
                                 }
#line 3340 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 128:
#line 1402 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.btag) = (yyvsp[-1].btag);
                                     if ((yyval.btag)->transform != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "transform");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.btag)->transform = TEXT;
                                 }
#line 3355 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 129:
#line 1413 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.btag) = (yyvsp[-2].btag);
                                     if ((yyval.btag)->transform != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     "transform");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else {
                                         (yyval.btag)->transform = CONTENT;
                                         (yyval.btag)->content_types = (yyvsp[0].sl);
                                     }
                                 }
#line 3373 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1430 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.dttag) = new_dttags(); }
#line 3379 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1432 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.dttag) = (yyvsp[-1].dttag);
                                     if ((yyval.dttag)->zonetag != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":originalzone");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.dttag)->zonetag = ORIGINALZONE;
                                 }
#line 3394 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 138:
#line 1448 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.dttag) = new_dttags(); }
#line 3400 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1458 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     struct dttags *dttags = (yyvsp[-2].dttag);
                                     if (dttags->zonetag != -1) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":zone");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else if (verify_zone(parse_script, (yyvsp[0].sval)) == -1) {
                                         YYERROR; /*vr called yyerror()*/
                                     }
                                     else {
                                         dttags->zone = (yyvsp[0].sval);
                                         dttags->zonetag = ZONE;
                                     }
                                 }
#line 3421 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1477 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.nval) = verify_date_part(parse_script, (yyvsp[0].sval));
                                     if ((yyval.nval) == -1) {
                                         YYERROR; /* vdp called yyerror() */
                                     }
                                 }
#line 3432 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1485 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = ALL; }
#line 3438 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1486 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = LOCALPART; }
#line 3444 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 146:
#line 1487 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = DOMAIN; }
#line 3450 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1489 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.subaddress) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "subaddress");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.nval) = USER;
                                 }
#line 3464 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 148:
#line 1499 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.subaddress) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "subaddress");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.nval) = DETAIL;
                                 }
#line 3478 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1509 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = IS; }
#line 3484 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1510 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = CONTAINS; }
#line 3490 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 151:
#line 1511 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = MATCHES; }
#line 3496 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1513 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.regex) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "regex");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.nval) = REGEX;
                                 }
#line 3510 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 153:
#line 1525 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.relational) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "relational");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.nval) = COUNT;
                                 }
#line 3524 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1535 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.relational) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "relational");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.nval) = VALUE;
                                 }
#line 3538 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1547 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = OVER; }
#line 3544 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1548 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = UNDER; }
#line 3550 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1552 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.copy) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "copy");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.nval) = 1;
                                 }
#line 3564 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1564 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.mailbox) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "mailbox");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     (yyval.nval) = 1;
                                 }
#line 3578 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1575 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.ftag) = new_ftags(); }
#line 3584 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1577 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.ftag) = (yyvsp[-1].ftag);
                                     if ((yyval.ftag)->copy) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":copy");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.ftag)->copy = (yyvsp[0].nval);
                                 }
#line 3599 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1588 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.ftag) = (yyvsp[-1].ftag);
                                     if ((yyval.ftag)->create) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":create");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.ftag)->create = (yyvsp[0].nval);
                                 }
#line 3614 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1599 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!parse_script->support.imap4flags) {
                                         parse_error(parse_script,
                                                     SIEVE_MISSING_REQUIRE,
                                                     "imap4flags");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     if ((yyval.ftag)->flags != NULL) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":flags");
                                         YYERROR; /* pe should call yyerror() */
                                     }

                                     (yyval.ftag) = (yyvsp[-2].ftag);
                                     if (!parse_script->support.variables) {
                                         verify_flaglist((yyvsp[0].sl));
                                     }
                                     if (!(yyvsp[0].sl)->count) strarray_add((yyvsp[0].sl), "");
                                     (yyval.ftag)->flags = (yyvsp[0].sl);
                                 }
#line 3640 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1622 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = 0; }
#line 3646 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1624 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.nval) = (yyvsp[-1].nval);
                                     if ((yyval.nval)) {
                                         parse_error(parse_script,
                                                     SIEVE_DUPLICATE_TAG,
                                                     ":copy");
                                         YYERROR; /* pe should call yyerror() */
                                     }
                                     else (yyval.nval) = (yyvsp[0].nval);
                                 }
#line 3661 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1636 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.testl) = (yyvsp[-1].testl); }
#line 3667 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1639 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.testl) = new_testlist((yyvsp[0].test), NULL); }
#line 3673 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1640 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.testl) = new_testlist((yyvsp[-2].test), (yyvsp[0].testl)); }
#line 3679 "sieve/sieve.c" /* yacc.c:1646  */
    break;


#line 3683 "sieve/sieve.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
      yyerror (parse_script, YY_("syntax error"));
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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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
        yyerror (parse_script, yymsgp);
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
                      yytoken, &yylval, parse_script);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[yystate], yyvsp, parse_script);
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
  yyerror (parse_script, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, parse_script);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, parse_script);
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
#line 1643 "sieve/sieve.y" /* yacc.c:1906  */



/*
 * Actions
 */

void yyerror(sieve_script_t *parse_script, const char *msg)
{
    parse_script->err++;
    if (parse_script->interp.err) {
        parse_script->interp.err(sievelineno, msg,
                                 parse_script->interp.interp_context,
                                 parse_script->script_context);
    }
}

static void parse_error(sieve_script_t *parse_script, int err, ...)
{
    va_list args;

    va_start(args, err);
    vsnprintf(parse_script->sieveerr, ERR_BUF_SIZE, error_message(err), args);
    yyerror(parse_script, parse_script->sieveerr);
    va_end(args);
}

static char *check_reqs(sieve_script_t *parse_script, strarray_t *sa)
{
    char *s;
    struct buf errs = BUF_INITIALIZER;
    char *res;

    while ((s = strarray_shift(sa))) {
        if (!script_require(parse_script, s)) {
            if (!errs.len)
                buf_printf(&errs,
                           "Unsupported feature(s) in \"require\": \"%s\"", s);
            else buf_printf(&errs, ", \"%s\"", s);
        }
        free(s);
    }
    strarray_free(sa);

    res = buf_release(&errs);
    if (!res[0]) {
        free(res);
        return NULL;
    }

    return res;
}

static test_t *build_address(int t, struct aetags *ae,
                             strarray_t *sl, strarray_t *pl)
{
    test_t *ret = new_test(t);  /* can be either ADDRESS or ENVELOPE */

    assert((t == ADDRESS) || (t == ENVELOPE));

    if (ret) {
        ret->u.ae.comptag = ae->comptags.match;
        ret->u.ae.relation=ae->comptags.relation;
        ret->u.ae.comparator=xstrdup(ae->comptags.comparator);
        ret->u.ae.index = ae->comptags.index;
        ret->u.ae.sl = sl;
        ret->u.ae.pl = pl;
        ret->u.ae.addrpart = ae->addrtag;
        free_aetags(ae);

    }
    return ret;
}

static test_t *build_header(int t, struct comptags *c,
                            strarray_t *sl, strarray_t *pl)
{
    test_t *ret = new_test(t);  /* can be HEADER or HASFLAG or STRINGT */

    assert((t == HEADER) || (t == HASFLAG) || (t == STRINGT));

    if (ret) {
        ret->u.h.comptag = c->match;
        ret->u.h.relation = c->relation;
        ret->u.h.comparator = xstrdup(c->comparator);
        ret->u.h.index = c->index;
        ret->u.h.sl = sl;
        ret->u.h.pl = pl;
        free_comptags(c, 1);
    }
    return ret;
}

static test_t *build_body(int t, struct btags *b, strarray_t *pl)
{
    test_t *ret = new_test(t);  /* can be BODY */

    assert(t == BODY);

    if (ret) {
        ret->u.b.comptag = b->comptags.match;
        ret->u.b.relation = b->comptags.relation;
        ret->u.b.comparator = xstrdup(b->comptags.comparator);
        ret->u.b.transform = b->transform;
        ret->u.b.offset = b->offset;
        ret->u.b.content_types = b->content_types; b->content_types = NULL;
        ret->u.b.pl = pl;
        free_btags(b);
    }
    return ret;
}

static test_t *build_mailboxtest(int t, struct comptags *c,
                                 const char *extname, const char *keyname,
                                 strarray_t *keylist)
{
    test_t *ret = new_test(t);

    if (ret) {
        ret->u.mbx.extname = xstrdupnull(extname);
        ret->u.mbx.keyname = xstrdupnull(keyname);
        ret->u.mbx.keylist = keylist;
        if (c) {
            canon_comptags(c);
            ret->u.mbx.comptag = c->match;
            ret->u.mbx.relation = c->relation;
            ret->u.mbx.comparator = xstrdup(c->comparator);
            free_comptags(c, 1);
        }
    }

    return ret;
}

static commandlist_t *build_vacation(int t, struct vtags *v, char *reason)
{
    commandlist_t *ret = new_command(t);

    assert(t == VACATION);

    if (ret) {
        ret->u.v.subject = v->subject; v->subject = NULL;
        ret->u.v.from = v->from; v->from = NULL;
        ret->u.v.handle = v->handle; v->handle = NULL;
        ret->u.v.seconds = v->seconds;
        ret->u.v.mime = v->mime;
        ret->u.v.addresses = v->addresses; v->addresses = NULL;
        free_vtags(v);
        ret->u.v.message = reason;
    }
    return ret;
}

static commandlist_t *build_notify(int t, struct ntags *n)
{
    commandlist_t *ret = new_command(t);

    assert(t == NOTIFY);
       if (ret) {
        ret->u.n.method = n->method; n->method = NULL;
        ret->u.n.id = n->id; n->id = NULL;
        ret->u.n.options = n->options; n->options = NULL;
        ret->u.n.priority = n->priority;
        ret->u.n.message = n->message; n->message = NULL;
        free_ntags(n);
    }
    return ret;
}

static commandlist_t *build_denotify(int t, struct dtags *d)
{
    commandlist_t *ret = new_command(t);

    assert(t == DENOTIFY);

    if (ret) {
        ret->u.d.comptag = d->comptags.match;
        ret->u.d.relation = d->comptags.relation;
        ret->u.d.pattern = xstrdupnull(d->pattern);
        ret->u.d.priority = d->priority;
        free_dtags(d);
    }
    return ret;
}

static commandlist_t *build_keep(int t, struct ftags *f)
{
    commandlist_t *ret = new_command(t);

    assert(t == KEEP);

    if (ret) {
        ret->u.k.copy = f->copy;
        ret->u.k.flags = f->flags; f->flags = NULL;
        free_ftags(f);
    }
    return ret;
}

static commandlist_t *build_fileinto(int t, struct ftags *f, char *folder)
{
    commandlist_t *ret = new_command(t);

    assert(t == FILEINTO);

    if (ret) {
        ret->u.f.copy = f->copy;
        ret->u.f.create = f->create;
        ret->u.f.flags = f->flags; f->flags = NULL;
        if (config_getswitch(IMAPOPT_SIEVE_UTF8FILEINTO)) {
            ret->u.f.folder = xmalloc(5 * strlen(folder) + 1);
            UTF8_to_mUTF7(ret->u.f.folder, folder);
        }
        else {
            ret->u.f.folder = xstrdup(folder);
        }
        free_ftags(f);
    }
    return ret;
}

static commandlist_t *build_redirect(int t, int copy, char *address)
{
    commandlist_t *ret = new_command(t);

    assert(t == REDIRECT);

    if (ret) {
        ret->u.r.copy = copy;
        ret->u.r.address = address;
    }
    return ret;
}

static commandlist_t *build_include(int t, struct itags *i, char* script)
{
    commandlist_t *ret = new_command(t);

    assert(t == INCLUDE);

    if (i->location == -1) i->location = PERSONAL;
    if (i->once == -1) i->once = 0;
    if (i->optional == -1) i->optional = 0;

    if (ret) {
        ret->u.inc.location = i->location;
        ret->u.inc.once = i->once;
        ret->u.inc.optional = i->optional;
        ret->u.inc.script = script;
        free(i);
    }
    return ret;
}

static test_t *build_date(int t, struct dttags *dt,
                          char *hn, int part, strarray_t *kl)
{
    test_t *ret = new_test(t);
    assert(t == DATE || t == CURRENTDATE);

    if (ret) {
        ret->u.dt.comptag = dt->comptags.match;
        ret->u.dt.relation = dt->comptags.relation;
        ret->u.dt.comparator = xstrdup(dt->comptags.comparator);
        ret->u.dt.index = dt->comptags.index;
        ret->u.dt.zone = xstrdupnull(dt->zone);
        ret->u.dt.zonetag = dt->zonetag;
        ret->u.dt.date_part = part;
        ret->u.dt.header_name = xstrdupnull(hn);
        ret->u.dt.kl = kl;
        free_dttags(dt);
    }
    return ret;
}

static commandlist_t *build_set(int t, struct stags *s,
                                char *variable, char *value)
{
    commandlist_t *ret = new_command(t);

    assert(t == SET);

    if (ret) {
        ret->u.s.mod40 = s->mod40;
        ret->u.s.mod30 = s->mod30;
        ret->u.s.mod20 = s->mod20;
        ret->u.s.mod10 = s->mod10;
        ret->u.s.variable = xstrdup(variable);
        ret->u.s.value = xstrdup(value);

        free_stags(s);
    }

    return ret;
}

static commandlist_t *build_flag(int t, char *variable, strarray_t *flags)
{
    commandlist_t *ret = new_command(t);

    assert(t == SETFLAG || t == ADDFLAG || t == REMOVEFLAG);

    if (ret) {
        ret->u.fl.variable = xstrdup(variable ? variable : "");
        ret->u.fl.flags = flags;
    }

    return ret;
}

static struct aetags *new_aetags(void)
{
    struct aetags *r = (struct aetags *) xmalloc(sizeof(struct aetags));

    init_comptags(&r->comptags);
    r->addrtag = -1;

    return r;
}

static struct aetags *canon_aetags(struct aetags *ae)
{
    canon_comptags(&ae->comptags);
    if (ae->addrtag == -1) { ae->addrtag = ALL; }
    return ae;
}

static void free_aetags(struct aetags *ae)
{
    free_comptags(&ae->comptags, 0);
    free(ae);
}

static struct comptags *new_comptags(void)
{
    struct comptags *c = (struct comptags *) xmalloc(sizeof(struct comptags));

    return init_comptags(c);
}

static struct comptags *init_comptags(struct comptags *c)
{
    c->match = c->relation = -1;
    c->comparator = NULL;
    c->index = 0;

    return c;
}

static struct comptags *canon_comptags(struct comptags *c)
{
    if (c->match == -1) c->match = IS;
    if (c->comparator == NULL) c->comparator = xstrdup("i;ascii-casemap");
    return c;
}

static void free_comptags(struct comptags *c, int destroy)
{
    free(c->comparator);
    if (destroy) free(c);
}

static struct btags *new_btags(void)
{
    struct btags *r = (struct btags *) xmalloc(sizeof(struct btags));

    init_comptags(&r->comptags);
    r->transform = r->offset = -1;
    r->content_types = NULL;

    return r;
}

static struct btags *canon_btags(struct btags *b)
{
    canon_comptags(&b->comptags);
    if (b->transform == -1) b->transform = TEXT;
    if (b->content_types == NULL) {
        b->content_types = strarray_new();
        if (b->transform == RAW) strarray_append(b->content_types, "");
        else strarray_append(b->content_types, "text");
    }
    if (b->offset == -1) b->offset = 0;
    return b;
}

static void free_btags(struct btags *b)
{
    free_comptags(&b->comptags, 0);
    if (b->content_types) strarray_free(b->content_types);
    free(b);
}

static struct vtags *new_vtags(void)
{
    struct vtags *r = (struct vtags *) xmalloc(sizeof(struct vtags));

    r->seconds = -1;
    r->addresses = NULL;
    r->subject = NULL;
    r->from = NULL;
    r->handle = NULL;
    r->mime = -1;

    return r;
}

static struct vtags *canon_vtags(sieve_script_t *parse_script, struct vtags *v)
{
    assert(parse_script->interp.vacation != NULL);

    if (v->seconds == -1) v->seconds = 7 * DAY2SEC;
    if (v->seconds < parse_script->interp.vacation->min_response)
        v->seconds = parse_script->interp.vacation->min_response;
    if (v->seconds > parse_script->interp.vacation->max_response)
        v->seconds = parse_script->interp.vacation->max_response;
    if (v->mime == -1) v->mime = 0;

    return v;
}

static void free_vtags(struct vtags *v)
{
    strarray_free(v->addresses);
    free(v->subject);
    free(v->from);
    free(v->handle);
    free(v);
}

static struct itags *new_itags()
{
    struct itags *r = (struct itags *) xmalloc(sizeof(struct itags));

    r->once = -1;
    r->location = -1;
    r->optional = -1;

    return r;
}

static struct dttags *new_dttags(void)
{
    struct dttags *dt = (struct dttags *) xmalloc(sizeof(struct dttags));

    init_comptags(&dt->comptags);
    dt->zonetag = -1;
    dt->zone = NULL;
    return dt;
}

static struct dttags *canon_dttags(struct dttags *dt)
{
    char zone[14];
    int gmoffset;
    int hours;
    int minutes;
    struct tm tm;
    time_t t;

    canon_comptags(&dt->comptags);
    if (dt->comptags.index == 0) dt->comptags.index = 1;
    if (dt->zonetag == -1) {
        t = time(NULL);
        localtime_r(&t, &tm);
        gmoffset = gmtoff_of(&tm, t) / 60;
        hours = abs(gmoffset) / 60;
        minutes = abs(gmoffset) % 60;
        snprintf(zone, sizeof(zone), "%c%02d%02d",
                 (gmoffset >= 0 ? '+' : '-'), hours, minutes);
        dt->zone = xstrdup(zone);
        dt->zonetag = ZONE;
    }
    return dt;
}

static void free_dttags(struct dttags *dt)
{
    free_comptags(&dt->comptags, 0);
    free(dt->zone);
    free(dt);
}


static struct ntags *new_ntags(void)
{
    struct ntags *r = (struct ntags *) xmalloc(sizeof(struct ntags));

    r->method = NULL;
    r->id = NULL;
    r->options = NULL;
    r->priority = -1;
    r->message = NULL;

    return r;
}

static struct ntags *canon_ntags(struct ntags *n)
{
    if (n->priority == -1) n->priority = NORMAL;
    if (n->message == NULL) n->message = xstrdup("$from$: $subject$");
    if (n->method == NULL) n->method = xstrdup("default");
    return n;
}
static struct dtags *canon_dtags(struct dtags *d)
{
    canon_comptags(&d->comptags);
    if (d->priority == -1) d->priority = ANY;
    return d;
}

static void free_ntags(struct ntags *n)
{
    free(n->method);
    free(n->id);
    strarray_free(n->options);
    free(n->message);
    free(n);
}

static struct dtags *new_dtags(void)
{
    struct dtags *r = (struct dtags *) xzmalloc(sizeof(struct dtags));

    init_comptags(&r->comptags);
    r->comptags.comparator = xstrdup("i;ascii-casemap");
    r->priority = -1;

    return r;
}

static void free_dtags(struct dtags *d)
{
    if (!d) return;
    free_comptags(&d->comptags, 0);
    free(d);
}

static struct ftags *new_ftags(void)
{
    struct ftags *f = (struct ftags *) xzmalloc(sizeof(struct ftags));
    return f;
}

static struct ftags *canon_ftags(struct ftags *f)
{
    return f;
}

static struct stags *new_stags(void)
{
    struct stags *s = (struct stags *) xmalloc(sizeof(struct stags));

    s->mod40 = 0;
    s->mod30 = 0;
    s->mod20 = 0;
    s->mod10 = 0;

    return s;
}

static struct stags *canon_stags(struct stags *s)
{
    return s;
}

static void free_stags(struct stags *s)
{
    free(s);
}

static void free_ftags(struct ftags *f)
{
    if (!f) return;
    strarray_free(f->flags);
    free(f);
}

static int verify_identifier(sieve_script_t *parse_script, char *s)
{
    /* identifier         = (ALPHA / "_") *(ALPHA / DIGIT / "_") */

    if (!is_identifier(s)) {
        snprintf(parse_script->sieveerr, ERR_BUF_SIZE,
                 "string '%s': not a valid sieve identifier", s);
        yyerror(parse_script, parse_script->sieveerr);
        return 0;
    }
    return 1;
}

static int verify_stringlist(sieve_script_t *parse_script, strarray_t *sa,
                             int (*verify)(sieve_script_t*, char *))
{
    int i;

    for (i = 0 ; i < sa->count ; i++) {
        if (!verify(parse_script, sa->data[i])) return 0;
    }
    return 1;
}

static int verify_address(sieve_script_t *parse_script, char *s)
{
    parse_script->addrerr[0] = '\0';    /* paranoia */
    YY_BUFFER_STATE buffer = addr_scan_string(s);
    if (addrparse(parse_script)) {
        snprintf(parse_script->sieveerr, ERR_BUF_SIZE,
                 "address '%s': %s", s, parse_script->addrerr);
        yyerror(parse_script, parse_script->sieveerr);
        addr_delete_buffer(buffer);
        return 0;
    }
    addr_delete_buffer(buffer);
    return 1;
}

static int verify_mailbox(sieve_script_t *parse_script, char *s)
{
    if (!verify_utf8(parse_script, s)) return 0;

    /* xxx if not a mailbox, call yyerror */
    return 1;
}

static int verify_header(sieve_script_t *parse_script, char *hdr)
{
    char *h = hdr;

    while (*h) {
        /* field-name      =       1*ftext
           ftext           =       %d33-57 / %d59-126
           ; Any character except
           ;  controls, SP, and
           ;  ":". */
        if (!((*h >= 33 && *h <= 57) || (*h >= 59 && *h <= 126))) {
            snprintf(parse_script->sieveerr, ERR_BUF_SIZE,
                     "header '%s': not a valid header", hdr);
            yyerror(parse_script, parse_script->sieveerr);
            return 0;
        }
        h++;
    }
    return 1;
}

static int verify_addrheader(sieve_script_t *parse_script, char *hdr)
{
    const char **h, *hdrs[] = {
        "from", "sender", "reply-to",   /* RFC2822 originator fields */
        "to", "cc", "bcc",              /* RFC2822 destination fields */
        "resent-from", "resent-sender", /* RFC2822 resent fields */
        "resent-to", "resent-cc", "resent-bcc",
        "return-path",                  /* RFC2822 trace fields */
        "disposition-notification-to",  /* RFC2298 MDN request fields */
        "delivered-to",                 /* non-standard (loop detection) */
        "approved",                     /* RFC1036 moderator/control fields */
        NULL
    };

    if (!config_getswitch(IMAPOPT_RFC3028_STRICT))
        return verify_header(parse_script, hdr);

    for (lcase(hdr), h = hdrs; *h; h++) {
        if (!strcmp(*h, hdr)) return 1;
    }

    snprintf(parse_script->sieveerr, ERR_BUF_SIZE,
             "header '%s': not a valid header for an address test", hdr);
    yyerror(parse_script, parse_script->sieveerr);
    return 0;
}

static int verify_envelope(sieve_script_t *parse_script, char *env)
{
    lcase(env);
    if (!config_getswitch(IMAPOPT_RFC3028_STRICT) ||
        !strcmp(env, "from") || !strcmp(env, "to") || !strcmp(env, "auth")) {
        return 1;
    }

    snprintf(parse_script->sieveerr, ERR_BUF_SIZE,
             "env-part '%s': not a valid part for an envelope test", env);
    yyerror(parse_script, parse_script->sieveerr);
    return 0;
}

static int verify_relat(sieve_script_t *parse_script, char *r)
{
    /* this really should have been a token to begin with.*/
    lcase(r);
    if (!strcmp(r, "gt")) return GT;
    else if (!strcmp(r, "ge")) return GE;
    else if (!strcmp(r, "lt")) return LT;
    else if (!strcmp(r, "le")) return LE;
    else if (!strcmp(r, "ne")) return NE;
    else if (!strcmp(r, "eq")) return EQ;
    else {
        snprintf(parse_script->sieveerr, ERR_BUF_SIZE,
                 "flag '%s': not a valid relational operation", r);
        yyerror(parse_script, parse_script->sieveerr);
        return -1;
    }
}

static int verify_zone(sieve_script_t *parse_script, char *tz)
{
    int valid = 0;
    unsigned hours;
    unsigned minutes;
    char sign;

    if (sscanf(tz, "%c%02u%02u", &sign, &hours, &minutes) != 3) {
        valid |= -1;
    }

    // test sign
    switch (sign) {
    case '+':
    case '-':
        break;

    default:
        valid |= -1;
        break;
    }

    // test minutes
    if (minutes > 59) {
            valid |= -1;
    }

    if (valid != 0) {
        snprintf(parse_script->sieveerr, ERR_BUF_SIZE,
                 "flag '%s': not a valid timezone offset", tz);
        yyerror(parse_script, parse_script->sieveerr);
    }

    return valid;
}

static int verify_date_part(sieve_script_t *parse_script, char *dp)
{
    lcase(dp);
    if (!strcmp(dp, "year")) return YEAR;
    else if (!strcmp(dp, "month")) return MONTH;
    else if (!strcmp(dp, "day")) return DAY;
    else if (!strcmp(dp, "date")) return DATE;
    else if (!strcmp(dp, "julian")) return JULIAN;
    else if (!strcmp(dp, "hour")) return HOUR;
    else if (!strcmp(dp, "minute")) return MINUTE;
    else if (!strcmp(dp, "second")) return SECOND;
    else if (!strcmp(dp, "time")) return TIME;
    else if (!strcmp(dp, "iso8601")) return ISO8601;
    else if (!strcmp(dp, "std11")) return STD11;
    else if (!strcmp(dp, "zone")) return ZONE;
    else if (!strcmp(dp, "weekday")) return WEEKDAY;
    else {
        snprintf(parse_script->sieveerr, ERR_BUF_SIZE,
                 "'%s': not a valid date-part", dp);
        yyerror(parse_script, parse_script->sieveerr);
    }

    return -1;
}

#ifdef ENABLE_REGEX
static int verify_regex(sieve_script_t *parse_script, char *s, int cflags)
{
    int ret;
    regex_t *reg = (regex_t *) xmalloc(sizeof(regex_t));

    if ((ret = regcomp(reg, s, cflags)) != 0) {
        (void) regerror(ret, reg, parse_script->sieveerr, ERR_BUF_SIZE);
        yyerror(parse_script, parse_script->sieveerr);
        free(reg);
        return 0;
    }
    free(reg);
    return 1;
}

static int verify_regexs(sieve_script_t *parse_script,
                         const strarray_t *sa, char *comp)
{
    int i;
    int cflags = REG_EXTENDED | REG_NOSUB;

#ifdef HAVE_PCREPOSIX_H
    /* support UTF8 comparisons */
    cflags |= REG_UTF8;
#endif

    if (!strcmp(comp, "i;ascii-casemap")) {
        cflags |= REG_ICASE;
    }

    for (i = 0 ; i < sa->count ; i++) {
        if ((verify_regex(parse_script, sa->data[i], cflags)) == 0)
            return 0;
    }
    return 1;
}
#else

static int verify_regexs(sieve_script_t *parse_script __attribute__((unused)),
                         const strarray_t *sa __attribute__((unused)),
                         char *comp __attribute__((unused)))
{
    return 0;
}
#endif /* ENABLE_REGEX */

static int verify_patternlist(sieve_script_t *parse_script,
                              strarray_t *sa, struct comptags *c,
                              int (*verify)(sieve_script_t*, char *))
{
    if (verify && !verify_stringlist(parse_script, sa, verify)) return 0;

    return (c->match == REGEX) ?
        verify_regexs(parse_script, sa, c->comparator) : 1;
}

/*
 * Valid UTF-8 check (from RFC 2640 Annex B.1)
 *
 * The following routine checks if a byte sequence is valid UTF-8. This
 * is done by checking for the proper tagging of the first and following
 * bytes to make sure they conform to the UTF-8 format. It then checks
 * to assure that the data part of the UTF-8 sequence conforms to the
 * proper range allowed by the encoding. Note: This routine will not
 * detect characters that have not been assigned and therefore do not
 * exist.
 */
static int verify_utf8(sieve_script_t *parse_script, char *s)
{
    const char *buf = s;
    const char *endbuf = s + strlen(s);
    unsigned char byte2mask = 0x00, c;
    int trailing = 0;  /* trailing (continuation) bytes to follow */

    while (buf != endbuf) {
        c = *buf++;
        if (trailing) {
            if ((c & 0xC0) == 0x80) {           /* Does trailing byte
                                                   follow UTF-8 format? */
                if (byte2mask) {                /* Need to check 2nd byte
                                                   for proper range? */
                    if (c & byte2mask)          /* Are appropriate bits set? */
                        byte2mask = 0x00;
                    else
                        break;
                }
                trailing--;
            }
            else
                break;
        }
        else {
            if ((c & 0x80) == 0x00)             /* valid 1 byte UTF-8 */
                continue;
            else if ((c & 0xE0) == 0xC0)        /* valid 2 byte UTF-8 */
                if (c & 0x1E) {                 /* Is UTF-8 byte
                                                   in proper range? */
                    trailing = 1;
                }
                else
                    break;
            else if ((c & 0xF0) == 0xE0) {      /* valid 3 byte UTF-8 */
                if (!(c & 0x0F)) {              /* Is UTF-8 byte
                                                   in proper range? */
                    byte2mask = 0x20;           /* If not, set mask
                                                   to check next byte */
                }
                trailing = 2;
            }
            else if ((c & 0xF8) == 0xF0) {      /* valid 4 byte UTF-8 */
                if (!(c & 0x07)) {              /* Is UTF-8 byte
                                                   in proper range? */
                    byte2mask = 0x30;           /* If not, set mask
                                                   to check next byte */
                }
                trailing = 3;
            }
            else if ((c & 0xFC) == 0xF8) {      /* valid 5 byte UTF-8 */
                if (!(c & 0x03)) {              /* Is UTF-8 byte
                                                   in proper range? */
                    byte2mask = 0x38;           /* If not, set mask
                                                   to check next byte */
                }
                trailing = 4;
            }
            else if ((c & 0xFE) == 0xFC) {      /* valid 6 byte UTF-8 */
                if (!(c & 0x01)) {              /* Is UTF-8 byte
                                                   in proper range? */
                    byte2mask = 0x3C;           /* If not, set mask
                                                   to check next byte */
                }
                trailing = 5;
            }
            else
                break;
        }
    }

    if ((buf != endbuf) || trailing) {
        snprintf(parse_script->sieveerr, ERR_BUF_SIZE,
                 "string '%s': not valid utf8", s);
        yyerror(parse_script, parse_script->sieveerr);
        return 0;
    }

    return 1;
}
