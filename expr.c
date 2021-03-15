#include "expr.h"

#include <assert.h>
#include <math.h>

#include "ast.h"
#include "sym.h"

// clang-format off
#include "parser.h"
#include "lexer.h"
// clang-format on

int yyparse(yyscan_t scanner, expr_ast_t *output);

expr_scalar_t _expr_program_evaluate_ast_id(expr_program_t expr, expr_ast_t ast);
expr_scalar_t _expr_program_evaluate_ast(expr_program_t expr, expr_ast_t ast);

struct expr_program_s {
    expr_ast_t ast;
    expr_sym_table_t symbols;
};

expr_program_t expr_program_create(const char *code) {
    expr_program_t program = NULL;

    yyscan_t scanner = NULL;
    expr_ast_t ast = NULL;

    if (yylex_init(&scanner)) {
        return NULL;
    }

    YY_BUFFER_STATE buf = yy_scan_string(code, scanner);

    if (yyparse(scanner, &ast)) {
        yy_delete_buffer(buf, scanner);
        goto cleanup;
    }
    yy_delete_buffer(buf, scanner);

    program = malloc(sizeof(struct expr_program_s));
    program->ast = ast;
    program->symbols = expr_sym_table_create();

cleanup:
    if (scanner) {
        yylex_destroy(scanner);
    }
    return program;
}

void expr_program_destroy(expr_program_t program) {
    if (program) {
        expr_ast_destroy(program->ast);
        expr_sym_table_destroy(program->symbols);
        free(program);
    }
}

void expr_program_insert_symbol(expr_program_t program, const char *name, int arity,
                                void *location) {
    if (program == NULL) {
        return;
    }

    expr_sym_table_insert(program->symbols, name, arity, location);
}

expr_scalar_t _expr_call_fn(expr_program_t program, void *fn, expr_ast_list_t args) {
    int arity = expr_ast_list_length(args);

    assert(arity > 0);

    switch (arity) {
    case 1:
        return ((expr_scalar_t(*)(expr_scalar_t))fn)(
            _expr_program_evaluate_ast(program, args->args[0]));
    case 2:
        return ((expr_scalar_t(*)(expr_scalar_t, expr_scalar_t))fn)(
            _expr_program_evaluate_ast(program, args->args[0]),
            _expr_program_evaluate_ast(program, args->args[1]));
    case 3:
        return ((expr_scalar_t(*)(expr_scalar_t, expr_scalar_t, expr_scalar_t))fn)(
            _expr_program_evaluate_ast(program, args->args[0]),
            _expr_program_evaluate_ast(program, args->args[1]),
            _expr_program_evaluate_ast(program, args->args[2]));
    case 4:
        return ((expr_scalar_t(*)(expr_scalar_t, expr_scalar_t, expr_scalar_t, expr_scalar_t))fn)(
            _expr_program_evaluate_ast(program, args->args[0]),
            _expr_program_evaluate_ast(program, args->args[1]),
            _expr_program_evaluate_ast(program, args->args[2]),
            _expr_program_evaluate_ast(program, args->args[3]));
    case 5:
        return ((expr_scalar_t(*)(expr_scalar_t, expr_scalar_t, expr_scalar_t, expr_scalar_t,
                                  expr_scalar_t))fn)(
            _expr_program_evaluate_ast(program, args->args[0]),
            _expr_program_evaluate_ast(program, args->args[1]),
            _expr_program_evaluate_ast(program, args->args[2]),
            _expr_program_evaluate_ast(program, args->args[3]),
            _expr_program_evaluate_ast(program, args->args[4]));
    case 6:
        return ((expr_scalar_t(*)(expr_scalar_t, expr_scalar_t, expr_scalar_t, expr_scalar_t,
                                  expr_scalar_t, expr_scalar_t))fn)(
            _expr_program_evaluate_ast(program, args->args[0]),
            _expr_program_evaluate_ast(program, args->args[1]),
            _expr_program_evaluate_ast(program, args->args[2]),
            _expr_program_evaluate_ast(program, args->args[3]),
            _expr_program_evaluate_ast(program, args->args[4]),
            _expr_program_evaluate_ast(program, args->args[5]));
    case 7:
        return ((expr_scalar_t(*)(expr_scalar_t, expr_scalar_t, expr_scalar_t, expr_scalar_t,
                                  expr_scalar_t, expr_scalar_t, expr_scalar_t))fn)(
            _expr_program_evaluate_ast(program, args->args[0]),
            _expr_program_evaluate_ast(program, args->args[1]),
            _expr_program_evaluate_ast(program, args->args[2]),
            _expr_program_evaluate_ast(program, args->args[3]),
            _expr_program_evaluate_ast(program, args->args[4]),
            _expr_program_evaluate_ast(program, args->args[5]),
            _expr_program_evaluate_ast(program, args->args[6]));
    case 8:
        return ((expr_scalar_t(*)(expr_scalar_t, expr_scalar_t, expr_scalar_t, expr_scalar_t,
                                  expr_scalar_t, expr_scalar_t, expr_scalar_t, expr_scalar_t))fn)(
            _expr_program_evaluate_ast(program, args->args[0]),
            _expr_program_evaluate_ast(program, args->args[1]),
            _expr_program_evaluate_ast(program, args->args[2]),
            _expr_program_evaluate_ast(program, args->args[3]),
            _expr_program_evaluate_ast(program, args->args[4]),
            _expr_program_evaluate_ast(program, args->args[5]),
            _expr_program_evaluate_ast(program, args->args[6]),
            _expr_program_evaluate_ast(program, args->args[7]));
    case 9:
        return ((expr_scalar_t(*)(expr_scalar_t, expr_scalar_t, expr_scalar_t, expr_scalar_t,
                                  expr_scalar_t, expr_scalar_t, expr_scalar_t, expr_scalar_t,
                                  expr_scalar_t))fn)(
            _expr_program_evaluate_ast(program, args->args[0]),
            _expr_program_evaluate_ast(program, args->args[1]),
            _expr_program_evaluate_ast(program, args->args[2]),
            _expr_program_evaluate_ast(program, args->args[3]),
            _expr_program_evaluate_ast(program, args->args[4]),
            _expr_program_evaluate_ast(program, args->args[5]),
            _expr_program_evaluate_ast(program, args->args[6]),
            _expr_program_evaluate_ast(program, args->args[7]),
            _expr_program_evaluate_ast(program, args->args[8]));
    case 10:
        return ((expr_scalar_t(*)(expr_scalar_t, expr_scalar_t, expr_scalar_t, expr_scalar_t,
                                  expr_scalar_t, expr_scalar_t, expr_scalar_t, expr_scalar_t,
                                  expr_scalar_t, expr_scalar_t))fn)(
            _expr_program_evaluate_ast(program, args->args[0]),
            _expr_program_evaluate_ast(program, args->args[1]),
            _expr_program_evaluate_ast(program, args->args[2]),
            _expr_program_evaluate_ast(program, args->args[3]),
            _expr_program_evaluate_ast(program, args->args[4]),
            _expr_program_evaluate_ast(program, args->args[5]),
            _expr_program_evaluate_ast(program, args->args[6]),
            _expr_program_evaluate_ast(program, args->args[7]),
            _expr_program_evaluate_ast(program, args->args[8]),
            _expr_program_evaluate_ast(program, args->args[9]));
    }
    return NAN;
}

expr_scalar_t _expr_program_evaluate_ast_id(expr_program_t program, expr_ast_t ast) {
    // assert(ast->type == AST_EXPR_ID || ast->type == AST_EXPR_ID_CACHED);

    // Return the value at the cached memory location.
    if (ast->type == AST_EXPR_ID_CACHED) {
        if (ast->args != NULL) {
            return _expr_call_fn(program, ast->lval.pval, ast->args);
        }
        return *ast->lval.pval;
    }

    // Lookup the symbol in the symbols table.
    int arity = 0;
    if (ast->args) {
        arity = ast->args->count;
    }

    expr_sym_t symbol = expr_sym_table_lookup(program->symbols, ast->lval.sval, arity);
    if (symbol == NULL) {
        fprintf(stderr, "could not find symbol: %s/%d\n", ast->lval.sval, arity);
        return NAN;
    }

    // Cache the memory location for faster access.
    ast->lval.pval = symbol->value;
    ast->type = AST_EXPR_ID_CACHED;

    if (ast->args != NULL) {
        return _expr_call_fn(program, ast->lval.pval, ast->args);
    }
    return *ast->lval.pval;
}

expr_scalar_t _expr_program_evaluate_ast(expr_program_t program, expr_ast_t ast) {
    switch (ast->type) {
    case AST_EXPR_NUMBER:
        return ast->lval.dval;
    case AST_EXPR_ID:
    case AST_EXPR_ID_CACHED:
        return _expr_program_evaluate_ast_id(program, ast);
    case AST_EXPR_PLUS:
        return _expr_program_evaluate_ast(program, ast->left) +
               _expr_program_evaluate_ast(program, ast->right);
    case AST_EXPR_MINUS:
        return _expr_program_evaluate_ast(program, ast->left) -
               _expr_program_evaluate_ast(program, ast->right);
    case AST_EXPR_MULT:
        return _expr_program_evaluate_ast(program, ast->left) *
               _expr_program_evaluate_ast(program, ast->right);
    case AST_EXPR_DIV: {
        expr_scalar_t lhs = _expr_program_evaluate_ast(program, ast->left);
        expr_scalar_t rhs = _expr_program_evaluate_ast(program, ast->right);
        if (rhs == 0.0) {
            return NAN;
        }
        return lhs / rhs;
    }
    case AST_EXPR_LT:
        return _expr_program_evaluate_ast(program, ast->left) <
               _expr_program_evaluate_ast(program, ast->right);
    case AST_EXPR_GT:
        return _expr_program_evaluate_ast(program, ast->left) >
               _expr_program_evaluate_ast(program, ast->right);
    case AST_EXPR_AND:
        return (_expr_program_evaluate_ast(program, ast->left) != 0.0) &&
               (_expr_program_evaluate_ast(program, ast->right) != 0.0);
    case AST_EXPR_OR:
        return (_expr_program_evaluate_ast(program, ast->left) != 0.0) ||
               (_expr_program_evaluate_ast(program, ast->right) != 0.0);
    case AST_EXPR_POW:
        return pow(_expr_program_evaluate_ast(program, ast->left),
                   _expr_program_evaluate_ast(program, ast->right));
    case AST_EXPR_UMINUS:
        return -_expr_program_evaluate_ast(program, ast->right);
    case AST_EXPR_NOT:
        return (_expr_program_evaluate_ast(program, ast->right) == 0.0);

    default:
        return 0;
    }
}

expr_scalar_t expr_program_evaluate(expr_program_t program) {
    return _expr_program_evaluate_ast(program, program->ast);
}
