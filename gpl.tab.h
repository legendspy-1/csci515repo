/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_GPL_TAB_H_INCLUDED
# define YY_YY_GPL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "gpl.y"

  #include <string>
  class Expression;
  class Variable;
  class Statement;
  #ifndef P1
    #include "types_and_ops.h"  //include in all projects except the first
  #endif
  #ifdef GRAPHICS
    #include "Window.h"
  #endif

#line 62 "gpl.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_INT = 258,                   /* "int"  */
    T_DOUBLE = 259,                /* "double"  */
    T_STRING = 260,                /* "string"  */
    T_TRIANGLE = 261,              /* "triangle"  */
    T_PIXMAP = 262,                /* "pixmap"  */
    T_CIRCLE = 263,                /* "circle"  */
    T_RECTANGLE = 264,             /* "rectangle"  */
    T_TEXTBOX = 265,               /* "textbox"  */
    T_FORWARD = 266,               /* "forward"  */
    T_INITIALIZATION = 267,        /* "initialization"  */
    T_TERMINATION = 268,           /* "termination"  */
    T_ON = 269,                    /* "on"  */
    T_ANIMATION = 270,             /* "animation"  */
    T_IF = 271,                    /* "if"  */
    T_FOR = 272,                   /* "for"  */
    T_ELSE = 273,                  /* "else"  */
    T_EXIT = 274,                  /* "exit"  */
    T_PRINT = 275,                 /* "print"  */
    T_TRUE = 276,                  /* "true"  */
    T_FALSE = 277,                 /* "false"  */
    T_SPACE = 278,                 /* "space"  */
    T_LEFTARROW = 279,             /* "leftarrow"  */
    T_RIGHTARROW = 280,            /* "rightarrow"  */
    T_UPARROW = 281,               /* "uparrow"  */
    T_DOWNARROW = 282,             /* "downarrow"  */
    T_LEFTMOUSE_DOWN = 283,        /* "leftmouse_down"  */
    T_MIDDLEMOUSE_DOWN = 284,      /* "middlemouse_down"  */
    T_RIGHTMOUSE_DOWN = 285,       /* "rightmouse_down"  */
    T_LEFTMOUSE_UP = 286,          /* "leftmouse_up"  */
    T_MIDDLEMOUSE_UP = 287,        /* "middlemouse_up"  */
    T_RIGHTMOUSE_UP = 288,         /* "rightmouse_up"  */
    T_MOUSE_MOVE = 289,            /* "mouse_move"  */
    T_MOUSE_DRAG = 290,            /* "mouse_drag"  */
    T_F1 = 291,                    /* "f1"  */
    T_AKEY = 292,                  /* "akey"  */
    T_SKEY = 293,                  /* "skey"  */
    T_DKEY = 294,                  /* "dkey"  */
    T_FKEY = 295,                  /* "fkey"  */
    T_HKEY = 296,                  /* "hkey"  */
    T_JKEY = 297,                  /* "jkey"  */
    T_KKEY = 298,                  /* "kkey"  */
    T_LKEY = 299,                  /* "lkey"  */
    T_WKEY = 300,                  /* "wkey"  */
    T_ZKEY = 301,                  /* "zkey"  */
    T_LPAREN = 302,                /* "("  */
    T_RPAREN = 303,                /* ")"  */
    T_LBRACE = 304,                /* "{"  */
    T_RBRACE = 305,                /* "}"  */
    T_LBRACKET = 306,              /* "["  */
    T_RBRACKET = 307,              /* "]"  */
    T_SEMIC = 308,                 /* ";"  */
    T_COMMA = 309,                 /* ","  */
    T_PERIOD = 310,                /* "."  */
    T_ASSIGN = 311,                /* "="  */
    T_PLUS_ASSIGN = 312,           /* "+="  */
    T_MINUS_ASSIGN = 313,          /* "-="  */
    T_PLUS_PLUS = 314,             /* "++"  */
    T_MINUS_MINUS = 315,           /* "--"  */
    T_SIN = 316,                   /* "sin"  */
    T_COS = 317,                   /* "cos"  */
    T_TAN = 318,                   /* "tan"  */
    T_ASIN = 319,                  /* "asin"  */
    T_ACOS = 320,                  /* "acos"  */
    T_ATAN = 321,                  /* "atan"  */
    T_SQRT = 322,                  /* "sqrt"  */
    T_ABS = 323,                   /* "abs"  */
    T_FLOOR = 324,                 /* "floor"  */
    T_RANDOM = 325,                /* "random"  */
    T_TOUCHES = 326,               /* "touches"  */
    T_NEAR = 327,                  /* "near"  */
    T_MULTIPLY = 328,              /* "*"  */
    T_DIVIDE = 329,                /* "/"  */
    T_PLUS = 330,                  /* "+"  */
    T_MINUS = 331,                 /* "-"  */
    T_MOD = 332,                   /* "%"  */
    T_LESS = 333,                  /* "<"  */
    T_GREATER = 334,               /* ">"  */
    T_LESS_EQUAL = 335,            /* "<="  */
    T_GREATER_EQUAL = 336,         /* ">="  */
    T_EQUAL = 337,                 /* "=="  */
    T_NOT_EQUAL = 338,             /* "!="  */
    T_NOT = 339,                   /* "!"  */
    T_AND = 340,                   /* "&&"  */
    T_OR = 341,                    /* "||"  */
    T_INT_CONSTANT = 342,          /* "int constant"  */
    T_DOUBLE_CONSTANT = 343,       /* "double constant"  */
    T_STRING_CONSTANT = 344,       /* "string constant"  */
    T_ID = 345,                    /* "identifier"  */
    T_ERROR = 346,                 /* "error"  */
    left = 347,                    /* left  */
    NEGATION = 348,                /* NEGATION  */
    IF_NO_ELSE = 349               /* IF_NO_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 32 "gpl.y"

 int            union_int;
 std::string*   union_string;  // MUST be a pointer to a string
 double         union_double;
 gamelang::Type union_gpl_type;
 const Expression* union_expression_ptr;
 Variable* union_variable_ptr;

#line 182 "gpl.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_GPL_TAB_H_INCLUDED  */
