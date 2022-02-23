/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
#line 179 "sieve/sieve.y" /* yacc.c:1921  */

    int nval;
    char *sval;
    arrayu64_t *nl;
    strarray_t *sl;
    comp_t *ctag;
    test_t *test;
    testlist_t *testl;
    commandlist_t *cl;

#line 361 "sieve/sieve.h" /* yacc.c:1921  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif



int sieveparse (sieve_script_t *sscript);

#endif /* !YY_SIEVE_SIEVE_SIEVE_H_INCLUDED  */
