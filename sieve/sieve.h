/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 238 "sieve/sieve.y" /* yacc.c:1909  */

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

#line 295 "sieve/sieve.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int sieveparse (sieve_script_t *parse_script);

#endif /* !YY_SIEVE_SIEVE_SIEVE_H_INCLUDED  */
