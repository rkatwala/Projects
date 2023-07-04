%option noyywrap
%{
//c code here
#include <stdio.h>
#include "y.tab.h"

extern char *identToken;
extern int numberToken;

%}

%option yylineno

DIGIT [0-9]
ALPHA [a-zA-Z]
SPECIAL [!@#$%^&*?/<>:+=-|\/]
  /* add any further unspecified special characters which should NOT be a substring of any identifier! */
IDENTIFIER ({ALPHA}({ALPHA}|{DIGIT}|_)*)
INVALID ({DIGIT}({ALPHA}|{DIGIT}|_)*|_({ALPHA}|{DIGIT}|_)*)|.|({IDENTIFIER}({ALPHA}|{DIGIT}|_|{SPECIAL})*)|({ALPHA}|{DIGIT}|_|{SPECIAL})*
  /*INVALID ({DIGIT}({ALPHA}|{DIGIT}|_)*|_({ALPHA}|{DIGIT}|_)*)|.*/
COMMENT #({IDENTIFIER}|{INVALID})*

%{
int column = 1;
%}

%{
extern int line_num;
%}



%%
"num" {column += yyleng; return INTEGER;}
"array" {column += yyleng; return ARRAY;}
"while" {column += yyleng; return WHILE;}
"do" {column += yyleng; return DO;}
"proceed" {column += yyleng; return CONT;}
"leave" {column += yyleng; return BREAK;}
"read" {column += yyleng; return READ;}
"write" {column += yyleng; return WRITE;}
"if" {column += yyleng; return IF;}
"then" {column += yyleng; return THEN;}
"else" {column += yyleng; return ELSE;}
"func" {column += yyleng; return FUNCTION;}
"ret" {column += yyleng; return RETURN;}
"is" {column += yyleng; return ASSIGN;}
"plus" {column += yyleng; return ADD;}
"minus" {column += yyleng; return SUB;}
"times" {column += yyleng; return MULT;}
"divby" {column += yyleng; return DIV;}
"lt" {column += yyleng; return LT;}
"gt" {column += yyleng; return GT;}
"lte" {column += yyleng; return LTE;}
"gte" {column += yyleng; return GTE;}
"neq" {column += yyleng; return NEQ;}
"eq" {column += yyleng; return EQ;}
"{" {column += yyleng; return BEGIN_BLOCK;} 
"}" {column += yyleng; return END_BLOCK;}
";" {column += yyleng; return SEMICOLON;}
"," {column += yyleng; return COMMA;}
"[" {column += yyleng; return LEFT_SQR_BRACKET;}
"]" {column += yyleng; return RIGHT_SQR_BRACKET;}
"(" {column += yyleng; return LEFT_PAREN;}
")" {column += yyleng; return RIGHT_PAREN;}
":" {column += yyleng; return COLON;}
{COMMENT} ;
" " { column++; }
"\t" { column++; }
"\r" { ++yylineno; column = 1;  }
"\n" { ++yylineno; column = 1; line_num++; }
{IDENTIFIER} {
   column += yyleng;
   char* token = strdup(yytext);
   //char token[yyleng];    // new
   strcpy(token, yytext);
   yylval.op_val = token;
   identToken = yytext; 
   return IDENT; 
}
{DIGIT}+ {
  column += yyleng; 
  char* token = strdup(yytext);
  //char token[yyleng]; // new
  strcpy(token, yytext);
  yylval.op_val = token;
  numberToken = atoi(yytext); 
  return NUMBER;
}


. {printf ("**ERROR. Unidentified identifier '%s' by line %u, column %d\n", yytext, yylineno, column);}
{INVALID} { printf("**ERROR. Unidentified identifier '%s' by line %u, column %d\n", yytext, yylineno, column);}
%%
