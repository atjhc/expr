#ifndef AST_H
#define AST_H

#include <stdio.h>

typedef enum {
    AST_EXPR_PLUS = 0,
    AST_EXPR_MINUS,
    AST_EXPR_MULT,
    AST_EXPR_DIV,
    AST_EXPR_UMINUS,
    AST_EXPR_POW,
    AST_EXPR_ID,
    AST_EXPR_ID_CACHED,
    AST_EXPR_NUMBER,
    AST_EXPR_PAREN,
    AST_EXPR_LT,
    AST_EXPR_GT,
    AST_EXPR_AND,
    AST_EXPR_OR,
    AST_EXPR_NOT
} expr_ast_type_t;

#ifndef NULL
#define NULL ((void *)0)
#endif

struct expr_ast_s;
struct expr_ast_list_s;

typedef struct expr_ast_list_s {
    struct expr_ast_s *head;
    struct expr_ast_list_s *tail;
} * expr_ast_list_t;

typedef struct expr_ast_s {
    expr_ast_type_t type;
    union {
        char *sval;
        double dval;
        double *pval;
    } lval;

    struct expr_ast_list_s *args;
    struct expr_ast_s *left, *right;
} * expr_ast_t;

expr_ast_t expr_ast_create(expr_ast_type_t type, ...);
void expr_ast_destroy(expr_ast_t expr);

expr_ast_list_t expr_ast_list_create(expr_ast_t expr);
void expr_ast_list_destroy(expr_ast_list_t expr_list);

expr_ast_list_t expr_ast_list_cons(expr_ast_list_t expr_list, expr_ast_t expr);
int expr_ast_list_length(expr_ast_list_t expr_list);

void _expr_ast_list_fprint(FILE *f, expr_ast_list_t expr_list);
void _expr_ast_fprint(FILE *f, expr_ast_t expr);

#endif // AST_H