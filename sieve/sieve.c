/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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
#define YYBISON_VERSION "3.3.2"

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


/* First part of user prologue.  */
#line 1 "sieve/sieve.y" /* yacc.c:337  */

/* sieve.y -- sieve parser
 * Larry Greenfield
 * Ken Murchison
 *
 * Copyright (c) 1994-2017 Carnegie Mellon University.  All rights reserved.
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

/*
 * Yacc definitions
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "xmalloc.h"
#include "sieve/bytecode.h"
#include "sieve/comparator.h"
#include "sieve/interp.h"
#include "sieve/script.h"
#include "sieve/tree.h"
#include "sieve/flags.h"
#include "sieve/grammar.h"
#include "sieve/sieve_err.h"

#include "util.h"
#include "imparse.h"
#include "libconfig.h"
#include "times.h"
#include "tok.h"

#define ERR_BUF_SIZE 1024

int encoded_char = 0;    /* used to send encoded-character feedback to lexer */
static comp_t *ctags;    /* used for accessing comp_t* in a test/command union */
static int *copy;        /* used for accessing copy flag in a command union */
static int *create;      /* used for accessing create flag in a command union */
static strarray_t **flags; /* used for accessing imap flags in a command union */
static char **specialuse; /* used for accessing special-use flag in a command */
static char **mailboxid; /* used for accessing mailboxid in a command */
static char **fccfolder; /* used for accessing fcc.folder in a command */
static unsigned bctype;  /* used to set the bytecode command type in mtags */

extern int addrparse(sieve_script_t*);
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE addr_scan_string(const char*);
extern void addr_delete_buffer(YY_BUFFER_STATE);

extern int sievelineno;

void sieveerror_c(sieve_script_t*, int code, ...);

static int check_reqs(sieve_script_t*, strarray_t *sl);
static int chk_match_vars(sieve_script_t*, char *s);

static unsigned bc_precompile(cmdarg_t args[], const char *fmt, ...);

/* construct/canonicalize action commands */
static commandlist_t *build_keep(sieve_script_t*, commandlist_t *c);
static commandlist_t *build_fileinto(sieve_script_t*,
                                     commandlist_t *c, char *folder);
static commandlist_t *build_redirect(sieve_script_t*,
                                     commandlist_t *c, char *addr);
static commandlist_t *build_rej_err(sieve_script_t*, int t, char *message);
static commandlist_t *build_vacation(sieve_script_t*, commandlist_t *t, char *s);
static commandlist_t *build_flag(sieve_script_t*,
                                 commandlist_t *c, strarray_t *flags);
static commandlist_t *build_notify(sieve_script_t*, int t,
                                   commandlist_t *c, char *method);
static commandlist_t *build_denotify(sieve_script_t*, commandlist_t *c);
static commandlist_t *build_include(sieve_script_t*, commandlist_t *c, char*);
static commandlist_t *build_set(sieve_script_t*, commandlist_t *c,
                                char *variable, char *value);
static commandlist_t *build_addheader(sieve_script_t*, commandlist_t *c,
                                      char *name, char *value);
static commandlist_t *build_deleteheader(sieve_script_t*, commandlist_t *c,
                                         char *name, strarray_t *values);
static commandlist_t *build_log(sieve_script_t*, char *text);
static commandlist_t *build_snooze(sieve_script_t *sscript,
                                   commandlist_t *c, arrayu64_t *times);

/* construct/canonicalize test commands */
static test_t *build_anyof(sieve_script_t*, testlist_t *tl);
static test_t *build_allof(sieve_script_t*, testlist_t *tl);
static test_t *build_not(sieve_script_t*, test_t *t);
static test_t *build_address(sieve_script_t*, test_t *t,
                             strarray_t *sl, strarray_t *pl);
static test_t *build_envelope(sieve_script_t*, test_t *t,
                              strarray_t *sl, strarray_t *pl);
static test_t *build_header(sieve_script_t*, test_t *t,
                            strarray_t *sl, strarray_t *pl);
static test_t *build_body(sieve_script_t*, test_t *t, strarray_t *pl);
static test_t *build_stringt(sieve_script_t*, test_t *t,
                             strarray_t *sl, strarray_t *pl);
static test_t *build_hasflag(sieve_script_t*, test_t *t,
                             strarray_t *sl, strarray_t *pl);
static test_t *build_date(sieve_script_t*, test_t *t,
                          char *hn, char *part, strarray_t *kl);
static test_t *build_ihave(sieve_script_t*, strarray_t *sa);
static test_t *build_mbox_meta(sieve_script_t*, test_t *t, char *extname,
                               char *keyname, strarray_t *keylist);
static test_t *build_duplicate(sieve_script_t*, test_t *t);
static test_t *build_jmapquery(sieve_script_t*, test_t *t, char *json);

static int verify_weekday(sieve_script_t *sscript, char *day);
static int verify_time(sieve_script_t *sscript, char *time);

void yyerror(sieve_script_t*, const char *msg);
extern int yylex(void*, sieve_script_t*);
extern void sieverestart(FILE *f);

#define supported(capa) (sscript->support & capa)

#define _verify_flaglist(flags) \
  (supported(SIEVE_CAPA_VARIABLES) || verify_flaglist(flags))

#define YYERROR_VERBOSE /* I want better error messages! */

/* byacc default is 500, bison default is 10000 - go with the
   larger to support big sieve scripts (see Bug #3461) */
#define YYSTACKSIZE 10000

#line 240 "sieve/sieve.c" /* yacc.c:337  */
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
    REQUIRE = 263,
    STOP = 264,
    DISCARD = 265,
    KEEP = 266,
    FILEINTO = 267,
    REDIRECT = 268,
    ANYOF = 269,
    ALLOF = 270,
    EXISTS = 271,
    NOT = 272,
    SFALSE = 273,
    STRUE = 274,
    SIZE = 275,
    HEADERT = 276,
    ADDRESS = 277,
    ENVELOPE = 278,
    COMPARATOR = 279,
    OVER = 280,
    UNDER = 281,
    ALL = 282,
    LOCALPART = 283,
    DOMAIN = 284,
    IS = 285,
    CONTAINS = 286,
    MATCHES = 287,
    OCTET = 288,
    ASCIICASEMAP = 289,
    ASCIINUMERIC = 290,
    REGEX = 291,
    QUOTEREGEX = 292,
    COPY = 293,
    BODY = 294,
    RAW = 295,
    TEXT = 296,
    CONTENT = 297,
    ENVIRONMENT = 298,
    STRINGT = 299,
    SET = 300,
    LOWER = 301,
    UPPER = 302,
    LOWERFIRST = 303,
    UPPERFIRST = 304,
    QUOTEWILDCARD = 305,
    LENGTH = 306,
    VACATION = 307,
    DAYS = 308,
    SUBJECT = 309,
    FROM = 310,
    ADDRESSES = 311,
    MIME = 312,
    HANDLE = 313,
    SECONDS = 314,
    COUNT = 315,
    VALUE = 316,
    GT = 317,
    GE = 318,
    LT = 319,
    LE = 320,
    EQ = 321,
    NE = 322,
    FLAGS = 323,
    HASFLAG = 324,
    SETFLAG = 325,
    ADDFLAG = 326,
    REMOVEFLAG = 327,
    MARK = 328,
    UNMARK = 329,
    USER = 330,
    DETAIL = 331,
    DATE = 332,
    CURRENTDATE = 333,
    ORIGINALZONE = 334,
    ZONE = 335,
    INDEX = 336,
    LAST = 337,
    ADDHEADER = 338,
    DELETEHEADER = 339,
    REJCT = 340,
    EREJECT = 341,
    METHOD = 342,
    OPTIONS = 343,
    MESSAGE = 344,
    IMPORTANCE = 345,
    VALIDNOTIFYMETHOD = 346,
    NOTIFYMETHODCAPABILITY = 347,
    NOTIFY = 348,
    ENOTIFY = 349,
    ENCODEURL = 350,
    DENOTIFY = 351,
    ID = 352,
    ANY = 353,
    LOW = 354,
    NORMAL = 355,
    HIGH = 356,
    IHAVE = 357,
    ERROR = 358,
    MAILBOXEXISTS = 359,
    CREATE = 360,
    METADATA = 361,
    METADATAEXISTS = 362,
    SERVERMETADATA = 363,
    SERVERMETADATAEXISTS = 364,
    BYTIMEREL = 365,
    BYTIMEABS = 366,
    BYMODE = 367,
    BYTRACE = 368,
    DSNNOTIFY = 369,
    DSNRET = 370,
    VALIDEXTLIST = 371,
    LIST = 372,
    INCLUDE = 373,
    OPTIONAL = 374,
    ONCE = 375,
    RETURN = 376,
    PERSONAL = 377,
    GLOBAL = 378,
    DUPLICATE = 379,
    HEADER = 380,
    UNIQUEID = 381,
    SPECIALUSEEXISTS = 382,
    SPECIALUSE = 383,
    FCC = 384,
    MAILBOXID = 385,
    MAILBOXIDEXISTS = 386,
    LOG = 387,
    JMAPQUERY = 388,
    SNOOZE = 389,
    MAILBOX = 390,
    ADDFLAGS = 391,
    REMOVEFLAGS = 392,
    WEEKDAYS = 393,
    TZID = 394
  };
#endif
/* Tokens.  */
#define NUMBER 258
#define STRING 259
#define IF 260
#define ELSIF 261
#define ELSE 262
#define REQUIRE 263
#define STOP 264
#define DISCARD 265
#define KEEP 266
#define FILEINTO 267
#define REDIRECT 268
#define ANYOF 269
#define ALLOF 270
#define EXISTS 271
#define NOT 272
#define SFALSE 273
#define STRUE 274
#define SIZE 275
#define HEADERT 276
#define ADDRESS 277
#define ENVELOPE 278
#define COMPARATOR 279
#define OVER 280
#define UNDER 281
#define ALL 282
#define LOCALPART 283
#define DOMAIN 284
#define IS 285
#define CONTAINS 286
#define MATCHES 287
#define OCTET 288
#define ASCIICASEMAP 289
#define ASCIINUMERIC 290
#define REGEX 291
#define QUOTEREGEX 292
#define COPY 293
#define BODY 294
#define RAW 295
#define TEXT 296
#define CONTENT 297
#define ENVIRONMENT 298
#define STRINGT 299
#define SET 300
#define LOWER 301
#define UPPER 302
#define LOWERFIRST 303
#define UPPERFIRST 304
#define QUOTEWILDCARD 305
#define LENGTH 306
#define VACATION 307
#define DAYS 308
#define SUBJECT 309
#define FROM 310
#define ADDRESSES 311
#define MIME 312
#define HANDLE 313
#define SECONDS 314
#define COUNT 315
#define VALUE 316
#define GT 317
#define GE 318
#define LT 319
#define LE 320
#define EQ 321
#define NE 322
#define FLAGS 323
#define HASFLAG 324
#define SETFLAG 325
#define ADDFLAG 326
#define REMOVEFLAG 327
#define MARK 328
#define UNMARK 329
#define USER 330
#define DETAIL 331
#define DATE 332
#define CURRENTDATE 333
#define ORIGINALZONE 334
#define ZONE 335
#define INDEX 336
#define LAST 337
#define ADDHEADER 338
#define DELETEHEADER 339
#define REJCT 340
#define EREJECT 341
#define METHOD 342
#define OPTIONS 343
#define MESSAGE 344
#define IMPORTANCE 345
#define VALIDNOTIFYMETHOD 346
#define NOTIFYMETHODCAPABILITY 347
#define NOTIFY 348
#define ENOTIFY 349
#define ENCODEURL 350
#define DENOTIFY 351
#define ID 352
#define ANY 353
#define LOW 354
#define NORMAL 355
#define HIGH 356
#define IHAVE 357
#define ERROR 358
#define MAILBOXEXISTS 359
#define CREATE 360
#define METADATA 361
#define METADATAEXISTS 362
#define SERVERMETADATA 363
#define SERVERMETADATAEXISTS 364
#define BYTIMEREL 365
#define BYTIMEABS 366
#define BYMODE 367
#define BYTRACE 368
#define DSNNOTIFY 369
#define DSNRET 370
#define VALIDEXTLIST 371
#define LIST 372
#define INCLUDE 373
#define OPTIONAL 374
#define ONCE 375
#define RETURN 376
#define PERSONAL 377
#define GLOBAL 378
#define DUPLICATE 379
#define HEADER 380
#define UNIQUEID 381
#define SPECIALUSEEXISTS 382
#define SPECIALUSE 383
#define FCC 384
#define MAILBOXID 385
#define MAILBOXIDEXISTS 386
#define LOG 387
#define JMAPQUERY 388
#define SNOOZE 389
#define MAILBOX 390
#define ADDFLAGS 391
#define REMOVEFLAGS 392
#define WEEKDAYS 393
#define TZID 394

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 178 "sieve/sieve.y" /* yacc.c:352  */

    int nval;
    char *sval;
    arrayu64_t *nl;
    strarray_t *sl;
    comp_t *ctag;
    test_t *test;
    testlist_t *testl;
    commandlist_t *cl;

#line 572 "sieve/sieve.c" /* yacc.c:352  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int sieveparse (sieve_script_t *sscript);

#endif /* !YY_SIEVE_SIEVE_SIEVE_H_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   717

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  148
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  86
/* YYNRULES -- Number of rules.  */
#define YYNRULES  280
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  400

#define YYUNDEFTOK  2
#define YYMAXUTOK   394

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     146,   147,     2,     2,   143,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   140,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   141,     2,   142,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   144,     2,   145,     2,     2,     2,     2,
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
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   362,   362,   363,   367,   368,   373,   374,   378,   379,
     380,   392,   393,   397,   398,   402,   403,   407,   414,   421,
     425,   426,   427,   428,   430,   434,   445,   446,   447,   451,
     452,   457,   458,   467,   476,   489,   490,   497,   498,   499,
     500,   501,   503,   506,   510,   515,   518,   522,   523,   526,
     529,   530,   531,   536,   540,   545,   565,   573,   574,   575,
     576,   577,   582,   599,   616,   634,   654,   658,   659,   671,
     678,   688,   702,   715,   727,   743,   755,   771,   772,   781,
     790,   799,   808,   821,   822,   825,   826,   829,   830,   842,
     853,   858,   866,   875,   889,   899,   910,   921,   930,   940,
     944,   960,   961,   962,   963,   968,   969,   970,   975,   976,
     995,   996,  1001,  1002,  1015,  1019,  1020,  1021,  1022,  1027,
    1028,  1039,  1049,  1060,  1070,  1073,  1083,  1093,  1104,  1115,
    1130,  1131,  1132,  1137,  1141,  1151,  1160,  1166,  1176,  1177,
    1178,  1180,  1196,  1212,  1222,  1235,  1236,  1240,  1241,  1245,
    1249,  1250,  1254,  1255,  1259,  1266,  1273,  1277,  1278,  1282,
    1283,  1284,  1285,  1286,  1287,  1293,  1302,  1305,  1307,  1310,
    1312,  1316,  1323,  1325,  1328,  1331,  1334,  1341,  1345,  1347,
    1354,  1354,  1358,  1365,  1365,  1369,  1377,  1384,  1386,  1393,
    1400,  1407,  1412,  1417,  1418,  1423,  1427,  1428,  1429,  1430,
    1435,  1445,  1467,  1468,  1469,  1470,  1483,  1484,  1489,  1490,
    1491,  1492,  1493,  1494,  1499,  1519,  1534,  1535,  1536,  1550,
    1561,  1576,  1595,  1599,  1600,  1601,  1602,  1603,  1608,  1623,
    1624,  1625,  1626,  1637,  1638,  1643,  1647,  1648,  1649,  1650,
    1655,  1659,  1660,  1665,  1669,  1679,  1692,  1693,  1698,  1699,
    1704,  1708,  1709,  1710,  1715,  1719,  1720,  1725,  1729,  1730,
    1739,  1740,  1741,  1746,  1763,  1767,  1768,  1769,  1774,  1779,
    1780,  1785,  1790,  1791,  1796,  1797,  1809,  1819,  1828,  1841,
    1842
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NUMBER", "STRING", "IF", "ELSIF",
  "ELSE", "REQUIRE", "STOP", "DISCARD", "KEEP", "FILEINTO", "REDIRECT",
  "ANYOF", "ALLOF", "EXISTS", "NOT", "SFALSE", "STRUE", "SIZE", "HEADERT",
  "ADDRESS", "ENVELOPE", "COMPARATOR", "OVER", "UNDER", "ALL", "LOCALPART",
  "DOMAIN", "IS", "CONTAINS", "MATCHES", "OCTET", "ASCIICASEMAP",
  "ASCIINUMERIC", "REGEX", "QUOTEREGEX", "COPY", "BODY", "RAW", "TEXT",
  "CONTENT", "ENVIRONMENT", "STRINGT", "SET", "LOWER", "UPPER",
  "LOWERFIRST", "UPPERFIRST", "QUOTEWILDCARD", "LENGTH", "VACATION",
  "DAYS", "SUBJECT", "FROM", "ADDRESSES", "MIME", "HANDLE", "SECONDS",
  "COUNT", "VALUE", "GT", "GE", "LT", "LE", "EQ", "NE", "FLAGS", "HASFLAG",
  "SETFLAG", "ADDFLAG", "REMOVEFLAG", "MARK", "UNMARK", "USER", "DETAIL",
  "DATE", "CURRENTDATE", "ORIGINALZONE", "ZONE", "INDEX", "LAST",
  "ADDHEADER", "DELETEHEADER", "REJCT", "EREJECT", "METHOD", "OPTIONS",
  "MESSAGE", "IMPORTANCE", "VALIDNOTIFYMETHOD", "NOTIFYMETHODCAPABILITY",
  "NOTIFY", "ENOTIFY", "ENCODEURL", "DENOTIFY", "ID", "ANY", "LOW",
  "NORMAL", "HIGH", "IHAVE", "ERROR", "MAILBOXEXISTS", "CREATE",
  "METADATA", "METADATAEXISTS", "SERVERMETADATA", "SERVERMETADATAEXISTS",
  "BYTIMEREL", "BYTIMEABS", "BYMODE", "BYTRACE", "DSNNOTIFY", "DSNRET",
  "VALIDEXTLIST", "LIST", "INCLUDE", "OPTIONAL", "ONCE", "RETURN",
  "PERSONAL", "GLOBAL", "DUPLICATE", "HEADER", "UNIQUEID",
  "SPECIALUSEEXISTS", "SPECIALUSE", "FCC", "MAILBOXID", "MAILBOXIDEXISTS",
  "LOG", "JMAPQUERY", "SNOOZE", "MAILBOX", "ADDFLAGS", "REMOVEFLAGS",
  "WEEKDAYS", "TZID", "';'", "'['", "']'", "','", "'{'", "'}'", "'('",
  "')'", "$accept", "start", "reqs", "commands", "command",
  "optstringlist", "stringlist", "strings", "string1", "string", "require",
  "control", "thenelse", "elsif", "block", "itags", "location", "action",
  "ktags", "flags", "ftags", "copy", "create", "specialuse", "mailboxid",
  "rtags", "delbytags", "dsntags", "stags", "mod40", "mod30", "mod20",
  "mod15", "mod10", "vtags", "fcctags", "flagaction", "flagtags",
  "flagmark", "ahtags", "dhtags", "reject", "ntags", "priority", "dtags",
  "sntags", "weekdaylist", "weekdays", "weekday", "timelist", "times",
  "time1", "time", "testlist", "tests", "test", "$@1", "$@2", "sizetag",
  "htags", "matchtype", "matchtag", "relmatch", "relation", "listmatch",
  "comparator", "collation", "indexext", "index", "atags", "addrpart",
  "addrparttag", "subaddress", "etags", "envtags", "btags", "transform",
  "strtags", "hftags", "dttags", "zone", "cdtags", "methtags", "mtags",
  "duptags", "idtype", YY_NULLPTR
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
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
      59,    91,    93,    44,   123,   125,    40,    41
};
# endif

#define YYPACT_NINF -350

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-350)))

#define YYTABLE_NINF -18

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,     2,    16,   472,     6,  -350,    14,  -117,  -350,  -350,
    -350,  -102,   566,   -95,  -350,  -350,  -350,  -350,  -350,  -350,
    -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,
    -350,    14,  -350,   -91,    14,  -350,  -350,   277,  -350,   -81,
    -350,  -350,    14,  -350,  -122,  -350,  -350,  -350,  -350,  -103,
    -103,     2,   566,  -350,  -350,    42,  -350,  -350,  -350,  -350,
    -350,  -350,  -350,  -350,  -350,     2,  -350,     2,     2,  -350,
      14,  -350,     2,     2,  -350,     2,     2,    14,  -350,   -55,
    -350,    -3,    89,   279,   247,   558,     5,   567,   399,   478,
     -59,    60,  -350,  -350,   122,  -350,  -350,     2,  -350,  -350,
      14,   566,  -350,  -350,  -350,  -350,  -350,  -350,    95,    70,
     132,   296,   400,   403,    79,   307,   635,   489,  -350,   403,
    -350,  -350,  -350,     2,  -350,  -350,  -350,   -34,  -350,     2,
    -350,  -350,   373,    71,     2,  -350,  -350,  -350,    14,    14,
    -350,  -350,  -350,  -350,  -350,  -350,   109,    14,    14,  -350,
      14,    14,  -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,
    -350,  -350,  -350,  -350,  -350,    14,  -350,  -350,  -350,  -350,
    -350,   110,    14,    14,     2,  -350,    14,   111,    14,  -350,
    -350,  -350,  -350,  -350,  -350,  -350,    14,     7,  -350,  -350,
    -350,  -350,  -350,  -350,   115,  -350,  -350,     2,  -350,  -350,
     468,  -350,  -350,  -350,    14,    14,     2,    14,   -38,    14,
    -350,  -350,  -350,  -350,  -350,  -350,  -350,    14,  -350,  -350,
    -350,  -350,  -350,   -18,  -350,  -350,    14,     2,     2,     3,
      14,   119,  -350,  -350,  -350,  -350,  -350,  -350,  -350,   -16,
    -350,   -22,   -15,  -350,     2,  -350,  -350,  -350,  -350,  -350,
    -350,  -350,  -350,  -350,  -350,     2,  -350,  -350,  -350,  -350,
    -350,  -350,  -350,     2,  -350,  -350,  -350,  -350,  -350,  -350,
       2,  -350,  -350,  -350,  -350,     2,  -350,  -350,     2,  -350,
    -350,  -350,     2,  -350,  -350,  -350,    14,    14,  -350,  -350,
    -350,  -350,     2,  -350,  -350,  -350,    14,  -350,  -350,   403,
    -350,   403,    14,   126,  -350,  -350,  -350,    14,  -350,  -350,
     -13,   566,   -55,  -350,  -350,  -350,  -350,  -350,  -350,  -350,
    -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,
    -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,
    -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,
    -350,  -350,  -350,  -350,  -350,  -350,  -350,   129,  -350,  -350,
    -350,   -63,  -350,  -350,   566,  -350,  -350,  -350,  -350,  -350,
    -350,  -350,  -350,     2,  -350,     2,    14,  -350,  -350,     2,
    -350,  -350,  -350,  -350,  -350,  -350,   -46,  -350,  -350,   119,
    -350,  -350,  -350,     2,  -350,  -350,   129,  -350,  -350,  -350
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     0,     0,     4,    18,     0,     0,    13,    17,
       1,     0,     0,     0,    40,    53,    56,    66,    77,    91,
     105,   106,   107,   110,   111,   112,   114,   119,   120,   121,
     133,     0,    31,     0,     0,   136,     3,     0,     8,     0,
     108,    44,     0,     5,     0,    15,    19,    10,   192,     0,
       0,     0,     0,   162,   163,     0,   195,   222,   235,   243,
     240,   250,   254,   257,   264,     0,   268,     0,     0,   180,
       0,   183,     0,     0,   274,     0,     0,     0,    20,     0,
      21,    37,     0,     0,     0,     0,     0,     0,    49,    50,
       0,     0,    24,    51,     0,     7,     9,     0,    47,    14,
       0,     0,   159,   160,   164,   161,   193,   194,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   176,     0,
     178,   179,   271,     0,   271,   185,   186,   187,   188,    17,
     190,   191,     0,    26,     0,    54,    62,    63,     0,     0,
      38,    58,    57,    59,    60,    61,     0,     0,     0,    74,
       0,     0,    68,    39,    67,    69,    70,    88,    83,    84,
      85,    86,    87,    90,    89,     0,    78,    79,    80,    81,
      82,     0,     0,     0,     0,    97,     0,     0,     0,    42,
     102,   101,   103,   104,    99,   113,     0,     0,   202,   203,
     204,   205,   206,   207,     0,   221,   214,    11,   115,   200,
       0,   116,   117,   118,     0,     0,     0,     0,     0,     0,
     130,   131,   132,    48,   124,   127,   134,     0,    22,    34,
      33,    35,    36,     0,    32,   155,     0,     0,     0,     0,
       0,     0,   138,   139,   140,    52,   150,   154,    43,   109,
      16,     0,   157,   165,     0,   196,   197,   198,   199,   219,
     229,   230,   231,   233,   234,     0,   224,   225,   226,   227,
     223,   228,   232,     0,   237,   238,   239,   236,   248,   249,
       0,   169,   246,   247,   244,     0,   241,   242,     0,   251,
     252,   253,   173,   255,   256,   259,     0,     0,   260,   261,
     262,   258,     0,   266,   267,   265,     0,   269,   270,     0,
     182,     0,     0,     0,   278,   279,   280,     0,   189,    30,
       0,     0,     0,    25,    55,    64,    65,    71,    72,    73,
      75,    76,    41,    92,    94,    95,    96,    98,    93,   100,
      45,   216,   217,   218,   215,   220,    46,    12,   210,   211,
     212,   213,   208,   209,   201,   122,   126,   129,   128,   123,
     125,   135,    23,   137,   141,   142,   149,     0,   143,   145,
     144,     0,   152,   156,     0,   166,   167,   168,   245,   170,
     171,   172,   263,     0,   175,     0,     0,   272,   273,     0,
     276,   277,   275,    29,    27,    28,     0,   147,   151,     0,
     158,   174,   177,     0,   184,   146,     0,   153,   181,   148
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -350,  -350,   133,   -33,  -350,  -350,   -39,  -350,   140,   -31,
    -350,  -350,  -173,  -350,  -164,  -350,  -350,  -350,  -350,    23,
    -350,    66,   -77,   -72,   -67,  -350,  -350,  -350,  -350,  -350,
    -350,  -350,  -350,  -350,  -350,    62,  -350,  -350,  -350,  -350,
    -350,  -350,  -350,   -87,  -350,  -350,  -350,  -350,  -349,  -350,
    -350,   -78,  -235,   116,  -199,   -51,  -350,  -350,  -350,  -350,
     591,  -350,  -350,  -350,   -79,   193,  -350,   -97,    82,  -350,
      59,  -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,  -350,
      54,  -350,  -350,    48,  -350,  -350
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    36,    37,   336,     7,    44,     8,     9,
       4,    38,    78,   313,   133,    91,   224,    39,    81,   180,
      82,   142,   181,   182,   183,    83,   155,   156,    84,   166,
     167,   168,   169,   170,    85,   184,    40,    97,    41,    86,
      87,    42,    88,   215,    89,    94,   358,   386,   359,   235,
     361,   236,   237,   102,   241,    79,   122,   124,   108,   109,
     377,   199,   200,   344,   201,   378,   334,   248,   249,   110,
     260,   261,   262,   111,   113,   112,   274,   114,   115,   116,
     291,   117,   119,   299,   127,   307
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      90,   105,   216,    93,    95,   143,     5,   356,   387,     5,
     144,    98,   104,   259,     1,   145,    10,   232,     5,   290,
      99,   100,   233,    46,   302,   303,   118,   234,   120,   121,
     246,   257,   265,   125,   126,   280,   128,   130,    47,   123,
     331,   332,   333,   101,   129,    80,   131,   399,   304,    92,
     242,   140,   153,   165,   179,   186,   197,   213,   238,    96,
     223,   210,   211,   212,     5,   134,   239,   106,   107,   240,
     244,   255,   263,   271,     5,   278,   282,   311,   312,   388,
     389,   218,   275,     5,   300,   287,   292,   185,   296,   132,
     308,   305,   306,     5,   187,   314,   395,   396,   243,   310,
     188,   189,   190,   187,   135,   141,   191,   315,   316,   188,
     189,   190,   317,   323,   328,   191,   318,   319,   335,   320,
     321,   349,   352,   225,   -17,   363,   225,   136,   364,   381,
     192,   193,   383,   356,   322,   326,     5,    43,   384,   192,
     193,   324,   325,     6,   357,   327,    45,   329,   385,   154,
     214,   194,   195,   362,   397,   330,   187,   134,   337,   250,
     251,   252,   188,   189,   190,   390,   103,   347,   191,   203,
     267,   295,   301,   345,   346,     0,   348,     0,   350,   219,
     220,     0,   221,   222,     0,     0,   351,   196,   354,   355,
       0,     0,   192,   193,   137,   353,   196,     0,     0,   360,
       0,     0,     0,     0,     0,   365,     0,   253,   254,     0,
       0,     6,     0,   194,   195,     0,   366,   138,     0,   139,
       6,     0,     0,     0,   367,     0,     0,   137,     0,     0,
       0,   368,     0,     0,     0,     0,   369,     0,     0,   370,
       0,     0,     0,   371,     0,     0,     0,     0,     0,   196,
     138,     5,   139,   374,     0,   372,   373,   226,   227,   228,
     229,   230,     0,   231,     0,   375,     0,     0,   376,     0,
     379,   380,     0,     6,     0,     0,   382,    -6,    11,     0,
     202,     0,    12,     5,   157,     0,    13,    14,    15,    16,
      17,     0,     0,   158,   159,   160,   161,   162,   163,     0,
       5,     0,   247,   258,   266,   273,   277,   281,   284,   289,
     294,     5,   298,   242,     0,     0,     0,   136,     0,     0,
     187,     0,    18,   250,   251,   252,   188,   189,   190,    19,
       0,   187,   191,     0,   391,     0,   392,   188,   189,   190,
     394,     0,   164,   191,     0,   393,     0,    20,    21,    22,
      23,    24,     0,     0,   398,     0,   192,   193,     0,     0,
      25,    26,    27,    28,     0,     0,     0,   192,   193,     0,
      29,   253,   254,    30,    11,     0,     0,     0,    12,     0,
      31,     0,    13,    14,    15,    16,    17,     0,     0,   146,
     147,   148,   149,   150,   151,    32,   152,     0,    33,     0,
       0,     0,     0,     5,     5,     0,     0,     5,     0,    34,
       0,    35,     0,   196,     0,     0,     0,     0,    18,     0,
       0,     0,    -6,     0,   187,    19,     0,   187,     0,     0,
     188,   189,   190,   188,   189,   190,   191,     6,     0,   191,
     268,   269,   270,    20,    21,    22,    23,    24,     6,     0,
       0,     0,     0,     0,   204,     0,    25,    26,    27,    28,
     192,   193,     0,   192,   193,     0,    29,   134,     0,    30,
       0,     0,    -2,    11,     0,     0,    31,    12,     0,     0,
       0,    13,    14,    15,    16,    17,   205,   206,   207,   208,
       0,    32,     0,     5,    33,     0,   209,     0,   210,   211,
     212,     0,     0,     0,   137,    34,     0,    35,   188,   189,
     190,     0,     0,   187,   191,     0,     0,    18,   309,   188,
     189,   190,     0,     0,    19,   191,     0,   138,   178,   139,
     338,   339,   340,   341,   342,   343,     0,     0,   192,   193,
       0,     6,    20,    21,    22,    23,    24,     0,     0,   192,
     193,     0,     0,     0,     0,    25,    26,    27,    28,     0,
       0,     0,     5,     0,     0,    29,     0,    48,    30,   286,
       0,     5,     0,     0,     0,    31,     0,   210,   211,   212,
      49,    50,    51,    52,    53,    54,    55,    56,    57,    58,
      32,   187,     0,    33,     0,     0,     0,   188,   189,   190,
       0,     0,     0,   191,    34,    59,    35,     0,     0,    60,
      61,   171,   172,   173,   174,   175,   176,   177,     0,     0,
       0,     0,     0,     0,     0,     0,   134,   192,   193,     0,
       0,     0,     0,     0,     0,    62,     0,     0,     0,     5,
       0,     0,     0,    63,    64,     0,     0,     0,   194,   195,
       0,     0,     0,     0,     0,     0,     0,    65,    66,   187,
       0,     0,     0,   137,     0,   188,   189,   190,    67,     0,
      68,   191,    69,    70,    71,    72,     0,     0,   198,     0,
     217,     0,    73,     0,   196,     0,   138,   178,   139,     0,
      74,     0,     0,    75,     0,   192,   193,    76,     0,    77,
     245,   256,   264,   272,   276,   279,   283,   288,   293,     0,
     297,     0,     0,     0,   285,   286,   194,   195
};

static const yytype_int16 yycheck[] =
{
      31,    52,    89,    34,    37,    82,     4,     4,   357,     4,
      82,    42,    51,   110,     8,    82,     0,    94,     4,   116,
     142,   143,    94,   140,    58,    59,    65,    94,    67,    68,
     109,   110,   111,    72,    73,   114,    75,    76,   140,    70,
      33,    34,    35,   146,    75,   140,    77,   396,    82,   140,
     101,    82,    83,    84,    85,    86,    87,    88,    97,   140,
      91,    99,   100,   101,     4,    68,    97,    25,    26,   100,
     109,   110,   111,   112,     4,   114,   115,     6,     7,   142,
     143,   140,   113,     4,   123,   116,   117,    82,   119,   144,
     129,   125,   126,     4,    24,   134,   142,   143,     3,   132,
      30,    31,    32,    24,    81,    82,    36,   138,   139,    30,
      31,    32,     3,     3,     3,    36,   147,   148,     3,   150,
     151,   208,   140,     4,   140,   147,     4,    38,   143,     3,
      60,    61,   145,     4,   165,   174,     4,     4,   311,    60,
      61,   172,   173,   141,   141,   176,     6,   178,   312,    83,
      88,    81,    82,   231,   389,   186,    24,    68,   197,    27,
      28,    29,    30,    31,    32,   364,    50,   206,    36,    87,
     111,   117,   124,   204,   205,    -1,   207,    -1,   209,   119,
     120,    -1,   122,   123,    -1,    -1,   217,   117,   227,   228,
      -1,    -1,    60,    61,   105,   226,   117,    -1,    -1,   230,
      -1,    -1,    -1,    -1,    -1,   244,    -1,    75,    76,    -1,
      -1,   141,    -1,    81,    82,    -1,   255,   128,    -1,   130,
     141,    -1,    -1,    -1,   263,    -1,    -1,   105,    -1,    -1,
      -1,   270,    -1,    -1,    -1,    -1,   275,    -1,    -1,   278,
      -1,    -1,    -1,   282,    -1,    -1,    -1,    -1,    -1,   117,
     128,     4,   130,   292,    -1,   286,   287,   135,   136,   137,
     138,   139,    -1,   141,    -1,   296,    -1,    -1,   299,    -1,
     301,   302,    -1,   141,    -1,    -1,   307,     0,     1,    -1,
      87,    -1,     5,     4,    37,    -1,     9,    10,    11,    12,
      13,    -1,    -1,    46,    47,    48,    49,    50,    51,    -1,
       4,    -1,   109,   110,   111,   112,   113,   114,   115,   116,
     117,     4,   119,   364,    -1,    -1,    -1,    38,    -1,    -1,
      24,    -1,    45,    27,    28,    29,    30,    31,    32,    52,
      -1,    24,    36,    -1,   373,    -1,   375,    30,    31,    32,
     379,    -1,    95,    36,    -1,   376,    -1,    70,    71,    72,
      73,    74,    -1,    -1,   393,    -1,    60,    61,    -1,    -1,
      83,    84,    85,    86,    -1,    -1,    -1,    60,    61,    -1,
      93,    75,    76,    96,     1,    -1,    -1,    -1,     5,    -1,
     103,    -1,     9,    10,    11,    12,    13,    -1,    -1,   110,
     111,   112,   113,   114,   115,   118,   117,    -1,   121,    -1,
      -1,    -1,    -1,     4,     4,    -1,    -1,     4,    -1,   132,
      -1,   134,    -1,   117,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    -1,   145,    -1,    24,    52,    -1,    24,    -1,    -1,
      30,    31,    32,    30,    31,    32,    36,   141,    -1,    36,
      40,    41,    42,    70,    71,    72,    73,    74,   141,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    83,    84,    85,    86,
      60,    61,    -1,    60,    61,    -1,    93,    68,    -1,    96,
      -1,    -1,     0,     1,    -1,    -1,   103,     5,    -1,    -1,
      -1,     9,    10,    11,    12,    13,    87,    88,    89,    90,
      -1,   118,    -1,     4,   121,    -1,    97,    -1,    99,   100,
     101,    -1,    -1,    -1,   105,   132,    -1,   134,    30,    31,
      32,    -1,    -1,    24,    36,    -1,    -1,    45,   145,    30,
      31,    32,    -1,    -1,    52,    36,    -1,   128,   129,   130,
      62,    63,    64,    65,    66,    67,    -1,    -1,    60,    61,
      -1,   141,    70,    71,    72,    73,    74,    -1,    -1,    60,
      61,    -1,    -1,    -1,    -1,    83,    84,    85,    86,    -1,
      -1,    -1,     4,    -1,    -1,    93,    -1,     1,    96,    80,
      -1,     4,    -1,    -1,    -1,   103,    -1,    99,   100,   101,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
     118,    24,    -1,   121,    -1,    -1,    -1,    30,    31,    32,
      -1,    -1,    -1,    36,   132,    39,   134,    -1,    -1,    43,
      44,    53,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    60,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,     4,
      -1,    -1,    -1,    77,    78,    -1,    -1,    -1,    81,    82,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    91,    92,    24,
      -1,    -1,    -1,   105,    -1,    30,    31,    32,   102,    -1,
     104,    36,   106,   107,   108,   109,    -1,    -1,    87,    -1,
      89,    -1,   116,    -1,   117,    -1,   128,   129,   130,    -1,
     124,    -1,    -1,   127,    -1,    60,    61,   131,    -1,   133,
     109,   110,   111,   112,   113,   114,   115,   116,   117,    -1,
     119,    -1,    -1,    -1,    79,    80,    81,    82
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,   149,   150,   158,     4,   141,   154,   156,   157,
       0,     1,     5,     9,    10,    11,    12,    13,    45,    52,
      70,    71,    72,    73,    74,    83,    84,    85,    86,    93,
      96,   103,   118,   121,   132,   134,   151,   152,   159,   165,
     184,   186,   189,   150,   155,   156,   140,   140,     1,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    39,
      43,    44,    69,    77,    78,    91,    92,   102,   104,   106,
     107,   108,   109,   116,   124,   127,   131,   133,   160,   203,
     140,   166,   168,   173,   176,   182,   187,   188,   190,   192,
     157,   163,   140,   157,   193,   151,   140,   185,   157,   142,
     143,   146,   201,   201,   154,   203,    25,    26,   206,   207,
     217,   221,   223,   222,   225,   226,   227,   229,   154,   230,
     154,   154,   204,   157,   205,   154,   154,   232,   154,   157,
     154,   157,   144,   162,    68,   167,    38,   105,   128,   130,
     157,   167,   169,   170,   171,   172,   110,   111,   112,   113,
     114,   115,   117,   157,   169,   174,   175,    37,    46,    47,
      48,    49,    50,    51,    95,   157,   177,   178,   179,   180,
     181,    53,    54,    55,    56,    57,    58,    59,   129,   157,
     167,   170,   171,   172,   183,    82,   157,    24,    30,    31,
      32,    36,    60,    61,    81,    82,   117,   157,   208,   209,
     210,   212,   213,   216,    55,    87,    88,    89,    90,    97,
      99,   100,   101,   157,   183,   191,   191,   208,   140,   119,
     120,   122,   123,   157,   164,     4,   135,   136,   137,   138,
     139,   141,   170,   171,   172,   197,   199,   200,   154,   157,
     157,   202,   203,     3,   154,   208,   212,   213,   215,   216,
      27,    28,    29,    75,    76,   154,   208,   212,   213,   215,
     218,   219,   220,   154,   208,   212,   213,   218,    40,    41,
      42,   154,   208,   213,   224,   157,   208,   213,   154,   208,
     212,   213,   154,   208,   213,    79,    80,   157,   208,   213,
     215,   228,   157,   208,   213,   228,   157,   208,   213,   231,
     154,   231,    58,    59,    82,   125,   126,   233,   154,   145,
     151,     6,     7,   161,   154,   157,   157,     3,   157,   157,
     157,   157,   157,     3,   157,   157,   154,   157,     3,   157,
     157,    33,    34,    35,   214,     3,   153,   154,    62,    63,
      64,    65,    66,    67,   211,   157,   157,   154,   157,   191,
     157,   157,   140,   157,   154,   154,     4,   141,   194,   196,
     157,   198,   199,   147,   143,   154,   154,   154,   154,   154,
     154,   154,   157,   157,   154,   157,   157,   208,   213,   157,
     157,     3,   157,   145,   160,   162,   195,   196,   142,   143,
     202,   154,   154,   157,   154,   142,   143,   200,   154,   196
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   148,   149,   149,   150,   150,   151,   151,   152,   152,
     152,   153,   153,   154,   154,   155,   155,   156,   157,   158,
     159,   159,   159,   159,   159,   160,   161,   161,   161,   162,
     162,   163,   163,   163,   163,   164,   164,   165,   165,   165,
     165,   165,   165,   165,   165,   165,   165,   165,   165,   165,
     165,   165,   165,   166,   166,   167,   168,   168,   168,   168,
     168,   168,   169,   170,   171,   172,   173,   173,   173,   173,
     173,   174,   174,   174,   174,   175,   175,   176,   176,   176,
     176,   176,   176,   177,   177,   178,   178,   179,   179,   180,
     181,   182,   182,   182,   182,   182,   182,   182,   182,   182,
     183,   183,   183,   183,   183,   184,   184,   184,   185,   185,
     186,   186,   187,   187,   188,   188,   188,   188,   188,   189,
     189,   190,   190,   190,   190,   190,   190,   190,   190,   190,
     191,   191,   191,   192,   192,   192,   193,   193,   193,   193,
     193,   193,   193,   193,   193,   194,   194,   195,   195,   196,
     197,   197,   198,   198,   199,   200,   201,   202,   202,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   203,   203,   203,   203,   203,   203,   203,
     204,   203,   203,   205,   203,   203,   203,   203,   203,   203,
     203,   203,   203,   206,   206,   207,   207,   207,   207,   207,
     208,   208,   209,   209,   209,   209,   210,   210,   211,   211,
     211,   211,   211,   211,   212,   213,   214,   214,   214,   215,
     216,   216,   217,   217,   217,   217,   217,   217,   218,   219,
     219,   219,   219,   220,   220,   221,   221,   221,   221,   221,
     222,   222,   222,   223,   223,   223,   223,   223,   224,   224,
     225,   225,   225,   225,   226,   226,   226,   227,   227,   227,
     227,   227,   227,   228,   229,   229,   229,   229,   230,   230,
     230,   231,   231,   231,   232,   232,   232,   232,   232,   233,
     233
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     2,     1,     2,
       2,     0,     1,     1,     3,     1,     3,     1,     1,     3,
       2,     2,     3,     4,     2,     3,     0,     2,     2,     3,
       2,     0,     2,     2,     2,     1,     1,     2,     3,     3,
       1,     4,     3,     3,     1,     4,     4,     2,     3,     2,
       2,     2,     3,     0,     2,     2,     0,     2,     2,     2,
       2,     2,     1,     1,     2,     2,     0,     2,     2,     2,
       2,     2,     2,     2,     1,     2,     2,     0,     2,     2,
       2,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     3,     3,     3,     3,     3,     2,     3,     2,
       2,     1,     1,     1,     1,     1,     1,     1,     0,     2,
       1,     1,     0,     2,     0,     2,     2,     2,     2,     1,
       1,     0,     3,     3,     2,     3,     3,     2,     3,     3,
       1,     1,     1,     0,     2,     3,     0,     3,     2,     2,
       2,     3,     3,     3,     3,     1,     3,     1,     3,     1,
       1,     3,     1,     3,     1,     1,     3,     1,     3,     2,
       2,     2,     1,     1,     2,     3,     4,     4,     4,     3,
       4,     4,     4,     3,     5,     4,     2,     5,     2,     2,
       0,     6,     3,     0,     5,     2,     2,     2,     2,     3,
       2,     2,     1,     1,     1,     0,     2,     2,     2,     2,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     1,     1,
       2,     1,     0,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     2,     2,     2,     2,
       0,     2,     2,     0,     2,     3,     2,     2,     1,     1,
       0,     2,     2,     2,     0,     2,     2,     0,     2,     2,
       2,     2,     2,     2,     0,     2,     2,     2,     0,     2,
       2,     0,     2,     2,     0,     3,     3,     3,     2,     1,
       1
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
        yyerror (sscript, YY_("syntax error: cannot back up")); \
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
                  Type, Value, sscript); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, sieve_script_t *sscript)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (sscript);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, sieve_script_t *sscript)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep, sscript);
  YYFPRINTF (yyo, ")");
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, sieve_script_t *sscript)
{
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              , sscript);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule, sscript); \
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

  if (! yyres)
    return yystrlen (yystr);

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, sieve_script_t *sscript)
{
  YYUSE (yyvaluep);
  YYUSE (sscript);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
    case 4: /* STRING  */
#line 172 "sieve/sieve.y" /* yacc.c:1257  */
      { free(((*yyvaluep).sval));          }
#line 1818 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 151: /* commands  */
#line 168 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1824 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 152: /* command  */
#line 168 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1830 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 153: /* optstringlist  */
#line 171 "sieve/sieve.y" /* yacc.c:1257  */
      { strarray_free(((*yyvaluep).sl)); }
#line 1836 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 154: /* stringlist  */
#line 171 "sieve/sieve.y" /* yacc.c:1257  */
      { strarray_free(((*yyvaluep).sl)); }
#line 1842 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 155: /* strings  */
#line 171 "sieve/sieve.y" /* yacc.c:1257  */
      { strarray_free(((*yyvaluep).sl)); }
#line 1848 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 156: /* string1  */
#line 171 "sieve/sieve.y" /* yacc.c:1257  */
      { strarray_free(((*yyvaluep).sl)); }
#line 1854 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 157: /* string  */
#line 172 "sieve/sieve.y" /* yacc.c:1257  */
      { free(((*yyvaluep).sval));          }
#line 1860 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 159: /* control  */
#line 168 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1866 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 160: /* thenelse  */
#line 168 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1872 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 161: /* elsif  */
#line 168 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1878 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 162: /* block  */
#line 168 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1884 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 165: /* action  */
#line 168 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1890 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 168: /* ftags  */
#line 168 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1896 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 197: /* timelist  */
#line 173 "sieve/sieve.y" /* yacc.c:1257  */
      { arrayu64_free(((*yyvaluep).nl)); }
#line 1902 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 198: /* times  */
#line 173 "sieve/sieve.y" /* yacc.c:1257  */
      { arrayu64_free(((*yyvaluep).nl)); }
#line 1908 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 199: /* time1  */
#line 173 "sieve/sieve.y" /* yacc.c:1257  */
      { arrayu64_free(((*yyvaluep).nl)); }
#line 1914 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 201: /* testlist  */
#line 169 "sieve/sieve.y" /* yacc.c:1257  */
      { free_testlist(((*yyvaluep).testl)); }
#line 1920 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 202: /* tests  */
#line 169 "sieve/sieve.y" /* yacc.c:1257  */
      { free_testlist(((*yyvaluep).testl)); }
#line 1926 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 203: /* test  */
#line 170 "sieve/sieve.y" /* yacc.c:1257  */
      { free_test(((*yyvaluep).test));     }
#line 1932 "sieve/sieve.c" /* yacc.c:1257  */
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
yyparse (sieve_script_t *sscript)
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
      yychar = yylex (&yylval, sscript);
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
#line 362 "sieve/sieve.y" /* yacc.c:1652  */
    { sscript->cmds = NULL; }
#line 2203 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 3:
#line 363 "sieve/sieve.y" /* yacc.c:1652  */
    { sscript->cmds = (yyvsp[0].cl); }
#line 2209 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 7:
#line 374 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = (yyvsp[-1].cl); (yyval.cl)->next = (yyvsp[0].cl); }
#line 2215 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 10:
#line 380 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     struct buf buf = BUF_INITIALIZER;
                                     buf_printf(&buf, "%s: line %d",
                                                error_message(SIEVE_UNSUPP_EXT),
                                                sievelineno);
                                     sscript->support |= SIEVE_CAPA_IHAVE;
                                     (yyval.cl) = build_rej_err(sscript, B_ERROR,
                                                        buf_release(&buf));
                                 }
#line 2229 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 11:
#line 392 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.sl) = strarray_new(); }
#line 2235 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 14:
#line 398 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.sl) = (yyvsp[-1].sl); }
#line 2241 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 16:
#line 403 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.sl) = (yyvsp[-2].sl); strarray_appendm((yyval.sl), (yyvsp[0].sval)); }
#line 2247 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 17:
#line 407 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.sl) = strarray_new();
                                     strarray_appendm((yyval.sl), (yyvsp[0].sval));
                                 }
#line 2256 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 18:
#line 414 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.sval) = (yyvsp[0].sval); chk_match_vars(sscript, (yyval.sval)); }
#line 2262 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 19:
#line 421 "sieve/sieve.y" /* yacc.c:1652  */
    { check_reqs(sscript, (yyvsp[-1].sl)); }
#line 2268 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 20:
#line 425 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = (yyvsp[0].cl); }
#line 2274 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 21:
#line 426 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_STOP, sscript); }
#line 2280 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 22:
#line 427 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_rej_err(sscript, B_ERROR, (yyvsp[-1].sval)); }
#line 2286 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 23:
#line 429 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_include(sscript, (yyvsp[-2].cl), (yyvsp[-1].sval)); }
#line 2292 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 24:
#line 430 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_RETURN, sscript); }
#line 2298 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 25:
#line 434 "sieve/sieve.y" /* yacc.c:1652  */
    { 
                                     if ((yyvsp[-2].test)->ignore_err) {
                                         /* end of block - decrement counter */
                                         sscript->ignore_err--;
                                     }

                                     (yyval.cl) = new_if((yyvsp[-2].test), (yyvsp[-1].cl), (yyvsp[0].cl));
                                 }
#line 2311 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 26:
#line 445 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = NULL; }
#line 2317 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 27:
#line 446 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = (yyvsp[0].cl); }
#line 2323 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 28:
#line 447 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = (yyvsp[0].cl); }
#line 2329 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 29:
#line 451 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = (yyvsp[-1].cl); }
#line 2335 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 30:
#line 452 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = NULL; }
#line 2341 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 31:
#line 457 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_INCLUDE, sscript); }
#line 2347 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 32:
#line 458 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.inc.location != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "location");
                                     }

                                     (yyval.cl)->u.inc.location = (yyvsp[0].nval);
                                 }
#line 2361 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 33:
#line 467 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.inc.once != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":once");
                                     }

                                     (yyval.cl)->u.inc.once = INC_ONCE_MASK;
                                 }
#line 2375 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 34:
#line 476 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.inc.optional != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":optional");
                                     }

                                     (yyval.cl)->u.inc.optional = INC_OPTIONAL_MASK;
                                 }
#line 2389 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 35:
#line 489 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_PERSONAL; }
#line 2395 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 36:
#line 490 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_GLOBAL;   }
#line 2401 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 37:
#line 497 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_keep(sscript, (yyvsp[0].cl)); }
#line 2407 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 38:
#line 498 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_fileinto(sscript, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2413 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 39:
#line 499 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_redirect(sscript, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2419 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 40:
#line 500 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_DISCARD, sscript); }
#line 2425 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 41:
#line 502 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_set(sscript, (yyvsp[-2].cl), (yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 2431 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 42:
#line 503 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_vacation(sscript, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2437 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 43:
#line 507 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_flag(sscript, (yyvsp[-1].cl), (yyvsp[0].sl)); }
#line 2443 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 44:
#line 510 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_flag(sscript,
                                                   new_command((yyvsp[0].nval), sscript),
                                                   strarray_split("\\Flagged",
                                                                  NULL, 0)); }
#line 2452 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 45:
#line 516 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_addheader(sscript,
                                                        (yyvsp[-2].cl), (yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 2459 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 46:
#line 519 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_deleteheader(sscript,
                                                           (yyvsp[-2].cl), (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 2466 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 47:
#line 522 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_rej_err(sscript, (yyvsp[-1].nval), (yyvsp[0].sval)); }
#line 2472 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 48:
#line 523 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_notify(sscript,
                                                     B_ENOTIFY, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2479 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 49:
#line 526 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_notify(sscript,
                                                     B_NOTIFY, (yyvsp[0].cl), NULL); }
#line 2486 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 50:
#line 529 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_denotify(sscript, (yyvsp[0].cl)); }
#line 2492 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 51:
#line 530 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_log(sscript, (yyvsp[0].sval)); }
#line 2498 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 52:
#line 531 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_snooze(sscript, (yyvsp[-1].cl), (yyvsp[0].nl)); }
#line 2504 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 53:
#line 536 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_KEEP, sscript);
                                     flags = &((yyval.cl)->u.k.flags);
                                 }
#line 2513 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 55:
#line 545 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* **flags assigned by the calling rule */
                                     if (*flags != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":flags");
                                         strarray_free(*flags);
                                     }
                                     else if (!supported(SIEVE_CAPA_IMAP4FLAGS)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "imap4flags");
                                     }

                                     *flags = (yyvsp[0].sl);
                                 }
#line 2534 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 56:
#line 565 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_FILEINTO, sscript);
                                     copy = &((yyval.cl)->u.f.copy);
                                     flags = &((yyval.cl)->u.f.flags);
                                     create = &((yyval.cl)->u.f.create);
                                     specialuse = &((yyval.cl)->u.f.specialuse);
                                     mailboxid = &((yyval.cl)->u.f.mailboxid);
                                 }
#line 2547 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 62:
#line 582 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* *copy assigned by the calling rule */
                                     if ((*copy)++) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":copy");
                                     }
                                     else if (!supported(SIEVE_CAPA_COPY)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "copy");
                                     }
                                 }
#line 2565 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 63:
#line 599 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* *create assigned by the calling rule */
                                     if ((*create)++) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":create");
                                     }
                                     else if (!supported(SIEVE_CAPA_MAILBOX)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "mailbox");
                                     }
                                 }
#line 2583 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 64:
#line 616 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* **specialuse assigned by calling rule */
                                     if (*specialuse != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":specialuse");
                                         free(*specialuse);
                                     }
                                     else if (!supported(SIEVE_CAPA_SPECIAL_USE)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "special-use");
                                     }

                                     *specialuse = (yyvsp[0].sval);
                                 }
#line 2604 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 65:
#line 634 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* **mailboxid assigned by the calling rule */
                                     if (*mailboxid != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":mailboxid");
                                         free(*mailboxid);
                                     }
                                     else if (!supported(SIEVE_CAPA_MAILBOXID)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "mailboxid");
                                     }

                                     *mailboxid = (yyvsp[0].sval);
                                 }
#line 2625 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 66:
#line 654 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_REDIRECT, sscript);
                                     copy = &((yyval.cl)->u.r.copy);
                                 }
#line 2634 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 68:
#line 659 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.r.list++) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":list");
                                     }
                                     else if (!supported(SIEVE_CAPA_EXTLISTS)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "extlists");
                                     }
                                 }
#line 2651 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 69:
#line 671 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (!supported(SIEVE_CAPA_REDIR_DELBY)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "redirect-deliverby");
                                     }
                                 }
#line 2663 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 70:
#line 678 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (!supported(SIEVE_CAPA_REDIR_DSN)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "redirect-dsn");
                                     }
                                 }
#line 2675 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 71:
#line 688 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* $0 refers to rtags */
                                     commandlist_t *c = (yyvsp[-2].cl);

                                     if (c->u.r.bytime != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":bytime*");
                                     }                                         

                                     struct buf buf = BUF_INITIALIZER;
                                     buf_printf(&buf, "+%d", (yyvsp[0].nval));
                                     c->u.r.bytime = buf_release(&buf);
                                 }
#line 2694 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 72:
#line 702 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* $0 refers to rtags */
                                     commandlist_t *c = (yyvsp[-2].cl);

                                     if (c->u.r.bytime != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":bytimerelative"
                                                      " OR :bytimeabsolute");
                                     }

                                     c->u.r.bytime = (yyvsp[0].sval);
                                 }
#line 2712 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 73:
#line 715 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* $0 refers to rtags */
                                     commandlist_t *c = (yyvsp[-2].cl);

                                     if (c->u.r.bymode != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":bymode");
                                     }

                                     c->u.r.bymode = (yyvsp[0].sval);
                                 }
#line 2729 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 74:
#line 727 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* $0 refers to rtags */
                                     commandlist_t *c = (yyvsp[-1].cl);

                                     if (c->u.r.bytrace != 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":bytrace");
                                     }

                                     c->u.r.bytrace = 1;
                                 }
#line 2746 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 75:
#line 743 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* $0 refers to rtags */
                                     commandlist_t *c = (yyvsp[-2].cl);

                                     if (c->u.r.dsn_notify != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":notify");
                                     }                                         

                                     c->u.r.dsn_notify = (yyvsp[0].sval);
                                 }
#line 2763 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 76:
#line 755 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* $0 refers to rtags */
                                     commandlist_t *c = (yyvsp[-2].cl);

                                     if (c->u.r.dsn_ret != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":ret");
                                     }

                                     c->u.r.dsn_ret = (yyvsp[0].sval);
                                 }
#line 2780 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 77:
#line 771 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_SET, sscript); }
#line 2786 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 78:
#line 772 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.s.modifiers & BFV_MOD40_MASK) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "precedence 40 modifier");
                                     }

                                     (yyval.cl)->u.s.modifiers |= (yyvsp[0].nval);
                                 }
#line 2800 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 79:
#line 781 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.s.modifiers & BFV_MOD30_MASK) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "precedence 30 modifier");
                                     }

                                     (yyval.cl)->u.s.modifiers |= (yyvsp[0].nval);
                                 }
#line 2814 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 80:
#line 790 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.s.modifiers & BFV_MOD20_MASK) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "precedence 20 modifier");
                                     }

                                     (yyval.cl)->u.s.modifiers |= (yyvsp[0].nval);
                                 }
#line 2828 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 81:
#line 799 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.s.modifiers & BFV_MOD15_MASK) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "precedence 15 modifier");
                                     }

                                     (yyval.cl)->u.s.modifiers |= (yyvsp[0].nval);
                                 }
#line 2842 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 82:
#line 808 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.s.modifiers & BFV_MOD10_MASK) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "precedence 10 modifier");
                                     }

                                     (yyval.cl)->u.s.modifiers |= (yyvsp[0].nval);
                                 }
#line 2856 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 83:
#line 821 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = BFV_LOWER; }
#line 2862 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 84:
#line 822 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = BFV_UPPER; }
#line 2868 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 85:
#line 825 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = BFV_LOWERFIRST; }
#line 2874 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 86:
#line 826 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = BFV_UPPERFIRST; }
#line 2880 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 87:
#line 829 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = BFV_QUOTEWILDCARD; }
#line 2886 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 88:
#line 830 "sieve/sieve.y" /* yacc.c:1652  */
    { 
                                     if (!supported(SIEVE_CAPA_REGEX)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "regex");
                                     }

                                     (yyval.nval) = BFV_QUOTEREGEX;
                                 }
#line 2900 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 89:
#line 842 "sieve/sieve.y" /* yacc.c:1652  */
    { 
                                     if (!supported(SIEVE_CAPA_ENOTIFY)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "enotify");
                                     }

                                     (yyval.nval) = BFV_ENCODEURL;
                                 }
#line 2914 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 90:
#line 853 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = BFV_LENGTH; }
#line 2920 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 91:
#line 858 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_VACATION, sscript);
                                     flags = &((yyval.cl)->u.v.fcc.flags);
                                     create = &((yyval.cl)->u.v.fcc.create);
                                     specialuse = &((yyval.cl)->u.v.fcc.specialuse);
                                     mailboxid = &((yyval.cl)->u.v.fcc.mailboxid);
                                     fccfolder = &((yyval.cl)->u.v.fcc.folder);
                                 }
#line 2933 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 92:
#line 866 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.v.seconds != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":days");
                                     }

                                     (yyval.cl)->u.v.seconds = (yyvsp[0].nval) * DAY2SEC;
                                 }
#line 2947 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 93:
#line 875 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (!supported(SIEVE_CAPA_VACATION_SEC)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "vacation-seconds");
                                     }
                                     if ((yyval.cl)->u.v.seconds != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":seconds");
                                     }

                                     (yyval.cl)->u.v.seconds = (yyvsp[0].nval);
                                 }
#line 2966 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 94:
#line 889 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.v.subject != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":subject");
                                         free((yyval.cl)->u.v.subject);
                                     }

                                     (yyval.cl)->u.v.subject = (yyvsp[0].sval);
                                 }
#line 2981 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 95:
#line 899 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.v.from != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":from");
                                         free((yyval.cl)->u.v.from);
                                     }

                                     (yyval.cl)->u.v.from = (yyvsp[0].sval);
                                 }
#line 2996 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 96:
#line 911 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.v.addresses != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":addresses");
                                         strarray_free((yyval.cl)->u.v.addresses);
                                     }

                                     (yyval.cl)->u.v.addresses = (yyvsp[0].sl);
                                 }
#line 3011 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 97:
#line 921 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.v.mime != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":mime");
                                     }

                                     (yyval.cl)->u.v.mime = 1;
                                 }
#line 3025 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 98:
#line 930 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.v.handle != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":handle");
                                         free((yyval.cl)->u.v.handle);
                                     }

                                     (yyval.cl)->u.v.handle = (yyvsp[0].sval);
                                 }
#line 3040 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 100:
#line 944 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* **fccfolder assigned by the calling rule */
                                     if (*fccfolder != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":fcc");
                                         free(*fccfolder);
                                     }
                                     else if (!supported(SIEVE_CAPA_FCC)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "fcc");
                                     }

                                     *fccfolder = (yyvsp[0].sval);
                                 }
#line 3061 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 105:
#line 968 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_SETFLAG;    }
#line 3067 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 106:
#line 969 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_ADDFLAG;    }
#line 3073 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 107:
#line 970 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_REMOVEFLAG; }
#line 3079 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 108:
#line 975 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command((yyvsp[0].nval), sscript); }
#line 3085 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 109:
#line 976 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.fl.variable != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_ARG,
                                                      "variablename");
                                         free((yyval.cl)->u.fl.variable);
                                     }
                                     else if (!supported(SIEVE_CAPA_IMAP4FLAGS)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "imap4flags");
                                     }

                                     (yyval.cl)->u.fl.variable = (yyvsp[0].sval);
                                 }
#line 3105 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 110:
#line 995 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_ADDFLAG;   }
#line 3111 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 111:
#line 996 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_REMOVEFLAG; }
#line 3117 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 112:
#line 1001 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_ADDHEADER, sscript); }
#line 3123 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 113:
#line 1002 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.ah.index < 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":last");
                                     }

                                     (yyval.cl)->u.ah.index = -1;
                                 }
#line 3137 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 114:
#line 1015 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_DELETEHEADER, sscript);
                                     ctags = &((yyval.cl)->u.dh.comp);
                                 }
#line 3146 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 119:
#line 1027 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_REJECT;  }
#line 3152 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 120:
#line 1028 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_EREJECT; }
#line 3158 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 121:
#line 1039 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_ENOTIFY, sscript);
                                     flags = &((yyval.cl)->u.n.fcc.flags);
                                     create = &((yyval.cl)->u.n.fcc.create);
                                     specialuse = &((yyval.cl)->u.n.fcc.specialuse);
                                     mailboxid = &((yyval.cl)->u.n.fcc.mailboxid);
                                     fccfolder = &((yyval.cl)->u.n.fcc.folder);
                                 }
#line 3171 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 122:
#line 1049 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.from != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":from");
                                         free((yyval.cl)->u.n.from);
                                     }

                                     (yyval.cl)->u.n.from = (yyvsp[0].sval);
                                 }
#line 3186 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 123:
#line 1061 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.priority != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":importance");
                                     }

                                     (yyval.cl)->u.n.priority = (yyvsp[0].nval);
                                 }
#line 3200 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 125:
#line 1073 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.id != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":id");
                                         free((yyval.cl)->u.n.id);
                                     }

                                     (yyval.cl)->u.n.id = (yyvsp[0].sval);
                                 }
#line 3215 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 126:
#line 1083 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.method != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":method");
                                         free((yyval.cl)->u.n.method);
                                     }

                                     (yyval.cl)->u.n.method = (yyvsp[0].sval);
                                 }
#line 3230 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 127:
#line 1093 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.priority != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "priority");
                                     }

                                     (yyval.cl)->u.n.priority = (yyvsp[0].nval);
                                 }
#line 3244 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 128:
#line 1104 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.message != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":message");
                                         free((yyval.cl)->u.n.message);
                                     }

                                     (yyval.cl)->u.n.message = (yyvsp[0].sval);
                                 }
#line 3259 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 129:
#line 1116 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.options != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":options");
                                         strarray_free((yyval.cl)->u.n.options);
                                     }

                                     (yyval.cl)->u.n.options = (yyvsp[0].sl);
                                 }
#line 3274 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 130:
#line 1130 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_LOW;    }
#line 3280 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 131:
#line 1131 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_NORMAL; }
#line 3286 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 132:
#line 1132 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_HIGH;   }
#line 3292 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 133:
#line 1137 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_DENOTIFY, sscript);
                                     ctags = &((yyval.cl)->u.d.comp);
                                 }
#line 3301 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 134:
#line 1141 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.d.priority != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "priority");
                                     }

                                     (yyval.cl)->u.d.priority = (yyvsp[0].nval);
                                 }
#line 3315 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 135:
#line 1152 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.d.pattern) free((yyval.cl)->u.d.pattern);
                                     (yyval.cl)->u.d.pattern = (yyvsp[0].sval);
                                 }
#line 3324 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 136:
#line 1160 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_SNOOZE, sscript);
                                     create = &((yyval.cl)->u.sn.f.create);
                                     specialuse = &((yyval.cl)->u.sn.f.specialuse);
                                     mailboxid = &((yyval.cl)->u.sn.f.mailboxid);
                                 }
#line 3335 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 137:
#line 1166 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.sn.f.folder != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":mailbox");
                                         free((yyval.cl)->u.sn.f.folder);
                                     }

                                     (yyval.cl)->u.sn.f.folder = (yyvsp[0].sval);
                                 }
#line 3350 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 141:
#line 1181 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.sn.addflags != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":addflags");
                                         free((yyval.cl)->u.sn.addflags);
                                     }
                                     else if (!supported(SIEVE_CAPA_IMAP4FLAGS)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "imap4flags");
                                     }

                                     (yyval.cl)->u.sn.addflags = (yyvsp[0].sl);
                                 }
#line 3370 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 142:
#line 1197 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.sn.removeflags != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":removeflags");
                                         free((yyval.cl)->u.sn.removeflags);
                                     }
                                     else if (!supported(SIEVE_CAPA_IMAP4FLAGS)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "imap4flags");
                                     }

                                     (yyval.cl)->u.sn.removeflags = (yyvsp[0].sl);
                                 }
#line 3390 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 143:
#line 1213 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.sn.days != 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":weekdays");
                                     }

                                     (yyval.cl)->u.sn.days = (yyvsp[0].nval);
                                 }
#line 3404 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 144:
#line 1222 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.sn.tzid != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":tzid");
                                         free((yyval.cl)->u.sn.tzid);
                                     }

                                     (yyval.cl)->u.sn.tzid = (yyvsp[0].sval);
                                 }
#line 3419 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 146:
#line 1236 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = (yyvsp[-1].nval); }
#line 3425 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 148:
#line 1241 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = (yyvsp[-2].nval) | (yyvsp[0].nval); }
#line 3431 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 149:
#line 1245 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = verify_weekday(sscript, (yyvsp[0].sval)); }
#line 3437 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 151:
#line 1250 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nl) = (yyvsp[-1].nl); }
#line 3443 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 153:
#line 1255 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nl) = (yyvsp[-2].nl); arrayu64_add((yyval.nl), (yyvsp[0].nval)); }
#line 3449 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 154:
#line 1259 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.nl) = arrayu64_new();
                                     arrayu64_add((yyval.nl), (yyvsp[0].nval));
                                 }
#line 3458 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 155:
#line 1266 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = verify_time(sscript, (yyvsp[0].sval)); }
#line 3464 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 156:
#line 1273 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.testl) = (yyvsp[-1].testl); }
#line 3470 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 157:
#line 1277 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.testl) = new_testlist((yyvsp[0].test), NULL); }
#line 3476 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 158:
#line 1278 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.testl) = new_testlist((yyvsp[-2].test), (yyvsp[0].testl)); }
#line 3482 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 159:
#line 1282 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_anyof(sscript, (yyvsp[0].testl)); }
#line 3488 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 160:
#line 1283 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_allof(sscript, (yyvsp[0].testl)); }
#line 3494 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 161:
#line 1284 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_not(sscript, (yyvsp[0].test));   }
#line 3500 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 162:
#line 1285 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = new_test(BC_FALSE, sscript); }
#line 3506 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 163:
#line 1286 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = new_test(BC_TRUE, sscript);  }
#line 3512 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 164:
#line 1287 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_EXISTS, sscript);
                                     (yyval.test)->u.sl = (yyvsp[0].sl);
                                     (yyval.test)->nargs = bc_precompile((yyval.test)->args, "S",
                                                               (yyval.test)->u.sl);
                                 }
#line 3523 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 165:
#line 1293 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_SIZE, sscript);
                                     (yyval.test)->u.sz.t = (yyvsp[-1].nval);
                                     (yyval.test)->u.sz.n = (yyvsp[0].nval);
                                     (yyval.test)->nargs = bc_precompile((yyval.test)->args, "ii",
                                                               (yyval.test)->u.sz.t,
                                                               (yyval.test)->u.sz.n);
                                 }
#line 3536 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 166:
#line 1303 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_header(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3542 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 167:
#line 1306 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_address(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3548 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 168:
#line 1308 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_envelope(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3554 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 169:
#line 1310 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_body(sscript, (yyvsp[-1].test), (yyvsp[0].sl)); }
#line 3560 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 170:
#line 1313 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_mbox_meta(sscript,
                                                        (yyvsp[-2].test), NULL, (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3567 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 171:
#line 1317 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_stringt(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3573 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 172:
#line 1324 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_hasflag(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3579 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 173:
#line 1326 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_hasflag(sscript, (yyvsp[-1].test), NULL, (yyvsp[0].sl)); }
#line 3585 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 174:
#line 1329 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_date(sscript, (yyvsp[-3].test), (yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3591 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 175:
#line 1332 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_date(sscript, (yyvsp[-2].test), NULL, (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3597 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 176:
#line 1335 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_VALIDNOTIFYMETHOD, sscript);
                                     (yyval.test)->u.sl = (yyvsp[0].sl);
                                     (yyval.test)->nargs = bc_precompile((yyval.test)->args, "S",
                                                               (yyval.test)->u.sl);
                                 }
#line 3608 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 177:
#line 1342 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_mbox_meta(sscript,
                                                        (yyvsp[-3].test), (yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3615 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 178:
#line 1345 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_ihave(sscript, (yyvsp[0].sl)); }
#line 3621 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 179:
#line 1348 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_MAILBOXEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), NULL, NULL, (yyvsp[0].sl));
                                 }
#line 3631 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 180:
#line 1354 "sieve/sieve.y" /* yacc.c:1652  */
    { bctype = BC_METADATA; }
#line 3637 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 181:
#line 1355 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_mbox_meta(sscript,
                                                        (yyvsp[-3].test), (yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3644 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 182:
#line 1359 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_METADATAEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), (yyvsp[-1].sval), NULL, (yyvsp[0].sl));
                                 }
#line 3654 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 183:
#line 1365 "sieve/sieve.y" /* yacc.c:1652  */
    { bctype = BC_SERVERMETADATA; }
#line 3660 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 184:
#line 1366 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_mbox_meta(sscript,
                                                        (yyvsp[-2].test), NULL, (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3667 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 185:
#line 1370 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_SERVERMETADATAEXISTS,
                                                   sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), NULL, NULL, (yyvsp[0].sl));
                                 }
#line 3678 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 186:
#line 1378 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_VALIDEXTLIST, sscript);
                                     (yyval.test)->u.sl = (yyvsp[0].sl);
                                     (yyval.test)->nargs = bc_precompile((yyval.test)->args, "S",
                                                               (yyval.test)->u.sl);
                                 }
#line 3689 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 187:
#line 1384 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_duplicate(sscript, (yyvsp[0].test)); }
#line 3695 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 188:
#line 1387 "sieve/sieve.y" /* yacc.c:1652  */
    { 
                                     (yyval.test) = new_test(BC_SPECIALUSEEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), NULL, NULL, (yyvsp[0].sl));
                                 }
#line 3705 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 189:
#line 1394 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_SPECIALUSEEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), (yyvsp[-1].sval), NULL, (yyvsp[0].sl));
                                 }
#line 3715 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 190:
#line 1401 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_MAILBOXIDEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), NULL, NULL, (yyvsp[0].sl));
                                 }
#line 3725 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 191:
#line 1407 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_JMAPQUERY, sscript);
                                     (yyval.test) = build_jmapquery(sscript, (yyval.test), (yyvsp[0].sval));
                                 }
#line 3734 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 192:
#line 1412 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = new_test(BC_FALSE, sscript); }
#line 3740 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 193:
#line 1417 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_OVER;  }
#line 3746 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 194:
#line 1418 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_UNDER; }
#line 3752 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 195:
#line 1423 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_HEADER, sscript);
                                     ctags = &((yyval.test)->u.hhs.comp);
                                 }
#line 3761 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 200:
#line 1435 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* *ctags assigned by the calling rule */
                                     if (ctags->match != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "match-type");
                                     }

                                     ctags->match = (yyvsp[0].nval);
                                 }
#line 3776 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 201:
#line 1446 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (ctags->match != B_COUNT &&
                                         ctags->match != B_VALUE &&
                                         !supported(SIEVE_CAPA_RELATIONAL)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "relational");
                                     }
                                     if (ctags->match != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "match-type");
                                     }

                                     ctags->match = (yyvsp[-1].nval);
                                     ctags->relation = (yyvsp[0].nval);
                                 }
#line 3798 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 202:
#line 1467 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_IS;       }
#line 3804 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 203:
#line 1468 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_CONTAINS; }
#line 3810 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 204:
#line 1469 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_MATCHES;  }
#line 3816 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 205:
#line 1470 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (!supported(SIEVE_CAPA_REGEX)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "regex");
                                     }

                                     (yyval.nval) = B_REGEX;
                                 }
#line 3830 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 206:
#line 1483 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_COUNT; }
#line 3836 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 207:
#line 1484 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_VALUE; }
#line 3842 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 208:
#line 1489 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_EQ; }
#line 3848 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 209:
#line 1490 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_NE; }
#line 3854 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 210:
#line 1491 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_GT; }
#line 3860 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 211:
#line 1492 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_GE; }
#line 3866 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 212:
#line 1493 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_LT; }
#line 3872 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 213:
#line 1494 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_LE; }
#line 3878 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 214:
#line 1499 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* *ctags assigned by the calling rule */
                                     if (ctags->match != B_LIST &&
                                         !supported(SIEVE_CAPA_EXTLISTS)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "extlists");
                                     }
                                     if (ctags->match != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "match-type");
                                     }

                                     ctags->match = B_LIST;
                                 }
#line 3899 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 215:
#line 1520 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* *ctags assigned by the calling rule */
                                     if (ctags->collation != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":comparator");
                                     }

                                     ctags->collation = (yyvsp[0].nval);
                                 }
#line 3914 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 216:
#line 1534 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_OCTET;        }
#line 3920 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 217:
#line 1535 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_ASCIICASEMAP; }
#line 3926 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 218:
#line 1536 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (!supported(SIEVE_CAPA_COMP_NUMERIC)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "comparator-"
                                                      "i;ascii-numeric");
                                     }

                                     (yyval.nval) = B_ASCIINUMERIC;
                                 }
#line 3941 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 219:
#line 1550 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* *ctags assigned by the calling rule */
                                     if (ctags->index != 0 &&
                                         !supported(SIEVE_CAPA_INDEX)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "index");
                                     }
                                 }
#line 3955 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 220:
#line 1561 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* *ctags assigned by the calling rule */
                                     if (ctags->index == INT_MIN) {
                                         /* parsed :last before :index */
                                         ctags->index = -(yyvsp[0].nval);
                                     }
                                     else if (ctags->index != 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":index");
                                     }
                                     else {
                                         ctags->index = (yyvsp[0].nval);
                                     }
                                 }
#line 3975 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 221:
#line 1576 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (ctags->index > 0) {
                                         ctags->index *= -1;
                                     }
                                     else if (ctags->index < 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":last");
                                     }
                                     else {
                                         /* special value to indicate that
                                            we parsed :last before :index */
                                         ctags->index = INT_MIN;
                                     }
                                 }
#line 3995 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 222:
#line 1595 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_ADDRESS, sscript);
                                     ctags = &((yyval.test)->u.ae.comp);
                                 }
#line 4004 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 228:
#line 1608 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* $0 refers to a test_t* (ADDR/ENV)*/
                                     test_t *test = (yyvsp[-1].test);

                                     if (test->u.ae.addrpart != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "address-part");
                                     }

                                     test->u.ae.addrpart = (yyvsp[0].nval);
                                 }
#line 4021 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 229:
#line 1623 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_ALL;       }
#line 4027 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 230:
#line 1624 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_LOCALPART; }
#line 4033 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 231:
#line 1625 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_DOMAIN;    }
#line 4039 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 232:
#line 1626 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (!supported(SIEVE_CAPA_SUBADDRESS)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "subaddress");
                                     }
                                 }
#line 4051 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 233:
#line 1637 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_USER;   }
#line 4057 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 234:
#line 1638 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_DETAIL; }
#line 4063 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 235:
#line 1643 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_ENVELOPE, sscript);
                                     ctags = &((yyval.test)->u.ae.comp);
                                 }
#line 4072 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 240:
#line 1655 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_ENVIRONMENT, sscript);
                                     ctags = &((yyval.test)->u.mm.comp);
                                 }
#line 4081 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 243:
#line 1665 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_BODY, sscript);
                                     ctags = &((yyval.test)->u.b.comp);
                                 }
#line 4090 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 244:
#line 1669 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.b.transform != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "transform");
                                     }

                                     (yyval.test)->u.b.transform = (yyvsp[0].nval);
                                 }
#line 4104 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 245:
#line 1680 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.b.transform != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "transform");
                                         strarray_free((yyval.test)->u.b.content_types);
                                     }

                                     (yyval.test)->u.b.transform = B_CONTENT;
                                     (yyval.test)->u.b.content_types = (yyvsp[0].sl);
                                 }
#line 4120 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 248:
#line 1698 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_RAW;  }
#line 4126 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 249:
#line 1699 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_TEXT; }
#line 4132 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 250:
#line 1704 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_STRING, sscript);
                                     ctags = &((yyval.test)->u.hhs.comp);
                                 }
#line 4141 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 254:
#line 1715 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_HASFLAG, sscript);
                                     ctags = &((yyval.test)->u.hhs.comp);
                                 }
#line 4150 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 257:
#line 1725 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_DATE, sscript);
                                     ctags = &((yyval.test)->u.dt.comp);
                                 }
#line 4159 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 259:
#line 1730 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.dt.zone.tag != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":originalzone");
                                     }

                                     (yyval.test)->u.dt.zone.tag = B_ORIGINALZONE;
                                 }
#line 4173 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 263:
#line 1746 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* $0 refers to a test_t* ([CURRENT]DATE)*/
                                     test_t *test = (yyvsp[-2].test);

                                     if (test->u.dt.zone.tag != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":zone");
                                     }

                                     test->u.dt.zone.tag = B_TIMEZONE;
                                     test->u.dt.zone.offset = (yyvsp[0].sval);
                                 }
#line 4191 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 264:
#line 1763 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_CURRENTDATE, sscript);
                                     ctags = &((yyval.test)->u.dt.comp);
                                 }
#line 4200 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 268:
#line 1774 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_NOTIFYMETHODCAPABILITY,
                                                   sscript);
                                     ctags = &((yyval.test)->u.mm.comp);
                                 }
#line 4210 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 271:
#line 1785 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* bctype assigned by the calling rule */
                                     (yyval.test) = new_test(bctype, sscript);
                                     ctags = &((yyval.test)->u.mm.comp);
                                 }
#line 4220 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 274:
#line 1796 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = new_test(BC_DUPLICATE, sscript); }
#line 4226 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 275:
#line 1797 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.dup.idtype != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      (yyvsp[-1].nval) == HEADER ?
                                                      ":header" : ":uniqueid");
                                         free((yyval.test)->u.dup.idval);
                                     }

                                     (yyval.test)->u.dup.idtype = (yyvsp[-1].nval);
                                     (yyval.test)->u.dup.idval = (yyvsp[0].sval);
                                 }
#line 4243 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 276:
#line 1809 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.dup.handle != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":handle");
                                         free((yyval.test)->u.dup.handle);
                                     }

                                     (yyval.test)->u.dup.handle = (yyvsp[0].sval);
                                 }
#line 4258 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 277:
#line 1819 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.dup.seconds != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":seconds");
                                     }

                                     (yyval.test)->u.dup.seconds = (yyvsp[0].nval);
                                 }
#line 4272 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 278:
#line 1828 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.dup.last != 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":last");
                                     }

                                     (yyval.test)->u.dup.last = 1;
                                 }
#line 4286 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 279:
#line 1841 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_HEADER;   }
#line 4292 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 280:
#line 1842 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_UNIQUEID; }
#line 4298 "sieve/sieve.c" /* yacc.c:1652  */
    break;


#line 4302 "sieve/sieve.c" /* yacc.c:1652  */
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
      yyerror (sscript, YY_("syntax error"));
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
        yyerror (sscript, yymsgp);
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
                      yytoken, &yylval, sscript);
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
                  yystos[yystate], yyvsp, sscript);
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
  yyerror (sscript, YY_("memory exhausted"));
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
                  yytoken, &yylval, sscript);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, sscript);
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
#line 1846 "sieve/sieve.y" /* yacc.c:1918  */



/*
 * Yacc actions
 */

void yyerror(sieve_script_t *sscript, const char *msg)
{
    if (sscript->ignore_err) return;

    sscript->err++;
    if (sscript->interp.err) {
        sscript->interp.err(sievelineno, msg, sscript->interp.interp_context,
                            sscript->script_context);
    }
}


static void
__attribute__((format(printf, 2, 0)))
vsieveerror_f(sieve_script_t *sscript,
              const char *fmt, va_list args)
{
    buf_reset(&sscript->sieveerr);
    buf_vprintf(&sscript->sieveerr, fmt, args);
    yyerror(sscript, buf_cstring(&sscript->sieveerr));
}

void
__attribute__((format(printf, 2, 3)))
sieveerror_f(sieve_script_t *sscript, const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vsieveerror_f(sscript, fmt, args);
    va_end(args);
}

void sieveerror_c(sieve_script_t *sscript, int code, ...)
{
    va_list args;

    va_start(args, code);
    vsieveerror_f(sscript, error_message(code), args);
    va_end(args);
}

/*
 * variable-ref        =  "${" [namespace] variable-name "}"
 * namespace           =  identifier "." *sub-namespace
 * sub-namespace       =  variable-name "."
 * variable-name       =  num-variable / identifier
 * num-variable        =  1*DIGIT
 * identifier          =  (ALPHA / "_") *(ALPHA / DIGIT / "_")
 */
static int find_variables(sieve_script_t *sscript, char *s, int find_one)
{
    char *p = s;

    if (!supported(SIEVE_CAPA_VARIABLES)) return !find_one;

    while ((p = strstr(p, "${"))) {
        long num = 0, is_id = 0;

        p += 2;  /* skip over beginning of variable-ref */

        do {
            if (isdigit(*p)) {
                /* possible num-variable - get value and skip over digits */
                num = strtol(p, &p, 10);
            }
            else if (!find_one) {
                /* validating match variables - ignoroe identifiers */
                break;
            }
            else if (isalpha(*p) || *p == '_') {
                /* possible identifier - skip over identifier chars */
                for (++p; isalnum(*p) || *p == '_'; p++);
                is_id = 1;
            }
            else {
                /* not a valid variable-name */
                break;
            }

            if (*p == '}') {
                /* end of variable-ref */
                if (find_one) return 1;

                /* validating match variables */
                if (!is_id && num > MAX_MATCH_VARS) {
                    sieveerror_f(sscript, "string '%s':"
                                 " match variable index > %u unsupported",
                                 s, MAX_MATCH_VARS);
                    return 0;
                }
            }

        } while (is_id && *p == '.' && *(++p));  /* (sub-)namespace */
    }

    return !find_one;
}

static int chk_match_vars(sieve_script_t *sscript, char *s)
{
    return find_variables(sscript, s, 0 /* find_one */);
}

static int contains_variable(sieve_script_t *sscript, char *s)
{
    return find_variables(sscript, s, 1 /* find_one */);
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
static int verify_utf8(sieve_script_t *sscript, char *s)
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
        sieveerror_f(sscript, "string '%s': not valid utf8", s);
        return 0;
    }

    return 1;
}

static int verify_stringlist(sieve_script_t *sscript, strarray_t *sa,
                             int (*verify)(sieve_script_t*, char *))
{
    int i;

    for (i = 0 ; i < strarray_size(sa) ; i++) {
        if (!verify(sscript, (char *) strarray_nth(sa, i))) return 0;
    }
    return 1;
}

#ifdef ENABLE_REGEX
static int verify_regexlist(sieve_script_t *sscript,
                            const strarray_t *sa, int collation)
{
    int i, ret = 0;
    regex_t reg;
    int cflags = REG_EXTENDED | REG_NOSUB;

#ifdef HAVE_PCREPOSIX_H
    /* support UTF8 comparisons */
    cflags |= REG_UTF8;
#endif

    if (collation == B_ASCIICASEMAP) {
        cflags |= REG_ICASE;
    }

    for (i = 0 ; !ret && i < strarray_size(sa) ; i++) {
        const char *s = strarray_nth(sa, i);

        /* Don't try to validate a regex that includes variables */
        if (supported(SIEVE_CAPA_VARIABLES) && strstr(s, "${")) continue;

        /* Check if the regex will compile */
        if ((ret = regcomp(&reg, s, cflags)) != 0) {
            size_t errbuf_size = regerror(ret, &reg, NULL, 0);

            buf_reset(&sscript->sieveerr);
            buf_ensure(&sscript->sieveerr, errbuf_size);
            (void) regerror(ret, &reg,
                            (char *) buf_base(&sscript->sieveerr),
                            errbuf_size);
            buf_truncate(&sscript->sieveerr, errbuf_size);
            yyerror(sscript, buf_cstring(&sscript->sieveerr));
        }

        regfree(&reg);
    }

    return (ret == 0);
}
#else

static int verify_regexlist(sieve_script_t *sscript __attribute__((unused)),
                            const strarray_t *sa __attribute__((unused)),
                            char *comp __attribute__((unused)))
{
    return 0;
}
#endif /* ENABLE_REGEX */

static int verify_patternlist(sieve_script_t *sscript,
                              strarray_t *sa, comp_t *c,
                              int (*verify)(sieve_script_t*, char *))
{
    if (verify && !verify_stringlist(sscript, sa, verify)) return 0;

    canon_comptags(c, sscript);

    return (c->match == B_REGEX) ?
        verify_regexlist(sscript, sa, c->collation) : 1;
}

static int verify_address(sieve_script_t *sscript, char *s)
{
    if (contains_variable(sscript, s)) return 1;

    YY_BUFFER_STATE buffer = addr_scan_string(s);
    int r = 1;

    sscript->addrerr[0] = '\0';    /* paranoia */
    if (addrparse(sscript)) {
        sieveerror_f(sscript, "address '%s': %s", s, sscript->addrerr);
        r = 0;
    }
    addr_delete_buffer(buffer);

    return r;
}

static int verify_mailbox(sieve_script_t *sscript, char *s)
{
    if (!verify_utf8(sscript, s)) {
        sieveerror_f(sscript, "mailbox '%s': not a valid mailbox", s);
        return 0;
    }

    return 1;
}

static int verify_header(sieve_script_t *sscript, char *hdr)
{
    char *h = hdr;

    while (*h) {
        /* field-name      =       1*ftext
           ftext           =       %d33-57 / %d59-126
           ; Any character except
           ;  controls, SP, and
           ;  ":". */
        if (!((*h >= 33 && *h <= 57) || (*h >= 59 && *h <= 126))) {
            sieveerror_f(sscript, "header '%s': not a valid header", hdr);
            return 0;
        }
        h++;
    }
    return 1;
}

static int verify_addrheader(sieve_script_t *sscript, char *hdr)
{
    const char **h, *hdrs[] = {
        "from", "sender", "reply-to",   /* RFC 5322 originator fields */
        "to", "cc", "bcc",              /* RFC 5322 destination fields */
        "message-id", "in-reply-to",    /* RFC 5322 identification fields */
        "references",
        "resent-from", "resent-sender", /* RFC 5322 resent fields */
        "resent-to", "resent-cc", "resent-bcc",
        "return-path",                  /* RFC 5322 trace fields */
        "disposition-notification-to",  /* RFC 8098 MDN request fields */
        "approved",                     /* RFC 5536 moderator/control fields */
        "delivered-to",                 /* non-standard (loop detection) */
        NULL
    };

    if (contains_variable(sscript, hdr)) return 1;

    if (!config_getswitch(IMAPOPT_RFC3028_STRICT))
        return verify_header(sscript, hdr);

    for (lcase(hdr), h = hdrs; *h; h++) {
        if (!strcmp(*h, hdr)) return 1;
    }

    sieveerror_f(sscript,
                 "header '%s': not a valid header for an address test", hdr);
    return 0;
}

static int verify_envelope(sieve_script_t *sscript, char *env)
{
    if (contains_variable(sscript, env)) return 1;

    lcase(env);
    if (!config_getswitch(IMAPOPT_RFC3028_STRICT) ||
        !strcmp(env, "from") || !strcmp(env, "to") || !strcmp(env, "auth")) {
        return 1;
    }

    sieveerror_f(sscript,
                 "env-part '%s': not a valid part for an envelope test", env);
    return 0;
}

static int verify_list(sieve_script_t *sscript, char *s)
{
    if (sscript->interp.isvalidlist &&
        sscript->interp.isvalidlist(sscript->interp.interp_context, s)
        != SIEVE_OK) {
        sieveerror_f(sscript, "list '%s': is not valid/supported", s);
        return 0;
    }

    return 1;
}

static int check_reqs(sieve_script_t *sscript, strarray_t *sa)
{
    char *s;
    struct buf *errs = &sscript->sieveerr;
    int ret = 1, sep = ':';

    buf_setcstr(errs, "Unsupported feature(s) in \"require\"");
    while ((s = strarray_shift(sa))) {
        if (!script_require(sscript, s)) {
            buf_printf(errs, "%c \"%s\"", sep, s);
            ret = 0;
            sep = ',';
        }
        free(s);
    }
    strarray_free(sa);

    if (ret == 0) yyerror(sscript, buf_cstring(&sscript->sieveerr));
    else if (supported(SIEVE_CAPA_IHAVE)) {
        /* mark all allowed extensions as supported */
        sscript->support |= (SIEVE_CAPA_ALL & ~SIEVE_CAPA_IHAVE_INCOMPAT);
    }

    encoded_char = supported(SIEVE_CAPA_ENCODED_CHAR);

    return ret;
}

/* take a format string and a variable list of arguments
   and populate the command arguments array */
static unsigned bc_precompile(cmdarg_t args[], const char *fmt, ...)
{
    va_list ap;
    unsigned n = 0;

    va_start(ap, fmt);
    for (n = 0; *fmt; fmt++, n++) {
        args[n].type = *fmt;

        switch (*fmt) {
        case 'i':
            args[n].u.i = va_arg(ap, int);
            break;
        case 's':
            args[n].u.s = va_arg(ap, const char *);
            break;
        case 'S':
            args[n].u.sa = va_arg(ap, const strarray_t *);
            break;
        case 'U':
            args[n].u.ua = va_arg(ap, const arrayu64_t *);
            break;
        case 't':
            args[n].u.t = va_arg(ap, const test_t *);
            break;
        case 'T':
            args[n].u.tl = va_arg(ap, const testlist_t *);
            break;
        case 'C': {
            /* Expand the comparator into its component parts */
            const comp_t *c = va_arg(ap, const comp_t *);

            args[n].type = AT_INT;
            args[n].u.i = c->match;
            args[++n].type = AT_INT;
            args[n].u.i = c->relation;
            args[++n].type = AT_INT;
            args[n].u.i = c->collation;
            break;
        }
        case 'Z': {
            /* Expand the zone into its component parts */
            const zone_t *z = va_arg(ap, const zone_t *);

            args[n].type = AT_INT;
            args[n].u.i = z->tag;

            if (z->tag == B_TIMEZONE) {
                args[++n].type = AT_STR;
                args[n].u.s = z->offset;
            }
            break;
        }
        default: assert(*fmt);
        }
    }
    va_end(ap);

    return n;
}

static commandlist_t *build_keep(sieve_script_t *sscript, commandlist_t *c)
{
    assert(c && c->type == B_KEEP);

    if (c->u.k.flags && !_verify_flaglist(c->u.k.flags)) {
        strarray_add(c->u.k.flags, "");
    }

    c->nargs = bc_precompile(c->args, "S", c->u.k.flags);

    return c;
}

static commandlist_t *build_fileinto(sieve_script_t *sscript,
                                     commandlist_t *c, char *folder)
{
    assert(c && c->type == B_FILEINTO);

    if (c->u.f.flags && !_verify_flaglist(c->u.f.flags)) {
        strarray_add(c->u.f.flags, "");
    }
    verify_mailbox(sscript, folder);
    c->u.f.folder = folder;

    c->nargs = bc_precompile(c->args, "ssiSis",
                             c->u.f.mailboxid,
                             c->u.f.specialuse,
                             c->u.f.create,
                             c->u.f.flags,
                             c->u.f.copy,
                             c->u.f.folder);

    return c;
}

static commandlist_t *build_redirect(sieve_script_t *sscript,
                                     commandlist_t *c, char *address)
{
    assert(c && c->type == B_REDIRECT);

    if (c->u.r.list) verify_list(sscript, address);
    else verify_address(sscript, address);

    /* Verify DELIVERBY values */
    if (c->u.r.bytime) {
        if (!supported(SIEVE_CAPA_VARIABLES)) {
            time_t t;

            if (c->u.r.bytime[0] != '+' &&
                time_from_iso8601(c->u.r.bytime, &t) == -1) {
                sieveerror_f(sscript,
                             "string '%s': not a valid DELIVERBY time value",
                             c->u.r.bytime);
            }
            if (c->u.r.bymode &&
                strcasecmp(c->u.r.bymode, "NOTIFY") &&
                strcasecmp(c->u.r.bymode, "RETURN")) {
                sieveerror_f(sscript,
                             "string '%s': not a valid DELIVERBY mode value",
                             c->u.r.bymode);
            }
        }
    }
    else if (c->u.r.bymode || c->u.r.bytrace) {
        sieveerror_c(sscript, SIEVE_MISSING_TAG,
                     ":bytimerelative OR :bytimeabsolute");
    }

    /* Verify DSN NOTIFY value(s) */
    if (c->u.r.dsn_notify && !supported(SIEVE_CAPA_VARIABLES)) {
        tok_t tok =
            TOK_INITIALIZER(c->u.r.dsn_notify, ",", TOK_TRIMLEFT|TOK_TRIMRIGHT);
        char *token;
        int never = 0;

        while ((token = tok_next(&tok))) {
            if (!strcasecmp(token, "NEVER")) never = 1;
            else if (never) {
                sieveerror_f(sscript,
                             "DSN NOTIFY value 'NEVER' MUST be used by itself");
                break;
            }
            else if (strcasecmp(token, "SUCCESS") &&
                     strcasecmp(token, "FAILURE") &&
                     strcasecmp(token, "DELAY")) {
                sieveerror_f(sscript,
                             "string '%s': not a valid DSN NOTIFY value",
                             token);
                break;
            }
        }
        tok_fini(&tok);
    }

    /* Verify DSN RET value */
    if (c->u.r.dsn_ret && !supported(SIEVE_CAPA_VARIABLES) &&
        strcasecmp(c->u.r.dsn_ret, "FULL") &&
        strcasecmp(c->u.r.dsn_ret, "HDRS")) {
        sieveerror_f(sscript, "string '%s': not a valid DSN RET value",
                     c->u.r.dsn_ret);
    }

    c->u.r.address = address;

    c->nargs = bc_precompile(c->args, "ssissiis",
                             c->u.r.bytime,
                             c->u.r.bymode,
                             c->u.r.bytrace,
                             c->u.r.dsn_notify,
                             c->u.r.dsn_ret,
                             c->u.r.list,
                             c->u.r.copy,
                             c->u.r.address);

    return c;
}

static int verify_identifier(sieve_script_t *sscript, char *s)
{
    /* identifier         = (ALPHA / "_") *(ALPHA / DIGIT / "_") */

    if (!is_identifier(s)) {
        sieveerror_f(sscript,
                     "string '%s': not a valid sieve identifier", s);
        return 0;
    }
    return 1;
}

static commandlist_t *build_set(sieve_script_t *sscript,
                                commandlist_t *c, char *variable, char *value)
{
    assert(c && c->type == B_SET);

    verify_identifier(sscript, variable);
    verify_utf8(sscript, value);

    c->u.s.variable = variable;
    c->u.s.value = value;

    c->nargs = bc_precompile(c->args, "iss",
                             c->u.s.modifiers,
                             c->u.s.variable,
                             c->u.s.value);

    return c;
}

static commandlist_t *build_vacation(sieve_script_t *sscript,
                                     commandlist_t *c, char *message)
{
    int min = sscript->interp.vacation->min_response;
    int max = sscript->interp.vacation->max_response;

    assert(c && c->type == B_VACATION);

    if (c->u.v.handle) verify_utf8(sscript, c->u.v.handle);
    if (c->u.v.subject) verify_utf8(sscript, c->u.v.subject);
    if (c->u.v.from) verify_address(sscript, c->u.v.from);
    if (c->u.v.addresses)
        verify_stringlist(sscript, c->u.v.addresses, verify_address);
    if (c->u.v.mime == -1) {
        verify_utf8(sscript, message);
        c->u.v.mime = 0;
    }
    if (c->u.v.fcc.folder) {
        verify_mailbox(sscript, c->u.v.fcc.folder);
        if (c->u.v.fcc.flags && !_verify_flaglist(c->u.v.fcc.flags)) {
            strarray_add(c->u.v.fcc.flags, "");
        }
    }
    else if (c->u.v.fcc.create || c->u.v.fcc.flags ||
             c->u.v.fcc.specialuse || c->u.v.fcc.mailboxid) {
        sieveerror_c(sscript, SIEVE_MISSING_TAG, ":fcc");
    }

    c->u.v.message = message;

    if (c->u.v.seconds == -1) c->u.v.seconds = 7 * DAY2SEC;
    if (c->u.v.seconds < min) c->u.v.seconds = min;
    if (c->u.v.seconds > max) c->u.v.seconds = max;

    c->nargs = bc_precompile(c->args,
                             c->u.v.fcc.folder ? "SssiisssiSss" : "Sssiisss",
                             c->u.v.addresses,
                             c->u.v.subject,
                             c->u.v.message,
                             c->u.v.seconds,
                             c->u.v.mime,
                             c->u.v.from,
                             c->u.v.handle,
                             c->u.v.fcc.folder,
                             c->u.v.fcc.create,
                             c->u.v.fcc.flags,
                             c->u.v.fcc.specialuse,
                             c->u.v.fcc.mailboxid);

    return c;
}

static commandlist_t *build_flag(sieve_script_t *sscript,
                                 commandlist_t *c, strarray_t *flags)
{
    assert(c && (c->type == B_SETFLAG ||
                 c->type == B_ADDFLAG ||
                 c->type == B_REMOVEFLAG));

    if (!_verify_flaglist(flags)) {
        strarray_add(flags, "");
    }
    c->u.fl.flags = flags;

    if (!c->u.fl.variable) c->u.fl.variable = xstrdup("");
    else if (!is_identifier(c->u.fl.variable)) {
        sieveerror_c(sscript, SIEVE_INVALID_VALUE, "variablename");
    }

    c->nargs = bc_precompile(c->args, "sS",
                             c->u.fl.variable,
                             c->u.fl.flags);

    return c;
}

static commandlist_t *build_addheader(sieve_script_t *sscript,
                                      commandlist_t *c, char *name, char *value)
{
    assert(c && c->type == B_ADDHEADER);

    verify_header(sscript, name);
    verify_utf8(sscript, value);

    if (c->u.ah.index == 0) c->u.ah.index = 1;
    c->u.ah.name = name;
    c->u.ah.value = value;

    c->nargs = bc_precompile(c->args, "iss",
                             c->u.ah.index,
                             c->u.ah.name,
                             c->u.ah.value);

    return c;
}

static commandlist_t *build_deleteheader(sieve_script_t *sscript,
                                         commandlist_t *c,
                                         char *name, strarray_t *values)
{
    assert(c && c->type == B_DELETEHEADER);

    if (!strcasecmp("Received", name) || !strcasecmp("Auto-Submitted", name)) {
        sieveerror_f(sscript,
                     "MUST NOT delete Received or Auto-Submitted headers");
    }
    else if (c->u.dh.comp.index == INT_MIN) {
        sieveerror_c(sscript, SIEVE_MISSING_TAG, ":index");
    }

    verify_header(sscript, name);
    verify_patternlist(sscript, values, &c->u.dh.comp, verify_utf8);

    c->u.dh.name = name;
    c->u.dh.values = values;

    c->nargs = bc_precompile(c->args, "iCsS",
                             c->u.dh.comp.index,
                             &c->u.dh.comp,
                             c->u.dh.name,
                             c->u.dh.values);

    return c;
}

static int verify_weekday(sieve_script_t *sscript, char *day)
{
    int n = day[0] - '0';

    if (n >= 0 && n <= 6 && day[1] == '\0') {
        return (1 << n);
    }

    sieveerror_f(sscript, "'%s': not a valid weekday for snooze", day);
    return 0;
}

static int verify_time(sieve_script_t *sscript, char *time)
{
    struct tm tm;
    int t = 0;
    char *r = strptime(time, "%T", &tm);

    if (r && *r == '\0') {
        t = 3600 * tm.tm_hour + 60 * tm.tm_min + tm.tm_sec;
    }
    else {
        sieveerror_f(sscript, "'%s': not a valid time for snooze", time);
    }

    free(time);  /* done with this string */

    return t;
}

static commandlist_t *build_snooze(sieve_script_t *sscript,
                                   commandlist_t *c, arrayu64_t *times)
{
    assert(c && c->type == B_SNOOZE);

    if (c->u.sn.f.folder) verify_mailbox(sscript, c->u.sn.f.folder);
    if (c->u.sn.addflags && !_verify_flaglist(c->u.sn.addflags)) {
        strarray_add(c->u.sn.addflags, "");
    }
    if (c->u.sn.removeflags && !_verify_flaglist(c->u.sn.removeflags)) {
        strarray_add(c->u.sn.removeflags, "");
    }
    if (!c->u.sn.days) c->u.sn.days = 0x7f; /* all days */

    /* Sort times earliest -> latest */
    arrayu64_sort(times, NULL/*ascending*/);
    c->u.sn.times = times;

    c->nargs = bc_precompile(c->args, "sssiSSisU",
                             c->u.sn.f.folder,
                             c->u.sn.f.mailboxid,
                             c->u.sn.f.specialuse,
                             c->u.sn.f.create,
                             c->u.sn.addflags,
                             c->u.sn.removeflags,
                             c->u.sn.days,
                             c->u.sn.tzid,
                             c->u.sn.times);

    return c;
}

static commandlist_t *build_rej_err(sieve_script_t *sscript,
                                    int t, char *message)
{
    commandlist_t *c;

    assert(t == B_REJECT || t == B_EREJECT || t == B_ERROR);

    verify_utf8(sscript, message);

    c = new_command(t, sscript);
    c->u.str = message;

    c->nargs = bc_precompile(c->args, "s", c->u.str);

    return c;
}

static commandlist_t *build_notify(sieve_script_t *sscript, int t,
                                   commandlist_t *c, char *method)
{
    assert(c && (t == B_NOTIFY || t == B_ENOTIFY));

    if (t == B_ENOTIFY) {
        if (!supported(SIEVE_CAPA_ENOTIFY)) {
            sieveerror_c(sscript, SIEVE_MISSING_REQUIRE, "enotify");
        }
        if (c->u.n.id != NULL) {
            sieveerror_c(sscript, SIEVE_UNEXPECTED_TAG, ":id");
        }
        if (c->u.n.method != NULL) {
            sieveerror_c(sscript, SIEVE_UNEXPECTED_TAG, ":method");
        }
        if (c->u.n.fcc.folder) {
            verify_mailbox(sscript, c->u.n.fcc.folder);
            if (c->u.n.fcc.flags && !_verify_flaglist(c->u.n.fcc.flags)) {
                strarray_add(c->u.n.fcc.flags, "");
            }
        }
        else if (c->u.n.fcc.create || c->u.n.fcc.flags ||
                 c->u.n.fcc.specialuse || c->u.n.fcc.mailboxid) {
            sieveerror_c(sscript, SIEVE_MISSING_TAG, ":fcc");
        }

        c->u.n.method = method;
    }
    else {
        if (!supported(SIEVE_CAPA_NOTIFY)) {
            sieveerror_c(sscript, SIEVE_MISSING_REQUIRE, "notify");
        }
        if (c->u.n.from != NULL) {
            sieveerror_c(sscript, SIEVE_UNEXPECTED_TAG, ":from");
        }
        if (c->u.n.fcc.folder != NULL) {
            sieveerror_c(sscript, SIEVE_UNEXPECTED_TAG, ":fcc");
        }
        if (c->u.n.fcc.create != 0) {
            sieveerror_c(sscript, SIEVE_UNEXPECTED_TAG, ":create");
        }
        if (c->u.n.fcc.flags != NULL) {
            sieveerror_c(sscript, SIEVE_UNEXPECTED_TAG, ":flags");
        }
        if (c->u.n.fcc.specialuse != NULL) {
            sieveerror_c(sscript, SIEVE_UNEXPECTED_TAG, ":specialuse");
        }

        if (!c->u.n.method) c->u.n.method = xstrdup("default");
    }

    c->type = t;
    if (c->u.n.priority == -1) c->u.n.priority = B_NORMAL;
    if (!c->u.n.message) c->u.n.message = xstrdup("$from$: $subject$");

    c->nargs = bc_precompile(c->args, "ssSis",
                             c->u.n.method,
                             (c->type == B_ENOTIFY) ? c->u.n.from : c->u.n.id,
                             c->u.n.options,
                             c->u.n.priority,
                             c->u.n.message);

    return c;
}

static commandlist_t *build_denotify(sieve_script_t *sscript,
                                     commandlist_t *t)
{
    assert(t && t->type == B_DENOTIFY);

    canon_comptags(&t->u.d.comp, sscript);

    if (t->u.d.priority == -1) t->u.d.priority = B_ANY;
    if (t->u.d.pattern) {
        strarray_t sa = STRARRAY_INITIALIZER;

        strarray_pushm(&sa, t->u.d.pattern);
        verify_patternlist(sscript, &sa, &t->u.d.comp, NULL);
        strarray_pop(&sa);
        strarray_fini(&sa);
    }

    t->nargs = bc_precompile(t->args, "iiis",
                             t->u.d.priority,
                             t->u.d.comp.match,
                             t->u.d.comp.relation,
                             t->u.d.pattern);

    return t;
}

static commandlist_t *build_include(sieve_script_t *sscript,
                                    commandlist_t *c, char *script)
{
    assert(c && c->type == B_INCLUDE);

    if (strchr(script, '/')) {
        sieveerror_c(sscript, SIEVE_INVALID_VALUE, "script-name");
    }

    c->u.inc.script = script;
    if (c->u.inc.once == -1) c->u.inc.once = 0;
    if (c->u.inc.location == -1) c->u.inc.location = B_PERSONAL;
    if (c->u.inc.optional == -1) c->u.inc.optional = 0;

    c->nargs = bc_precompile(c->args, "is",
                             c->u.inc.location |
                                 (c->u.inc.once | c->u.inc.optional),
                             c->u.inc.script);

    return c;
}

static commandlist_t *build_log(sieve_script_t *sscript, char *text)
{
    commandlist_t *c;

    verify_utf8(sscript, text);

    c = new_command(B_LOG, sscript);
    c->u.l.text = text;

    c->nargs = bc_precompile(c->args, "s", c->u.l.text);

    return c;
}

static test_t *build_anyof(sieve_script_t *sscript, testlist_t *tl)
{
    test_t *t;

    assert(tl);

    if (tl->next == NULL) {
        /* collapse single item list into a simple test */
        t = tl->t;
        free(tl);
    }
    else {
        test_t *fail = NULL, *maybe = NULL;

        /* create ANYOF test */
        t = new_test(BC_ANYOF, sscript);
        t->u.tl = tl;

        /* find first test that did/didn't set ignore_err */
        for ( ; tl && !fail && !maybe; tl = tl->next) {
            if (tl->t->ignore_err) {
                if (!fail) fail = tl->t;
            }
            else if (!maybe) maybe = tl->t;
        }

        if (fail) {
            if (maybe) {
                /* test may succeed - backout ignore_err */
                sscript->ignore_err = --fail->ignore_err;
            }
            else {
                /* test will fail - revert ignore_err to first value */
                sscript->ignore_err = t->ignore_err = fail->ignore_err;
            }
        }

        t->nargs = bc_precompile(t->args, "T", t->u.tl);
    }

    return t;
}

static test_t *build_allof(sieve_script_t *sscript, testlist_t *tl)
{
    test_t *t;

    assert(tl);

    if (tl->next == NULL) {
        /* collapse single item list into a simple test */
        t = tl->t;
        free(tl);
    }
    else {
        /* create ALLOF test */
        t = new_test(BC_ALLOF, sscript);
        t->u.tl = tl;

        /* find first test that set ignore_err and revert to that value */
        for ( ; tl; tl = tl->next) {
            if (tl->t->ignore_err) {
                sscript->ignore_err = t->ignore_err = tl->t->ignore_err;
                break;
            }
        }

        t->nargs = bc_precompile(t->args, "T", t->u.tl);
    }

    return t;
}

static test_t *build_not(sieve_script_t *sscript, test_t *t)
{
    test_t *n;

    assert(t);

    if (t->ignore_err) {
        /* test will succeed - backout ignore_err */
        sscript->ignore_err = --t->ignore_err;
    }

    n = new_test(BC_NOT, sscript);
    n->u.t = t;

    n->nargs = bc_precompile(n->args, "t", n->u.t);

    return n;
}

static test_t *build_hhs(sieve_script_t *sscript, test_t *t,
                         strarray_t *sl, strarray_t *pl)
{
    assert(t);

    verify_patternlist(sscript, pl, &t->u.hhs.comp, verify_utf8);

    t->u.hhs.sl = sl;
    t->u.hhs.pl = pl;

    t->nargs += bc_precompile(t->args + t->nargs, "CSS",
                              &t->u.hhs.comp,
                              t->u.hhs.sl,
                              t->u.hhs.pl);

    return t;
}

static test_t *build_header(sieve_script_t *sscript, test_t *t,
                            strarray_t *sl, strarray_t *pl)
{
    assert(t && t->type == BC_HEADER);

    if (t->u.hhs.comp.index == INT_MIN) {
        sieveerror_c(sscript, SIEVE_MISSING_TAG, ":index");
    }

    verify_stringlist(sscript, sl, verify_header);

    t->nargs = bc_precompile(t->args, "i", t->u.hhs.comp.index);

    return build_hhs(sscript, t, sl, pl);
}

static test_t *build_stringt(sieve_script_t *sscript, test_t *t,
                             strarray_t *sl, strarray_t *pl)
{
    assert(t && t->type == BC_STRING);

    verify_stringlist(sscript, sl, verify_utf8);

    return build_hhs(sscript, t, sl, pl);
}

static test_t *build_hasflag(sieve_script_t *sscript, test_t *t,
                             strarray_t *sl, strarray_t *pl)
{
    assert(t && t->type == BC_HASFLAG);

    if (sl) {
        if (!supported(SIEVE_CAPA_VARIABLES)) {
            sieveerror_c(sscript, SIEVE_MISSING_REQUIRE, "variables");
        }

        verify_stringlist(sscript, sl, verify_identifier);
    }

    return build_hhs(sscript, t, sl, pl);
}

static test_t *build_ae(sieve_script_t *sscript, test_t *t,
                        strarray_t *sl, strarray_t *pl)
{
    assert(t);

    verify_patternlist(sscript, pl, &t->u.ae.comp, NULL);

    if (t->u.ae.addrpart == -1) t->u.ae.addrpart = B_ALL;
    t->u.ae.sl = sl;
    t->u.ae.pl = pl;

    t->nargs += bc_precompile(t->args + t->nargs, "CiSS",
                              &t->u.ae.comp,
                              t->u.ae.addrpart,
                              t->u.ae.sl,
                              t->u.ae.pl);

    return t;
}

static test_t *build_address(sieve_script_t *sscript, test_t *t,
                             strarray_t *sl, strarray_t *pl)
{
    assert(t && t->type == BC_ADDRESS);

    if (t->u.ae.comp.index == INT_MIN) {
        sieveerror_c(sscript, SIEVE_MISSING_TAG, ":index");
    }

    verify_stringlist(sscript, sl, verify_addrheader);

    t->nargs = bc_precompile(t->args, "i", t->u.ae.comp.index);

    return build_ae(sscript, t, sl, pl);
}

static test_t *build_envelope(sieve_script_t *sscript, test_t *t,
                              strarray_t *sl, strarray_t *pl)
{
    assert(t && t->type == BC_ENVELOPE);

    verify_stringlist(sscript, sl, verify_envelope);

    return build_ae(sscript, t, sl, pl);
}

static test_t *build_body(sieve_script_t *sscript,
                          test_t *t, strarray_t *pl)
{
    assert(t && (t->type == BC_BODY));

    verify_patternlist(sscript, pl, &t->u.b.comp, verify_utf8);

    if (t->u.b.offset == -1) t->u.b.offset = 0;
    if (t->u.b.transform == -1) t->u.b.transform = B_TEXT;
    if (t->u.b.content_types == NULL) {
        t->u.b.content_types = strarray_new();
        strarray_append(t->u.b.content_types,
                        (t->u.b.transform == B_RAW) ? "" : "text");
    }
    t->u.b.pl = pl;

    t->nargs = bc_precompile(t->args, "CiiSS",
                             &t->u.b.comp,
                             t->u.b.transform,
                             t->u.b.offset,
                             t->u.b.content_types,
                             t->u.b.pl);

    return t;
}

static const struct {
    const char *name;
    unsigned bytecode;
} date_parts[] = {
    { "year",    B_YEAR    },
    { "month",   B_MONTH   },
    { "day",     B_DAY     },
    { "date",    B_DATE    },
    { "julian",  B_JULIAN  },
    { "hour",    B_HOUR    },
    { "minute",  B_MINUTE  },
    { "second",  B_SECOND  },
    { "time",    B_TIME    },
    { "iso8601", B_ISO8601 },
    { "std11",   B_STD11   },
    { "zone",    B_ZONE    },
    { "weekday", B_WEEKDAY },
    { NULL,      0         }
};

static int verify_date_part(sieve_script_t *sscript, char *part)
{
    int i;

    for (i = 0; date_parts[i].name && strcasecmp(date_parts[i].name, part); i++);

    if (!date_parts[i].name) {
        sieveerror_f(sscript, "invalid date-part '%s'", part);
    }

    return date_parts[i].bytecode;
}

static test_t *build_date(sieve_script_t *sscript,
                          test_t *t, char *hn, char *part, strarray_t *kl)
{
    assert(t && (t->type == BC_DATE || t->type == BC_CURRENTDATE));

    if (hn) verify_header(sscript, hn);
    verify_patternlist(sscript, kl, &t->u.dt.comp, NULL);

    if (t->u.dt.comp.index == 0) {
        t->u.dt.comp.index = 1;
    }
    else if (t->u.dt.comp.index == INT_MIN) {
        sieveerror_c(sscript, SIEVE_MISSING_TAG, ":index");
    }

    if (t->u.dt.zone.tag == -1) {
        t->u.dt.zone.tag = B_TIMEZONE;
    }

    t->u.dt.date_part = verify_date_part(sscript, part);
    t->u.dt.header_name = hn;
    t->u.dt.kl = kl;

    if (t->type == BC_DATE) {
        t->nargs = bc_precompile(t->args, "iZCisS",
                                 t->u.dt.comp.index,
                                 &t->u.dt.zone,
                                 &t->u.dt.comp,
                                 t->u.dt.date_part,
                                 t->u.dt.header_name,
                                 t->u.dt.kl);
    }
    else {
        t->nargs = bc_precompile(t->args, "ZCiS",
                                 &t->u.dt.zone,
                                 &t->u.dt.comp,
                                 t->u.dt.date_part,
                                 t->u.dt.kl);
    }

    return t;
}

static test_t *build_ihave(sieve_script_t *sscript, strarray_t *sa)
{
    test_t *t;
    int i;

    t = new_test(BC_IHAVE, sscript);
    t->u.sl = sa;

    /* check if we support all listed extensions */
    for (i = 0; i < strarray_size(sa); i++) {
        unsigned long long capa = lookup_capability(strarray_nth(sa, i));

        if (!capa) {
            /* need to start ignoring errors immediately in case this ihave
               is part of a testlist with an unknown test later in the list */
            if (!t->ignore_err) t->ignore_err = ++sscript->ignore_err;
        }
        else if (capa & SIEVE_CAPA_IHAVE_INCOMPAT) {
            /* incompatible extension used in ihave - parse error */
            sscript->ignore_err = 0;
            sieveerror_c(sscript, SIEVE_IHAVE_INCOMPAT, strarray_nth(sa, i));
            break;
        }
    }

    t->nargs = bc_precompile(t->args, "S", t->u.sl);

    return t;
}

static test_t *build_mbox_meta(sieve_script_t *sscript,
                               test_t *t, char *extname,
                               char *keyname, strarray_t *keylist)
{
    assert(t);

    canon_comptags(&t->u.mm.comp, sscript);
    t->u.mm.extname = extname;
    t->u.mm.keyname = keyname;
    t->u.mm.keylist = keylist;

    switch (t->type) {
    case BC_MAILBOXEXISTS:
    case BC_MAILBOXIDEXISTS:
    case BC_SERVERMETADATAEXISTS:
        t->nargs = bc_precompile(t->args, "S",
                                 t->u.mm.keylist);
        break;

    case BC_METADATAEXISTS:
    case BC_SPECIALUSEEXISTS:
        t->nargs = bc_precompile(t->args, "sS",
                                 t->u.mm.extname,
                                 t->u.mm.keylist);
        break;

    case BC_SERVERMETADATA:
    case BC_ENVIRONMENT:
        t->nargs = bc_precompile(t->args, "CsS",
                                 &t->u.mm.comp,
                                 t->u.mm.keyname,
                                 t->u.mm.keylist);
        break;

    case BC_METADATA:
    case BC_NOTIFYMETHODCAPABILITY:
        t->nargs = bc_precompile(t->args, "CssS",
                                 &t->u.mm.comp,
                                 t->u.mm.extname,
                                 t->u.mm.keyname,
                                 t->u.mm.keylist);
        break;

    default:
        assert(0);
        break;
    }

    return t;
}

static test_t *build_duplicate(sieve_script_t *sscript, test_t *t)
{
    assert(t && t->type == BC_DUPLICATE);

    switch (t->u.dup.idtype) {
    case B_HEADER:
        verify_header(sscript, t->u.dup.idval);
        break;

    case B_UNIQUEID:
        verify_utf8(sscript, t->u.dup.idval);
        break;

    default:
        t->u.dup.idtype = B_HEADER;
        t->u.dup.idval = xstrdup("Message-ID");
        break;
    }

    if (!t->u.dup.handle) t->u.dup.handle = xstrdup("");
    else verify_utf8(sscript, t->u.dup.handle);

    if (t->u.dup.seconds == -1) t->u.dup.seconds = 7 * 86400; /* 7 days */

    t->nargs = bc_precompile(t->args, "issii",
                             t->u.dup.idtype,
                             t->u.dup.idval,
                             t->u.dup.handle,
                             t->u.dup.seconds,
                             t->u.dup.last);

    return t;
}

#ifdef WITH_JMAP
#include "imap/jmap_api.h"
#include "imap/jmap_mail_query_parse.h"

struct filter_rock {
    strarray_t *path;
    unsigned is_invalid;
};

static void filter_parser_invalid(const char *field, void *rock)
{
    struct filter_rock *frock = (struct filter_rock *) rock;

    if (!frock->is_invalid++) strarray_push(frock->path, field);
}

static void filter_parser_push_index(const char *field, size_t index,
                                     const char *name, void *rock)
{
    struct filter_rock *frock = (struct filter_rock *) rock;
    struct buf buf = BUF_INITIALIZER;

    if (!frock->is_invalid) {
        if (name) buf_printf(&buf, "%s[%zu:%s]", field, index, name);
        else buf_printf(&buf, "%s[%zu]", field, index);
        strarray_pushm(frock->path, buf_release(&buf));
    }
}

static void filter_parser_pop(void *rock)
{
    struct filter_rock *frock = (struct filter_rock *) rock;

    if (!frock->is_invalid) free(strarray_pop(frock->path));
}

static test_t *build_jmapquery(sieve_script_t *sscript, test_t *t, char *json)
{
    json_t *jquery;
    json_error_t jerr;

    assert(t && t->type == BC_JMAPQUERY);

    /* validate query */
    jquery = json_loads(json, 0, &jerr);
    if (jquery) {
        strarray_t path = STRARRAY_INITIALIZER;
        strarray_t capabilities = STRARRAY_INITIALIZER;
        struct filter_rock frock = { &path, 0 };
        jmap_email_filter_parse_ctx_t parse_ctx = {
            NULL,
            &filter_parser_invalid,
            &filter_parser_push_index,
            &filter_parser_pop,
            &capabilities,
            &frock
        };

        strarray_append(&capabilities, JMAP_URN_MAIL);
        strarray_append(&capabilities, JMAP_MAIL_EXTENSION);

        jmap_email_filter_parse(jquery, &parse_ctx);

        if (frock.is_invalid) {
            char *s = strarray_join(&path, "/");

            sieveerror_f(sscript, "invalid jmapquery argument: '%s'", s);
            free(s);
        }

        strarray_fini(&path);
        strarray_fini(&capabilities);
    }
    else {
        sieveerror_f(sscript, "invalid jmapquery format");
    }

    t->u.jquery = json_dumps(jquery, JSON_COMPACT);
    json_decref(jquery);

    free(json);  /* done with this string */

    t->nargs = bc_precompile(t->args, "s", t->u.jquery);

    return t;
}
#else
static test_t *build_jmapquery(sieve_script_t *sscript, test_t *t, char *json)
{
    sieveerror_c(sscript, SIEVE_UNSUPP_EXT, "vnd.cyrus.jmapquery");

    free(json);  /* done with this string */

    return t;
}
#endif /* WITH_JMAP */
