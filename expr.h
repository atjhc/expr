#ifndef EXPR_H
#define EXPR_H

#ifdef __cplusplus
extern "C" {
#endif

typedef double scalar_t;
typedef struct expr_s *expr_t;

expr_t expr_create(const char *code);
void expr_destroy(expr_t expr);

void expr_insert_symbol(expr_t expr, const char *name, int arity, void *location);

scalar_t expr_evaluate(expr_t expr);

#ifdef __cplusplus
}
#endif

#endif // EXPR_H