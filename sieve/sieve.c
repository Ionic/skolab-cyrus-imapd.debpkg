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
#include "sieve/comparator.h"
#include "sieve/interp.h"
#include "sieve/script.h"
#include "sieve/tree.h"
#include "sieve/flags.h"
#include "sieve/grammar.h"
#include "sieve/sieve_err.h"

#include "lib/gmtoff.h"
#include "util.h"
#include "imparse.h"
#include "libconfig.h"
#include "times.h"
#include "tok.h"

#define ERR_BUF_SIZE 1024

int encoded_char = 0;  /* used to send encoded-character feedback to lexer */
int getdatepart = 0;   /* used to send start state feedback to lexer */
static comp_t *ctags;  /* used for accessing comp_t* in a test/command union */

extern int addrparse(sieve_script_t*);
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE addr_scan_string(const char*);
extern void addr_delete_buffer(YY_BUFFER_STATE);

extern int sievelineno;

void sieveerror_c(sieve_script_t*, int code, ...);

static int check_reqs(sieve_script_t*, strarray_t *sl);
static int chk_match_vars(sieve_script_t*, char *s);

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
                          char *hn, int part, strarray_t *kl);
static test_t *build_ihave(sieve_script_t*, strarray_t *sa);
static test_t *build_mbox_meta(sieve_script_t*, test_t *t, char *extname,
                               char *keyname, strarray_t *keylist);
static test_t *build_duplicate(sieve_script_t*, test_t *t);
static test_t *build_jmapquery(sieve_script_t*, test_t *t, const char *json);

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

#line 228 "sieve/sieve.c" /* yacc.c:339  */

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
    TIMEZONE = 336,
    YEARP = 337,
    MONTHP = 338,
    DAYP = 339,
    DATEP = 340,
    JULIAN = 341,
    HOURP = 342,
    MINUTEP = 343,
    SECONDP = 344,
    TIMEP = 345,
    ISO8601 = 346,
    STD11 = 347,
    ZONEP = 348,
    WEEKDAYP = 349,
    INDEX = 350,
    LAST = 351,
    ADDHEADER = 352,
    DELETEHEADER = 353,
    REJCT = 354,
    EREJECT = 355,
    METHOD = 356,
    OPTIONS = 357,
    MESSAGE = 358,
    IMPORTANCE = 359,
    VALIDNOTIFYMETHOD = 360,
    NOTIFYMETHODCAPABILITY = 361,
    NOTIFY = 362,
    ENOTIFY = 363,
    ENCODEURL = 364,
    DENOTIFY = 365,
    ID = 366,
    ANY = 367,
    LOW = 368,
    NORMAL = 369,
    HIGH = 370,
    IHAVE = 371,
    ERROR = 372,
    MAILBOXEXISTS = 373,
    CREATE = 374,
    METADATA = 375,
    METADATAEXISTS = 376,
    SERVERMETADATA = 377,
    SERVERMETADATAEXISTS = 378,
    BYTIMEREL = 379,
    BYTIMEABS = 380,
    BYMODE = 381,
    BYTRACE = 382,
    DSNNOTIFY = 383,
    DSNRET = 384,
    VALIDEXTLIST = 385,
    LIST = 386,
    INCLUDE = 387,
    OPTIONAL = 388,
    ONCE = 389,
    RETURN = 390,
    PERSONAL = 391,
    GLOBAL = 392,
    DUPLICATE = 393,
    HEADER = 394,
    UNIQUEID = 395,
    SPECIALUSEEXISTS = 396,
    SPECIALUSE = 397,
    FCC = 398,
    MAILBOXID = 399,
    MAILBOXIDEXISTS = 400,
    LOG = 401,
    JMAPQUERY = 402,
    SNOOZE = 403,
    MAILBOX = 404,
    ADDFLAGS = 405,
    REMOVEFLAGS = 406,
    WEEKDAYS = 407
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
#define TIMEZONE 336
#define YEARP 337
#define MONTHP 338
#define DAYP 339
#define DATEP 340
#define JULIAN 341
#define HOURP 342
#define MINUTEP 343
#define SECONDP 344
#define TIMEP 345
#define ISO8601 346
#define STD11 347
#define ZONEP 348
#define WEEKDAYP 349
#define INDEX 350
#define LAST 351
#define ADDHEADER 352
#define DELETEHEADER 353
#define REJCT 354
#define EREJECT 355
#define METHOD 356
#define OPTIONS 357
#define MESSAGE 358
#define IMPORTANCE 359
#define VALIDNOTIFYMETHOD 360
#define NOTIFYMETHODCAPABILITY 361
#define NOTIFY 362
#define ENOTIFY 363
#define ENCODEURL 364
#define DENOTIFY 365
#define ID 366
#define ANY 367
#define LOW 368
#define NORMAL 369
#define HIGH 370
#define IHAVE 371
#define ERROR 372
#define MAILBOXEXISTS 373
#define CREATE 374
#define METADATA 375
#define METADATAEXISTS 376
#define SERVERMETADATA 377
#define SERVERMETADATAEXISTS 378
#define BYTIMEREL 379
#define BYTIMEABS 380
#define BYMODE 381
#define BYTRACE 382
#define DSNNOTIFY 383
#define DSNRET 384
#define VALIDEXTLIST 385
#define LIST 386
#define INCLUDE 387
#define OPTIONAL 388
#define ONCE 389
#define RETURN 390
#define PERSONAL 391
#define GLOBAL 392
#define DUPLICATE 393
#define HEADER 394
#define UNIQUEID 395
#define SPECIALUSEEXISTS 396
#define SPECIALUSE 397
#define FCC 398
#define MAILBOXID 399
#define MAILBOXIDEXISTS 400
#define LOG 401
#define JMAPQUERY 402
#define SNOOZE 403
#define MAILBOX 404
#define ADDFLAGS 405
#define REMOVEFLAGS 406
#define WEEKDAYS 407

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 170 "sieve/sieve.y" /* yacc.c:355  */

    int nval;
    char *sval;
    arrayu64_t *nl;
    strarray_t *sl;
    comp_t *ctag;
    test_t *test;
    testlist_t *testl;
    commandlist_t *cl;

#line 583 "sieve/sieve.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int sieveparse (sieve_script_t *sscript);

#endif /* !YY_SIEVE_SIEVE_SIEVE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 599 "sieve/sieve.c" /* yacc.c:358  */

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   722

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  161
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  119
/* YYNRULES -- Number of rules.  */
#define YYNRULES  321
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  438

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   407

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
     159,   160,     2,     2,   156,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   153,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   154,     2,   155,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   157,     2,   158,     2,     2,     2,     2,
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
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   358,   358,   359,   363,   364,   369,   370,   374,   375,
     376,   388,   389,   393,   394,   398,   399,   403,   410,   417,
     421,   422,   423,   427,   438,   439,   440,   444,   445,   452,
     453,   454,   455,   456,   458,   461,   465,   467,   470,   474,
     475,   478,   481,   482,   483,   484,   486,   491,   492,   497,
     531,   532,   533,   534,   535,   536,   541,   562,   591,   624,
     662,   663,   664,   676,   683,   693,   707,   720,   732,   748,
     760,   776,   777,   786,   795,   804,   813,   826,   827,   830,
     831,   834,   835,   845,   854,   859,   860,   869,   883,   893,
     904,   915,   924,   934,   938,   964,   965,   966,   971,   972,
     973,   978,   979,   998,   999,  1004,  1005,  1018,  1019,  1019,
    1020,  1020,  1021,  1021,  1022,  1022,  1027,  1028,  1039,  1042,
    1053,  1063,  1066,  1076,  1086,  1097,  1108,  1123,  1124,  1125,
    1130,  1131,  1141,  1141,  1150,  1151,  1160,  1169,  1182,  1183,
    1188,  1189,  1199,  1201,  1212,  1223,  1236,  1237,  1241,  1242,
    1246,  1250,  1251,  1255,  1256,  1260,  1267,  1274,  1278,  1279,
    1283,  1284,  1285,  1286,  1287,  1288,  1292,  1298,  1301,  1303,
    1306,  1308,  1312,  1319,  1321,  1325,  1325,  1328,  1330,  1335,
    1339,  1341,  1348,  1352,  1359,  1363,  1371,  1376,  1378,  1385,
    1392,  1399,  1404,  1409,  1410,  1415,  1416,  1416,  1417,  1417,
    1418,  1418,  1419,  1419,  1424,  1433,  1455,  1456,  1457,  1458,
    1469,  1470,  1475,  1476,  1477,  1478,  1479,  1480,  1485,  1504,
    1518,  1519,  1520,  1532,  1552,  1576,  1577,  1578,  1578,  1579,
    1579,  1580,  1580,  1581,  1581,  1586,  1601,  1602,  1603,  1604,
    1615,  1616,  1621,  1622,  1623,  1623,  1624,  1624,  1625,  1625,
    1630,  1631,  1631,  1632,  1632,  1637,  1638,  1648,  1661,  1661,
    1662,  1662,  1667,  1668,  1673,  1674,  1674,  1675,  1675,  1676,
    1676,  1681,  1682,  1682,  1683,  1683,  1688,  1689,  1690,  1699,
    1699,  1700,  1700,  1701,  1701,  1706,  1723,  1724,  1725,  1725,
    1726,  1726,  1731,  1732,  1733,  1734,  1735,  1736,  1737,  1738,
    1739,  1740,  1741,  1742,  1743,  1748,  1749,  1749,  1750,  1750,
    1755,  1756,  1756,  1757,  1757,  1762,  1763,  1775,  1785,  1794,
    1807,  1808
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
  "DATE", "CURRENTDATE", "ORIGINALZONE", "ZONE", "TIMEZONE", "YEARP",
  "MONTHP", "DAYP", "DATEP", "JULIAN", "HOURP", "MINUTEP", "SECONDP",
  "TIMEP", "ISO8601", "STD11", "ZONEP", "WEEKDAYP", "INDEX", "LAST",
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
  "WEEKDAYS", "';'", "'['", "']'", "','", "'{'", "'}'", "'('", "')'",
  "$accept", "start", "reqs", "commands", "command", "optstringlist",
  "stringlist", "strings", "string1", "string", "require", "control",
  "thenelse", "elsif", "block", "action", "ktags", "flags", "ftags",
  "copy", "create", "specialuse", "mailboxid", "rtags", "delbytags",
  "dsntags", "stags", "mod40", "mod30", "mod20", "mod15", "mod10", "vtags",
  "fcctags", "flagaction", "flagtags", "flagmark", "ahtags", "dhtags",
  "$@1", "$@2", "$@3", "$@4", "reject", "ntags", "priority", "dtags",
  "$@5", "itags", "location", "sntags", "weekdaylist", "weekdays",
  "weekday", "timelist", "times", "time1", "time", "testlist", "tests",
  "test", "$@6", "sizetag", "htags", "$@7", "$@8", "$@9", "$@10",
  "matchtype", "matchtag", "relmatch", "relation", "listmatch",
  "comparator", "collation", "idxtags", "atags", "$@11", "$@12", "$@13",
  "$@14", "addrpart", "addrparttag", "subaddress", "etags", "$@15", "$@16",
  "$@17", "envtags", "$@18", "$@19", "btags", "$@20", "$@21", "transform",
  "strtags", "$@22", "$@23", "$@24", "hftags", "$@25", "$@26", "dttags",
  "$@27", "$@28", "$@29", "zone", "cdtags", "$@30", "$@31", "datepart",
  "methtags", "$@32", "$@33", "mtags", "$@34", "$@35", "duptags", "idtype", YY_NULLPTR
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
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,    59,    91,    93,    44,   123,   125,    40,
      41
};
# endif

#define YYPACT_NINF -346

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-346)))

#define YYTABLE_NINF -314

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      29,     1,    13,   430,    29,  -346,    38,  -109,  -346,  -346,
    -346,  -102,   495,   -80,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,    38,  -346,  -346,    38,  -346,  -346,   270,  -346,   -77,
    -346,  -346,    38,  -346,   -87,  -346,  -346,  -346,  -346,   -81,
     -81,     1,   495,  -346,  -346,    76,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,     1,  -346,     1,     1,  -346,
      38,  -346,     1,     1,  -346,     1,     1,    38,  -346,   -76,
    -346,    17,    45,   105,   360,   253,     0,     2,   148,   -22,
     -49,    62,  -346,    23,  -346,  -346,     1,  -346,  -346,    38,
     495,  -346,  -346,  -346,  -346,  -346,  -346,   104,    -1,     4,
      11,     6,    37,     5,    30,    32,   561,  -346,    48,  -346,
    -346,    66,     1,    66,  -346,  -346,   160,  -346,     1,  -346,
    -346,   349,   119,     1,  -346,  -346,  -346,    38,    38,  -346,
    -346,  -346,  -346,  -346,  -346,   111,    38,    38,  -346,    38,
      38,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,    38,  -346,  -346,  -346,  -346,  -346,
     120,    38,    38,     1,  -346,    38,   134,    38,  -346,  -346,
    -346,  -346,  -346,  -346,    38,     1,   108,    35,   137,    51,
      38,    38,     1,    38,   -95,    38,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,   108,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,    38,     1,     1,     3,   174,  -346,  -346,  -346,
    -346,  -346,    28,  -346,    25,    44,  -346,     1,   108,    35,
     137,    51,  -346,  -346,  -346,  -346,  -346,     1,   108,    35,
     137,    51,  -346,  -346,  -346,     1,  -346,   108,    35,   137,
    -346,  -346,     1,  -346,   108,   137,  -346,     1,   108,   137,
       1,   108,    35,   137,     1,   108,   137,  -346,   107,  -346,
     108,   137,    51,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,   108,   137,
       1,    38,   108,   137,    38,   108,   137,  -346,     1,    38,
     190,  -346,  -346,  -346,    38,  -346,  -346,    49,   495,   -76,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,   222,  -346,
    -346,   157,  -346,   199,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,    38,  -346,  -346,  -346,  -346,   216,  -346,  -346,
      -6,  -346,  -346,   495,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,   616,  -346,  -346,  -346,  -346,  -346,  -346,     1,
    -346,  -346,     1,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,    56,  -346,  -346,   174,  -346,
       1,  -346,  -346,  -346,   216,  -346,  -346,  -346
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     0,     0,     4,    18,     0,     0,    13,    17,
       1,     0,     0,     0,    32,    47,    50,    60,    71,    85,
      98,    99,   100,   103,   104,   105,   107,   116,   117,   118,
     130,     0,   134,    46,     0,   140,     3,     0,     8,     0,
     101,    36,     0,     5,     0,    15,    19,    10,   192,     0,
       0,     0,     0,   163,   164,     0,   195,   225,   242,   255,
     250,   264,   271,   276,   286,     0,   305,     0,     0,   310,
       0,   310,     0,     0,   315,     0,     0,     0,    20,     0,
      21,    29,     0,     0,     0,     0,     0,   108,    41,   132,
       0,     0,    44,     0,     7,     9,     0,    39,    14,     0,
       0,   160,   161,   165,   162,   193,   194,     0,   196,   227,
     244,   258,   251,   265,   272,   279,   288,   178,   306,   180,
     181,   311,     0,   311,   185,   186,   187,   188,    17,   190,
     191,     0,    24,     0,    48,    56,    57,     0,     0,    30,
      52,    51,    53,    54,    55,     0,     0,     0,    68,     0,
       0,    62,    31,    61,    63,    64,    82,    77,    78,    79,
      80,    81,    84,    83,     0,    72,    73,    74,    75,    76,
       0,     0,     0,     0,    91,     0,     0,     0,    34,    96,
      95,    97,    93,   106,     0,    11,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   127,   128,   129,    40,
     121,   124,   131,     0,    22,   137,   136,   138,   139,    43,
     135,   156,     0,     0,     0,     0,     0,   142,    45,   151,
     155,    35,   102,    16,     0,   158,   166,     0,     0,     0,
       0,     0,   236,   237,   238,   240,   241,     0,     0,     0,
       0,     0,   226,   235,   239,     0,   243,     0,     0,     0,
     262,   263,     0,   170,     0,     0,   256,     0,     0,     0,
       0,     0,     0,     0,   174,     0,     0,   278,     0,   175,
       0,     0,     0,   277,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   287,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   183,     0,     0,
       0,   319,   320,   321,     0,   189,    28,     0,     0,     0,
      23,    49,    58,    59,    65,    66,    67,    69,    70,    33,
      86,    88,    89,    90,    92,    87,    94,    37,    38,    12,
     206,   207,   208,   209,   210,   211,   109,   204,     0,   218,
     111,     0,   113,     0,   224,   115,   119,   123,   126,   125,
     120,   122,     0,   141,   143,   144,   150,     0,   145,   146,
       0,   153,   157,     0,   167,   197,   199,   201,   203,   168,
     228,   230,   232,   234,   169,   245,   247,   249,   257,   259,
     261,   171,   252,   254,   172,   266,   268,   270,   173,   273,
     275,   285,     0,   280,   282,   284,   289,   291,   177,     0,
     307,   309,     0,   312,   314,   184,   317,   318,   316,    27,
      25,    26,   214,   215,   216,   217,   212,   213,   205,   220,
     221,   222,   219,   223,   133,     0,   148,   152,     0,   159,
       0,   179,   182,   147,     0,   154,   176,   149
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -346,  -346,   217,   -26,  -346,  -346,   -51,  -346,   219,    33,
    -346,  -346,   -86,  -346,   -82,  -346,  -346,   133,  -346,   152,
     155,   156,   147,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,   153,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,   -88,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -345,  -346,  -346,    26,  -185,   194,  -117,
     -50,  -346,  -346,  -346,  -346,  -346,  -346,  -346,   332,  -346,
    -346,  -346,  -174,   426,  -346,  -188,  -346,  -346,  -346,  -346,
    -346,   138,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,  -346,
    -346,  -346,  -346,  -346,  -346,  -346,   139,  -346,  -346,  -346,
    -139,  -346,  -346,  -346,   183,  -346,  -346,  -346,  -346
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    36,    37,   328,     7,    44,     8,     9,
       4,    38,    78,   310,   132,    39,    81,   179,    82,   141,
     180,   181,   144,    83,   154,   155,    84,   165,   166,   167,
     168,   169,    85,   182,    40,    96,    41,    86,    87,   186,
     187,   188,   189,    42,    88,   201,    89,   203,    91,   210,
      93,   358,   425,   359,   218,   360,   219,   220,   101,   224,
      79,   392,   107,   108,   228,   229,   230,   231,   336,   337,
     338,   418,   340,   342,   422,   345,   109,   238,   239,   240,
     241,   242,   243,   244,   110,   247,   248,   249,   112,   258,
     259,   111,   254,   255,   256,   113,   261,   262,   263,   114,
     265,   266,   115,   270,   271,   272,   273,   116,   288,   289,
     290,   118,   292,   293,   121,   295,   296,   126,   304
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     103,   202,   104,     5,     5,     5,     5,   356,     5,     5,
       5,    94,   426,    10,   117,     5,   119,   120,   196,   197,
     198,   124,   125,  -200,   127,   129,  -112,   211,  -231,  -269,
    -260,   232,   233,   234,     5,  -248,     5,     1,   232,   233,
     234,     5,     5,   368,    46,   221,   250,   251,   252,     5,
     225,    47,     5,   373,  -274,   366,  -281,   227,   237,   245,
     253,  -253,   260,   264,    90,   371,     5,    92,    98,    99,
       5,   297,  -308,    80,   376,    97,    95,   305,   100,   235,
     236,   131,   311,   135,   395,   133,   235,   236,   386,   437,
    -313,   196,   197,   198,  -202,  -202,   183,  -114,  -114,  -233,
    -233,   105,   106,   122,   204,   307,   350,   226,   128,     5,
     130,   267,   268,   133,   314,   139,   152,   164,   178,   184,
     185,   199,   323,   320,   209,   308,   309,  -283,  -283,   222,
    -198,   -42,   223,  -110,   329,  -229,  -267,   325,   330,   331,
     332,   348,  -246,   135,   333,   257,   343,   344,   269,   427,
     428,   291,     5,     6,   294,     6,   298,   357,     6,     6,
       6,   341,   354,   355,   136,     6,   339,   138,   334,   335,
     312,   313,   212,   213,   214,   215,   364,   216,   211,   315,
     316,   -17,   317,   318,     6,   362,   369,   137,   391,   138,
     419,   420,   421,   407,   374,   205,   206,   319,   207,   208,
     363,   378,   423,   190,   321,   322,   381,   409,   324,   384,
     326,   433,   434,   388,   134,   140,   133,   327,   299,   300,
     356,    43,   410,   346,   347,    45,   349,   411,   351,   145,
     146,   147,   148,   149,   150,   153,   151,   142,   143,   398,
     217,   200,   361,   435,   102,   353,   429,   405,   246,   191,
     192,   193,   194,   430,   123,   287,   301,     5,     0,   195,
       0,   196,   197,   198,     0,     0,     0,   136,     0,     0,
      -6,    11,     0,     0,     0,    12,     0,     0,     0,    13,
      14,    15,    16,    17,   412,   413,   414,   415,   416,   417,
     137,   177,     0,     0,     0,     0,     0,     0,     0,   302,
     303,     0,     0,     0,     0,     0,   170,   171,   172,   173,
     174,   175,   176,   225,     0,    18,     0,     0,     0,     0,
       0,   133,    19,     0,   399,     0,     0,   402,     0,     0,
       0,     0,   406,     0,     0,     0,     0,   408,     0,     0,
      20,    21,    22,    23,    24,     0,     0,     0,   431,     0,
      11,   432,     0,     0,    12,     0,     0,     0,    13,    14,
      15,    16,    17,     0,     5,     0,     0,    25,    26,    27,
      28,     0,   136,     0,     0,     0,     0,    29,     0,   436,
      30,     0,     0,     0,     0,   424,     0,    31,     0,     0,
       0,     0,     0,     0,    18,   137,   177,   156,     0,     0,
       0,    19,    32,     0,     0,    33,   157,   158,   159,   160,
     161,   162,     0,     0,     0,     0,    34,     0,    35,    20,
      21,    22,    23,    24,     0,     0,     0,     0,    -6,     0,
      -2,    11,     0,     0,     0,    12,     0,     0,     0,    13,
      14,    15,    16,    17,     0,     0,    25,    26,    27,    28,
       0,     0,     0,     0,     0,     0,    29,     0,     0,    30,
       0,     0,     0,     0,     0,     0,    31,     0,     0,   163,
       0,     0,     0,     0,     0,    18,     0,     0,     0,     0,
       0,    32,    19,     0,    33,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,    48,    35,     0,     0,
      20,    21,    22,    23,    24,     0,     0,   306,     0,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,     0,
       0,     0,     0,     0,     0,     0,     0,    25,    26,    27,
      28,     0,     0,     0,    59,   352,     0,    29,    60,    61,
      30,     0,     0,     0,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     365,     0,    32,     0,    62,    33,     0,     0,     0,     0,
     370,     0,    63,    64,     0,     0,    34,     0,    35,   375,
       0,     0,     0,     0,     0,  -290,   379,     0,     0,     0,
     382,     0,     0,   385,     0,     0,     0,   389,     0,     0,
      65,    66,   393,     0,     0,     0,     0,     0,     0,     0,
       0,    67,     0,    68,     0,    69,    70,    71,    72,     0,
     396,     0,     0,     0,   400,    73,     0,   403,     0,     0,
       0,     0,     0,    74,     0,     0,    75,     0,     0,     0,
      76,   268,    77,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   367,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   372,     0,     0,     0,
       0,     0,     0,     0,     0,   377,     0,     0,     0,     0,
       0,   380,     0,     0,     0,   383,     0,     0,     0,   387,
       0,     0,   390,     0,     0,     0,     0,   394,   274,   275,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,     0,     0,     0,     0,   397,     0,     0,     0,   401,
       0,     0,   404
};

static const yytype_int16 yycheck[] =
{
      51,    89,    52,     4,     4,     4,     4,     4,     4,     4,
       4,    37,   357,     0,    65,     4,    67,    68,   113,   114,
     115,    72,    73,    24,    75,    76,    24,     4,    24,    24,
      24,    27,    28,    29,     4,    24,     4,     8,    27,    28,
      29,     4,     4,   231,   153,    96,    40,    41,    42,     4,
     100,   153,     4,   241,    24,   229,    24,   108,   109,   110,
     111,    24,   113,   114,    31,   239,     4,    34,   155,   156,
       4,   122,    24,   153,   248,    42,   153,   128,   159,    75,
      76,   157,   133,    38,   272,    68,    75,    76,   262,   434,
      24,   113,   114,   115,    95,    96,    96,    95,    96,    95,
      96,    25,    26,    70,   153,   131,   194,     3,    75,     4,
      77,    79,    80,    68,     3,    82,    83,    84,    85,    86,
      87,    88,   173,     3,    91,     6,     7,    95,    96,    96,
     131,   153,    99,   131,   185,   131,   131,     3,    30,    31,
      32,   192,   131,    38,    36,   112,    95,    96,   115,   155,
     156,   118,     4,   154,   121,   154,   123,   154,   154,   154,
     154,    24,   213,   214,   119,   154,   131,   144,    60,    61,
     137,   138,   149,   150,   151,   152,   227,   154,     4,   146,
     147,   153,   149,   150,   154,   160,   237,   142,    81,   144,
      33,    34,    35,     3,   245,   133,   134,   164,   136,   137,
     156,   252,     3,    55,   171,   172,   257,   158,   175,   260,
     177,   155,   156,   264,    81,    82,    68,   184,    58,    59,
       4,     4,   308,   190,   191,     6,   193,   309,   195,   124,
     125,   126,   127,   128,   129,    83,   131,    82,    82,   290,
      93,    88,   216,   428,    50,   212,   363,   298,   110,   101,
     102,   103,   104,   392,    71,   116,    96,     4,    -1,   111,
      -1,   113,   114,   115,    -1,    -1,    -1,   119,    -1,    -1,
       0,     1,    -1,    -1,    -1,     5,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    62,    63,    64,    65,    66,    67,
     142,   143,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   139,
     140,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    59,   363,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    68,    52,    -1,   291,    -1,    -1,   294,    -1,    -1,
      -1,    -1,   299,    -1,    -1,    -1,    -1,   304,    -1,    -1,
      70,    71,    72,    73,    74,    -1,    -1,    -1,   399,    -1,
       1,   402,    -1,    -1,     5,    -1,    -1,    -1,     9,    10,
      11,    12,    13,    -1,     4,    -1,    -1,    97,    98,    99,
     100,    -1,   119,    -1,    -1,    -1,    -1,   107,    -1,   430,
     110,    -1,    -1,    -1,    -1,   352,    -1,   117,    -1,    -1,
      -1,    -1,    -1,    -1,    45,   142,   143,    37,    -1,    -1,
      -1,    52,   132,    -1,    -1,   135,    46,    47,    48,    49,
      50,    51,    -1,    -1,    -1,    -1,   146,    -1,   148,    70,
      71,    72,    73,    74,    -1,    -1,    -1,    -1,   158,    -1,
       0,     1,    -1,    -1,    -1,     5,    -1,    -1,    -1,     9,
      10,    11,    12,    13,    -1,    -1,    97,    98,    99,   100,
      -1,    -1,    -1,    -1,    -1,    -1,   107,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,   117,    -1,    -1,   109,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,   132,    52,    -1,   135,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   146,     1,   148,    -1,    -1,
      70,    71,    72,    73,    74,    -1,    -1,   158,    -1,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    97,    98,    99,
     100,    -1,    -1,    -1,    39,   203,    -1,   107,    43,    44,
     110,    -1,    -1,    -1,    -1,    -1,    -1,   117,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     228,    -1,   132,    -1,    69,   135,    -1,    -1,    -1,    -1,
     238,    -1,    77,    78,    -1,    -1,   146,    -1,   148,   247,
      -1,    -1,    -1,    -1,    -1,    24,   254,    -1,    -1,    -1,
     258,    -1,    -1,   261,    -1,    -1,    -1,   265,    -1,    -1,
     105,   106,   270,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   116,    -1,   118,    -1,   120,   121,   122,   123,    -1,
     288,    -1,    -1,    -1,   292,   130,    -1,   295,    -1,    -1,
      -1,    -1,    -1,   138,    -1,    -1,   141,    -1,    -1,    -1,
     145,    80,   147,    82,    83,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,   230,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   240,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   249,    -1,    -1,    -1,    -1,
      -1,   255,    -1,    -1,    -1,   259,    -1,    -1,    -1,   263,
      -1,    -1,   266,    -1,    -1,    -1,    -1,   271,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    -1,    -1,    -1,    -1,   289,    -1,    -1,    -1,   293,
      -1,    -1,   296
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint16 yystos[] =
{
       0,     8,   162,   163,   171,     4,   154,   167,   169,   170,
       0,     1,     5,     9,    10,    11,    12,    13,    45,    52,
      70,    71,    72,    73,    74,    97,    98,    99,   100,   107,
     110,   117,   132,   135,   146,   148,   164,   165,   172,   176,
     195,   197,   204,   163,   168,   169,   153,   153,     1,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    39,
      43,    44,    69,    77,    78,   105,   106,   116,   118,   120,
     121,   122,   123,   130,   138,   141,   145,   147,   173,   221,
     153,   177,   179,   184,   187,   193,   198,   199,   205,   207,
     170,   209,   170,   211,   164,   153,   196,   170,   155,   156,
     159,   219,   219,   167,   221,    25,    26,   223,   224,   237,
     245,   252,   249,   256,   260,   263,   268,   167,   272,   167,
     167,   275,   170,   275,   167,   167,   278,   167,   170,   167,
     170,   157,   175,    68,   178,    38,   119,   142,   144,   170,
     178,   180,   181,   182,   183,   124,   125,   126,   127,   128,
     129,   131,   170,   180,   185,   186,    37,    46,    47,    48,
      49,    50,    51,   109,   170,   188,   189,   190,   191,   192,
      53,    54,    55,    56,    57,    58,    59,   143,   170,   178,
     181,   182,   194,    96,   170,   170,   200,   201,   202,   203,
      55,   101,   102,   103,   104,   111,   113,   114,   115,   170,
     194,   206,   206,   208,   153,   133,   134,   136,   137,   170,
     210,     4,   149,   150,   151,   152,   154,   183,   215,   217,
     218,   167,   170,   170,   220,   221,     3,   167,   225,   226,
     227,   228,    27,    28,    29,    75,    76,   167,   238,   239,
     240,   241,   242,   243,   244,   167,   242,   246,   247,   248,
      40,    41,    42,   167,   253,   254,   255,   170,   250,   251,
     167,   257,   258,   259,   167,   261,   262,    79,    80,   170,
     264,   265,   266,   267,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,   267,   269,   270,
     271,   170,   273,   274,   170,   276,   277,   167,   170,    58,
      59,    96,   139,   140,   279,   167,   158,   164,     6,     7,
     174,   167,   170,   170,     3,   170,   170,   170,   170,   170,
       3,   170,   170,   167,   170,     3,   170,   170,   166,   167,
      30,    31,    32,    36,    60,    61,   229,   230,   231,   131,
     233,    24,   234,    95,    96,   236,   170,   170,   167,   170,
     206,   170,   229,   170,   167,   167,     4,   154,   212,   214,
     216,   217,   160,   156,   167,   229,   233,   234,   236,   167,
     229,   233,   234,   236,   167,   229,   233,   234,   167,   229,
     234,   167,   229,   234,   167,   229,   233,   234,   167,   229,
     234,    81,   222,   229,   234,   236,   229,   234,   167,   170,
     229,   234,   170,   229,   234,   167,   170,     3,   170,   158,
     173,   175,    62,    63,    64,    65,    66,    67,   232,    33,
      34,    35,   235,     3,   170,   213,   214,   155,   156,   220,
     271,   167,   167,   155,   156,   218,   167,   214
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint16 yyr1[] =
{
       0,   161,   162,   162,   163,   163,   164,   164,   165,   165,
     165,   166,   166,   167,   167,   168,   168,   169,   170,   171,
     172,   172,   172,   173,   174,   174,   174,   175,   175,   176,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   176,   176,   176,   177,   177,   178,
     179,   179,   179,   179,   179,   179,   180,   181,   182,   183,
     184,   184,   184,   184,   184,   185,   185,   185,   185,   186,
     186,   187,   187,   187,   187,   187,   187,   188,   188,   189,
     189,   190,   190,   191,   192,   193,   193,   193,   193,   193,
     193,   193,   193,   193,   194,   194,   194,   194,   195,   195,
     195,   196,   196,   197,   197,   198,   198,   199,   200,   199,
     201,   199,   202,   199,   203,   199,   204,   204,   205,   205,
     205,   205,   205,   205,   205,   205,   205,   206,   206,   206,
     207,   207,   208,   207,   209,   209,   209,   209,   210,   210,
     211,   211,   211,   211,   211,   211,   212,   212,   213,   213,
     214,   215,   215,   216,   216,   217,   218,   219,   220,   220,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   222,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   223,   223,   224,   225,   224,   226,   224,
     227,   224,   228,   224,   229,   229,   230,   230,   230,   230,
     231,   231,   232,   232,   232,   232,   232,   232,   233,   234,
     235,   235,   235,   236,   236,   237,   237,   238,   237,   239,
     237,   240,   237,   241,   237,   242,   243,   243,   243,   243,
     244,   244,   245,   245,   246,   245,   247,   245,   248,   245,
     249,   250,   249,   251,   249,   252,   252,   252,   253,   252,
     254,   252,   255,   255,   256,   257,   256,   258,   256,   259,
     256,   260,   261,   260,   262,   260,   263,   263,   263,   264,
     263,   265,   263,   266,   263,   267,   268,   268,   269,   268,
     270,   268,   271,   271,   271,   271,   271,   271,   271,   271,
     271,   271,   271,   271,   271,   272,   273,   272,   274,   272,
     275,   276,   275,   277,   275,   278,   278,   278,   278,   278,
     279,   279
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     2,     1,     2,
       2,     0,     1,     1,     3,     1,     3,     1,     1,     3,
       2,     2,     3,     3,     0,     2,     2,     3,     2,     2,
       3,     3,     1,     4,     3,     3,     1,     4,     4,     2,
       3,     2,     2,     3,     2,     3,     1,     0,     2,     2,
       0,     2,     2,     2,     2,     2,     1,     1,     2,     2,
       0,     2,     2,     2,     2,     2,     2,     2,     1,     2,
       2,     0,     2,     2,     2,     2,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     3,     3,     3,     3,
       3,     2,     3,     2,     2,     1,     1,     1,     1,     1,
       1,     0,     2,     1,     1,     0,     2,     0,     0,     3,
       0,     3,     0,     3,     0,     3,     1,     1,     0,     3,
       3,     2,     3,     3,     2,     3,     3,     1,     1,     1,
       0,     2,     0,     4,     0,     2,     2,     2,     1,     1,
       0,     3,     2,     3,     3,     3,     1,     3,     1,     3,
       1,     1,     3,     1,     3,     1,     1,     3,     1,     3,
       2,     2,     2,     1,     1,     2,     3,     4,     4,     4,
       3,     4,     4,     4,     3,     0,     6,     4,     2,     5,
       2,     2,     5,     3,     4,     2,     2,     2,     2,     3,
       2,     2,     1,     1,     1,     0,     0,     3,     0,     3,
       0,     3,     0,     3,     1,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     2,     1,     0,     2,     0,     3,     0,
       3,     0,     3,     0,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     2,     0,     3,     0,     3,     0,     3,
       0,     0,     3,     0,     3,     0,     2,     3,     0,     3,
       0,     3,     1,     1,     0,     0,     3,     0,     3,     0,
       3,     0,     0,     3,     0,     3,     0,     2,     2,     0,
       3,     0,     3,     0,     3,     2,     0,     2,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     0,     3,     0,     3,
       0,     0,     3,     0,     3,     0,     3,     3,     3,     2,
       1,     1
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, sieve_script_t *sscript)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (sscript);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, sieve_script_t *sscript)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, sscript);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule, sieve_script_t *sscript)
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
#line 164 "sieve/sieve.y" /* yacc.c:1257  */
      { free(((*yyvaluep).sval));          }
#line 1875 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 164: /* commands  */
#line 160 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1881 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 165: /* command  */
#line 160 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1887 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 166: /* optstringlist  */
#line 163 "sieve/sieve.y" /* yacc.c:1257  */
      { strarray_free(((*yyvaluep).sl)); }
#line 1893 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 167: /* stringlist  */
#line 163 "sieve/sieve.y" /* yacc.c:1257  */
      { strarray_free(((*yyvaluep).sl)); }
#line 1899 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 168: /* strings  */
#line 163 "sieve/sieve.y" /* yacc.c:1257  */
      { strarray_free(((*yyvaluep).sl)); }
#line 1905 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 169: /* string1  */
#line 163 "sieve/sieve.y" /* yacc.c:1257  */
      { strarray_free(((*yyvaluep).sl)); }
#line 1911 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 170: /* string  */
#line 164 "sieve/sieve.y" /* yacc.c:1257  */
      { free(((*yyvaluep).sval));          }
#line 1917 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 172: /* control  */
#line 160 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1923 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 173: /* thenelse  */
#line 160 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1929 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 174: /* elsif  */
#line 160 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1935 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 175: /* block  */
#line 160 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1941 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 176: /* action  */
#line 160 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1947 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 215: /* timelist  */
#line 165 "sieve/sieve.y" /* yacc.c:1257  */
      { arrayu64_free(((*yyvaluep).nl)); }
#line 1953 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 216: /* times  */
#line 165 "sieve/sieve.y" /* yacc.c:1257  */
      { arrayu64_free(((*yyvaluep).nl)); }
#line 1959 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 217: /* time1  */
#line 165 "sieve/sieve.y" /* yacc.c:1257  */
      { arrayu64_free(((*yyvaluep).nl)); }
#line 1965 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 219: /* testlist  */
#line 161 "sieve/sieve.y" /* yacc.c:1257  */
      { free_testlist(((*yyvaluep).testl)); }
#line 1971 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 220: /* tests  */
#line 161 "sieve/sieve.y" /* yacc.c:1257  */
      { free_testlist(((*yyvaluep).testl)); }
#line 1977 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 221: /* test  */
#line 162 "sieve/sieve.y" /* yacc.c:1257  */
      { free_test(((*yyvaluep).test));     }
#line 1983 "sieve/sieve.c" /* yacc.c:1257  */
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
#line 358 "sieve/sieve.y" /* yacc.c:1646  */
    { sscript->cmds = NULL; }
#line 2251 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 3:
#line 359 "sieve/sieve.y" /* yacc.c:1646  */
    { sscript->cmds = (yyvsp[0].cl); }
#line 2257 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 7:
#line 370 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = (yyvsp[-1].cl); (yyval.cl)->next = (yyvsp[0].cl); }
#line 2263 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 10:
#line 376 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     struct buf buf = BUF_INITIALIZER;
                                     buf_printf(&buf, "%s: line %d",
                                                error_message(SIEVE_UNSUPP_EXT),
                                                sievelineno);
                                     sscript->support |= SIEVE_CAPA_IHAVE;
                                     (yyval.cl) = build_rej_err(sscript, ERROR,
                                                        buf_release(&buf));
                                 }
#line 2277 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 11:
#line 388 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.sl) = strarray_new(); }
#line 2283 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 14:
#line 394 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.sl) = (yyvsp[-1].sl); }
#line 2289 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 16:
#line 399 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.sl) = (yyvsp[-2].sl); strarray_appendm((yyval.sl), (yyvsp[0].sval)); }
#line 2295 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 17:
#line 403 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.sl) = strarray_new();
                                     strarray_appendm((yyval.sl), (yyvsp[0].sval));
                                 }
#line 2304 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 18:
#line 410 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.sval) = (yyvsp[0].sval); chk_match_vars(sscript, (yyval.sval)); }
#line 2310 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 19:
#line 417 "sieve/sieve.y" /* yacc.c:1646  */
    { check_reqs(sscript, (yyvsp[-1].sl)); }
#line 2316 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 20:
#line 421 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = (yyvsp[0].cl); }
#line 2322 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 21:
#line 422 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(STOP, sscript); }
#line 2328 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 22:
#line 423 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_rej_err(sscript, ERROR, (yyvsp[-1].sval)); }
#line 2334 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 23:
#line 427 "sieve/sieve.y" /* yacc.c:1646  */
    { 
                                     if ((yyvsp[-2].test)->ignore_err) {
                                         /* end of block - decrement counter */
                                         sscript->ignore_err--;
                                     }

                                     (yyval.cl) = new_if((yyvsp[-2].test), (yyvsp[-1].cl), (yyvsp[0].cl));
                                 }
#line 2347 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 24:
#line 438 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = NULL; }
#line 2353 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 25:
#line 439 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = (yyvsp[0].cl); }
#line 2359 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 26:
#line 440 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = (yyvsp[0].cl); }
#line 2365 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 27:
#line 444 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = (yyvsp[-1].cl); }
#line 2371 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 28:
#line 445 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = NULL; }
#line 2377 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 29:
#line 452 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_keep(sscript, (yyvsp[0].cl)); }
#line 2383 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 30:
#line 453 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_fileinto(sscript, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2389 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 31:
#line 454 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_redirect(sscript, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2395 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 32:
#line 455 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(DISCARD, sscript); }
#line 2401 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 33:
#line 457 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_set(sscript, (yyvsp[-2].cl), (yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 2407 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 34:
#line 458 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_vacation(sscript, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2413 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 35:
#line 462 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_flag(sscript, (yyvsp[-1].cl), (yyvsp[0].sl)); }
#line 2419 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 36:
#line 465 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command((yyvsp[0].nval), sscript); }
#line 2425 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 37:
#line 468 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_addheader(sscript,
                                                        (yyvsp[-2].cl), (yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 2432 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 38:
#line 471 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_deleteheader(sscript,
                                                           (yyvsp[-2].cl), (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 2439 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 39:
#line 474 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_rej_err(sscript, (yyvsp[-1].nval), (yyvsp[0].sval)); }
#line 2445 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 40:
#line 475 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_notify(sscript,
                                                     ENOTIFY, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2452 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 41:
#line 478 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_notify(sscript,
                                                     NOTIFY, (yyvsp[0].cl), NULL); }
#line 2459 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 42:
#line 481 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_denotify(sscript, (yyvsp[0].cl)); }
#line 2465 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 43:
#line 482 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_include(sscript, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2471 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 44:
#line 483 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_log(sscript, (yyvsp[0].sval)); }
#line 2477 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 45:
#line 485 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = build_snooze(sscript, (yyvsp[-1].cl), (yyvsp[0].nl)); }
#line 2483 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 46:
#line 486 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(RETURN, sscript); }
#line 2489 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 47:
#line 491 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(KEEP, sscript); }
#line 2495 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 49:
#line 497 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     /* $0 refers to ktags, ftags, or vtags */
                                     commandlist_t *c = (yyvsp[-2].cl);
                                     strarray_t **flags = NULL;

                                     switch (c->type) {
                                     case KEEP:
                                         flags = &c->u.k.flags; break;
                                     case FILEINTO:
                                         flags = &c->u.f.flags; break;
                                     case VACATION:
                                         flags = &c->u.v.fcc.flags; break;
                                     case ENOTIFY:
                                         flags = &c->u.n.fcc.flags; break;
                                     }

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
#line 2530 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 50:
#line 531 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(FILEINTO, sscript); }
#line 2536 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 56:
#line 541 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     /* $0 refers to ftags or rtags */
                                     commandlist_t *c = (yyvsp[-1].cl);
                                     int *copy = (c->type == FILEINTO) ?
                                         &c->u.f.copy : &c->u.r.copy;

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
#line 2558 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 57:
#line 562 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     /* $0 refers to ftags or vtags */
                                     commandlist_t *c = (yyvsp[-1].cl);
                                     int *create = NULL;

                                     switch (c->type) {
                                     case FILEINTO:
                                         create = &c->u.f.create; break;
                                     case VACATION:
                                         create = &c->u.v.fcc.create; break;
                                     case ENOTIFY:
                                         create = &c->u.n.fcc.create; break;
                                     }

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
#line 2588 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 58:
#line 591 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     /* $0 refers to ftags or vtags */
                                     commandlist_t *c = (yyvsp[-2].cl);
                                     char **specialuse = NULL;

                                     switch (c->type) {
                                     case FILEINTO:
                                         specialuse = &c->u.f.specialuse;
                                         break;
                                     case VACATION:
                                         specialuse = &c->u.v.fcc.specialuse;
                                         break;
                                     case ENOTIFY:
                                         specialuse = &c->u.n.fcc.specialuse;
                                         break;
                                     }

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
#line 2624 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 59:
#line 624 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     /* $0 refers to ftags, sntags or vtags */
                                     commandlist_t *c = (yyvsp[-2].cl);
                                     char **mailboxid = NULL;

                                     switch (c->type) {
                                     case FILEINTO:
                                         mailboxid = &c->u.f.mailboxid;
                                         break;
                                     case SNOOZE:
                                         mailboxid = &c->u.sn.mailbox;
                                         break;
                                     case VACATION:
                                         mailboxid = &c->u.v.fcc.mailboxid;
                                         break;
                                     case ENOTIFY:
                                         mailboxid = &c->u.n.fcc.mailboxid;
                                         break;
                                     }

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
#line 2663 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 60:
#line 662 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(REDIRECT, sscript); }
#line 2669 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 62:
#line 664 "sieve/sieve.y" /* yacc.c:1646  */
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
#line 2686 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 63:
#line 676 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!supported(SIEVE_CAPA_REDIR_DELBY)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "redirect-deliverby");
                                     }
                                 }
#line 2698 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 64:
#line 683 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!supported(SIEVE_CAPA_REDIR_DSN)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "redirect-dsn");
                                     }
                                 }
#line 2710 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 65:
#line 693 "sieve/sieve.y" /* yacc.c:1646  */
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
#line 2729 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 66:
#line 707 "sieve/sieve.y" /* yacc.c:1646  */
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
#line 2747 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 67:
#line 720 "sieve/sieve.y" /* yacc.c:1646  */
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
#line 2764 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 68:
#line 732 "sieve/sieve.y" /* yacc.c:1646  */
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
#line 2781 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 69:
#line 748 "sieve/sieve.y" /* yacc.c:1646  */
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
#line 2798 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 70:
#line 760 "sieve/sieve.y" /* yacc.c:1646  */
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
#line 2815 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 71:
#line 776 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(SET, sscript); }
#line 2821 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 72:
#line 777 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.s.mod40) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "precedence 40 modifier");
                                     }

                                     (yyval.cl)->u.s.mod40 = (yyvsp[0].nval);
                                 }
#line 2835 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 73:
#line 786 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.s.mod30) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "precedence 30 modifier");
                                     }

                                     (yyval.cl)->u.s.mod30 = (yyvsp[0].nval);
                                 }
#line 2849 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 74:
#line 795 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.s.mod20) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "precedence 20 modifier");
                                     }

                                     (yyval.cl)->u.s.mod20 = (yyvsp[0].nval);
                                 }
#line 2863 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 75:
#line 804 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.s.mod15) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "precedence 15 modifier");
                                     }

                                     (yyval.cl)->u.s.mod15 = (yyvsp[0].nval);
                                 }
#line 2877 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 76:
#line 813 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.s.mod10) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "precedence 10 modifier");
                                     }

                                     (yyval.cl)->u.s.mod10 = (yyvsp[0].nval);
                                 }
#line 2891 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 82:
#line 835 "sieve/sieve.y" /* yacc.c:1646  */
    { 
                                     if (!supported(SIEVE_CAPA_REGEX)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "regex");
                                     }
                                 }
#line 2903 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 83:
#line 845 "sieve/sieve.y" /* yacc.c:1646  */
    { 
                                     if (!supported(SIEVE_CAPA_ENOTIFY)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "enotify");
                                     }
                                 }
#line 2915 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 85:
#line 859 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(VACATION, sscript); }
#line 2921 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 86:
#line 860 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.v.seconds != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":days");
                                     }

                                     (yyval.cl)->u.v.seconds = (yyvsp[0].nval) * DAY2SEC;
                                 }
#line 2935 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 87:
#line 869 "sieve/sieve.y" /* yacc.c:1646  */
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
#line 2954 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 88:
#line 883 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.v.subject != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":subject");
                                         free((yyval.cl)->u.v.subject);
                                     }

                                     (yyval.cl)->u.v.subject = (yyvsp[0].sval);
                                 }
#line 2969 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 89:
#line 893 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.v.from != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":from");
                                         free((yyval.cl)->u.v.from);
                                     }

                                     (yyval.cl)->u.v.from = (yyvsp[0].sval);
                                 }
#line 2984 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 90:
#line 905 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.v.addresses != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":addresses");
                                         strarray_free((yyval.cl)->u.v.addresses);
                                     }

                                     (yyval.cl)->u.v.addresses = (yyvsp[0].sl);
                                 }
#line 2999 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 91:
#line 915 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.v.mime != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":mime");
                                     }

                                     (yyval.cl)->u.v.mime = 1;
                                 }
#line 3013 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 92:
#line 924 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.v.handle != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":handle");
                                         free((yyval.cl)->u.v.handle);
                                     }

                                     (yyval.cl)->u.v.handle = (yyvsp[0].sval);
                                 }
#line 3028 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 94:
#line 938 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     /* $0 refers to vtags or ntags */
                                     commandlist_t *c = (yyvsp[-2].cl);
                                     char **folder = NULL;

                                     switch (c->type) {
                                     case VACATION:
                                         folder = &c->u.v.fcc.folder; break;
                                     case ENOTIFY:
                                         folder = &c->u.n.fcc.folder; break;
                                     }

                                     if (*folder != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":fcc");
                                         free(*folder);
                                     }
                                     else if (!supported(SIEVE_CAPA_FCC)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "fcc");
                                     }

                                     *folder = (yyvsp[0].sval);
                                 }
#line 3059 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 101:
#line 978 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command((yyvsp[0].nval), sscript); }
#line 3065 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 102:
#line 979 "sieve/sieve.y" /* yacc.c:1646  */
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
#line 3085 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 105:
#line 1004 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(ADDHEADER, sscript); }
#line 3091 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 106:
#line 1005 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.ah.index < 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":last");
                                     }

                                     (yyval.cl)->u.ah.index = -1;
                                 }
#line 3105 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 107:
#line 1018 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(DELETEHEADER, sscript);}
#line 3111 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 108:
#line 1019 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].cl)->u.dh.comp); }
#line 3117 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 110:
#line 1020 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].cl)->u.dh.comp); }
#line 3123 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 112:
#line 1021 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].cl)->u.dh.comp); }
#line 3129 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 114:
#line 1022 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].cl)->u.dh.comp); }
#line 3135 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 118:
#line 1039 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(ENOTIFY, sscript); }
#line 3141 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 119:
#line 1042 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.n.from != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":from");
                                         free((yyval.cl)->u.n.from);
                                     }

                                     (yyval.cl)->u.n.from = (yyvsp[0].sval);
                                 }
#line 3156 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 120:
#line 1054 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.n.priority != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":importance");
                                     }

                                     (yyval.cl)->u.n.priority = (yyvsp[0].nval);
                                 }
#line 3170 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 122:
#line 1066 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.n.id != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":id");
                                         free((yyval.cl)->u.n.id);
                                     }

                                     (yyval.cl)->u.n.id = (yyvsp[0].sval);
                                 }
#line 3185 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 123:
#line 1076 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.n.method != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":method");
                                         free((yyval.cl)->u.n.method);
                                     }

                                     (yyval.cl)->u.n.method = (yyvsp[0].sval);
                                 }
#line 3200 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 124:
#line 1086 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.n.priority != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "priority");
                                     }

                                     (yyval.cl)->u.n.priority = (yyvsp[0].nval);
                                 }
#line 3214 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 125:
#line 1097 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.n.message != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":message");
                                         free((yyval.cl)->u.n.message);
                                     }

                                     (yyval.cl)->u.n.message = (yyvsp[0].sval);
                                 }
#line 3229 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 126:
#line 1109 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.n.options != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":options");
                                         strarray_free((yyval.cl)->u.n.options);
                                     }

                                     (yyval.cl)->u.n.options = (yyvsp[0].sl);
                                 }
#line 3244 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 130:
#line 1130 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(DENOTIFY, sscript); }
#line 3250 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 131:
#line 1131 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.d.priority != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "priority");
                                     }

                                     (yyval.cl)->u.d.priority = (yyvsp[0].nval);
                                 }
#line 3264 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 132:
#line 1141 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].cl)->u.d.comp); }
#line 3270 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 133:
#line 1142 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.d.pattern) free((yyval.cl)->u.d.pattern);
                                     (yyval.cl)->u.d.pattern = (yyvsp[0].sval);
                                 }
#line 3279 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 134:
#line 1150 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(INCLUDE, sscript); }
#line 3285 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 135:
#line 1151 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.inc.location != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "location");
                                     }

                                     (yyval.cl)->u.inc.location = (yyvsp[0].nval);
                                 }
#line 3299 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 136:
#line 1160 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.inc.once != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":once");
                                     }

                                     (yyval.cl)->u.inc.once = 1;
                                 }
#line 3313 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 137:
#line 1169 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.inc.optional != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":optional");
                                     }

                                     (yyval.cl)->u.inc.optional = 1;
                                 }
#line 3327 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 140:
#line 1188 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl) = new_command(SNOOZE, sscript); }
#line 3333 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 141:
#line 1189 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.sn.mailbox != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":mailbox");
                                         free((yyval.cl)->u.sn.mailbox);
                                     }

                                     (yyval.cl)->u.sn.mailbox = (yyvsp[0].sval);
                                 }
#line 3348 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 142:
#line 1199 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.cl)->u.sn.is_mboxid = 1; }
#line 3354 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 143:
#line 1202 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.sn.addflags != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":addflags");
                                         free((yyval.cl)->u.sn.addflags);
                                     }

                                     (yyval.cl)->u.sn.addflags = (yyvsp[0].sl);
                                 }
#line 3369 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 144:
#line 1213 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.sn.removeflags != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":removeflags");
                                         free((yyval.cl)->u.sn.removeflags);
                                     }

                                     (yyval.cl)->u.sn.removeflags = (yyvsp[0].sl);
                                 }
#line 3384 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 145:
#line 1224 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.cl)->u.sn.days != 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":weekdays");
                                     }

                                     (yyval.cl)->u.sn.days = (yyvsp[0].nval);
                                 }
#line 3398 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 147:
#line 1237 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = (yyvsp[-1].nval); }
#line 3404 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 149:
#line 1242 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = (yyvsp[-2].nval) | (yyvsp[0].nval); }
#line 3410 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 150:
#line 1246 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = verify_weekday(sscript, (yyvsp[0].sval)); }
#line 3416 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 152:
#line 1251 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nl) = (yyvsp[-1].nl); }
#line 3422 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 154:
#line 1256 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nl) = (yyvsp[-2].nl); arrayu64_add((yyval.nl), (yyvsp[0].nval)); }
#line 3428 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 155:
#line 1260 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.nl) = arrayu64_new();
                                     arrayu64_add((yyval.nl), (yyvsp[0].nval));
                                 }
#line 3437 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 156:
#line 1267 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.nval) = verify_time(sscript, (yyvsp[0].sval)); }
#line 3443 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 157:
#line 1274 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.testl) = (yyvsp[-1].testl); }
#line 3449 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 158:
#line 1278 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.testl) = new_testlist((yyvsp[0].test), NULL); }
#line 3455 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 159:
#line 1279 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.testl) = new_testlist((yyvsp[-2].test), (yyvsp[0].testl)); }
#line 3461 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 160:
#line 1283 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_anyof(sscript, (yyvsp[0].testl)); }
#line 3467 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 161:
#line 1284 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_allof(sscript, (yyvsp[0].testl)); }
#line 3473 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 162:
#line 1285 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_not(sscript, (yyvsp[0].test));   }
#line 3479 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 163:
#line 1286 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(SFALSE, sscript); }
#line 3485 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 164:
#line 1287 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(STRUE, sscript);  }
#line 3491 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 165:
#line 1288 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.test) = new_test(EXISTS, sscript);
                                     (yyval.test)->u.sl = (yyvsp[0].sl);
                                 }
#line 3500 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 166:
#line 1292 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.test) = new_test(SIZE, sscript);
                                     (yyval.test)->u.sz.t = (yyvsp[-1].nval);
                                     (yyval.test)->u.sz.n = (yyvsp[0].nval);
                                 }
#line 3510 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 167:
#line 1299 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_header(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3516 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 168:
#line 1302 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_address(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3522 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 169:
#line 1304 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_envelope(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3528 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 170:
#line 1306 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_body(sscript, (yyvsp[-1].test), (yyvsp[0].sl)); }
#line 3534 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 171:
#line 1309 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_mbox_meta(sscript,
                                                        (yyvsp[-2].test), NULL, (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3541 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 172:
#line 1313 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_stringt(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3547 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 173:
#line 1320 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_hasflag(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3553 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 174:
#line 1322 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_hasflag(sscript, (yyvsp[-1].test), NULL, (yyvsp[0].sl)); }
#line 3559 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 175:
#line 1325 "sieve/sieve.y" /* yacc.c:1646  */
    { getdatepart = 1; }
#line 3565 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 176:
#line 1326 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_date(sscript, (yyvsp[-4].test), (yyvsp[-3].sval), (yyvsp[-1].nval), (yyvsp[0].sl)); }
#line 3571 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 177:
#line 1329 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_date(sscript, (yyvsp[-2].test), NULL, (yyvsp[-1].nval), (yyvsp[0].sl)); }
#line 3577 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 178:
#line 1331 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.test) = new_test(VALIDNOTIFYMETHOD, sscript);
                                     (yyval.test)->u.sl = (yyvsp[0].sl);
                                 }
#line 3586 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 179:
#line 1336 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_mbox_meta(sscript,
                                                        (yyvsp[-3].test), (yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3593 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 180:
#line 1339 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_ihave(sscript, (yyvsp[0].sl)); }
#line 3599 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 181:
#line 1342 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.test) = new_test(MAILBOXEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), NULL, NULL, (yyvsp[0].sl));
                                 }
#line 3609 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 182:
#line 1349 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_mbox_meta(sscript,
                                                        (yyvsp[-3].test), (yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3616 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 183:
#line 1353 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.test) = new_test(METADATAEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), (yyvsp[-1].sval), NULL, (yyvsp[0].sl));
                                 }
#line 3626 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 184:
#line 1360 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_mbox_meta(sscript,
                                                        (yyvsp[-2].test), NULL, (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3633 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 185:
#line 1364 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.test) = new_test(SERVERMETADATAEXISTS,
                                                   sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), NULL, NULL, (yyvsp[0].sl));
                                 }
#line 3644 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 186:
#line 1372 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.test) = new_test(VALIDEXTLIST, sscript);
                                     (yyval.test)->u.sl = (yyvsp[0].sl);
                                 }
#line 3653 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 187:
#line 1376 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = build_duplicate(sscript, (yyvsp[0].test)); }
#line 3659 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 188:
#line 1379 "sieve/sieve.y" /* yacc.c:1646  */
    { 
                                     (yyval.test) = new_test(SPECIALUSEEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), NULL, NULL, (yyvsp[0].sl));
                                 }
#line 3669 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 189:
#line 1386 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.test) = new_test(SPECIALUSEEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), (yyvsp[-1].sval), NULL, (yyvsp[0].sl));
                                 }
#line 3679 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 190:
#line 1393 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.test) = new_test(MAILBOXIDEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), NULL, NULL, (yyvsp[0].sl));
                                 }
#line 3689 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 191:
#line 1399 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     (yyval.test) = new_test(JMAPQUERY, sscript);
                                     (yyval.test) = build_jmapquery(sscript, (yyval.test), (yyvsp[0].sval));
                                 }
#line 3698 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 192:
#line 1404 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(SFALSE, sscript); }
#line 3704 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 195:
#line 1415 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(HEADERT, sscript); }
#line 3710 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 196:
#line 1416 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.hhs.comp); }
#line 3716 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 198:
#line 1417 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.hhs.comp); }
#line 3722 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 200:
#line 1418 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.hhs.comp); }
#line 3728 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 202:
#line 1419 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.hhs.comp); }
#line 3734 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 204:
#line 1424 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (ctags->match != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "match-type");
                                     }

                                     ctags->match = (yyvsp[0].nval);
                                 }
#line 3748 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 205:
#line 1434 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (ctags->match != COUNT &&
                                         ctags->match != VALUE &&
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
#line 3770 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 209:
#line 1458 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!supported(SIEVE_CAPA_REGEX)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "regex");
                                     }
                                 }
#line 3782 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 218:
#line 1485 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (ctags->match != LIST &&
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

                                     ctags->match = LIST;
                                 }
#line 3802 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 219:
#line 1505 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (ctags->collation != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":comparator");
                                     }

                                     ctags->collation = (yyvsp[0].nval);
                                 }
#line 3816 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 222:
#line 1520 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!supported(SIEVE_CAPA_COMP_NUMERIC)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "comparator-"
                                                      "i;ascii-numeric");
                                     }
                                 }
#line 3829 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 223:
#line 1532 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (ctags->index == INT_MIN) {
                                         /* :last before :index */
                                         ctags->index = -(yyvsp[0].nval);
                                     }
                                     else if (ctags->index != 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":index");
                                     }
                                     else {
                                       if (!supported(SIEVE_CAPA_INDEX)) {
                                             sieveerror_c(sscript,
                                                          SIEVE_MISSING_REQUIRE,
                                                          "index");
                                         }

                                         ctags->index = (yyvsp[0].nval);
                                     }
                                 }
#line 3854 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 224:
#line 1552 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (ctags->index > 0) {
                                         ctags->index *= -1;
                                     }
                                     else if (ctags->index < 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":last");
                                     }
                                     else if (ctags->index == 0) {
                                       if (!supported(SIEVE_CAPA_INDEX)) {
                                             sieveerror_c(sscript,
                                                          SIEVE_MISSING_REQUIRE,
                                                          "index");
                                         }

                                         /* :last before :index */
                                         ctags->index = INT_MIN;
                                     }
                                 }
#line 3879 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 225:
#line 1576 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(ADDRESS, sscript); }
#line 3885 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 227:
#line 1578 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.ae.comp); }
#line 3891 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 229:
#line 1579 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.ae.comp); }
#line 3897 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 231:
#line 1580 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.ae.comp); }
#line 3903 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 233:
#line 1581 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.ae.comp); }
#line 3909 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 235:
#line 1586 "sieve/sieve.y" /* yacc.c:1646  */
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
#line 3926 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 239:
#line 1604 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if (!supported(SIEVE_CAPA_SUBADDRESS)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "subaddress");
                                     }
                                 }
#line 3938 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 242:
#line 1621 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(ENVELOPE, sscript); }
#line 3944 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 244:
#line 1623 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.ae.comp); }
#line 3950 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 246:
#line 1624 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.ae.comp); }
#line 3956 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 248:
#line 1625 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.ae.comp); }
#line 3962 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 250:
#line 1630 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(ENVIRONMENT, sscript); }
#line 3968 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 251:
#line 1631 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.mm.comp); }
#line 3974 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 253:
#line 1632 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.mm.comp); }
#line 3980 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 255:
#line 1637 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(BODY, sscript); }
#line 3986 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 256:
#line 1638 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.test)->u.b.transform != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "transform");
                                     }

                                     (yyval.test)->u.b.transform = (yyvsp[0].nval);
                                 }
#line 4000 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 257:
#line 1649 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.test)->u.b.transform != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      "transform");
                                         strarray_free((yyval.test)->u.b.content_types);
                                     }

                                     (yyval.test)->u.b.transform = CONTENT;
                                     (yyval.test)->u.b.content_types = (yyvsp[0].sl);
                                 }
#line 4016 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 258:
#line 1661 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.b.comp); }
#line 4022 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 260:
#line 1662 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.b.comp); }
#line 4028 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 264:
#line 1673 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(STRINGT, sscript); }
#line 4034 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 265:
#line 1674 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.hhs.comp); }
#line 4040 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 267:
#line 1675 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.hhs.comp); }
#line 4046 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 269:
#line 1676 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.hhs.comp); }
#line 4052 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 271:
#line 1681 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(HASFLAG, sscript); }
#line 4058 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 272:
#line 1682 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.hhs.comp); }
#line 4064 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 274:
#line 1683 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.hhs.comp); }
#line 4070 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 276:
#line 1688 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(DATE, sscript); }
#line 4076 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 278:
#line 1690 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.test)->u.dt.zonetag != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":originalzone");
                                     }

                                     (yyval.test)->u.dt.zonetag = ORIGINALZONE;
                                 }
#line 4090 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 279:
#line 1699 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.dt.comp); }
#line 4096 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 281:
#line 1700 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.dt.comp); }
#line 4102 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 283:
#line 1701 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.dt.comp); }
#line 4108 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 285:
#line 1706 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     /* $0 refers to a test_t* ([CURRENT]DATE)*/
                                     test_t *test = (yyvsp[-2].test);

                                     if (test->u.dt.zonetag != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":zone");
                                     }

                                     test->u.dt.zonetag = ZONE;
                                     test->u.dt.zone = (yyvsp[0].nval);
                                 }
#line 4126 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 286:
#line 1723 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(CURRENTDATE, sscript); }
#line 4132 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 288:
#line 1725 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.dt.comp); }
#line 4138 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 290:
#line 1726 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.dt.comp); }
#line 4144 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 305:
#line 1748 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(NOTIFYMETHODCAPABILITY, sscript); }
#line 4150 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 306:
#line 1749 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.mm.comp); }
#line 4156 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 308:
#line 1750 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.mm.comp); }
#line 4162 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 310:
#line 1755 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test((yyvsp[0].nval), sscript); }
#line 4168 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 311:
#line 1756 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.mm.comp); }
#line 4174 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 313:
#line 1757 "sieve/sieve.y" /* yacc.c:1646  */
    { ctags = &((yyvsp[0].test)->u.mm.comp); }
#line 4180 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 315:
#line 1762 "sieve/sieve.y" /* yacc.c:1646  */
    { (yyval.test) = new_test(DUPLICATE, sscript); }
#line 4186 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 316:
#line 1763 "sieve/sieve.y" /* yacc.c:1646  */
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
#line 4203 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 317:
#line 1775 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.test)->u.dup.handle != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":handle");
                                         free((yyval.test)->u.dup.handle);
                                     }

                                     (yyval.test)->u.dup.handle = (yyvsp[0].sval);
                                 }
#line 4218 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 318:
#line 1785 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.test)->u.dup.seconds != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":seconds");
                                     }

                                     (yyval.test)->u.dup.seconds = (yyvsp[0].nval);
                                 }
#line 4232 "sieve/sieve.c" /* yacc.c:1646  */
    break;

  case 319:
#line 1794 "sieve/sieve.y" /* yacc.c:1646  */
    {
                                     if ((yyval.test)->u.dup.last != 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":last");
                                     }

                                     (yyval.test)->u.dup.last = 1;
                                 }
#line 4246 "sieve/sieve.c" /* yacc.c:1646  */
    break;


#line 4250 "sieve/sieve.c" /* yacc.c:1646  */
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
#line 1812 "sieve/sieve.y" /* yacc.c:1906  */



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

    if (collation == ASCIICASEMAP) {
        cflags |= REG_ICASE;
    }

    for (i = 0 ; !ret && i < strarray_size(sa) ; i++) {
        if ((ret = regcomp(&reg, strarray_nth(sa, i), cflags)) != 0) {
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

    return (c->match == REGEX) ?
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
        "from", "sender", "reply-to",   /* RFC5322 originator fields */
        "to", "cc", "bcc",              /* RFC5322 destination fields */
        "message-id", "in-reply-to",    /* RFC5322 identification fields */
        "references"
        "resent-from", "resent-sender", /* RFC5322 resent fields */
        "resent-to", "resent-cc", "resent-bcc",
        "return-path",                  /* RFC5322 trace fields */
        "disposition-notification-to",  /* RFC8098 MDN request fields */
        "approved",                     /* RFC5536 moderator/control fields */
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

static commandlist_t *build_keep(sieve_script_t *sscript, commandlist_t *c)
{
    assert(c && c->type == KEEP);

    if (c->u.k.flags && !_verify_flaglist(c->u.k.flags)) {
        strarray_add(c->u.k.flags, "");
    }

    return c;
}

static commandlist_t *build_fileinto(sieve_script_t *sscript,
                                     commandlist_t *c, char *folder)
{
    assert(c && c->type == FILEINTO);

    if (c->u.f.flags && !_verify_flaglist(c->u.f.flags)) {
        strarray_add(c->u.f.flags, "");
    }
    verify_mailbox(sscript, folder);
    c->u.f.folder = folder;

    return c;
}

static commandlist_t *build_redirect(sieve_script_t *sscript,
                                     commandlist_t *c, char *address)
{
    assert(c && c->type == REDIRECT);

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
    assert(c && c->type == SET);

    verify_identifier(sscript, variable);
    verify_utf8(sscript, value);

    c->u.s.variable = variable;
    c->u.s.value = value;

    return c;
}

static commandlist_t *build_vacation(sieve_script_t *sscript,
                                     commandlist_t *c, char *message)
{
    int min = sscript->interp.vacation->min_response;
    int max = sscript->interp.vacation->max_response;

    assert(c && c->type == VACATION);

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
    else if (c->u.v.fcc.create || c->u.v.fcc.flags || c->u.v.fcc.specialuse) {
        sieveerror_c(sscript, SIEVE_MISSING_TAG, ":fcc");
    }

    c->u.v.message = message;

    if (c->u.v.seconds == -1) c->u.v.seconds = 7 * DAY2SEC;
    if (c->u.v.seconds < min) c->u.v.seconds = min;
    if (c->u.v.seconds > max) c->u.v.seconds = max;

    return c;
}

static commandlist_t *build_flag(sieve_script_t *sscript,
                                 commandlist_t *c, strarray_t *flags)
{
    assert(c &&
           (c->type == SETFLAG || c->type == ADDFLAG || c->type == REMOVEFLAG));

    if (!_verify_flaglist(flags)) {
        strarray_add(flags, "");
    }
    c->u.fl.flags = flags;

    if (!c->u.fl.variable) c->u.fl.variable = xstrdup("");
    else if (!is_identifier(c->u.fl.variable)) {
        sieveerror_c(sscript, SIEVE_INVALID_VALUE, "variablename");
    }

    return c;
}

static commandlist_t *build_addheader(sieve_script_t *sscript,
                                      commandlist_t *c, char *name, char *value)
{
    assert(c && c->type == ADDHEADER);

    verify_header(sscript, name);
    verify_utf8(sscript, value);

    if (c->u.ah.index == 0) c->u.ah.index = 1;
    c->u.ah.name = name;
    c->u.ah.value = value;

    return c;
}

static commandlist_t *build_deleteheader(sieve_script_t *sscript,
                                         commandlist_t *c,
                                         char *name, strarray_t *values)
{
    assert(c && c->type == DELETEHEADER);

    if (!strcasecmp("Received", name) || !strcasecmp("Auto-Submitted", name)) {
        sieveerror_f(sscript,
                     "MUST NOT delete Received or Auto-Submitted headers");
    }

    verify_header(sscript, name);
    verify_patternlist(sscript, values, &c->u.dh.comp, verify_utf8);

    c->u.dh.name = name;
    c->u.dh.values = values;

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
    char *r = strptime(time, "%T", &tm);

    if (r && *r == '\0') {
        return (3600 * tm.tm_hour + 60 * tm.tm_min + tm.tm_sec);
    }

    sieveerror_f(sscript, "'%s': not a valid time for snooze", time);
    return 0;
}

static commandlist_t *build_snooze(sieve_script_t *sscript,
                                   commandlist_t *c, arrayu64_t *times)
{
    assert(c && c->type == SNOOZE);

    if (c->u.sn.mailbox) verify_mailbox(sscript, c->u.sn.mailbox);
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

    return c;
}

static commandlist_t *build_rej_err(sieve_script_t *sscript,
                                    int t, char *message)
{
    commandlist_t *c;

    assert(t == REJCT || t == EREJECT || t == ERROR);

    verify_utf8(sscript, message);

    c = new_command(t, sscript);
    c->u.str = message;

    return c;
}

static commandlist_t *build_notify(sieve_script_t *sscript, int t,
                                   commandlist_t *c, char *method)
{
    assert(c && (t == NOTIFY || t == ENOTIFY));

    if (t == ENOTIFY) {
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
        else if (c->u.n.fcc.create || c->u.n.fcc.flags || c->u.n.fcc.specialuse) {
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
    if (c->u.n.priority == -1) c->u.n.priority = NORMAL;
    if (!c->u.n.message) c->u.n.message = xstrdup("$from$: $subject$");

    return c;
}

static commandlist_t *build_denotify(sieve_script_t *sscript,
                                     commandlist_t *t)
{
    assert(t && t->type == DENOTIFY);

    canon_comptags(&t->u.d.comp, sscript);
    if (t->u.d.priority == -1) t->u.d.priority = ANY;
    if (t->u.d.pattern) {
        strarray_t sa = STRARRAY_INITIALIZER;

        strarray_pushm(&sa, t->u.d.pattern);
        verify_patternlist(sscript, &sa, &t->u.d.comp, NULL);
        strarray_pop(&sa);
        strarray_fini(&sa);
    }

    return t;
}

static commandlist_t *build_include(sieve_script_t *sscript,
                                    commandlist_t *c, char *script)
{
    assert(c && c->type == INCLUDE);

    if (strchr(script, '/')) {
        sieveerror_c(sscript, SIEVE_INVALID_VALUE, "script-name");
    }

    c->u.inc.script = script;
    if (c->u.inc.once == -1) c->u.inc.once = 0;
    if (c->u.inc.location == -1) c->u.inc.location = PERSONAL;
    if (c->u.inc.optional == -1) c->u.inc.optional = 0;

    return c;
}

static commandlist_t *build_log(sieve_script_t *sscript, char *text)
{
    commandlist_t *c;

    if (!supported(SIEVE_CAPA_LOG)) {
          sieveerror_c(sscript, SIEVE_MISSING_REQUIRE, "x-cyrus-log");
    }

    verify_utf8(sscript, text);

    c = new_command(LOG, sscript);
    c->u.l.text = text;

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
        t = new_test(ANYOF, sscript);
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
        t = new_test(ALLOF, sscript);
        t->u.tl = tl;

        /* find first test that set ignore_err and revert to that value */
        for ( ; tl; tl = tl->next) {
            if (tl->t->ignore_err) {
                sscript->ignore_err = t->ignore_err = tl->t->ignore_err;
                break;
            }
        }
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

    n = new_test(NOT, sscript);
    n->u.t = t;

    return n;
}

static test_t *build_hhs(sieve_script_t *sscript, test_t *t,
                         strarray_t *sl, strarray_t *pl)
{
    assert(t);

    verify_patternlist(sscript, pl, &t->u.hhs.comp, verify_utf8);

    t->u.hhs.sl = sl;
    t->u.hhs.pl = pl;

    return t;
}

static test_t *build_header(sieve_script_t *sscript, test_t *t,
                            strarray_t *sl, strarray_t *pl)
{
    assert(t && t->type == HEADERT);

    verify_stringlist(sscript, sl, verify_header);

    return build_hhs(sscript, t, sl, pl);
}

static test_t *build_stringt(sieve_script_t *sscript, test_t *t,
                             strarray_t *sl, strarray_t *pl)
{
    assert(t && t->type == STRINGT);

    verify_stringlist(sscript, sl, verify_utf8);

    return build_hhs(sscript, t, sl, pl);
}

static test_t *build_hasflag(sieve_script_t *sscript, test_t *t,
                             strarray_t *sl, strarray_t *pl)
{
    assert(t && t->type == HASFLAG);

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

    if (t->u.ae.addrpart == -1) t->u.ae.addrpart = ALL;
    t->u.ae.sl = sl;
    t->u.ae.pl = pl;

    return t;
}

static test_t *build_address(sieve_script_t *sscript, test_t *t,
                             strarray_t *sl, strarray_t *pl)
{
    assert(t && t->type == ADDRESS);

    verify_stringlist(sscript, sl, verify_addrheader);

    return build_ae(sscript, t, sl, pl);
}

static test_t *build_envelope(sieve_script_t *sscript, test_t *t,
                              strarray_t *sl, strarray_t *pl)
{
    assert(t && t->type == ENVELOPE);

    verify_stringlist(sscript, sl, verify_envelope);

    return build_ae(sscript, t, sl, pl);
}

static test_t *build_body(sieve_script_t *sscript,
                          test_t *t, strarray_t *pl)
{
    assert(t && (t->type == BODY));

    verify_patternlist(sscript, pl, &t->u.b.comp, verify_utf8);

    if (t->u.b.offset == -1) t->u.b.offset = 0;
    if (t->u.b.transform == -1) t->u.b.transform = TEXT;
    if (t->u.b.content_types == NULL) {
        t->u.b.content_types = strarray_new();
        strarray_append(t->u.b.content_types,
                        (t->u.b.transform == RAW) ? "" : "text");
    }
    t->u.b.pl = pl;

    return t;
}

static test_t *build_date(sieve_script_t *sscript,
                          test_t *t, char *hn, int part, strarray_t *kl)
{
    assert(t && (t->type == DATE || t->type == CURRENTDATE));

    if (hn) verify_header(sscript, hn);
    verify_patternlist(sscript, kl, &t->u.dt.comp, NULL);

    if (t->u.dt.comp.index == 0) t->u.dt.comp.index = 1;
    if (t->u.dt.zonetag == -1) {
        struct tm tm;
        time_t now = time(NULL);

        localtime_r(&now, &tm);
        t->u.dt.zone = gmtoff_of(&tm, now) / 60;
        t->u.dt.zonetag = ZONE;
    }

    t->u.dt.date_part = part;
    t->u.dt.header_name = hn;
    t->u.dt.kl = kl;

    return t;
}

static test_t *build_ihave(sieve_script_t *sscript, strarray_t *sa)
{
    test_t *t;
    int i;

    t = new_test(IHAVE, sscript);
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

    return t;
}

static test_t *build_mbox_meta(sieve_script_t *sscript,
                               test_t *t, char *extname,
                               char *keyname, strarray_t *keylist)
{
    assert(t && (t->type == MAILBOXEXISTS || t->type == MAILBOXIDEXISTS ||
                 t->type == METADATA || t->type == METADATAEXISTS ||
                 t->type == SERVERMETADATA || t->type == SERVERMETADATAEXISTS ||
                 t->type == ENVIRONMENT || t->type == SPECIALUSEEXISTS ||
                 t->type == NOTIFYMETHODCAPABILITY));

    canon_comptags(&t->u.mm.comp, sscript);
    t->u.mm.extname = extname;
    t->u.mm.keyname = keyname;
    t->u.mm.keylist = keylist;

    return t;
}

static test_t *build_duplicate(sieve_script_t *sscript, test_t *t)
{
    assert(t && t->type == DUPLICATE);

    switch (t->u.dup.idtype) {
    case HEADER:
        verify_header(sscript, t->u.dup.idval);
        break;

    case UNIQUEID:
        verify_utf8(sscript, t->u.dup.idval);
        break;

    default:
        t->u.dup.idtype = HEADER;
        t->u.dup.idval = xstrdup("Message-ID");
        break;
    }

    if (!t->u.dup.handle) t->u.dup.handle = xstrdup("");
    else verify_utf8(sscript, t->u.dup.handle);

    if (t->u.dup.seconds == -1) t->u.dup.seconds = 7 * 86400; /* 7 days */

    return t;
}

#ifdef WITH_JMAP
#include "imap/json_support.h"

static int jmap_parse_condition(json_t *cond, strarray_t *path)
{
    json_t *val;
    const char *field;

    json_object_foreach(cond, field, val) {
        /* inMailbox* and *InThreadHaveKeywords properties are incompatible */
        if (!strcmp(field, "before") ||
            !strcmp(field, "after")) {
            if (!json_is_utcdate(val)) break;
        }
        else if (!strcmp(field, "minSize") ||
                 !strcmp(field, "maxSize")) {
            if (!json_is_integer(val)) break;
        }
        else if (!strcmp(field, "hasAttachment")) {
            if (!json_is_boolean(val)) break;
        }
        else if (!strcmp(field, "text") ||
                 !strcmp(field, "from") ||
                 !strcmp(field, "to") ||
                 !strcmp(field, "cc") ||
                 !strcmp(field, "bcc") ||
                 !strcmp(field, "subject") ||
                 !strcmp(field, "body")) {
            if (!json_is_string(val)) break;
        }
        else if (!strcmp(field, "header")) {
            size_t n = json_array_size(val);

            if (n == 0 || n > 2) break;

            do {
                const char *s = json_string_value(json_array_get(val, --n));

                if (!s || !strlen(s)) {
                    struct buf buf = BUF_INITIALIZER;

                    buf_printf(&buf, "header[%lu]", n);
                    strarray_pushm(path, buf_release(&buf));
                    return 0;
                }
            } while (n);
        }
        /* JMAP Search Extension: https://cyrusimap.org/ns/jmap/search */
        else if (!strcmp(field, "attachmentBody")) {
            if (!json_is_string(val)) break;
        }
        /* JMAP Mail Extension: https://cyrusimap.org/ns/jmap/mail */
        else if (!strcmp(field, "attachmentName") ||
                 !strcmp(field, "attachmentType")) {
            if (!json_is_string(val)) break;
        }
        /* JMAP Mail Extension: https://cyrusimap.org/ns/jmap/mail */
        else if (!strcmp(field, "fromContactGroupId") ||
                 !strcmp(field, "toContactGroupId") ||
                 !strcmp(field, "ccContactGroupId") ||
                 !strcmp(field, "bccContactGroupId")) {
            if (!json_is_string(val)) break;
        }
        /* JMAP Mail Extension: https://cyrusimap.org/ns/jmap/mail */
        else if (!strcmp(field, "fromAnyContact") ||
                 !strcmp(field, "toAnyContact") ||
                 !strcmp(field, "ccAnyContact") ||
                 !strcmp(field, "bccAnyContact")) {
            if (!json_is_boolean(val)) break;
        }
        else break;
    }

    if (field) {
        strarray_push(path, field);
        return 0;
    }

    return 1;
}

static int jmap_parse_filter(json_t *filter, strarray_t *path)
{
    json_t *arg, *val;
    const char *s;
    size_t i;

    if (!JNOTNULL(filter) || !json_is_object(filter)) return 0;

    arg = json_object_get(filter, "operator");
    if (!arg) return jmap_parse_condition(filter, path);

    strarray_push(path, "operator");
    if (!json_is_string(arg)) return 0;

    s = json_string_value(arg);
    if (strcmp("AND", s) && strcmp("OR", s) && strcmp("NOT", s)) return 0;
    free(strarray_pop(path));

    arg = json_object_get(filter, "conditions");
    if (!json_array_size(arg)) {
        strarray_push(path, "conditions");
        return 0;
    }

    json_array_foreach(arg, i, val) {
        struct buf buf = BUF_INITIALIZER;

        buf_printf(&buf, "conditions[%lu]", i);
        strarray_pushm(path, buf_release(&buf));
        if (!jmap_parse_filter(val, path)) return 0;
        free(strarray_pop(path));
    }

    return 1;
}

static test_t *build_jmapquery(sieve_script_t *sscript,
                               test_t *t, const char *json)
{
    strarray_t path = STRARRAY_INITIALIZER;
    json_t *jquery;
    json_error_t jerr;

    assert(t && t->type == JMAPQUERY);

    /* validate query */
    jquery = json_loads(json, 0, &jerr);
    if (!jmap_parse_filter(jquery, &path)) {
        char *s = strarray_join(&path, "/");

        if (s) sieveerror_f(sscript, "invalid jmapquery argument: '%s'", s);
        else sieveerror_f(sscript, "invalid jmapquery format");

        free(s);
    }
    strarray_fini(&path);

    t->u.jquery = json_dumps(jquery, JSON_COMPACT);
    json_decref(jquery);

    return t;
}
#else
static test_t *build_jmapquery(sieve_script_t *sscript, test_t *t,
                               const char *json __attribute__((unused)))
{
    sieveerror_c(sscript, SIEVE_UNSUPP_EXT, "x-cyrus-jmapquery");

    return t;
}
#endif /* WITH_JMAP */
