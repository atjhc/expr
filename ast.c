#include <assert.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

ast_expr_t ast_expr_create(ast_expr_type_t type, ...) {
    va_list ap;

    ast_expr_t expr = malloc(sizeof(struct ast_expr_s));
    if (expr == NULL)
        return NULL;

    expr->type = type;
    expr->args = NULL;
    expr->left = NULL;
    expr->right = NULL;

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
        expr->left = va_arg(ap, ast_expr_t);
        expr->right = va_arg(ap, ast_expr_t);
        break;

    case AST_EXPR_UMINUS:
    case AST_EXPR_NOT:
        expr->right = va_arg(ap, ast_expr_t);
        break;

    case AST_EXPR_NUMBER:
        expr->lval.dval = va_arg(ap, double);
        break;

    case AST_EXPR_ID:
        expr->lval.sval = strdup(va_arg(ap, char *));
        expr->args = va_arg(ap, ast_expr_list_t);
        break;

    default:
        assert("unexpected expression type");
        break;
    }

    return expr;
}

void ast_expr_destroy(ast_expr_t expr) {
    if (expr->type == AST_EXPR_ID) {
        free(expr->lval.sval);
    }

    if (expr->left) {
        ast_expr_destroy(expr->left);
    }

    if (expr->right) {
        ast_expr_destroy(expr->right);
    }

    if (expr->args) {
        ast_expr_list_destroy(expr->args);
    }

    free(expr);
}

ast_expr_list_t ast_expr_list_create(ast_expr_t expr) {
    ast_expr_list_t expr_list;

    expr_list = malloc(sizeof(struct ast_expr_list_s));
    if (expr_list == NULL)
        return NULL;

    expr_list->head = expr;
    expr_list->tail = NULL;

    return expr_list;
}

void ast_expr_list_destroy(ast_expr_list_t expr_list) {
    if (expr_list->tail != NULL) {
        ast_expr_list_destroy(expr_list->tail);
    }

    ast_expr_destroy(expr_list->head);

    free(expr_list);
}

ast_expr_list_t ast_expr_list_cons(ast_expr_list_t expr_list, ast_expr_t expr) {
    ast_expr_list_t new_expr_list;

    new_expr_list = ast_expr_list_create(expr);
    new_expr_list->tail = expr_list;

    return new_expr_list;
}

int ast_expr_list_length(ast_expr_list_t expr_list) {
    int i = 0;

    while (expr_list != NULL) {
        expr_list = expr_list->tail;
        i++;
    }

    return i;
}

#pragma mark - Debug

void _ast_expr_list_fprint(FILE *f, ast_expr_list_t expr_list) {
    if (expr_list == NULL)
        return;

    _ast_expr_fprint(f, expr_list->head);

    if (expr_list->tail != NULL) {
        fprintf(f, ", ");
        _ast_expr_list_fprint(f, expr_list->tail);
    }
}

void _ast_expr_fprint(FILE *f, ast_expr_t expr) {
    if (expr == NULL) {
        fprintf(f, "<null>");
        return;
    }

    switch (expr->type) {
    case AST_EXPR_NUMBER:
        fprintf(f, "%f", expr->lval.dval);
        break;

    case AST_EXPR_ID:
        fprintf(f, "%s", expr->lval.sval);
        if (expr->args != NULL) {
            fprintf(f, "(");
            _ast_expr_list_fprint(f, expr->args);
            fprintf(f, ")");
        }
        break;

    case AST_EXPR_UMINUS:
        fprintf(f, "-(");
        _ast_expr_fprint(f, expr->right);
        fprintf(f, ")");
        break;

    case AST_EXPR_PLUS:
        fprintf(f, "(");
        _ast_expr_fprint(f, expr->left);
        fprintf(f, " + ");
        _ast_expr_fprint(f, expr->right);
        fprintf(f, ")");
        break;

    case AST_EXPR_MINUS:
        fprintf(f, "(");
        _ast_expr_fprint(f, expr->left);
        fprintf(f, " - ");
        _ast_expr_fprint(f, expr->right);
        fprintf(f, ")");
        break;

    case AST_EXPR_MULT:
        fprintf(f, "(");
        _ast_expr_fprint(f, expr->left);
        fprintf(f, " * ");
        _ast_expr_fprint(f, expr->right);
        fprintf(f, ")");
        break;

    case AST_EXPR_DIV:
        fprintf(f, "(");
        _ast_expr_fprint(f, expr->left);
        fprintf(f, " / ");
        _ast_expr_fprint(f, expr->right);
        fprintf(f, ")");
        break;

    case AST_EXPR_POW:
        fprintf(f, "(");
        _ast_expr_fprint(f, expr->left);
        fprintf(f, " ^ ");
        _ast_expr_fprint(f, expr->right);
        fprintf(f, ")");
        break;

    default:
        break;
    }
}
