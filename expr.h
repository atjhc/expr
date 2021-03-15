#ifndef EXPR_H
#define EXPR_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(EXPR_SCALAR_USE_FLOAT)
typedef float expr_scalar_t;
#else
typedef double expr_scalar_t;
#endif

typedef struct expr_program_s *expr_program_t;

expr_program_t expr_program_create(const char *code);
void expr_program_destroy(expr_program_t program);

void expr_program_insert_symbol(expr_program_t program, const char *name, int arity,
                                void *location);

expr_scalar_t expr_program_evaluate(expr_program_t program);

#ifdef __cplusplus
}
#endif

#endif // EXPR_H