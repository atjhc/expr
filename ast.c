#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

expr_ast_t expr_ast_create(expr_ast_type_t type, ...) {
    va_list ap;

    expr_ast_t ast = malloc(sizeof(struct expr_ast_s));
    if (ast == NULL)
        return NULL;

    ast->type = type;
    ast->args = NULL;
    ast->left = NULL;
    ast->right = NULL;

    va_start(ap, type);

    switch (type) {
    case AST_EXPR_PLUS:
    case AST_EXPR_MINUS:
    case AST_EXPR_MULT:
    case AST_EXPR_DIV:
    case AST_EXPR_POW:
    case AST_EXPR_LT:
    case AST_EXPR_GT:
    case AST_EXPR_AND:
    case AST_EXPR_OR:
        ast->left = va_arg(ap, expr_ast_t);
        ast->right = va_arg(ap, expr_ast_t);
        break;

    case AST_EXPR_UMINUS:
    case AST_EXPR_NOT:
        ast->right = va_arg(ap, expr_ast_t);
        break;

    case AST_EXPR_NUMBER:
        ast->lval.dval = va_arg(ap, double);
        break;

    case AST_EXPR_ID:
        ast->lval.sval = strdup(va_arg(ap, char *));
        ast->args = va_arg(ap, expr_ast_list_t);
        break;

    default:
        assert("unexpected expression type");
        break;
    }

    return ast;
}

void expr_ast_destroy(expr_ast_t ast) {
    if (ast->type == AST_EXPR_ID) {
        free(ast->lval.sval);
    }

    if (ast->left) {
        expr_ast_destroy(ast->left);
    }

    if (ast->right) {
        expr_ast_destroy(ast->right);
    }

    if (ast->args) {
        expr_ast_list_destroy(ast->args);
    }

    free(ast);
}

expr_ast_list_t expr_ast_list_create(expr_ast_t ast) {
    expr_ast_list_t ast_list;

    ast_list = malloc(sizeof(struct expr_ast_list_s));
    if (ast_list == NULL)
        return NULL;

    ast_list->count = 1;
    ast_list->args = malloc(sizeof(expr_ast_t));
    ast_list->args[0] = ast;

    return ast_list;
}

void expr_ast_list_destroy(expr_ast_list_t ast_list) {
    for (unsigned int i = 0; i < ast_list->count; i++) {
        expr_ast_destroy(ast_list->args[i]);
    }
    free(ast_list);
}

expr_ast_list_t expr_ast_list_append(expr_ast_list_t ast_list, expr_ast_t ast) {
    ast_list->args = realloc(ast_list->args, sizeof(expr_ast_t) * (ast_list->count + 1));

    ast_list->args[ast_list->count] = ast;
    ast_list->count += 1;

    return ast_list;
}

unsigned int expr_ast_list_length(expr_ast_list_t ast_list) { return ast_list->count; }

#pragma mark - Debug

void _expr_ast_list_fprint(FILE *f, expr_ast_list_t ast_list) {
    if (ast_list == NULL)
        return;

    for (unsigned int i = 0; i < ast_list->count; i++) {
        if (i > 0) {
            fprintf(f, ", ");
        }
        _expr_ast_fprint(f, ast_list->args[i]);
    }
}

void _expr_ast_fprint(FILE *f, expr_ast_t ast) {
    if (ast == NULL) {
        fprintf(f, "<null>");
        return;
    }

    switch (ast->type) {
    case AST_EXPR_NUMBER:
        fprintf(f, "%f", ast->lval.dval);
        break;

    case AST_EXPR_ID:
        fprintf(f, "%s", ast->lval.sval);
        if (ast->args != NULL) {
            fprintf(f, "(");
            _expr_ast_list_fprint(f, ast->args);
            fprintf(f, ")");
        }
        break;

    case AST_EXPR_UMINUS:
        fprintf(f, "-(");
        _expr_ast_fprint(f, ast->right);
        fprintf(f, ")");
        break;

    case AST_EXPR_PLUS:
        fprintf(f, "(");
        _expr_ast_fprint(f, ast->left);
        fprintf(f, " + ");
        _expr_ast_fprint(f, ast->right);
        fprintf(f, ")");
        break;

    case AST_EXPR_MINUS:
        fprintf(f, "(");
        _expr_ast_fprint(f, ast->left);
        fprintf(f, " - ");
        _expr_ast_fprint(f, ast->right);
        fprintf(f, ")");
        break;

    case AST_EXPR_MULT:
        fprintf(f, "(");
        _expr_ast_fprint(f, ast->left);
        fprintf(f, " * ");
        _expr_ast_fprint(f, ast->right);
        fprintf(f, ")");
        break;

    case AST_EXPR_DIV:
        fprintf(f, "(");
        _expr_ast_fprint(f, ast->left);
        fprintf(f, " / ");
        _expr_ast_fprint(f, ast->right);
        fprintf(f, ")");
        break;

    case AST_EXPR_POW:
        fprintf(f, "(");
        _expr_ast_fprint(f, ast->left);
        fprintf(f, " ^ ");
        _expr_ast_fprint(f, ast->right);
        fprintf(f, ")");
        break;

    default:
        break;
    }
}
