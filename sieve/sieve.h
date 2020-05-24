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
#line 170 "sieve/sieve.y" /* yacc.c:1909  */

    int nval;
    char *sval;
    arrayu64_t *nl;
    strarray_t *sl;
    comp_t *ctag;
    test_t *test;
    testlist_t *testl;
    commandlist_t *cl;

#line 369 "sieve/sieve.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int sieveparse (sieve_script_t *sscript);

#endif /* !YY_SIEVE_SIEVE_SIEVE_H_INCLUDED  */
