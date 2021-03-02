%{

#include <string.h>

#include "ast.h"
#include "parser.h"

%}

%option reentrant bison-bridge
%option noyywrap

%%

([0-9]+)|([0-9]*\.[0-9]+)	{ yylval->dval = atof(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]*		{ yylval->aval = strdup(yytext); return ID; }
\(							return LPAREN;
\)							return RPAREN;
\+							return PLUS;
\-							return MINUS;
\*							return MULT;
\/							return DIV;
\^							return POW;
\,							return COMMA;
\<							return LT;
\>							return GT;
\|\|						return OR;
\&\&						return AND;
\!							return NOT;
[ \t\n]*					/* ignore whitespace */ ;

%%
