%pure-parser
%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }
%parse-param { expr_ast_t *output }

%{

#include <stdio.h>
#include <math.h>

#include "ast.h"

#ifndef YY_TYPEDEF_YY_SCANNER_T
    #define YY_TYPEDEF_YY_SCANNER_T
    typedef void* yyscan_t;
#endif

int yylex();
int yyerror();

%}

%union {
    expr_ast_t eval;
    expr_ast_list_t elval;
    char *aval;
    double dval;
}

%left AND OR
%left LT GT 
%left PLUS MINUS
%left MULT DIV
%nonassoc UMINUS
%nonassoc UNOT
%right POW

%token <aval> ID 
%token <dval> NUMBER
%token LPAREN RPAREN PLUS MULT MINUS DIV POW COMMA GT LT OR AND NOT 

%type <eval> expr
%type <elval> expr_list

%%

stmt: expr {
    if (output) *output = $1;
};

expr: LPAREN expr RPAREN            { $$ = $2; }
    | expr PLUS expr                { $$ = expr_ast_create(AST_EXPR_PLUS, $1, $3); }
    | expr MINUS expr               { $$ = expr_ast_create(AST_EXPR_MINUS, $1, $3); }
    | expr MULT expr                { $$ = expr_ast_create(AST_EXPR_MULT, $1, $3);  }
    | expr DIV expr                 { $$ = expr_ast_create(AST_EXPR_DIV, $1, $3); }
    | expr GT expr                  { $$ = expr_ast_create(AST_EXPR_GT, $1, $3); }
    | expr LT expr                  { $$ = expr_ast_create(AST_EXPR_LT, $1, $3); }
    | expr AND expr                 { $$ = expr_ast_create(AST_EXPR_AND, $1, $3); }
    | expr OR expr                  { $$ = expr_ast_create(AST_EXPR_OR, $1, $3); }
    | MINUS expr %prec UMINUS       { $$ = expr_ast_create(AST_EXPR_UMINUS, $2); }
    | NOT expr %prec UNOT           { $$ = expr_ast_create(AST_EXPR_NOT, $2); }
    | expr POW expr                 { $$ = expr_ast_create(AST_EXPR_POW, $1, $3); }
    | ID                            { $$ = expr_ast_create(AST_EXPR_ID, $1, NULL); free($1); }
    | ID LPAREN expr_list RPAREN    { $$ = expr_ast_create(AST_EXPR_ID, $1, $3); free($1); }
    | NUMBER                        { $$ = expr_ast_create(AST_EXPR_NUMBER, $1);  }
    ;

expr_list:  expr            { $$ = expr_ast_list_create($1); }
    | expr COMMA expr_list  { $$ = expr_ast_list_append($3, $1); }
    ;

%%

int yyerror(yyscan_t scanner, const char *msg) {
    printf("parser error: %s\n", msg);
    return 0;
}

