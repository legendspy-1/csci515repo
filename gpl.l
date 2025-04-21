
%option noyywrap
%option nodefault
%option nounput

%{
#include "gpl.tab.h"
#include "error.h"
#include <iostream>

int line_count = 1;

void illegal_token_error() {
  gamelang::error(gamelang::ILLEGAL_TOKEN, yytext);

  // create a string to hold the current text
  // put that string in the yylval union so it can be used by parser
  yylval.union_string = new std::string(yytext);
}

%}

%%

[ \t]    { /* ignore whitespace */ }

"int"          { return T_INT; }
"double"       { return T_DOUBLE; }
"string"       { return T_STRING; }
"triangle"     { return T_TRIANGLE; }
"pixmap"       { return T_PIXMAP; }
"circle"       { return T_CIRCLE; }
"rectangle"    { return T_RECTANGLE; }
"textbox"      { return T_TEXTBOX; }

 /* keywords */
"forward"        { return T_FORWARD; }
"initialization" { return T_INITIALIZATION; }
"termination"    { return T_TERMINATION; }
"on"            { return T_ON; }
"animation"     { return T_ANIMATION; }
"if"            { return T_IF; }
"for"           { return T_FOR; }
"else"          { return T_ELSE; }
"exit"          { yylval.union_int = line_count; return T_EXIT; }
"print"         { yylval.union_int = line_count; return T_PRINT; }
"true"          { return T_TRUE; }
"false"         { return T_FALSE; }

 /* event keys */
"space"              { return T_SPACE; }
"leftarrow"          { return T_LEFTARROW; }
"rightarrow"         { return T_RIGHTARROW; }
"uparrow"            { return T_UPARROW; }
"downarrow"          { return T_DOWNARROW; }
"leftmouse_down"     { return T_LEFTMOUSE_DOWN; }
"middlemouse_down"   { return T_MIDDLEMOUSE_DOWN; }
"rightmouse_down"    { return T_RIGHTMOUSE_DOWN; }
"leftmouse_up"       { return T_LEFTMOUSE_UP; }
"middlemouse_up"     { return T_MIDDLEMOUSE_UP; }
"rightmouse_up"      { return T_RIGHTMOUSE_UP; }
"mouse_move"         { return T_MOUSE_MOVE; }
"mouse_drag"         { return T_MOUSE_DRAG; }
"f1"                { return T_F1; }
"akey"              { return T_AKEY; }
"skey"              { return T_SKEY; }
"dkey"              { return T_DKEY; }
"fkey"              { return T_FKEY; }
"hkey"              { return T_HKEY; }
"jkey"              { return T_JKEY; }
"kkey"              { return T_KKEY; }
"lkey"              { return T_LKEY; }
"wkey"              { return T_WKEY; }
"zkey"              { return T_ZKEY; }

 /* punctuation */
"(" { return T_LPAREN; }
")" { return T_RPAREN; }
"{" { return T_LBRACE; }
"}" { return T_RBRACE; }
"[" { return T_LBRACKET; }
"]" { return T_RBRACKET; }
";" { return T_SEMIC; }
"," { return T_COMMA; }
"." { return T_PERIOD; }

 /* assignment operators
  * unlike C/C++/Java, assignment operators are NOT part of expressions
  * (no precedence level required)
  * unlike C/C++/Java, ++ and -- are not expressions operators
  * they are assignments operators
  */
"="   { return T_ASSIGN; }
"+="  { return T_PLUS_ASSIGN; }
"-="  { return T_MINUS_ASSIGN; }
"++"  { return T_PLUS_PLUS; }
"--"  { return T_MINUS_MINUS; }

 /* unary operators with textual names */
 /* (no precedence level required) */
"sin"    { return T_SIN; }
"cos"    { return T_COS; }
"tan"    { return T_TAN; }
"asin"   { return T_ASIN; }
"acos"   { return T_ACOS; }
"atan"   { return T_ATAN; }
"sqrt"   { return T_SQRT; }
"abs"    { return T_ABS; }
"floor"  { return T_FLOOR; }
"random" { return T_RANDOM; }

 /* graphical operators (also, add precedence level in .y file) */
"touches" { return T_TOUCHES; }
"near"    { return T_NEAR; }

 /* mathematical operators (also, add precedence level in .y file) */
"*"  { return T_MULTIPLY; }
"/"  { return T_DIVIDE; }
"+"  { return T_PLUS; }
"-"  { return T_MINUS; }
"%"  { return T_MOD; }

 /* logical operators (also, add precedence level in .y file) */
"<"   { return T_LESS; }
">"   { return T_GREATER; }
"<="  { return T_LESS_EQUAL; }
">="  { return T_GREATER_EQUAL; }
"=="  { return T_EQUAL; }
"!="  { return T_NOT_EQUAL; }
"!"   { return T_NOT; }
"&&"  { return T_AND; }
"||"  { return T_OR; }


[0-9]+ {
    yylval.union_int = atoi(yytext);
    return T_INT_CONSTANT;
}
[0-9]*"."[0-9]+ {
    yylval.union_double = atof(yytext);
    return T_DOUBLE_CONSTANT;
}
\"([^\"\n]|\\\")*\" {
    std::string str(yytext + 1, strlen(yytext) - 2); // Strip quotes
    yylval.union_string = new std::string(str);
    return T_STRING_CONSTANT;
}
[a-zA-Z_][a-zA-Z0-9_]* { yylval.union_string = new std::string(yytext); return T_ID; }


"//".* { /* Do nothing, ignore the comment */ }

"\n"                 { line_count = line_count +1; }

 /* This should be the last pattern. If the lexer reaches this pattern
    there has been an error
  */
.               {illegal_token_error(); return T_ERROR;}

%%

