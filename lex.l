%{
#include <stdio.h>
#include "y.tab.h"
#include "control.h"

%}
%option noyywrap
%%

"begin" { return BGIN; }
"end" { return END; }
"begin_function" { return BEGIN_FUNCTION; }
"end_function" {  return END_FUNCTION; }
"begin_statement" { return BEGIN_STATEMENT; }
"end_statement" { return END_STATEMENT; }
"begin_class" { return BEGIN_CLASS; }
"end_class" { return END_CLASS; }
"int" { return INT_TYPE; }
"bool" {return BOOL_TYPE; }
"float" { return FLOAT_TYPE; }
"char" { return CHAR_TYPE; }
"string" {return STRING_TYPE; }
"class" { return CLASS_TYPE; }
"array" {return ARRAY_TYPE; }
"const" {return IS_CONST;}
"def" { return DEF; }
"while"         { return WHILE; } 
"for"           { return FOR; }
"if"            { return IF; } 
"print"         { return PRINT; }

[0-9]+ { yylval.intval=atoi(yytext); return NR;}
"True"|"False" { yylval.strval=strdup(yytext); return BOOL_VALUE; }
\"[^\"]+\" { yylval.strval=strdup(yytext); return STRING_VALUE; }
-?[1-9][0-9]*|0 { yylval.strval=strdup(yytext); return INT_VALUE; }
'.' { return CHAR_VALUE; }
-?[1-9][0-9]*\.[0-9]*|-?0\.[0-9]* {
                                     yylval.strval=strdup(yytext);
                                     return FLOAT_VALUE;}


"<"             { return LR; }
">"             { return GR; }
">="            { return GE; }
"<="            { return LE; }
"=="            { return EQ; }
"!="            { return NE; }
"&&"            { return AND; }
"||"            { return OR; }
"!"             { return NOT; }

([A-Za-z\_][A-Za-z0-9\_]*\.[A-Za-z][A-Za-z0-9_]*)*|[A-Za-z\_][A-Za-z0-9\_]* {                      
                        yylval.strval=strdup(yytext);
                        return ID;
                     }
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
