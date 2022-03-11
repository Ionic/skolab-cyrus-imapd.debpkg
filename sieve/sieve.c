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
static commandlist_t *build_imip(sieve_script_t *sscript, commandlist_t *t);

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

#line 241 "sieve/sieve.c" /* yacc.c:337  */
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
    NID = 352,
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
    SNOOZE = 387,
    MAILBOX = 388,
    ADDFLAGS = 389,
    REMOVEFLAGS = 390,
    WEEKDAYS = 391,
    TZID = 392,
    LOG = 393,
    JMAPQUERY = 394,
    PROCESSIMIP = 395,
    INVITESONLY = 396,
    UPDATESONLY = 397,
    DELETECANCELED = 398,
    CALENDARID = 399,
    OUTCOME = 400,
    ERRSTR = 401
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
#define NID 352
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
#define SNOOZE 387
#define MAILBOX 388
#define ADDFLAGS 389
#define REMOVEFLAGS 390
#define WEEKDAYS 391
#define TZID 392
#define LOG 393
#define JMAPQUERY 394
#define PROCESSIMIP 395
#define INVITESONLY 396
#define UPDATESONLY 397
#define DELETECANCELED 398
#define CALENDARID 399
#define OUTCOME 400
#define ERRSTR 401

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 179 "sieve/sieve.y" /* yacc.c:352  */

    int nval;
    char *sval;
    arrayu64_t *nl;
    strarray_t *sl;
    comp_t *ctag;
    test_t *test;
    testlist_t *testl;
    commandlist_t *cl;

#line 587 "sieve/sieve.c" /* yacc.c:352  */
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
#define YYLAST   771

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  155
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  87
/* YYNRULES -- Number of rules.  */
#define YYNRULES  288
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  411

#define YYUNDEFTOK  2
#define YYMAXUTOK   401

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
     153,   154,     2,     2,   150,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,   147,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,   148,     2,   149,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,   151,     2,   152,     2,     2,     2,     2,
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
     145,   146
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   368,   368,   369,   373,   374,   379,   380,   384,   385,
     386,   398,   399,   403,   404,   408,   409,   413,   420,   427,
     431,   432,   433,   434,   436,   440,   451,   452,   453,   457,
     458,   463,   464,   473,   482,   495,   496,   503,   504,   505,
     506,   507,   509,   512,   516,   521,   524,   528,   529,   532,
     535,   536,   537,   538,   543,   547,   552,   572,   580,   581,
     582,   583,   584,   589,   606,   623,   648,   674,   678,   679,
     691,   698,   708,   730,   750,   762,   778,   790,   806,   807,
     816,   825,   834,   843,   856,   857,   860,   861,   864,   865,
     877,   888,   893,   901,   910,   924,   934,   945,   956,   965,
     975,   979,   995,   996,   997,   998,  1003,  1004,  1005,  1010,
    1011,  1030,  1031,  1036,  1037,  1050,  1054,  1055,  1056,  1057,
    1062,  1063,  1074,  1084,  1095,  1105,  1108,  1118,  1128,  1139,
    1150,  1165,  1166,  1167,  1172,  1176,  1186,  1195,  1201,  1211,
    1212,  1213,  1215,  1231,  1247,  1257,  1270,  1271,  1275,  1276,
    1280,  1284,  1285,  1289,  1290,  1294,  1301,  1306,  1307,  1329,
    1351,  1367,  1384,  1400,  1421,  1425,  1426,  1430,  1431,  1432,
    1433,  1434,  1435,  1441,  1450,  1453,  1455,  1458,  1460,  1464,
    1471,  1473,  1476,  1479,  1482,  1489,  1493,  1495,  1502,  1502,
    1506,  1513,  1513,  1517,  1525,  1532,  1534,  1541,  1548,  1555,
    1560,  1565,  1566,  1571,  1575,  1576,  1577,  1578,  1583,  1593,
    1615,  1616,  1617,  1618,  1631,  1632,  1637,  1638,  1639,  1640,
    1641,  1642,  1647,  1667,  1682,  1683,  1684,  1698,  1709,  1724,
    1743,  1747,  1748,  1749,  1750,  1751,  1756,  1771,  1772,  1773,
    1774,  1785,  1786,  1791,  1795,  1796,  1797,  1798,  1803,  1807,
    1808,  1813,  1817,  1827,  1840,  1841,  1846,  1847,  1852,  1856,
    1857,  1858,  1863,  1867,  1868,  1873,  1877,  1878,  1887,  1888,
    1889,  1894,  1911,  1915,  1916,  1917,  1922,  1927,  1928,  1933,
    1938,  1939,  1944,  1945,  1956,  1966,  1975,  1988,  1989
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
  "NOTIFY", "ENOTIFY", "ENCODEURL", "DENOTIFY", "NID", "ANY", "LOW",
  "NORMAL", "HIGH", "IHAVE", "ERROR", "MAILBOXEXISTS", "CREATE",
  "METADATA", "METADATAEXISTS", "SERVERMETADATA", "SERVERMETADATAEXISTS",
  "BYTIMEREL", "BYTIMEABS", "BYMODE", "BYTRACE", "DSNNOTIFY", "DSNRET",
  "VALIDEXTLIST", "LIST", "INCLUDE", "OPTIONAL", "ONCE", "RETURN",
  "PERSONAL", "GLOBAL", "DUPLICATE", "HEADER", "UNIQUEID",
  "SPECIALUSEEXISTS", "SPECIALUSE", "FCC", "MAILBOXID", "MAILBOXIDEXISTS",
  "SNOOZE", "MAILBOX", "ADDFLAGS", "REMOVEFLAGS", "WEEKDAYS", "TZID",
  "LOG", "JMAPQUERY", "PROCESSIMIP", "INVITESONLY", "UPDATESONLY",
  "DELETECANCELED", "CALENDARID", "OUTCOME", "ERRSTR", "';'", "'['", "']'",
  "','", "'{'", "'}'", "'('", "')'", "$accept", "start", "reqs",
  "commands", "command", "optstringlist", "stringlist", "strings",
  "string1", "string", "require", "control", "thenelse", "elsif", "block",
  "itags", "location", "action", "ktags", "flags", "ftags", "copy",
  "create", "specialuse", "mailboxid", "rtags", "delbytags", "dsntags",
  "stags", "mod40", "mod30", "mod20", "mod15", "mod10", "vtags", "fcctags",
  "flagaction", "flagtags", "flagmark", "ahtags", "dhtags", "reject",
  "ntags", "priority", "dtags", "sntags", "weekdaylist", "weekdays",
  "weekday", "timelist", "times", "time1", "time", "imiptags", "testlist",
  "tests", "test", "$@1", "$@2", "sizetag", "htags", "matchtype",
  "matchtag", "relmatch", "relation", "listmatch", "comparator",
  "collation", "indexext", "index", "atags", "addrpart", "addrparttag",
  "subaddress", "etags", "envtags", "btags", "transform", "strtags",
  "hftags", "dttags", "zone", "cdtags", "methtags", "mtags", "duptags",
  "idtype", YY_NULLPTR
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
     395,   396,   397,   398,   399,   400,   401,    59,    91,    93,
      44,   123,   125,    40,    41
};
# endif

#define YYPACT_NINF -358

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-358)))

#define YYTABLE_NINF -18

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       7,     2,    20,   495,     7,  -358,    31,  -122,  -358,  -358,
    -358,  -108,   515,  -101,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,    31,  -358,   -98,  -358,    31,  -358,  -358,    21,  -358,
     -96,  -358,  -358,    31,  -358,  -139,  -358,  -358,  -358,  -358,
     -93,   -93,     2,   515,  -358,  -358,    18,  -358,  -358,  -358,
    -358,  -358,  -358,  -358,  -358,  -358,     2,  -358,     2,     2,
    -358,    31,  -358,     2,     2,  -358,     2,     2,    31,  -358,
     -86,  -358,     4,    10,   223,   263,   604,     1,   643,   422,
     646,   -58,    63,  -358,    -3,  -358,   321,  -358,  -358,     2,
    -358,  -358,    31,   515,  -358,  -358,  -358,  -358,  -358,  -358,
      74,   343,   205,   222,   391,   457,   160,   414,   660,   540,
    -358,   457,  -358,  -358,  -358,     2,  -358,  -358,  -358,   -40,
    -358,     2,  -358,  -358,   316,    73,     2,  -358,  -358,  -358,
      31,    31,  -358,  -358,  -358,  -358,  -358,  -358,    96,    31,
      31,  -358,    31,    31,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,  -358,  -358,  -358,  -358,    31,  -358,  -358,
    -358,  -358,  -358,    97,    31,    31,     2,  -358,    31,    98,
      31,  -358,  -358,  -358,  -358,  -358,  -358,  -358,    31,    29,
    -358,  -358,  -358,  -358,  -358,  -358,   100,  -358,  -358,     2,
    -358,  -358,   586,  -358,  -358,  -358,    31,    31,     2,    31,
     -25,    31,  -358,  -358,  -358,  -358,  -358,  -358,  -358,    31,
    -358,  -358,  -358,  -358,  -358,   -39,  -358,  -358,    31,     2,
       2,     3,    31,   107,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,    31,    31,    31,  -358,   -35,  -358,   -41,
     -34,  -358,     2,  -358,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,     2,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,     2,  -358,  -358,  -358,  -358,  -358,  -358,     2,  -358,
    -358,  -358,  -358,     2,  -358,  -358,     2,  -358,  -358,  -358,
       2,  -358,  -358,  -358,    31,    31,  -358,  -358,  -358,  -358,
       2,  -358,  -358,  -358,    31,  -358,  -358,   457,  -358,   457,
      31,   117,  -358,  -358,  -358,    31,  -358,  -358,   -26,   515,
     -86,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,  -358,  -358,   124,  -358,  -358,  -358,   -80,
    -358,  -358,  -358,  -358,  -358,   515,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,  -358,     2,  -358,     2,    31,  -358,  -358,
       2,  -358,  -358,  -358,  -358,  -358,  -358,   -68,  -358,  -358,
     107,  -358,  -358,  -358,     2,  -358,  -358,   124,  -358,  -358,
    -358
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint16 yydefact[] =
{
       4,     0,     0,     0,     4,    18,     0,     0,    13,    17,
       1,     0,     0,     0,    40,    54,    57,    67,    78,    92,
     106,   107,   108,   111,   112,   113,   115,   120,   121,   122,
     134,     0,    31,     0,   137,     0,   157,     3,     0,     8,
       0,   109,    44,     0,     5,     0,    15,    19,    10,   200,
       0,     0,     0,     0,   170,   171,     0,   203,   230,   243,
     251,   248,   258,   262,   265,   272,     0,   276,     0,     0,
     188,     0,   191,     0,     0,   282,     0,     0,     0,    20,
       0,    21,    37,     0,     0,     0,     0,     0,     0,    49,
      50,     0,     0,    24,     0,    51,    53,     7,     9,     0,
      47,    14,     0,     0,   167,   168,   172,   169,   201,   202,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     184,     0,   186,   187,   279,     0,   279,   193,   194,   195,
     196,    17,   198,   199,     0,    26,     0,    55,    63,    64,
       0,     0,    38,    59,    58,    60,    61,    62,     0,     0,
       0,    75,     0,     0,    69,    39,    68,    70,    71,    89,
      84,    85,    86,    87,    88,    91,    90,     0,    79,    80,
      81,    82,    83,     0,     0,     0,     0,    98,     0,     0,
       0,    42,   103,   102,   104,   105,   100,   114,     0,     0,
     210,   211,   212,   213,   214,   215,     0,   229,   222,    11,
     116,   208,     0,   117,   118,   119,     0,     0,     0,     0,
       0,     0,   131,   132,   133,    48,   125,   128,   135,     0,
      22,    34,    33,    35,    36,     0,    32,   156,     0,     0,
       0,     0,     0,     0,   139,   140,   141,    52,   151,   155,
     158,   159,   160,     0,     0,     0,    43,   110,    16,     0,
     165,   173,     0,   204,   205,   206,   207,   227,   237,   238,
     239,   241,   242,     0,   232,   233,   234,   235,   231,   236,
     240,     0,   245,   246,   247,   244,   256,   257,     0,   177,
     254,   255,   252,     0,   249,   250,     0,   259,   260,   261,
     181,   263,   264,   267,     0,     0,   268,   269,   270,   266,
       0,   274,   275,   273,     0,   277,   278,     0,   190,     0,
       0,     0,   286,   287,   288,     0,   197,    30,     0,     0,
       0,    25,    56,    65,    66,    72,    73,    74,    76,    77,
      41,    93,    95,    96,    97,    99,    94,   101,    45,   224,
     225,   226,   223,   228,    46,    12,   218,   219,   220,   221,
     216,   217,   209,   123,   127,   130,   129,   124,   126,   136,
      23,   138,   142,   143,   150,     0,   144,   146,   145,     0,
     153,   161,   162,   163,   164,     0,   174,   175,   176,   253,
     178,   179,   180,   271,     0,   183,     0,     0,   280,   281,
       0,   284,   285,   283,    29,    27,    28,     0,   148,   152,
       0,   166,   182,   185,     0,   192,   147,     0,   154,   189,
     149
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -358,  -358,   125,   -36,  -358,  -358,    94,  -358,   129,   -31,
    -358,  -358,  -182,  -358,  -179,  -358,  -358,  -358,  -358,    14,
    -358,    64,   -70,   -67,   -66,  -358,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,  -358,  -358,    65,  -358,  -358,  -358,  -358,
    -358,  -358,  -358,   -87,  -358,  -358,  -358,  -358,  -357,  -358,
    -358,   -81,  -245,  -358,   105,  -217,   -44,  -358,  -358,  -358,
    -358,   638,  -358,  -358,  -358,   -75,   650,  -358,   -89,    77,
    -358,    53,  -358,  -358,  -358,  -358,  -358,  -358,  -358,  -358,
    -358,    50,  -358,  -358,    46,  -358,  -358
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,    37,    38,   344,     7,    45,     8,     9,
       4,    39,    79,   321,   135,    92,   226,    40,    82,   182,
      83,   144,   183,   184,   185,    84,   157,   158,    85,   168,
     169,   170,   171,   172,    86,   186,    41,    99,    42,    87,
      88,    43,    89,   217,    90,    94,   366,   397,   367,   237,
     369,   238,   239,    96,   104,   249,    80,   124,   126,   110,
     111,   388,   201,   202,   352,   203,   389,   342,   256,   257,
     112,   268,   269,   270,   113,   115,   114,   282,   116,   117,
     118,   299,   119,   121,   307,   129,   315
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      91,   227,    97,   218,    95,     5,     5,   364,   398,   107,
     101,   102,   100,   145,     5,     1,   146,   147,   310,   311,
      10,    -6,    11,   267,   234,    47,    12,   235,   236,   298,
      13,    14,    15,    16,    17,     5,   254,   265,   273,    48,
     125,   288,   312,   108,   109,   131,    81,   133,   138,    93,
     410,    98,   142,   155,   167,   181,   188,   199,   215,   250,
     103,   225,   339,   340,   341,   134,    18,     5,   247,   399,
     400,   248,   136,    19,   212,   213,   214,   251,   136,   319,
     320,   406,   407,   187,   283,   313,   314,   295,   300,   220,
     304,    20,    21,    22,    23,    24,   137,   143,   318,   325,
     331,   336,   139,   343,    25,    26,    27,    28,   360,   323,
     324,   227,   -17,   374,    29,   139,   375,    30,   326,   327,
     392,   328,   329,   357,    31,   140,   394,   141,   364,    44,
     228,   229,   230,   231,   232,    46,   330,   395,   140,    32,
     141,   396,    33,   332,   333,   233,   106,   335,   156,   337,
       6,   365,   370,    34,   216,   408,   105,   338,   401,    35,
     120,    36,   122,   123,     5,   205,   275,   127,   128,   303,
     130,   132,   309,    -6,     0,   353,   354,     0,   356,     0,
     358,     0,   221,   222,   189,   223,   224,     0,   359,     0,
     190,   191,   192,   246,     0,     0,   193,   361,     0,     0,
       0,   368,     0,     0,     0,   252,   263,   271,   279,     5,
     286,   290,   371,   372,   373,     0,     0,     0,     0,   308,
     194,   195,     0,     0,     0,   316,     5,     5,     0,   189,
     322,     0,   258,   259,   260,   190,   191,   192,     0,     0,
       0,   193,     0,     0,     0,     0,   189,     0,     0,   258,
     259,   260,   190,   191,   192,     0,     0,     0,   193,     0,
       0,   138,     0,   383,   384,   194,   195,     5,     0,     0,
     334,     0,     0,   386,     0,     0,   387,   198,   390,   391,
     261,   262,   194,   195,   393,     0,   196,   197,     0,     0,
       0,     0,     0,   345,     0,     0,     0,   261,   262,     0,
     159,     0,   355,     0,     0,     0,     0,     0,     6,   160,
     161,   162,   163,   164,   165,     0,     0,    11,     0,     0,
       0,    12,   198,   362,   363,    13,    14,    15,    16,    17,
       0,   250,     0,   148,   149,   150,   151,   152,   153,   198,
     154,     0,     0,     0,     0,     0,   376,     5,     0,     0,
       0,     0,     0,     6,     0,     0,   404,   377,   166,     0,
       0,    18,     0,     0,     0,   378,     0,   189,    19,     0,
       6,     0,   379,   190,   191,   192,     0,   380,     0,   193,
     381,     0,     0,     0,   382,     0,    20,    21,    22,    23,
      24,     0,     0,     0,   385,     5,     0,     0,     0,    25,
      26,    27,    28,   194,   195,     0,     0,     0,     0,    29,
       0,     0,    30,     0,     0,   189,     0,     0,     5,    31,
       0,   190,   191,   192,   196,   197,     5,   193,     0,     0,
       0,   276,   277,   278,    32,     0,     0,    33,   189,     0,
       0,     0,     0,     0,   190,   191,   192,     0,    34,     0,
     193,   194,   195,     0,    35,     0,    36,     0,     0,     0,
     198,     5,   240,   241,   242,   243,   244,   245,   317,     0,
       0,     0,     0,     0,   194,   195,     0,   206,   402,     0,
     403,   189,     0,     0,   405,     0,     0,   190,   191,   192,
     136,     6,     0,   193,     0,    -2,    11,     0,   409,     0,
      12,     0,     0,     0,    13,    14,    15,    16,    17,   207,
     208,   209,   210,     0,     0,     0,    49,   194,   195,   211,
       0,   212,   213,   214,     0,     0,     0,   139,     0,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,     6,
      18,     0,     0,     0,     5,     0,     0,    19,     0,     0,
     140,   180,   141,     0,    60,     0,     0,     0,    61,    62,
       0,     0,     6,     0,   189,    20,    21,    22,    23,    24,
     190,   191,   192,     0,     0,     0,   193,     0,    25,    26,
      27,    28,     0,     0,    63,     0,     0,     0,    29,     0,
       0,    30,    64,    65,     0,     0,     0,     0,    31,     0,
     194,   195,     0,     0,     0,     0,    66,    67,     5,     0,
       0,     0,     0,    32,     0,     0,    33,    68,     0,    69,
     294,    70,    71,    72,    73,     0,     0,    34,     0,     0,
       0,    74,     0,    35,     0,    36,     0,     0,     0,    75,
       0,     0,    76,     0,     0,     0,    77,     5,   346,   347,
     348,   349,   350,   351,    78,     0,     0,   173,   174,   175,
     176,   177,   178,   179,     5,     0,     0,   189,     0,     0,
       0,     0,   136,   190,   191,   192,   190,   191,   192,   193,
       0,     0,   193,     0,   189,     0,     0,     0,     0,     0,
     190,   191,   192,     0,     0,     0,   193,     0,     0,     0,
       0,     0,     0,   194,   195,     0,   194,   195,     0,   139,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     194,   195,     0,     0,   196,   197,   200,     0,   219,     0,
       0,     0,   140,   180,   141,     0,     0,     0,   204,   293,
     294,   196,   197,     0,     0,   212,   213,   214,     0,   253,
     264,   272,   280,   284,   287,   291,   296,   301,     0,   305,
     198,   255,   266,   274,   281,   285,   289,   292,   297,   302,
       0,   306
};

static const yytype_int16 yycheck[] =
{
      31,     4,    38,    90,    35,     4,     4,     4,   365,    53,
     149,   150,    43,    83,     4,     8,    83,    83,    58,    59,
       0,     0,     1,   112,    94,   147,     5,    94,    94,   118,
       9,    10,    11,    12,    13,     4,   111,   112,   113,   147,
      71,   116,    82,    25,    26,    76,   147,    78,    38,   147,
     407,   147,    83,    84,    85,    86,    87,    88,    89,   103,
     153,    92,    33,    34,    35,   151,    45,     4,    99,   149,
     150,   102,    68,    52,    99,   100,   101,     3,    68,     6,
       7,   149,   150,    82,   115,   125,   126,   118,   119,   147,
     121,    70,    71,    72,    73,    74,    82,    83,   134,     3,
       3,     3,   105,     3,    83,    84,    85,    86,   147,   140,
     141,     4,   147,   154,    93,   105,   150,    96,   149,   150,
       3,   152,   153,   210,   103,   128,   152,   130,     4,     4,
     133,   134,   135,   136,   137,     6,   167,   319,   128,   118,
     130,   320,   121,   174,   175,   148,    52,   178,    84,   180,
     148,   148,   233,   132,    89,   400,    51,   188,   375,   138,
      66,   140,    68,    69,     4,    88,   113,    73,    74,   119,
      76,    77,   126,   152,    -1,   206,   207,    -1,   209,    -1,
     211,    -1,   119,   120,    24,   122,   123,    -1,   219,    -1,
      30,    31,    32,    99,    -1,    -1,    36,   228,    -1,    -1,
      -1,   232,    -1,    -1,    -1,   111,   112,   113,   114,     4,
     116,   117,   243,   244,   245,    -1,    -1,    -1,    -1,   125,
      60,    61,    -1,    -1,    -1,   131,     4,     4,    -1,    24,
     136,    -1,    27,    28,    29,    30,    31,    32,    -1,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    24,    -1,    -1,    27,
      28,    29,    30,    31,    32,    -1,    -1,    -1,    36,    -1,
      -1,    38,    -1,   294,   295,    60,    61,     4,    -1,    -1,
     176,    -1,    -1,   304,    -1,    -1,   307,   117,   309,   310,
      75,    76,    60,    61,   315,    -1,    81,    82,    -1,    -1,
      -1,    -1,    -1,   199,    -1,    -1,    -1,    75,    76,    -1,
      37,    -1,   208,    -1,    -1,    -1,    -1,    -1,   148,    46,
      47,    48,    49,    50,    51,    -1,    -1,     1,    -1,    -1,
      -1,     5,   117,   229,   230,     9,    10,    11,    12,    13,
      -1,   375,    -1,   110,   111,   112,   113,   114,   115,   117,
     117,    -1,    -1,    -1,    -1,    -1,   252,     4,    -1,    -1,
      -1,    -1,    -1,   148,    -1,    -1,   387,   263,    95,    -1,
      -1,    45,    -1,    -1,    -1,   271,    -1,    24,    52,    -1,
     148,    -1,   278,    30,    31,    32,    -1,   283,    -1,    36,
     286,    -1,    -1,    -1,   290,    -1,    70,    71,    72,    73,
      74,    -1,    -1,    -1,   300,     4,    -1,    -1,    -1,    83,
      84,    85,    86,    60,    61,    -1,    -1,    -1,    -1,    93,
      -1,    -1,    96,    -1,    -1,    24,    -1,    -1,     4,   103,
      -1,    30,    31,    32,    81,    82,     4,    36,    -1,    -1,
      -1,    40,    41,    42,   118,    -1,    -1,   121,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    -1,   132,    -1,
      36,    60,    61,    -1,   138,    -1,   140,    -1,    -1,    -1,
     117,     4,   141,   142,   143,   144,   145,   146,   152,    -1,
      -1,    -1,    -1,    -1,    60,    61,    -1,    55,   384,    -1,
     386,    24,    -1,    -1,   390,    -1,    -1,    30,    31,    32,
      68,   148,    -1,    36,    -1,     0,     1,    -1,   404,    -1,
       5,    -1,    -1,    -1,     9,    10,    11,    12,    13,    87,
      88,    89,    90,    -1,    -1,    -1,     1,    60,    61,    97,
      -1,    99,   100,   101,    -1,    -1,    -1,   105,    -1,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,   148,
      45,    -1,    -1,    -1,     4,    -1,    -1,    52,    -1,    -1,
     128,   129,   130,    -1,    39,    -1,    -1,    -1,    43,    44,
      -1,    -1,   148,    -1,    24,    70,    71,    72,    73,    74,
      30,    31,    32,    -1,    -1,    -1,    36,    -1,    83,    84,
      85,    86,    -1,    -1,    69,    -1,    -1,    -1,    93,    -1,
      -1,    96,    77,    78,    -1,    -1,    -1,    -1,   103,    -1,
      60,    61,    -1,    -1,    -1,    -1,    91,    92,     4,    -1,
      -1,    -1,    -1,   118,    -1,    -1,   121,   102,    -1,   104,
      80,   106,   107,   108,   109,    -1,    -1,   132,    -1,    -1,
      -1,   116,    -1,   138,    -1,   140,    -1,    -1,    -1,   124,
      -1,    -1,   127,    -1,    -1,    -1,   131,     4,    62,    63,
      64,    65,    66,    67,   139,    -1,    -1,    53,    54,    55,
      56,    57,    58,    59,     4,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    68,    30,    31,    32,    30,    31,    32,    36,
      -1,    -1,    36,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      30,    31,    32,    -1,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    60,    61,    -1,    60,    61,    -1,   105,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      60,    61,    -1,    -1,    81,    82,    88,    -1,    90,    -1,
      -1,    -1,   128,   129,   130,    -1,    -1,    -1,    88,    79,
      80,    81,    82,    -1,    -1,    99,   100,   101,    -1,   111,
     112,   113,   114,   115,   116,   117,   118,   119,    -1,   121,
     117,   111,   112,   113,   114,   115,   116,   117,   118,   119,
      -1,   121
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,   156,   157,   165,     4,   148,   161,   163,   164,
       0,     1,     5,     9,    10,    11,    12,    13,    45,    52,
      70,    71,    72,    73,    74,    83,    84,    85,    86,    93,
      96,   103,   118,   121,   132,   138,   140,   158,   159,   166,
     172,   191,   193,   196,   157,   162,   163,   147,   147,     1,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      39,    43,    44,    69,    77,    78,    91,    92,   102,   104,
     106,   107,   108,   109,   116,   124,   127,   131,   139,   167,
     211,   147,   173,   175,   180,   183,   189,   194,   195,   197,
     199,   164,   170,   147,   200,   164,   208,   158,   147,   192,
     164,   149,   150,   153,   209,   209,   161,   211,    25,    26,
     214,   215,   225,   229,   231,   230,   233,   234,   235,   237,
     161,   238,   161,   161,   212,   164,   213,   161,   161,   240,
     161,   164,   161,   164,   151,   169,    68,   174,    38,   105,
     128,   130,   164,   174,   176,   177,   178,   179,   110,   111,
     112,   113,   114,   115,   117,   164,   176,   181,   182,    37,
      46,    47,    48,    49,    50,    51,    95,   164,   184,   185,
     186,   187,   188,    53,    54,    55,    56,    57,    58,    59,
     129,   164,   174,   177,   178,   179,   190,    82,   164,    24,
      30,    31,    32,    36,    60,    61,    81,    82,   117,   164,
     216,   217,   218,   220,   221,   224,    55,    87,    88,    89,
      90,    97,    99,   100,   101,   164,   190,   198,   198,   216,
     147,   119,   120,   122,   123,   164,   171,     4,   133,   134,
     135,   136,   137,   148,   177,   178,   179,   204,   206,   207,
     141,   142,   143,   144,   145,   146,   161,   164,   164,   210,
     211,     3,   161,   216,   220,   221,   223,   224,    27,    28,
      29,    75,    76,   161,   216,   220,   221,   223,   226,   227,
     228,   161,   216,   220,   221,   226,    40,    41,    42,   161,
     216,   221,   232,   164,   216,   221,   161,   216,   220,   221,
     161,   216,   221,    79,    80,   164,   216,   221,   223,   236,
     164,   216,   221,   236,   164,   216,   221,   239,   161,   239,
      58,    59,    82,   125,   126,   241,   161,   152,   158,     6,
       7,   168,   161,   164,   164,     3,   164,   164,   164,   164,
     164,     3,   164,   164,   161,   164,     3,   164,   164,    33,
      34,    35,   222,     3,   160,   161,    62,    63,    64,    65,
      66,    67,   219,   164,   164,   161,   164,   198,   164,   164,
     147,   164,   161,   161,     4,   148,   201,   203,   164,   205,
     206,   164,   164,   164,   154,   150,   161,   161,   161,   161,
     161,   161,   161,   164,   164,   161,   164,   164,   216,   221,
     164,   164,     3,   164,   152,   167,   169,   202,   203,   149,
     150,   210,   161,   161,   164,   161,   149,   150,   207,   161,
     203
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   155,   156,   156,   157,   157,   158,   158,   159,   159,
     159,   160,   160,   161,   161,   162,   162,   163,   164,   165,
     166,   166,   166,   166,   166,   167,   168,   168,   168,   169,
     169,   170,   170,   170,   170,   171,   171,   172,   172,   172,
     172,   172,   172,   172,   172,   172,   172,   172,   172,   172,
     172,   172,   172,   172,   173,   173,   174,   175,   175,   175,
     175,   175,   175,   176,   177,   178,   179,   180,   180,   180,
     180,   180,   181,   181,   181,   181,   182,   182,   183,   183,
     183,   183,   183,   183,   184,   184,   185,   185,   186,   186,
     187,   188,   189,   189,   189,   189,   189,   189,   189,   189,
     189,   190,   190,   190,   190,   190,   191,   191,   191,   192,
     192,   193,   193,   194,   194,   195,   195,   195,   195,   195,
     196,   196,   197,   197,   197,   197,   197,   197,   197,   197,
     197,   198,   198,   198,   199,   199,   199,   200,   200,   200,
     200,   200,   200,   200,   200,   200,   201,   201,   202,   202,
     203,   204,   204,   205,   205,   206,   207,   208,   208,   208,
     208,   208,   208,   208,   209,   210,   210,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   211,   211,   211,   211,   211,   211,   211,   212,   211,
     211,   213,   211,   211,   211,   211,   211,   211,   211,   211,
     211,   214,   214,   215,   215,   215,   215,   215,   216,   216,
     217,   217,   217,   217,   218,   218,   219,   219,   219,   219,
     219,   219,   220,   221,   222,   222,   222,   223,   224,   224,
     225,   225,   225,   225,   225,   225,   226,   227,   227,   227,
     227,   228,   228,   229,   229,   229,   229,   229,   230,   230,
     230,   231,   231,   231,   231,   231,   232,   232,   233,   233,
     233,   233,   234,   234,   234,   235,   235,   235,   235,   235,
     235,   236,   237,   237,   237,   237,   238,   238,   238,   239,
     239,   239,   240,   240,   240,   240,   240,   241,   241
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     2,     1,     2,
       2,     0,     1,     1,     3,     1,     3,     1,     1,     3,
       2,     2,     3,     4,     2,     3,     0,     2,     2,     3,
       2,     0,     2,     2,     2,     1,     1,     2,     3,     3,
       1,     4,     3,     3,     1,     4,     4,     2,     3,     2,
       2,     2,     3,     2,     0,     2,     2,     0,     2,     2,
       2,     2,     2,     1,     1,     2,     2,     0,     2,     2,
       2,     2,     2,     2,     2,     1,     2,     2,     0,     2,
       2,     2,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     3,     3,     3,     3,     3,     2,     3,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     0,
       2,     1,     1,     0,     2,     0,     2,     2,     2,     2,
       1,     1,     0,     3,     3,     2,     3,     3,     2,     3,
       3,     1,     1,     1,     0,     2,     3,     0,     3,     2,
       2,     2,     3,     3,     3,     3,     1,     3,     1,     3,
       1,     1,     3,     1,     3,     1,     1,     0,     2,     2,
       2,     3,     3,     3,     3,     1,     3,     2,     2,     2,
       1,     1,     2,     3,     4,     4,     4,     3,     4,     4,
       4,     3,     5,     4,     2,     5,     2,     2,     0,     6,
       3,     0,     5,     2,     2,     2,     2,     3,     2,     2,
       1,     1,     1,     0,     2,     2,     2,     2,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     1,     1,     2,     1,
       0,     2,     2,     2,     2,     2,     1,     1,     1,     1,
       1,     1,     1,     0,     2,     2,     2,     2,     0,     2,
       2,     0,     2,     3,     2,     2,     1,     1,     0,     2,
       2,     2,     0,     2,     2,     0,     2,     2,     2,     2,
       2,     2,     0,     2,     2,     2,     0,     2,     2,     0,
       2,     2,     0,     3,     3,     3,     2,     1,     1
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
#line 173 "sieve/sieve.y" /* yacc.c:1257  */
      { free(((*yyvaluep).sval));          }
#line 1855 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 158: /* commands  */
#line 169 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1861 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 159: /* command  */
#line 169 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1867 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 160: /* optstringlist  */
#line 172 "sieve/sieve.y" /* yacc.c:1257  */
      { strarray_free(((*yyvaluep).sl)); }
#line 1873 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 161: /* stringlist  */
#line 172 "sieve/sieve.y" /* yacc.c:1257  */
      { strarray_free(((*yyvaluep).sl)); }
#line 1879 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 162: /* strings  */
#line 172 "sieve/sieve.y" /* yacc.c:1257  */
      { strarray_free(((*yyvaluep).sl)); }
#line 1885 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 163: /* string1  */
#line 172 "sieve/sieve.y" /* yacc.c:1257  */
      { strarray_free(((*yyvaluep).sl)); }
#line 1891 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 164: /* string  */
#line 173 "sieve/sieve.y" /* yacc.c:1257  */
      { free(((*yyvaluep).sval));          }
#line 1897 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 166: /* control  */
#line 169 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1903 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 167: /* thenelse  */
#line 169 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1909 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 168: /* elsif  */
#line 169 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1915 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 169: /* block  */
#line 169 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1921 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 172: /* action  */
#line 169 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1927 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 175: /* ftags  */
#line 169 "sieve/sieve.y" /* yacc.c:1257  */
      { free_tree(((*yyvaluep).cl));     }
#line 1933 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 204: /* timelist  */
#line 174 "sieve/sieve.y" /* yacc.c:1257  */
      { arrayu64_free(((*yyvaluep).nl)); }
#line 1939 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 205: /* times  */
#line 174 "sieve/sieve.y" /* yacc.c:1257  */
      { arrayu64_free(((*yyvaluep).nl)); }
#line 1945 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 206: /* time1  */
#line 174 "sieve/sieve.y" /* yacc.c:1257  */
      { arrayu64_free(((*yyvaluep).nl)); }
#line 1951 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 209: /* testlist  */
#line 170 "sieve/sieve.y" /* yacc.c:1257  */
      { free_testlist(((*yyvaluep).testl)); }
#line 1957 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 210: /* tests  */
#line 170 "sieve/sieve.y" /* yacc.c:1257  */
      { free_testlist(((*yyvaluep).testl)); }
#line 1963 "sieve/sieve.c" /* yacc.c:1257  */
        break;

    case 211: /* test  */
#line 171 "sieve/sieve.y" /* yacc.c:1257  */
      { free_test(((*yyvaluep).test));     }
#line 1969 "sieve/sieve.c" /* yacc.c:1257  */
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
#line 368 "sieve/sieve.y" /* yacc.c:1652  */
    { sscript->cmds = NULL; }
#line 2240 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 3:
#line 369 "sieve/sieve.y" /* yacc.c:1652  */
    { sscript->cmds = (yyvsp[0].cl); }
#line 2246 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 7:
#line 380 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = (yyvsp[-1].cl); (yyval.cl)->next = (yyvsp[0].cl); }
#line 2252 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 10:
#line 386 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     struct buf buf = BUF_INITIALIZER;
                                     buf_printf(&buf, "%s: line %d",
                                                error_message(SIEVE_UNSUPP_EXT),
                                                sievelineno);
                                     sscript->support |= SIEVE_CAPA_IHAVE;
                                     (yyval.cl) = build_rej_err(sscript, B_ERROR,
                                                        buf_release(&buf));
                                 }
#line 2266 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 11:
#line 398 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.sl) = strarray_new(); }
#line 2272 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 14:
#line 404 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.sl) = (yyvsp[-1].sl); }
#line 2278 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 16:
#line 409 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.sl) = (yyvsp[-2].sl); strarray_appendm((yyval.sl), (yyvsp[0].sval)); }
#line 2284 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 17:
#line 413 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.sl) = strarray_new();
                                     strarray_appendm((yyval.sl), (yyvsp[0].sval));
                                 }
#line 2293 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 18:
#line 420 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.sval) = (yyvsp[0].sval); chk_match_vars(sscript, (yyval.sval)); }
#line 2299 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 19:
#line 427 "sieve/sieve.y" /* yacc.c:1652  */
    { check_reqs(sscript, (yyvsp[-1].sl)); }
#line 2305 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 20:
#line 431 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = (yyvsp[0].cl); }
#line 2311 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 21:
#line 432 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_STOP, sscript); }
#line 2317 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 22:
#line 433 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_rej_err(sscript, B_ERROR, (yyvsp[-1].sval)); }
#line 2323 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 23:
#line 435 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_include(sscript, (yyvsp[-2].cl), (yyvsp[-1].sval)); }
#line 2329 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 24:
#line 436 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_RETURN, sscript); }
#line 2335 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 25:
#line 440 "sieve/sieve.y" /* yacc.c:1652  */
    { 
                                     if ((yyvsp[-2].test)->ignore_err) {
                                         /* end of block - decrement counter */
                                         sscript->ignore_err--;
                                     }

                                     (yyval.cl) = new_if((yyvsp[-2].test), (yyvsp[-1].cl), (yyvsp[0].cl));
                                 }
#line 2348 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 26:
#line 451 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = NULL; }
#line 2354 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 27:
#line 452 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = (yyvsp[0].cl); }
#line 2360 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 28:
#line 453 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = (yyvsp[0].cl); }
#line 2366 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 29:
#line 457 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = (yyvsp[-1].cl); }
#line 2372 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 30:
#line 458 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = NULL; }
#line 2378 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 31:
#line 463 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_INCLUDE, sscript); }
#line 2384 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 32:
#line 464 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.inc.location != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_CONFLICTING_TAGS,
                                                      ":personal", ":location");
                                     }

                                     (yyval.cl)->u.inc.location = (yyvsp[0].nval);
                                 }
#line 2398 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 33:
#line 473 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.inc.once != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":once");
                                     }

                                     (yyval.cl)->u.inc.once = INC_ONCE_MASK;
                                 }
#line 2412 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 34:
#line 482 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.inc.optional != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":optional");
                                     }

                                     (yyval.cl)->u.inc.optional = INC_OPTIONAL_MASK;
                                 }
#line 2426 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 35:
#line 495 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_PERSONAL; }
#line 2432 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 36:
#line 496 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_GLOBAL;   }
#line 2438 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 37:
#line 503 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_keep(sscript, (yyvsp[0].cl)); }
#line 2444 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 38:
#line 504 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_fileinto(sscript, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2450 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 39:
#line 505 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_redirect(sscript, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2456 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 40:
#line 506 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_DISCARD, sscript); }
#line 2462 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 41:
#line 508 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_set(sscript, (yyvsp[-2].cl), (yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 2468 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 42:
#line 509 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_vacation(sscript, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2474 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 43:
#line 513 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_flag(sscript, (yyvsp[-1].cl), (yyvsp[0].sl)); }
#line 2480 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 44:
#line 516 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_flag(sscript,
                                                   new_command((yyvsp[0].nval), sscript),
                                                   strarray_split("\\Flagged",
                                                                  NULL, 0)); }
#line 2489 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 45:
#line 522 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_addheader(sscript,
                                                        (yyvsp[-2].cl), (yyvsp[-1].sval), (yyvsp[0].sval)); }
#line 2496 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 46:
#line 525 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_deleteheader(sscript,
                                                           (yyvsp[-2].cl), (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 2503 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 47:
#line 528 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_rej_err(sscript, (yyvsp[-1].nval), (yyvsp[0].sval)); }
#line 2509 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 48:
#line 529 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_notify(sscript,
                                                     B_ENOTIFY, (yyvsp[-1].cl), (yyvsp[0].sval)); }
#line 2516 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 49:
#line 532 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_notify(sscript,
                                                     B_NOTIFY, (yyvsp[0].cl), NULL); }
#line 2523 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 50:
#line 535 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_denotify(sscript, (yyvsp[0].cl)); }
#line 2529 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 51:
#line 536 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_log(sscript, (yyvsp[0].sval)); }
#line 2535 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 52:
#line 537 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_snooze(sscript, (yyvsp[-1].cl), (yyvsp[0].nl)); }
#line 2541 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 53:
#line 538 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = build_imip(sscript, (yyvsp[0].cl)); }
#line 2547 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 54:
#line 543 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_KEEP, sscript);
                                     flags = &((yyval.cl)->u.k.flags);
                                 }
#line 2556 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 56:
#line 552 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 2577 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 57:
#line 572 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_FILEINTO, sscript);
                                     copy = &((yyval.cl)->u.f.copy);
                                     flags = &((yyval.cl)->u.f.flags);
                                     create = &((yyval.cl)->u.f.create);
                                     specialuse = &((yyval.cl)->u.f.specialuse);
                                     mailboxid = &((yyval.cl)->u.f.mailboxid);
                                 }
#line 2590 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 63:
#line 589 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 2608 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 64:
#line 606 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 2626 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 65:
#line 623 "sieve/sieve.y" /* yacc.c:1652  */
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
                                     else if (*mailboxid != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_CONFLICTING_TAGS,
                                                      ":specialuse",
                                                      ":mailboxid");
                                     }

                                     *specialuse = (yyvsp[0].sval);
                                 }
#line 2653 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 66:
#line 648 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* **mailboxid assigned by calling rule */
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
                                     else if (*specialuse != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_CONFLICTING_TAGS,
                                                      ":mailboxid",
                                                      ":specialuse");
                                     }

                                     *mailboxid = (yyvsp[0].sval);
                                 }
#line 2680 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 67:
#line 674 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_REDIRECT, sscript);
                                     copy = &((yyval.cl)->u.r.copy);
                                 }
#line 2689 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 69:
#line 679 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 2706 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 70:
#line 691 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (!supported(SIEVE_CAPA_REDIR_DELBY)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "redirect-deliverby");
                                     }
                                 }
#line 2718 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 71:
#line 698 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (!supported(SIEVE_CAPA_REDIR_DSN)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "redirect-dsn");
                                     }
                                 }
#line 2730 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 72:
#line 708 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* $0 refers to rtags */
                                     commandlist_t *c = (yyvsp[-2].cl);

                                     if (c->u.r.bytime != NULL) {
                                         if (isdigit(c->u.r.bytime[0])) {
                                             sieveerror_c(sscript,
                                                          SIEVE_CONFLICTING_TAGS,
                                                          ":bytimerelative",
                                                          ":bytimeabsolute");
                                         }
                                         else {
                                             sieveerror_c(sscript,
                                                          SIEVE_DUPLICATE_TAG,
                                                          ":bytimerelative");
                                         }
                                     }                                         

                                     struct buf buf = BUF_INITIALIZER;
                                     buf_printf(&buf, "+%d", (yyvsp[0].nval));
                                     c->u.r.bytime = buf_release(&buf);
                                 }
#line 2757 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 73:
#line 730 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* $0 refers to rtags */
                                     commandlist_t *c = (yyvsp[-2].cl);

                                     if (c->u.r.bytime != NULL) {
                                         if (isdigit(c->u.r.bytime[0])) {
                                             sieveerror_c(sscript,
                                                          SIEVE_DUPLICATE_TAG,
                                                          ":bytimeabsolute");
                                         }
                                         else {
                                             sieveerror_c(sscript,
                                                          SIEVE_CONFLICTING_TAGS,
                                                          ":bytimeabsolute",
                                                          ":bytimerelative");
                                         }
                                     }

                                     c->u.r.bytime = (yyvsp[0].sval);
                                 }
#line 2782 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 74:
#line 750 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 2799 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 75:
#line 762 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 2816 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 76:
#line 778 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 2833 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 77:
#line 790 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 2850 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 78:
#line 806 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_SET, sscript); }
#line 2856 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 79:
#line 807 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.s.modifiers & BFV_MOD40_MASK) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "precedence 40 modifier");
                                     }

                                     (yyval.cl)->u.s.modifiers |= (yyvsp[0].nval);
                                 }
#line 2870 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 80:
#line 816 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.s.modifiers & BFV_MOD30_MASK) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "precedence 30 modifier");
                                     }

                                     (yyval.cl)->u.s.modifiers |= (yyvsp[0].nval);
                                 }
#line 2884 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 81:
#line 825 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.s.modifiers & BFV_MOD20_MASK) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "precedence 20 modifier");
                                     }

                                     (yyval.cl)->u.s.modifiers |= (yyvsp[0].nval);
                                 }
#line 2898 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 82:
#line 834 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.s.modifiers & BFV_MOD15_MASK) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "precedence 15 modifier");
                                     }

                                     (yyval.cl)->u.s.modifiers |= (yyvsp[0].nval);
                                 }
#line 2912 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 83:
#line 843 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.s.modifiers & BFV_MOD10_MASK) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "precedence 10 modifier");
                                     }

                                     (yyval.cl)->u.s.modifiers |= (yyvsp[0].nval);
                                 }
#line 2926 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 84:
#line 856 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = BFV_LOWER; }
#line 2932 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 85:
#line 857 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = BFV_UPPER; }
#line 2938 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 86:
#line 860 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = BFV_LOWERFIRST; }
#line 2944 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 87:
#line 861 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = BFV_UPPERFIRST; }
#line 2950 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 88:
#line 864 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = BFV_QUOTEWILDCARD; }
#line 2956 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 89:
#line 865 "sieve/sieve.y" /* yacc.c:1652  */
    { 
                                     if (!supported(SIEVE_CAPA_REGEX)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "regex");
                                     }

                                     (yyval.nval) = BFV_QUOTEREGEX;
                                 }
#line 2970 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 90:
#line 877 "sieve/sieve.y" /* yacc.c:1652  */
    { 
                                     if (!supported(SIEVE_CAPA_ENOTIFY)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "enotify");
                                     }

                                     (yyval.nval) = BFV_ENCODEURL;
                                 }
#line 2984 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 91:
#line 888 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = BFV_LENGTH; }
#line 2990 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 92:
#line 893 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_VACATION, sscript);
                                     flags = &((yyval.cl)->u.v.fcc.flags);
                                     create = &((yyval.cl)->u.v.fcc.create);
                                     specialuse = &((yyval.cl)->u.v.fcc.specialuse);
                                     mailboxid = &((yyval.cl)->u.v.fcc.mailboxid);
                                     fccfolder = &((yyval.cl)->u.v.fcc.folder);
                                 }
#line 3003 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 93:
#line 901 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.v.seconds != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":days");
                                     }

                                     (yyval.cl)->u.v.seconds = (yyvsp[0].nval) * DAY2SEC;
                                 }
#line 3017 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 94:
#line 910 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 3036 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 95:
#line 924 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.v.subject != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":subject");
                                         free((yyval.cl)->u.v.subject);
                                     }

                                     (yyval.cl)->u.v.subject = (yyvsp[0].sval);
                                 }
#line 3051 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 96:
#line 934 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.v.from != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":from");
                                         free((yyval.cl)->u.v.from);
                                     }

                                     (yyval.cl)->u.v.from = (yyvsp[0].sval);
                                 }
#line 3066 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 97:
#line 946 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.v.addresses != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":addresses");
                                         strarray_free((yyval.cl)->u.v.addresses);
                                     }

                                     (yyval.cl)->u.v.addresses = (yyvsp[0].sl);
                                 }
#line 3081 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 98:
#line 956 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.v.mime != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":mime");
                                     }

                                     (yyval.cl)->u.v.mime = 1;
                                 }
#line 3095 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 99:
#line 965 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.v.handle != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":handle");
                                         free((yyval.cl)->u.v.handle);
                                     }

                                     (yyval.cl)->u.v.handle = (yyvsp[0].sval);
                                 }
#line 3110 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 101:
#line 979 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 3131 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 106:
#line 1003 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_SETFLAG;    }
#line 3137 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 107:
#line 1004 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_ADDFLAG;    }
#line 3143 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 108:
#line 1005 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_REMOVEFLAG; }
#line 3149 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 109:
#line 1010 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command((yyvsp[0].nval), sscript); }
#line 3155 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 110:
#line 1011 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 3175 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 111:
#line 1030 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_ADDFLAG;   }
#line 3181 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 112:
#line 1031 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_REMOVEFLAG; }
#line 3187 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 113:
#line 1036 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_ADDHEADER, sscript); }
#line 3193 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 114:
#line 1037 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.ah.index < 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":last");
                                     }

                                     (yyval.cl)->u.ah.index = -1;
                                 }
#line 3207 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 115:
#line 1050 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_DELETEHEADER, sscript);
                                     ctags = &((yyval.cl)->u.dh.comp);
                                 }
#line 3216 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 120:
#line 1062 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_REJECT;  }
#line 3222 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 121:
#line 1063 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_EREJECT; }
#line 3228 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 122:
#line 1074 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_ENOTIFY, sscript);
                                     flags = &((yyval.cl)->u.n.fcc.flags);
                                     create = &((yyval.cl)->u.n.fcc.create);
                                     specialuse = &((yyval.cl)->u.n.fcc.specialuse);
                                     mailboxid = &((yyval.cl)->u.n.fcc.mailboxid);
                                     fccfolder = &((yyval.cl)->u.n.fcc.folder);
                                 }
#line 3241 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 123:
#line 1084 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.from != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":from");
                                         free((yyval.cl)->u.n.from);
                                     }

                                     (yyval.cl)->u.n.from = (yyvsp[0].sval);
                                 }
#line 3256 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 124:
#line 1096 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.priority != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":importance");
                                     }

                                     (yyval.cl)->u.n.priority = (yyvsp[0].nval);
                                 }
#line 3270 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 126:
#line 1108 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.id != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":id");
                                         free((yyval.cl)->u.n.id);
                                     }

                                     (yyval.cl)->u.n.id = (yyvsp[0].sval);
                                 }
#line 3285 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 127:
#line 1118 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.method != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":method");
                                         free((yyval.cl)->u.n.method);
                                     }

                                     (yyval.cl)->u.n.method = (yyvsp[0].sval);
                                 }
#line 3300 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 128:
#line 1128 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.priority != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "priority");
                                     }

                                     (yyval.cl)->u.n.priority = (yyvsp[0].nval);
                                 }
#line 3314 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 129:
#line 1139 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.message != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":message");
                                         free((yyval.cl)->u.n.message);
                                     }

                                     (yyval.cl)->u.n.message = (yyvsp[0].sval);
                                 }
#line 3329 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 130:
#line 1151 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.n.options != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":options");
                                         strarray_free((yyval.cl)->u.n.options);
                                     }

                                     (yyval.cl)->u.n.options = (yyvsp[0].sl);
                                 }
#line 3344 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 131:
#line 1165 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_LOW;    }
#line 3350 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 132:
#line 1166 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_NORMAL; }
#line 3356 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 133:
#line 1167 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_HIGH;   }
#line 3362 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 134:
#line 1172 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_DENOTIFY, sscript);
                                     ctags = &((yyval.cl)->u.d.comp);
                                 }
#line 3371 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 135:
#line 1176 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.d.priority != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "priority");
                                     }

                                     (yyval.cl)->u.d.priority = (yyvsp[0].nval);
                                 }
#line 3385 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 136:
#line 1187 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.d.pattern) free((yyval.cl)->u.d.pattern);
                                     (yyval.cl)->u.d.pattern = (yyvsp[0].sval);
                                 }
#line 3394 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 137:
#line 1195 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.cl) = new_command(B_SNOOZE, sscript);
                                     create = &((yyval.cl)->u.sn.f.create);
                                     specialuse = &((yyval.cl)->u.sn.f.specialuse);
                                     mailboxid = &((yyval.cl)->u.sn.f.mailboxid);
                                 }
#line 3405 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 138:
#line 1201 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.sn.f.folder != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":mailbox");
                                         free((yyval.cl)->u.sn.f.folder);
                                     }

                                     (yyval.cl)->u.sn.f.folder = (yyvsp[0].sval);
                                 }
#line 3420 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 142:
#line 1216 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 3440 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 143:
#line 1232 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 3460 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 144:
#line 1248 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.sn.days != 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":weekdays");
                                     }

                                     (yyval.cl)->u.sn.days = (yyvsp[0].nval);
                                 }
#line 3474 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 145:
#line 1257 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.sn.tzid != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":tzid");
                                         free((yyval.cl)->u.sn.tzid);
                                     }

                                     (yyval.cl)->u.sn.tzid = (yyvsp[0].sval);
                                 }
#line 3489 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 147:
#line 1271 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = (yyvsp[-1].nval); }
#line 3495 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 149:
#line 1276 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = (yyvsp[-2].nval) | (yyvsp[0].nval); }
#line 3501 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 150:
#line 1280 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = verify_weekday(sscript, (yyvsp[0].sval)); }
#line 3507 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 152:
#line 1285 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nl) = (yyvsp[-1].nl); }
#line 3513 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 154:
#line 1290 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nl) = (yyvsp[-2].nl); arrayu64_add((yyval.nl), (yyvsp[0].nval)); }
#line 3519 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 155:
#line 1294 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.nl) = arrayu64_new();
                                     arrayu64_add((yyval.nl), (yyvsp[0].nval));
                                 }
#line 3528 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 156:
#line 1301 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = verify_time(sscript, (yyvsp[0].sval)); }
#line 3534 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 157:
#line 1306 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.cl) = new_command(B_PROCESSIMIP, sscript); }
#line 3540 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 158:
#line 1307 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.imip.invites_only) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":invitesonly");
                                     }
                                     else if ((yyval.cl)->u.imip.updates_only) {
                                         sieveerror_c(sscript,
                                                      SIEVE_CONFLICTING_TAGS,
                                                      ":invitesonly",
                                                      ":updatesonly");
                                     }
                                     else if ((yyval.cl)->u.imip.delete_canceled) {
                                         sieveerror_c(sscript,
                                                      SIEVE_CONFLICTING_TAGS,
                                                      ":invitesonly",
                                                      ":deletecanceled");
                                     }

                                     (yyval.cl)->u.imip.invites_only = 1;
                                 }
#line 3566 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 159:
#line 1329 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.imip.updates_only) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":updatesonly");
                                     }
                                     else if ((yyval.cl)->u.imip.invites_only) {
                                         sieveerror_c(sscript,
                                                      SIEVE_CONFLICTING_TAGS,
                                                      ":invitesonly",
                                                      ":updatesonly");
                                     }
                                     else if ((yyval.cl)->u.imip.calendarid != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_CONFLICTING_TAGS,
                                                      ":updatesonly",
                                                      ":calendarid");
                                     }

                                     (yyval.cl)->u.imip.updates_only = 1;
                                 }
#line 3592 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 160:
#line 1352 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.imip.delete_canceled) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":deletecanceled");
                                     }
                                     else if ((yyval.cl)->u.imip.invites_only) {
                                         sieveerror_c(sscript,
                                                      SIEVE_CONFLICTING_TAGS,
                                                      ":invitesonly",
                                                      ":deletecanceled");
                                     }

                                     (yyval.cl)->u.imip.delete_canceled = 1;
                                 }
#line 3612 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 161:
#line 1368 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.imip.calendarid != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":calendarid");
                                         free((yyval.cl)->u.imip.calendarid);
                                     }
                                     else if ((yyval.cl)->u.imip.updates_only) {
                                         sieveerror_c(sscript,
                                                      SIEVE_CONFLICTING_TAGS,
                                                      ":updatesonly",
                                                      ":calendarid");
                                     }

                                     (yyval.cl)->u.imip.calendarid = (yyvsp[0].sval);
                                 }
#line 3633 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 162:
#line 1385 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.imip.outcome_var != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":outcome");
                                         free((yyval.cl)->u.imip.outcome_var);
                                     }
                                     else if (!supported(SIEVE_CAPA_VARIABLES)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "variables");
                                     }

                                     (yyval.cl)->u.imip.outcome_var = (yyvsp[0].sval);
                                 }
#line 3653 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 163:
#line 1400 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.cl)->u.imip.errstr_var != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":errstr");
                                         free((yyval.cl)->u.imip.errstr_var);
                                     }
                                     else if (!supported(SIEVE_CAPA_VARIABLES)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "variables");
                                     }

                                     (yyval.cl)->u.imip.errstr_var = (yyvsp[0].sval);
                                 }
#line 3673 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 164:
#line 1421 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.testl) = (yyvsp[-1].testl); }
#line 3679 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 165:
#line 1425 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.testl) = new_testlist((yyvsp[0].test), NULL); }
#line 3685 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 166:
#line 1426 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.testl) = new_testlist((yyvsp[-2].test), (yyvsp[0].testl)); }
#line 3691 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 167:
#line 1430 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_anyof(sscript, (yyvsp[0].testl)); }
#line 3697 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 168:
#line 1431 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_allof(sscript, (yyvsp[0].testl)); }
#line 3703 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 169:
#line 1432 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_not(sscript, (yyvsp[0].test));   }
#line 3709 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 170:
#line 1433 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = new_test(BC_FALSE, sscript); }
#line 3715 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 171:
#line 1434 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = new_test(BC_TRUE, sscript);  }
#line 3721 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 172:
#line 1435 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_EXISTS, sscript);
                                     (yyval.test)->u.sl = (yyvsp[0].sl);
                                     (yyval.test)->nargs = bc_precompile((yyval.test)->args, "S",
                                                               (yyval.test)->u.sl);
                                 }
#line 3732 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 173:
#line 1441 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_SIZE, sscript);
                                     (yyval.test)->u.sz.t = (yyvsp[-1].nval);
                                     (yyval.test)->u.sz.n = (yyvsp[0].nval);
                                     (yyval.test)->nargs = bc_precompile((yyval.test)->args, "ii",
                                                               (yyval.test)->u.sz.t,
                                                               (yyval.test)->u.sz.n);
                                 }
#line 3745 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 174:
#line 1451 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_header(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3751 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 175:
#line 1454 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_address(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3757 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 176:
#line 1456 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_envelope(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3763 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 177:
#line 1458 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_body(sscript, (yyvsp[-1].test), (yyvsp[0].sl)); }
#line 3769 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 178:
#line 1461 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_mbox_meta(sscript,
                                                        (yyvsp[-2].test), NULL, (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3776 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 179:
#line 1465 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_stringt(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3782 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 180:
#line 1472 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_hasflag(sscript, (yyvsp[-2].test), (yyvsp[-1].sl), (yyvsp[0].sl)); }
#line 3788 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 181:
#line 1474 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_hasflag(sscript, (yyvsp[-1].test), NULL, (yyvsp[0].sl)); }
#line 3794 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 182:
#line 1477 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_date(sscript, (yyvsp[-3].test), (yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3800 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 183:
#line 1480 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_date(sscript, (yyvsp[-2].test), NULL, (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3806 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 184:
#line 1483 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_VALIDNOTIFYMETHOD, sscript);
                                     (yyval.test)->u.sl = (yyvsp[0].sl);
                                     (yyval.test)->nargs = bc_precompile((yyval.test)->args, "S",
                                                               (yyval.test)->u.sl);
                                 }
#line 3817 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 185:
#line 1490 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_mbox_meta(sscript,
                                                        (yyvsp[-3].test), (yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3824 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 186:
#line 1493 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_ihave(sscript, (yyvsp[0].sl)); }
#line 3830 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 187:
#line 1496 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_MAILBOXEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), NULL, NULL, (yyvsp[0].sl));
                                 }
#line 3840 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 188:
#line 1502 "sieve/sieve.y" /* yacc.c:1652  */
    { bctype = BC_METADATA; }
#line 3846 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 189:
#line 1503 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_mbox_meta(sscript,
                                                        (yyvsp[-3].test), (yyvsp[-2].sval), (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3853 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 190:
#line 1507 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_METADATAEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), (yyvsp[-1].sval), NULL, (yyvsp[0].sl));
                                 }
#line 3863 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 191:
#line 1513 "sieve/sieve.y" /* yacc.c:1652  */
    { bctype = BC_SERVERMETADATA; }
#line 3869 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 192:
#line 1514 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_mbox_meta(sscript,
                                                        (yyvsp[-2].test), NULL, (yyvsp[-1].sval), (yyvsp[0].sl)); }
#line 3876 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 193:
#line 1518 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_SERVERMETADATAEXISTS,
                                                   sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), NULL, NULL, (yyvsp[0].sl));
                                 }
#line 3887 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 194:
#line 1526 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_VALIDEXTLIST, sscript);
                                     (yyval.test)->u.sl = (yyvsp[0].sl);
                                     (yyval.test)->nargs = bc_precompile((yyval.test)->args, "S",
                                                               (yyval.test)->u.sl);
                                 }
#line 3898 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 195:
#line 1532 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = build_duplicate(sscript, (yyvsp[0].test)); }
#line 3904 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 196:
#line 1535 "sieve/sieve.y" /* yacc.c:1652  */
    { 
                                     (yyval.test) = new_test(BC_SPECIALUSEEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), NULL, NULL, (yyvsp[0].sl));
                                 }
#line 3914 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 197:
#line 1542 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_SPECIALUSEEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), (yyvsp[-1].sval), NULL, (yyvsp[0].sl));
                                 }
#line 3924 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 198:
#line 1549 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_MAILBOXIDEXISTS, sscript);
                                     (yyval.test) = build_mbox_meta(sscript,
                                                          (yyval.test), NULL, NULL, (yyvsp[0].sl));
                                 }
#line 3934 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 199:
#line 1555 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_JMAPQUERY, sscript);
                                     (yyval.test) = build_jmapquery(sscript, (yyval.test), (yyvsp[0].sval));
                                 }
#line 3943 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 200:
#line 1560 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = new_test(BC_FALSE, sscript); }
#line 3949 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 201:
#line 1565 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_OVER;  }
#line 3955 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 202:
#line 1566 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_UNDER; }
#line 3961 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 203:
#line 1571 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_HEADER, sscript);
                                     ctags = &((yyval.test)->u.hhs.comp);
                                 }
#line 3970 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 208:
#line 1583 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* *ctags assigned by the calling rule */
                                     if (ctags->match != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "match-type");
                                     }

                                     ctags->match = (yyvsp[0].nval);
                                 }
#line 3985 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 209:
#line 1594 "sieve/sieve.y" /* yacc.c:1652  */
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
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "match-type");
                                     }

                                     ctags->match = (yyvsp[-1].nval);
                                     ctags->relation = (yyvsp[0].nval);
                                 }
#line 4007 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 210:
#line 1615 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_IS;       }
#line 4013 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 211:
#line 1616 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_CONTAINS; }
#line 4019 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 212:
#line 1617 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_MATCHES;  }
#line 4025 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 213:
#line 1618 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (!supported(SIEVE_CAPA_REGEX)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "regex");
                                     }

                                     (yyval.nval) = B_REGEX;
                                 }
#line 4039 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 214:
#line 1631 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_COUNT; }
#line 4045 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 215:
#line 1632 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_VALUE; }
#line 4051 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 216:
#line 1637 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_EQ; }
#line 4057 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 217:
#line 1638 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_NE; }
#line 4063 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 218:
#line 1639 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_GT; }
#line 4069 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 219:
#line 1640 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_GE; }
#line 4075 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 220:
#line 1641 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_LT; }
#line 4081 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 221:
#line 1642 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_LE; }
#line 4087 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 222:
#line 1647 "sieve/sieve.y" /* yacc.c:1652  */
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
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "match-type");
                                     }

                                     ctags->match = B_LIST;
                                 }
#line 4108 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 223:
#line 1668 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* *ctags assigned by the calling rule */
                                     if (ctags->collation != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":comparator");
                                     }

                                     ctags->collation = (yyvsp[0].nval);
                                 }
#line 4123 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 224:
#line 1682 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_OCTET;        }
#line 4129 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 225:
#line 1683 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_ASCIICASEMAP; }
#line 4135 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 226:
#line 1684 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (!supported(SIEVE_CAPA_COMP_NUMERIC)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "comparator-"
                                                      "i;ascii-numeric");
                                     }

                                     (yyval.nval) = B_ASCIINUMERIC;
                                 }
#line 4150 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 227:
#line 1698 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* *ctags assigned by the calling rule */
                                     if (ctags->index != 0 &&
                                         !supported(SIEVE_CAPA_INDEX)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "index");
                                     }
                                 }
#line 4164 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 228:
#line 1709 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 4184 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 229:
#line 1724 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 4204 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 230:
#line 1743 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_ADDRESS, sscript);
                                     ctags = &((yyval.test)->u.ae.comp);
                                 }
#line 4213 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 236:
#line 1756 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* $0 refers to a test_t* (ADDR/ENV)*/
                                     test_t *test = (yyvsp[-1].test);

                                     if (test->u.ae.addrpart != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "address-part");
                                     }

                                     test->u.ae.addrpart = (yyvsp[0].nval);
                                 }
#line 4230 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 237:
#line 1771 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_ALL;       }
#line 4236 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 238:
#line 1772 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_LOCALPART; }
#line 4242 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 239:
#line 1773 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_DOMAIN;    }
#line 4248 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 240:
#line 1774 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if (!supported(SIEVE_CAPA_SUBADDRESS)) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MISSING_REQUIRE,
                                                      "subaddress");
                                     }
                                 }
#line 4260 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 241:
#line 1785 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_USER;   }
#line 4266 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 242:
#line 1786 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_DETAIL; }
#line 4272 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 243:
#line 1791 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_ENVELOPE, sscript);
                                     ctags = &((yyval.test)->u.ae.comp);
                                 }
#line 4281 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 248:
#line 1803 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_ENVIRONMENT, sscript);
                                     ctags = &((yyval.test)->u.mm.comp);
                                 }
#line 4290 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 251:
#line 1813 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_BODY, sscript);
                                     ctags = &((yyval.test)->u.b.comp);
                                 }
#line 4299 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 252:
#line 1817 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.b.transform != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "transform");
                                     }

                                     (yyval.test)->u.b.transform = (yyvsp[0].nval);
                                 }
#line 4313 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 253:
#line 1828 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.b.transform != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_MULTIPLE_TAGS,
                                                      "transform");
                                         strarray_free((yyval.test)->u.b.content_types);
                                     }

                                     (yyval.test)->u.b.transform = B_CONTENT;
                                     (yyval.test)->u.b.content_types = (yyvsp[0].sl);
                                 }
#line 4329 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 256:
#line 1846 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_RAW;  }
#line 4335 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 257:
#line 1847 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_TEXT; }
#line 4341 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 258:
#line 1852 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_STRING, sscript);
                                     ctags = &((yyval.test)->u.hhs.comp);
                                 }
#line 4350 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 262:
#line 1863 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_HASFLAG, sscript);
                                     ctags = &((yyval.test)->u.hhs.comp);
                                 }
#line 4359 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 265:
#line 1873 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_DATE, sscript);
                                     ctags = &((yyval.test)->u.dt.comp);
                                 }
#line 4368 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 267:
#line 1878 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.dt.zone.tag != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":originalzone");
                                     }

                                     (yyval.test)->u.dt.zone.tag = B_ORIGINALZONE;
                                 }
#line 4382 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 271:
#line 1894 "sieve/sieve.y" /* yacc.c:1652  */
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
#line 4400 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 272:
#line 1911 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_CURRENTDATE, sscript);
                                     ctags = &((yyval.test)->u.dt.comp);
                                 }
#line 4409 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 276:
#line 1922 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     (yyval.test) = new_test(BC_NOTIFYMETHODCAPABILITY,
                                                   sscript);
                                     ctags = &((yyval.test)->u.mm.comp);
                                 }
#line 4419 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 279:
#line 1933 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     /* bctype assigned by the calling rule */
                                     (yyval.test) = new_test(bctype, sscript);
                                     ctags = &((yyval.test)->u.mm.comp);
                                 }
#line 4429 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 282:
#line 1944 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.test) = new_test(BC_DUPLICATE, sscript); }
#line 4435 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 283:
#line 1945 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.dup.idtype != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_CONFLICTING_TAGS,
                                                      ":header", ":uniqueid");
                                         free((yyval.test)->u.dup.idval);
                                     }

                                     (yyval.test)->u.dup.idtype = (yyvsp[-1].nval);
                                     (yyval.test)->u.dup.idval = (yyvsp[0].sval);
                                 }
#line 4451 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 284:
#line 1956 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.dup.handle != NULL) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":handle");
                                         free((yyval.test)->u.dup.handle);
                                     }

                                     (yyval.test)->u.dup.handle = (yyvsp[0].sval);
                                 }
#line 4466 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 285:
#line 1966 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.dup.seconds != -1) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":seconds");
                                     }

                                     (yyval.test)->u.dup.seconds = (yyvsp[0].nval);
                                 }
#line 4480 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 286:
#line 1975 "sieve/sieve.y" /* yacc.c:1652  */
    {
                                     if ((yyval.test)->u.dup.last != 0) {
                                         sieveerror_c(sscript,
                                                      SIEVE_DUPLICATE_TAG,
                                                      ":last");
                                     }

                                     (yyval.test)->u.dup.last = 1;
                                 }
#line 4494 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 287:
#line 1988 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_HEADER;   }
#line 4500 "sieve/sieve.c" /* yacc.c:1652  */
    break;

  case 288:
#line 1989 "sieve/sieve.y" /* yacc.c:1652  */
    { (yyval.nval) = B_UNIQUEID; }
#line 4506 "sieve/sieve.c" /* yacc.c:1652  */
    break;


#line 4510 "sieve/sieve.c" /* yacc.c:1652  */
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
#line 1993 "sieve/sieve.y" /* yacc.c:1918  */



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

static commandlist_t *build_imip(sieve_script_t *sscript, commandlist_t *c)
{
    unsigned flags = 0;

    assert(c && c->type == B_PROCESSIMIP);

    if (c->u.imip.invites_only) flags |= IMIP_INVITESONLY;
    if (c->u.imip.updates_only) flags |= IMIP_UPDATESONLY;
    if (c->u.imip.delete_canceled) flags |= IMIP_DELETECANCELED;

    if (c->u.imip.outcome_var) verify_identifier(sscript, c->u.imip.outcome_var);
    if (c->u.imip.errstr_var) verify_identifier(sscript, c->u.imip.errstr_var);
    
    c->nargs = bc_precompile(c->args, "isss",
                             flags,
                             c->u.imip.calendarid,
                             c->u.imip.outcome_var,
                             c->u.imip.errstr_var);

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
    free(part); /* done with this string */
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
