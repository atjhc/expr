#include "expr.h"

#include <assert.h>
#include <math.h>

#include "ast.h"
#include "sym.h"

// clang-format off
#include "parser.h"
#include "lexer.h"
// clang-format on

int yyparse(yyscan_t scanner, ast_expr_t *output);

scalar_t _expr_evaluate_ast_id(expr_t expr, ast_expr_t ast);
scalar_t _expr_evaluate_ast(expr_t expr, ast_expr_t ast);

struct expr_s {
    ast_expr_t ast;
    sym_table_t symbols;
};

expr_t expr_create(const char *code) {
    expr_t expr = NULL;

    yyscan_t scanner = NULL;
    ast_expr_t ast = NULL;

    if (yylex_init(&scanner)) {
        return NULL;
    }

    YY_BUFFER_STATE buf = yy_scan_string(code, scanner);

    if (yyparse(scanner, &ast)) {
        yy_delete_buffer(buf, scanner);
        goto cleanup;
    }
    yy_delete_buffer(buf, scanner);

    expr = malloc(sizeof(struct expr_s));
    expr->ast = ast;
    expr->symbols = sym_table_create();

cleanup:
    if (scanner) {
        yylex_destroy(scanner);
    }
    return expr;
}

void expr_destroy(expr_t expr) {
    if (expr) {
        ast_expr_destroy(expr->ast);
        sym_table_destroy(expr->symbols);
        free(expr);
    }
}

void expr_insert_symbol(expr_t expr, const char *name, int arity, void *location) {
    if (expr == NULL) {
        return;
    }

    sym_table_insert(expr->symbols, name, arity, location);
}

scalar_t _expr_call_fn(expr_t expr, void *fn, ast_expr_list_t args) {
    int arity = ast_expr_list_length(args);

    assert(arity > 0);

    switch (arity) {
    case 1:
        return ((scalar_t(*)(scalar_t))fn)(_expr_evaluate_ast(expr, args->head));
    case 2:
        return ((scalar_t(*)(scalar_t, scalar_t))fn)(_expr_evaluate_ast(expr, args->head),
                                                     _expr_evaluate_ast(expr, args->tail->head));
    case 3:
        return ((scalar_t(*)(scalar_t, scalar_t, scalar_t))fn)(
            _expr_evaluate_ast(expr, args->head), _expr_evaluate_ast(expr, args->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->head));
    case 4:
        return ((scalar_t(*)(scalar_t, scalar_t, scalar_t, scalar_t))fn)(
            _expr_evaluate_ast(expr, args->head), _expr_evaluate_ast(expr, args->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->head));
    case 5:
        return ((scalar_t(*)(scalar_t, scalar_t, scalar_t, scalar_t, scalar_t))fn)(
            _expr_evaluate_ast(expr, args->head), _expr_evaluate_ast(expr, args->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->head));
    case 6:
        return ((scalar_t(*)(scalar_t, scalar_t, scalar_t, scalar_t, scalar_t, scalar_t))fn)(
            _expr_evaluate_ast(expr, args->head), _expr_evaluate_ast(expr, args->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->head));
    case 7:
        return (
            (scalar_t(*)(scalar_t, scalar_t, scalar_t, scalar_t, scalar_t, scalar_t, scalar_t))fn)(
            _expr_evaluate_ast(expr, args->head), _expr_evaluate_ast(expr, args->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->tail->head));
    case 8:
        return ((scalar_t(*)(scalar_t, scalar_t, scalar_t, scalar_t, scalar_t, scalar_t, scalar_t,
                             scalar_t))fn)(
            _expr_evaluate_ast(expr, args->head), _expr_evaluate_ast(expr, args->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->tail->tail->head));
    case 9:
        return ((scalar_t(*)(scalar_t, scalar_t, scalar_t, scalar_t, scalar_t, scalar_t, scalar_t,
                             scalar_t, scalar_t))fn)(
            _expr_evaluate_ast(expr, args->head), _expr_evaluate_ast(expr, args->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->tail->tail->tail->head));
    case 10:
        return ((scalar_t(*)(scalar_t, scalar_t, scalar_t, scalar_t, scalar_t, scalar_t, scalar_t,
                             scalar_t, scalar_t, scalar_t))fn)(
            _expr_evaluate_ast(expr, args->head), _expr_evaluate_ast(expr, args->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr, args->tail->tail->tail->tail->tail->tail->tail->tail->head),
            _expr_evaluate_ast(expr,
                               args->tail->tail->tail->tail->tail->tail->tail->tail->tail->head));
    }
    return NAN;
}

scalar_t _expr_evaluate_ast_id(expr_t expr, ast_expr_t ast) {
    assert(ast->type == AST_EXPR_ID || ast->type == AST_EXPR_ID_CACHED);

    // Return the value at the cached memory location.
    if (ast->type == AST_EXPR_ID_CACHED) {
        if (ast->args != NULL) {
            return _expr_call_fn(expr, ast->lval.pval, ast->args);
        }
        return *ast->lval.pval;
    }

    // Lookup the symbol in the symbols table.
    int arity = 0;
    if (ast->args) {
        arity = ast_expr_list_length(ast->args);
    }

    sym_t symbol = sym_table_lookup(expr->symbols, ast->lval.sval, arity);
    if (symbol == NULL) {
        abort();
        return NAN;
    }

    // Cache the memory location for faster access.
    ast->lval.pval = symbol->value;
    ast->type = AST_EXPR_ID_CACHED;

    if (ast->args != NULL) {
        return _expr_call_fn(expr, ast->lval.pval, ast->args);
    }
    return *ast->lval.pval;
}

scalar_t _expr_evaluate_ast(expr_t expr, ast_expr_t ast) {
    switch (ast->type) {
    case AST_EXPR_NUMBER:
        return ast->lval.dval;
    case AST_EXPR_ID:
    case AST_EXPR_ID_CACHED:
        return _expr_evaluate_ast_id(expr, ast);
    case AST_EXPR_PLUS:
        return _expr_evaluate_ast(expr, ast->left) + _expr_evaluate_ast(expr, ast->right);
    case AST_EXPR_MINUS:
        return _expr_evaluate_ast(expr, ast->left) - _expr_evaluate_ast(expr, ast->right);
    case AST_EXPR_MULT:
        return _expr_evaluate_ast(expr, ast->left) * _expr_evaluate_ast(expr, ast->right);
    case AST_EXPR_DIV: {
        scalar_t lhs = _expr_evaluate_ast(expr, ast->left);
        scalar_t rhs = _expr_evaluate_ast(expr, ast->right);
        if (rhs == 0.0) {
            return NAN;
        }
        return lhs / rhs;
    }
    case AST_EXPR_LT:
        return _expr_evaluate_ast(expr, ast->left) < _expr_evaluate_ast(expr, ast->right);
    case AST_EXPR_GT:
        return _expr_evaluate_ast(expr, ast->left) > _expr_evaluate_ast(expr, ast->right);
    case AST_EXPR_AND:
        return (_expr_evaluate_ast(expr, ast->left) != 0.0) &&
               (_expr_evaluate_ast(expr, ast->right) != 0.0);
    case AST_EXPR_OR:
        return (_expr_evaluate_ast(expr, ast->left) != 0.0) ||
               (_expr_evaluate_ast(expr, ast->right) != 0.0);
    case AST_EXPR_POW:
        return pow(_expr_evaluate_ast(expr, ast->left), _expr_evaluate_ast(expr, ast->right));
    case AST_EXPR_UMINUS:
        return -_expr_evaluate_ast(expr, ast->right);
    case AST_EXPR_NOT:
        return (_expr_evaluate_ast(expr, ast->right) == 0.0);

    default:
        return 0;
    }
}

scalar_t expr_evaluate(expr_t expr) { return _expr_evaluate_ast(expr, expr->ast); }
