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
} ast_expr_type_t;

#ifndef NULL
#define NULL ((void *)0)
#endif

struct ast_expr_s;
struct ast_expr_list_s;

typedef struct ast_expr_list_s {
    struct ast_expr_s *head;
    struct ast_expr_list_s *tail;
} * ast_expr_list_t;

typedef struct ast_expr_s {
    ast_expr_type_t type;
    union {
        char *sval;
        double dval;
        double *pval;
    } lval;

    struct ast_expr_list_s *args;
    struct ast_expr_s *left, *right;
} * ast_expr_t;

ast_expr_t ast_expr_create(ast_expr_type_t type, ...);
void ast_expr_destroy(ast_expr_t expr);

ast_expr_list_t ast_expr_list_create(ast_expr_t expr);
void ast_expr_list_destroy(ast_expr_list_t expr_list);

ast_expr_list_t ast_expr_list_cons(ast_expr_list_t expr_list, ast_expr_t expr);
int ast_expr_list_length(ast_expr_list_t expr_list);

void _ast_expr_list_fprint(FILE *f, ast_expr_list_t expr_list);
void _ast_expr_fprint(FILE *f, ast_expr_t expr);

#endif // AST_H